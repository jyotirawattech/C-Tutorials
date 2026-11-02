// The Recursive Depth-First Search (DFS) State Machine
void sinkIsland(char** grid, int i, int j, int m, int n) {
    // 1. Boundary and Base Case Checks
    // If we step off the map, OR if we step into water ('0'), we stop exploring.
    if (i < 0 || i >= m || j < 0 || j >= n || grid[i][j] == '0') {
        return;
    }

    // 2. The Mutative Exploit
    // "Sink" the current piece of land so we never visit it again.
    // This entirely eliminates the need for an O(M * N) visited matrix!
    grid[i][j] = '0';

    // 3. The Call Stack Expansion
    // Recursively explore all four cardinal directions to sink the entire connected landmass.
    sinkIsland(grid, i - 1, j, m, n); // Up
    sinkIsland(grid, i + 1, j, m, n); // Down
    sinkIsland(grid, i, j - 1, m, n); // Left
    sinkIsland(grid, i, j + 1, m, n); // Right
}

int numIslands(char** grid, int gridSize, int* gridColSize) {
    // Hardware safety check
    if (gridSize == 0) return 0;

    int m = gridSize;
    int n = gridColSize[0];
    int island_count = 0;

    // Linear sweep of the 2D memory block
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            
            // We have discovered an unmapped piece of land!
            if (grid[i][j] == '1') {
                island_count++;
                
                // Immediately deploy the recursive DFS to sink the entire island
                sinkIsland(grid, i, j, m, n);
            }
        }
    }

    return island_count;
}