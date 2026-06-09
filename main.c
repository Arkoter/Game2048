#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#ifdef _WIN32
#include <windows.h>
#endif

#define SIZE 4

int score = 0;


#define COLOR_RESET "\033[0m"
#define BORDER_COLOR "\033[38;5;240m"

void printColor(int value) {
    if (value == 0) {
        printf(COLOR_RESET);
        return;
    }
    

    switch (value) {
        case 2:    printf("\033[38;5;228m\033[1m"); break;
        case 4:    printf("\033[38;5;221m\033[1m"); break;
        case 8:    printf("\033[38;5;214m\033[1m"); break;
        case 16:   printf("\033[38;5;208m\033[1m"); break;
        case 32:   printf("\033[38;5;203m\033[1m"); break;
        case 64:   printf("\033[38;5;196m\033[1m"); break;
        case 128:  printf("\033[38;5;226m\033[1m"); break;
        case 256:  printf("\033[38;5;227m\033[1m"); break; 
        case 512:  printf("\033[38;5;228m\033[1m"); break;
        case 1024: printf("\033[38;5;229m\033[1m"); break;
        case 2048: printf("\033[38;5;230m\033[1m"); break;
        default:   printf("\033[38;5;231m\033[1m"); break;
    }
}

void printGrid(int grid[SIZE][SIZE]) {
    printf("\033[2J\033[H");

    printf(COLOR_RESET "\n");
    printf("      \033[38;5;214m======================\n");
    printf("      |      \033[1m2 0 4 8       \033[0m\033[38;5;214m|\n");
    printf("      ======================\n\n" COLOR_RESET);

    printf("    " BORDER_COLOR "+------+------+------+------+\n");
    for (int i = 0; i < SIZE; i++) {
        printf("    |");
        for (int j = 0; j < SIZE; j++) {
            if (grid[i][j] == 0) {
                printf("      " BORDER_COLOR "|");
            } else {
                int val = grid[i][j];
                printColor(val);
                if (val < 10) {
                    printf("  %d   ", val);
                } else if (val < 100) {
                    printf("  %d  ", val);
                } else if (val < 1000) {
                    printf(" %d  ", val);
                } else {
                    printf(" %d ", val);
                }
                printf(BORDER_COLOR "|");
            }
        }
        printf("\n    +------+------+------+------+\n");
    }
    printf("\n      \033[38;5;214mSCORE: \033[1m%d\033[0m\n\n", score);
    printf(COLOR_RESET);
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

void slideLeft(int grid[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        int temp[SIZE] = {0};
        int pos = 0;
        for (int j = 0; j < SIZE; j++) {
            if (grid[i][j] != 0) {
                temp[pos++] = grid[i][j];
            }
        }
        for (int j = 0; j < SIZE; j++) {
            grid[i][j] = temp[j];
        }

        for (int j = 0; j < SIZE - 1; j++) {
            if (grid[i][j] != 0 && grid[i][j] == grid[i][j + 1]) {
                grid[i][j] *= 2;
                score += grid[i][j];
                grid[i][j + 1] = 0;
            }
        }

        int temp2[SIZE] = {0};
        pos = 0;
        for (int j = 0; j < SIZE; j++) {
            if (grid[i][j] != 0) {
                temp2[pos++] = grid[i][j];
            }
        }
        for (int j = 0; j < SIZE; j++) {
            grid[i][j] = temp2[j];
        }
    }
}

void slideRight(int grid[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        int temp[SIZE] = {0};
        int pos = SIZE - 1;
        for (int j = SIZE - 1; j >= 0; j--) {
            if (grid[i][j] != 0) {
                temp[pos--] = grid[i][j];
            }
        }
        for (int j = 0; j < SIZE; j++) {
            grid[i][j] = temp[j];
        }

        for (int j = SIZE - 1; j > 0; j--) {
            if (grid[i][j] != 0 && grid[i][j] == grid[i][j - 1]) {
                grid[i][j] *= 2;
                score += grid[i][j];
                grid[i][j - 1] = 0;
            }
        }

        int temp2[SIZE] = {0};
        pos = SIZE - 1;
        for (int j = SIZE - 1; j >= 0; j--) {
            if (grid[i][j] != 0) {
                temp2[pos--] = grid[i][j];
            }
        }
        for (int j = 0; j < SIZE; j++) {
            grid[i][j] = temp2[j];
        }
    }
}

void slideUp(int grid[SIZE][SIZE]) {
    for (int j = 0; j < SIZE; j++) {
        int temp[SIZE] = {0};
        int pos = 0;
        for (int i = 0; i < SIZE; i++) {
            if (grid[i][j] != 0) {
                temp[pos++] = grid[i][j];
            }
        }
        for (int i = 0; i < SIZE; i++) {
            grid[i][j] = temp[i];
        }

        for (int i = 0; i < SIZE - 1; i++) {
            if (grid[i][j] != 0 && grid[i][j] == grid[i + 1][j]) {
                grid[i][j] *= 2;
                score += grid[i][j];
                grid[i + 1][j] = 0;
            }
        }

        int temp2[SIZE] = {0};
        pos = 0;
        for (int i = 0; i < SIZE; i++) {
            if (grid[i][j] != 0) {
                temp2[pos++] = grid[i][j];
            }
        }
        for (int i = 0; i < SIZE; i++) {
            grid[i][j] = temp2[i];
        }
    }
}

void slideDown(int grid[SIZE][SIZE]) {
    for (int j = 0; j < SIZE; j++) {
        int temp[SIZE] = {0};
        int pos = SIZE - 1;
        for (int i = SIZE - 1; i >= 0; i--) {
            if (grid[i][j] != 0) {
                temp[pos--] = grid[i][j];
            }
        }
        for (int i = 0; i < SIZE; i++) {
            grid[i][j] = temp[i];
        }

        for (int i = SIZE - 1; i > 0; i--) {
            if (grid[i][j] != 0 && grid[i][j] == grid[i - 1][j]) {
                grid[i][j] *= 2;
                score += grid[i][j];
                grid[i - 1][j] = 0;
            }
        }

        int temp2[SIZE] = {0};
        pos = SIZE - 1;
        for (int i = SIZE - 1; i >= 0; i--) {
            if (grid[i][j] != 0) {
                temp2[pos--] = grid[i][j];
            }
        }
        for (int i = 0; i < SIZE; i++) {
            grid[i][j] = temp2[i];
        }
    }
}

#ifdef _WIN32
void enableVirtualTerminal() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return;
    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) return;
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}
#endif

int main() {
#ifdef _WIN32
    enableVirtualTerminal();
#endif

    int grid[SIZE][SIZE];
    srand(time(NULL));

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            grid[i][j] = 0;
        }
    }

    spawnRandomTwo(grid);
    spawnRandomTwo(grid);

    while (1) {
        printGrid(grid);
        
        int key = _getch();
        if (key == 224) {
            key = _getch();
            switch (key) {
                case 72: slideUp(grid); break;
                case 80: slideDown(grid); break;
                case 75: slideLeft(grid); break;
                case 77: slideRight(grid); break;
            }
        } else if (key == 'q' || key == 'Q') {
            break;
        }
    }

    return 0;
}