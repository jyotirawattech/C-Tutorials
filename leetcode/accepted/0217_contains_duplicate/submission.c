int compare (const void * a, const void * b) {
  return ( *(int*)a - *(int*)b );
}
bool containsDuplicate(int* arr, int n){
    if (0 == n)
        return false;
    qsort(arr, n, sizeof(int), compare);
    for(int i = 0; i < n-1; i++) {
        if(arr[i] == arr[i+1])
            return true;
    }
    return false;
}