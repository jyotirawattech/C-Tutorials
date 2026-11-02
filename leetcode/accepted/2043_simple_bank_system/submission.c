#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    long long* balances;
    int n;
} Bank;

Bank* bankCreate(long long* balance, int balanceSize) {
    Bank* obj = (Bank*)malloc(sizeof(Bank));
    // Since the system passes an existing array, we can just point to it.
    // In a real-world system, you might want to memcpy this to avoid 
    // the caller modifying the array outside the object.
    obj->balances = balance;
    obj->n = balanceSize;
    return obj;
}

// Inline helper for bounds checking
static inline bool isValid(Bank* obj, int account) {
    return account >= 1 && account <= obj->n;
}

bool bankTransfer(Bank* obj, int account1, int account2, long long money) {
    if (!isValid(obj, account1) || !isValid(obj, account2)) {
        return false;
    }
    if (obj->balances[account1 - 1] < money) {
        return false;
    }
    
    obj->balances[account1 - 1] -= money;
    obj->balances[account2 - 1] += money;
    return true;
}

bool bankDeposit(Bank* obj, int account, long long money) {
    if (!isValid(obj, account)) return false;
    
    obj->balances[account - 1] += money;
    return true;
}

bool bankWithdraw(Bank* obj, int account, long long money) {
    if (!isValid(obj, account)) return false;
    if (obj->balances[account - 1] < money) return false;
    
    obj->balances[account - 1] -= money;
    return true;
}

void bankFree(Bank* obj) {
    // If we malloc'd a new array during creation, we would free it here.
    // Since we just copied the pointer, we only free the object struct.
    free(obj);
}