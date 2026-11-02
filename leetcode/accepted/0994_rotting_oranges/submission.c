typedef struct {
    int r;
    int c;
    int time;
} Node;

int orangesRotting(int** grid, int gridSize, int* gridColSize) {
    int m = gridSize;
    int n = gridColSize[0];

    // 1. HARDWARE EXPLOIT: Fixed-size Stack Queue
    // Since the max grid is 10x10, the queue will NEVER exceed 100 elements.
    // We allocate it on the Call Stack for 0ms latency and zero memory leaks.
    Node q[100];
    int head = 0, tail = 0;

    int fresh_count = 0;
    int max_time = 0;

    // 2. The Multi-Source Initialization
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 2) {
                // Enqueue all rotten oranges at minute 0
                q[tail].r = i;
                q[tail].c = j;
                q[tail].time = 0;
                tail++;
            } else if (grid[i][j] == 1) {
                // Tally the fresh oranges
                fresh_count++;
            }
        }
    }

    // Base Case: If there are no fresh oranges to begin with
    if (fresh_count == 0) return 0;

    // The 4 Cardinal Directions: Up, Down, Left, Right
    int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    // 3. The Breadth-First Search (BFS) Engine
    while (head < tail) {
        // Pop the front of the queue
        Node curr = q[head++];
        max_time = curr.time; // Track the time of the latest rotten orange

        // Explore all 4 adjacent cells
        for (int d = 0; d < 4; d++) {
            int nr = curr.r + dirs[d][0];
            int nc = curr.c + dirs[d][1];

            // Boundary check AND check if it's a fresh orange
            if (nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc] == 1) {
                // IN-PLACE MUTATION: Rot the orange so we don't visit it again
                grid[nr][nc] = 2; 
                fresh_count--;    // Decrement our survival tracker
                
                // Push the newly rotted orange into the queue for the next minute
                q[tail].r = nr;
                q[tail].c = nc;
                q[tail].time = curr.time + 1;
                tail++;
            }
        }
    }

    // 4. The Final Integrity Check
    // If our fresh_count didn't hit 0, some oranges were trapped behind walls
    return fresh_count == 0 ? max_time : -1;
}