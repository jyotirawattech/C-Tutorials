#include <stdlib.h>

/* * Definition for a binary tree node.
 * struct TreeNode {
 * int val;
 * struct TreeNode *left;
 * struct TreeNode *right;
 * };
 */

// The Recursive Call Stack Builder
struct TreeNode* build(int* postorder, int* post_idx, int in_left, int in_right, int* in_map) {
    // Base Case: If the left boundary crosses the right, this subtree is empty
    if (in_left > in_right) {
        return NULL;
    }

    // 1. Identify the root (The last element in the current postorder sequence)
    int root_val = postorder[*post_idx];
    (*post_idx)--; // Consume the value by moving the pointer backward
    
    // 2. Allocate the node on the Heap
    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = root_val;
    root->left = NULL;
    root->right = NULL;

    // 3. Find the topological split index instantly in O(1) time
    int in_idx = in_map[root_val + 3000];

    // 4. The Call Stack Framing
    // CRITICAL: Because we are reading Postorder backward (Root -> Right -> Left),
    // we MUST recursively build the right subtree before the left subtree!
    root->right = build(postorder, post_idx, in_idx + 1, in_right, in_map);
    root->left  = build(postorder, post_idx, in_left, in_idx - 1, in_map);

    return root;
}

struct TreeNode* buildTree(int* inorder, int inorderSize, int* postorder, int postorderSize) {
    // HARDWARE EXPLOIT: Values are bounded between -3000 and 3000.
    // We allocate a flat 6001-element array to act as a perfect, collision-free Hash Map.
    int in_map[6001] = {0};
    
    // Pre-compute the index of every value in O(N) time
    for (int i = 0; i < inorderSize; i++) {
        in_map[inorder[i] + 3000] = i;
    }

    // We track our current position in the postorder array globally via pointer
    int post_idx = postorderSize - 1;
    
    // Fire off the recursive builder
    return build(postorder, &post_idx, 0, inorderSize - 1, in_map);
}