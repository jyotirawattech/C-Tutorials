#ifndef LEETCODE_ARCHIVE_COMPAT_H
#define LEETCODE_ARCHIVE_COMPAT_H

/* Compile-only LeetCode environment declarations. No archived source is rewritten. */
#include <assert.h>
#include <ctype.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef LC_TREE_NODE
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};
#endif

#ifdef LC_LIST_NODE
struct ListNode {
    int val;
    struct ListNode *next;
};
#endif

#ifdef LC_RANDOM_NODE
/* Problem 138's Node is deliberately separate from other problems' Node types. */
struct Node {
    int val;
    struct Node *next;
    struct Node *random;
};
#endif

#endif
