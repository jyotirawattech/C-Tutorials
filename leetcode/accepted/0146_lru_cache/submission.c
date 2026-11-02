#include <stdio.h>
#include <stdlib.h>

// Define the Node struct
typedef struct Node {
    int key;
    int val;
    struct Node* prev;
    struct Node* next;
} Node;

// Define the Cache struct (Simulating our "Object")
typedef struct {
    int capacity;
    int size;
    Node* hash[10005]; // Direct access table since keys are up to 10^4
    Node* head;
    Node* tail;
} LRUCache;

// Helper to remove a node
void removeNode(Node* node) {
    Node* prevNode = node->prev;
    Node* nextNode = node->next;
    prevNode->next = nextNode;
    nextNode->prev = prevNode;
}

// Helper to insert a node at the MRU position
void insertNode(LRUCache* obj, Node* node) {
    Node* prevNode = obj->tail->prev;
    Node* nextNode = obj->tail;
    
    prevNode->next = node;
    nextNode->prev = node;
    node->prev = prevNode;
    node->next = nextNode;
}

// "Constructor"
// "Constructor"
LRUCache* lRUCacheCreate(int capacity) {
    LRUCache* obj = (LRUCache*)malloc(sizeof(LRUCache));
    obj->capacity = capacity;
    obj->size = 0;
    
    // Initialize the hash map to NULL
    for (int i = 0; i < 10005; i++) {
        obj->hash[i] = NULL;
    }
    
    // THE FIX: Use calloc to automatically zero out the memory,
    // which safely sets pointers to NULL and integers to 0.
    obj->head = (Node*)calloc(1, sizeof(Node));
    obj->tail = (Node*)calloc(1, sizeof(Node));
    
    // Connect the dummy nodes
    obj->head->next = obj->tail;
    obj->tail->prev = obj->head;
    
    return obj;
}

int lRUCacheGet(LRUCache* obj, int key) {
    if (obj->hash[key] != NULL) {
        Node* node = obj->hash[key];
        removeNode(node);
        insertNode(obj, node);
        return node->val;
    }
    return -1;
}

void lRUCachePut(LRUCache* obj, int key, int value) {
    if (obj->hash[key] != NULL) {
        Node* existingNode = obj->hash[key];
        removeNode(existingNode);
        existingNode->val = value; // Update value
        insertNode(obj, existingNode);
        return;
    }
    
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->val = value;
    
    obj->hash[key] = newNode;
    insertNode(obj, newNode);
    obj->size++;
    
    if (obj->size > obj->capacity) {
        Node* lru = obj->head->next;
        removeNode(lru);
        obj->hash[lru->key] = NULL;
        free(lru); // Strict manual memory management
        obj->size--;
    }
}

// Destructor-like function
void lRUCacheFree(LRUCache* obj) {
    Node* curr = obj->head;
    while (curr != NULL) {
        Node* next = curr->next;
        free(curr);
        curr = next;
    }
    free(obj);
}