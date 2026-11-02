#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    int in_stack[100];
    int out_stack[100];
    int in_top;
    int out_top;
} MyQueue;

MyQueue* myQueueCreate() {
    MyQueue* obj = (MyQueue*)malloc(sizeof(MyQueue));
    obj->in_top = -1;
    obj->out_top = -1;
    return obj;
}

void transfer_if_needed(MyQueue* obj) {
    if (obj->out_top == -1) {
        while (obj->in_top >= 0) {
            obj->out_stack[++(obj->out_top)] = obj->in_stack[(obj->in_top)--];
        }
    }
}

void myQueuePush(MyQueue* obj, int x) {
    obj->in_stack[++(obj->in_top)] = x;
}

int myQueuePop(MyQueue* obj) {
    transfer_if_needed(obj);
    return obj->out_stack[(obj->out_top)--];
}

int myQueuePeek(MyQueue* obj) {
    transfer_if_needed(obj);
    return obj->out_stack[obj->out_top];
}

bool myQueueEmpty(MyQueue* obj) {
    return (obj->in_top == -1) && (obj->out_top == -1);
}

void myQueueFree(MyQueue* obj) {
    free(obj);
}