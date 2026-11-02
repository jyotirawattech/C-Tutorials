int timeRequiredToBuy(int* tickets, int ticketsSize, int k) {
    int total_time = 0;
    int target = tickets[k];
    
    for (int i = 0; i < ticketsSize; i++) {
        // C ternary operators for blistering fast ALU bounds checking
        if (i <= k) {
            total_time += (tickets[i] < target) ? tickets[i] : target;
        } else {
            total_time += (tickets[i] < target - 1) ? tickets[i] : target - 1;
        }
    }
    
    return total_time;
}