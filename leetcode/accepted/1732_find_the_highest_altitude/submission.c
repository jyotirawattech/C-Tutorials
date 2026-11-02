int largestAltitude(int* gain, int gainSize) {
    int current_alt = 0;
    int max_alt = 0; // Starts at 0, per the constraints
    
    for (int i = 0; i < gainSize; i++) {
        // Accumulate the delta
        current_alt += gain[i];
        
        // Push the maximum watermark upward if necessary
        if (current_alt > max_alt) {
            max_alt = current_alt;
        }
    }
    
    return max_alt;
}