#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 4

void printGrid(int grid[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (grid[i][j] == 0) {
                printf("X\t");
            } else {
                printf("%d\t", grid[i][j]);
            }
        }
        printf("\n\n");
    }
}

void spawnRandomTwo(int grid[SIZE][SIZE]) {
    int emptyCells[SIZE * SIZE][2];
    int count = 0;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (grid[i][j] == 0) {
                emptyCells[count][0] = i;
                emptyCells[count][1] = j;
                count++;
            }
        }
    }

    if (count > 0) {
        int r = rand() % count;
        int row = emptyCells[r][0];
        int col = emptyCells[r][1];
        grid[row][col] = 2;
    }
}

int main() {
    int grid[SIZE][SIZE];
    srand(time(NULL));

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            grid[i][j] = 0;
        }
    }

    spawnRandomTwo(grid);
    spawnRandomTwo(grid);

    printf("\n      --- 2048 ---\n\n");
    printGrid(grid);

    return 0;
}