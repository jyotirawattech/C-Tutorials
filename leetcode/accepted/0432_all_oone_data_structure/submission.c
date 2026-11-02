#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 100003

typedef struct Bucket Bucket;
typedef struct HashNode HashNode;

// The Node representing a specific string
struct HashNode {
    char key[12];
    Bucket* bucket;         // Pointer to its current frequency bucket
    HashNode* hash_next;    // Pointer for the Hash Map collision chain
    HashNode* b_prev;       // Pointer for the Bucket's internal DLL
    HashNode* b_next;       // Pointer for the Bucket's internal DLL
};

// The Node representing a Frequency
struct Bucket {
    int count;
    HashNode* keys_head;    // Head of the internal string DLL
    Bucket* prev;
    Bucket* next;
};

typedef struct {
    HashNode** table;
    Bucket* head;
    Bucket* tail;
} AllOne;

// Simple string hash function
unsigned int hash(const char* str) {
    unsigned int hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % HASH_SIZE;
}

// Find a string in the Hash Map
HashNode* get_node(AllOne* obj, const char* key) {
    unsigned int h = hash(key);
    HashNode* curr = obj->table[h];
    while (curr) {
        if (strcmp(curr->key, key) == 0) return curr;
        curr = curr->hash_next;
    }
    return NULL;
}

AllOne* allOneCreate() {
    AllOne* obj = (AllOne*)malloc(sizeof(AllOne));
    obj->table = (HashNode**)calloc(HASH_SIZE, sizeof(HashNode*));
    
    // Setup Dummy Nodes
    obj->head = (Bucket*)malloc(sizeof(Bucket));
    obj->tail = (Bucket*)malloc(sizeof(Bucket));
    obj->head->count = 0;
    obj->tail->count = 0;
    obj->head->keys_head = NULL;
    obj->tail->keys_head = NULL;
    
    obj->head->next = obj->tail;
    obj->head->prev = NULL;
    obj->tail->prev = obj->head;
    obj->tail->next = NULL;
    
    return obj;
}

// Helper to remove a HashNode from its Bucket's internal DLL
void remove_from_bucket(HashNode* node) {
    Bucket* b = node->bucket;
    if (node->b_prev) node->b_prev->b_next = node->b_next;
    else b->keys_head = node->b_next; // It was the head
    
    if (node->b_next) node->b_next->b_prev = node->b_prev;
    
    node->b_prev = NULL;
    node->b_next = NULL;
}

// Helper to add a HashNode to a Bucket's internal DLL
void add_to_bucket(Bucket* b, HashNode* node) {
    node->bucket = b;
    node->b_next = b->keys_head;
    if (b->keys_head) b->keys_head->b_prev = node;
    b->keys_head = node;
    node->b_prev = NULL;
}

// Helper to create and insert a new Bucket
Bucket* insert_bucket_after(Bucket* prev_b, int count) {
    Bucket* new_b = (Bucket*)malloc(sizeof(Bucket));
    new_b->count = count;
    new_b->keys_head = NULL;
    
    new_b->prev = prev_b;
    new_b->next = prev_b->next;
    prev_b->next->prev = new_b;
    prev_b->next = new_b;
    
    return new_b;
}

void allOneInc(AllOne* obj, char * key) {
    HashNode* node = get_node(obj, key);
    
    if (!node) {
        // Create new HashNode
        node = (HashNode*)malloc(sizeof(HashNode));
        strcpy(node->key, key);
        node->b_prev = NULL; node->b_next = NULL;
        
        // Add to Hash Map
        unsigned int h = hash(key);
        node->hash_next = obj->table[h];
        obj->table[h] = node;
        
        // Ensure count=1 bucket exists
        if (obj->head->next->count != 1) {
            insert_bucket_after(obj->head, 1);
        }
        add_to_bucket(obj->head->next, node);
        return;
    }
    
    // Node exists, move it to count + 1 bucket
    Bucket* curr_b = node->bucket;
    Bucket* next_b = curr_b->next;
    
    if (next_b == obj->tail || next_b->count != curr_b->count + 1) {
        next_b = insert_bucket_after(curr_b, curr_b->count + 1);
    }
    
    remove_from_bucket(node);
    add_to_bucket(next_b, node);
    
    // Clean up empty bucket
    if (!curr_b->keys_head) {
        curr_b->prev->next = curr_b->next;
        curr_b->next->prev = curr_b->prev;
        free(curr_b);
    }
}

void allOneDec(AllOne* obj, char * key) {
    HashNode* node = get_node(obj, key);
    if (!node) return;
    
    Bucket* curr_b = node->bucket;
    remove_from_bucket(node);
    
    if (curr_b->count == 1) {
        // Delete entirely from Hash Map
        unsigned int h = hash(key);
        HashNode* curr = obj->table[h];
        HashNode* prev = NULL;
        while (curr != node) {
            prev = curr;
            curr = curr->hash_next;
        }
        if (prev) prev->hash_next = curr->hash_next;
        else obj->table[h] = curr->hash_next;
        
        free(node);
    } else {
        Bucket* prev_b = curr_b->prev;
        if (prev_b == obj->head || prev_b->count != curr_b->count - 1) {
            prev_b = insert_bucket_after(curr_b->prev, curr_b->count - 1);
        }
        add_to_bucket(prev_b, node);
    }
    
    // Clean up empty bucket
    if (!curr_b->keys_head) {
        curr_b->prev->next = curr_b->next;
        curr_b->next->prev = curr_b->prev;
        free(curr_b);
    }
}

char * allOneGetMaxKey(AllOne* obj) {
    if (obj->head->next == obj->tail) return "";
    return obj->tail->prev->keys_head->key;
}

char * allOneGetMinKey(AllOne* obj) {
    if (obj->head->next == obj->tail) return "";
    return obj->head->next->keys_head->key;
}

void allOneFree(AllOne* obj) {
    // Memory cleanup logic goes here
    free(obj->head);
    free(obj->tail);
    free(obj->table);
    free(obj);
}