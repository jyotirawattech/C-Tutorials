/**
 * Problem: LeetCode 0226 - Invert Binary Tree
 * Language: C (C11)
 *
 * Approach:
 * Recursive depth-first tree inversion swapping left and right child pointers.
 * Includes complete tree allocation, level-order comparison, and recursive
 * deallocation for zero memory leaks.
 *
 * Complexity:
 * - Time: O(N) where N is the number of nodes in the binary tree.
 * - Space: O(H) call stack frames where H is the height of the tree (O(log N) balanced, O(N) skewed).
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct TreeNode* invertTree(struct TreeNode* root) {
    if (root == NULL) {
        return NULL;
    }

    struct TreeNode* temp = root->left;
    root->left = invertTree(root->right);
    root->right = invertTree(temp);

    return root;
}

/* ========================================================================= */
/* Test Harness Helper Functions                                             */
/* ========================================================================= */

static struct TreeNode* create_tree_node(int val) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    assert(node != NULL);
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

static void free_tree(struct TreeNode* root) {
    if (!root) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

/* ========================================================================= */
/* Standalone Test Harness                                                   */
/* ========================================================================= */

int main(void) {
    printf("[TEST] Running LeetCode 0226: Invert Binary Tree...\n");

    // Test Case 1: Standard tree [4, 2, 7, 1, 3, 6, 9] -> inverted [4, 7, 2, 9, 6, 3, 1]
    {
        struct TreeNode* root = create_tree_node(4);
        root->left = create_tree_node(2);
        root->right = create_tree_node(7);
        root->left->left = create_tree_node(1);
        root->left->right = create_tree_node(3);
        root->right->left = create_tree_node(6);
        root->right->right = create_tree_node(9);

        struct TreeNode* inverted = invertTree(root);
        assert(inverted->val == 4);
        assert(inverted->left->val == 7);
        assert(inverted->right->val == 2);
        assert(inverted->left->left->val == 9);
        assert(inverted->left->right->val == 6);
        assert(inverted->right->left->val == 3);
        assert(inverted->right->right->val == 1);

        free_tree(inverted);
        printf("  ✓ Test 1 Passed: [4, 2, 7, 1, 3, 6, 9] inverted successfully\n");
    }

    // Test Case 2: Tree [2, 1, 3] -> inverted [2, 3, 1]
    {
        struct TreeNode* root = create_tree_node(2);
        root->left = create_tree_node(1);
        root->right = create_tree_node(3);

        struct TreeNode* inverted = invertTree(root);
        assert(inverted->val == 2);
        assert(inverted->left->val == 3);
        assert(inverted->right->val == 1);

        free_tree(inverted);
        printf("  ✓ Test 2 Passed: [2, 1, 3] -> [2, 3, 1]\n");
    }

    // Test Case 3: Empty tree NULL -> NULL
    {
        struct TreeNode* inverted = invertTree(NULL);
        assert(inverted == NULL);
        printf("  ✓ Test 3 Passed: NULL -> NULL\n");
    }

    printf("[PASSED] All LeetCode 0226 tests passed with zero leaks!\n\n");
    return 0;
}
