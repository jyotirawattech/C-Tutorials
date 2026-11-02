#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODES 400000 // Memory Pool Size

typedef struct {
    int left_child;
    int right_child;
    bool tracked;
    bool lazy;     // Flag indicating pending updates
    bool lazy_val; // The value to propagate (true for Add, false for Remove)
} SegNode;

typedef struct {
    SegNode* tree;
    int node_count;
} RangeModule;

RangeModule* rangeModuleCreate() {
    RangeModule* obj = (RangeModule*)malloc(sizeof(RangeModule));
    // Pre-allocate memory pool for Dynamic Segment Tree
    obj->tree = (SegNode*)calloc(MAX_NODES, sizeof(SegNode));
    obj->node_count = 2; // Index 0 is null, Index 1 is the Root
    return obj;
}

// Push lazy updates down to children
void pushDown(RangeModule* obj, int idx) {
    if (!obj->tree[idx].lazy) return;
    
    // Dynamically create children if they don't exist
    if (!obj->tree[idx].left_child) obj->tree[idx].left_child = obj->node_count++;
    if (!obj->tree[idx].right_child) obj->tree[idx].right_child = obj->node_count++;
    
    int l = obj->tree[idx].left_child;
    int r = obj->tree[idx].right_child;
    bool val = obj->tree[idx].lazy_val;
    
    obj->tree[l].tracked = val;
    obj->tree[l].lazy = true;
    obj->tree[l].lazy_val = val;
    
    obj->tree[r].tracked = val;
    obj->tree[r].lazy = true;
    obj->tree[r].lazy_val = val;
    
    obj->tree[idx].lazy = false;
}

// Update Range
void update(RangeModule* obj, int idx, int l, int r, int ql, int qr, bool val) {
    if (ql <= l && r <= qr) {
        obj->tree[idx].tracked = val;
        obj->tree[idx].lazy = true;
        obj->tree[idx].lazy_val = val;
        return;
    }
    
    pushDown(obj, idx);
    int mid = l + (r - l) / 2;
    
    if (!obj->tree[idx].left_child) obj->tree[idx].left_child = obj->node_count++;
    if (!obj->tree[idx].right_child) obj->tree[idx].right_child = obj->node_count++;
    
    if (ql <= mid) update(obj, obj->tree[idx].left_child, l, mid, ql, qr, val);
    if (qr > mid) update(obj, obj->tree[idx].right_child, mid + 1, r, ql, qr, val);
    
    obj->tree[idx].tracked = obj->tree[obj->tree[idx].left_child].tracked && 
                             obj->tree[obj->tree[idx].right_child].tracked;
}

bool query(RangeModule* obj, int idx, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return obj->tree[idx].tracked;
    
    pushDown(obj, idx);
    int mid = l + (r - l) / 2;
    bool res = true;
    
    if (ql <= mid) {
        if (!obj->tree[idx].left_child) return false; // Not tracked
        res = res && query(obj, obj->tree[idx].left_child, l, mid, ql, qr);
    }
    if (qr > mid) {
        if (!obj->tree[idx].right_child) return false;
        res = res && query(obj, obj->tree[idx].right_child, mid + 1, r, ql, qr);
    }
    return res;
}

void rangeModuleAddRange(RangeModule* obj, int left, int right) {
    update(obj, 1, 1, 1e9, left, right - 1, true);
}

bool rangeModuleQueryRange(RangeModule* obj, int left, int right) {
    return query(obj, 1, 1, 1e9, left, right - 1);
}

void rangeModuleRemoveRange(RangeModule* obj, int left, int right) {
    update(obj, 1, 1, 1e9, left, right - 1, false);
}

void rangeModuleFree(RangeModule* obj) {
    free(obj->tree);
    free(obj);
}