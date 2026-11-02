#include <stdlib.h>

typedef struct {
    int r1, c1, r2, c2, val;
} Update;

typedef struct {
    int** matrix;
    int rows, cols;
    Update* history;
    int history_size;
} SubrectangleQueries;

SubrectangleQueries* subrectangleQueriesCreate(int** rectangle, int rectangleSize, int* rectangleColSize) {
    SubrectangleQueries* obj = (SubrectangleQueries*)malloc(sizeof(SubrectangleQueries));
    obj->rows = rectangleSize;
    obj->cols = rectangleColSize[0];
    obj->matrix = rectangle;
    obj->history = (Update*)malloc(500 * sizeof(Update)); // Pre-allocated based on constraints
    obj->history_size = 0;
    return obj;
}

void subrectangleQueriesUpdateSubrectangle(SubrectangleQueries* obj, int r1, int c1, int r2, int c2, int newValue) {
    obj->history[obj->history_size++] = (Update){r1, c1, r2, c2, newValue};
}

int subrectangleQueriesGetValue(SubrectangleQueries* obj, int row, int col) {
    for (int i = obj->history_size - 1; i >= 0; i--) {
        Update u = obj->history[i];
        if (row >= u.r1 && row <= u.r2 && col >= u.c1 && col <= u.c2) {
            return u.val;
        }
    }
    return obj->matrix[row][col];
}

void subrectangleQueriesFree(SubrectangleQueries* obj) {
    free(obj->history);
    free(obj);
}