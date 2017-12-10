/* GAME OF LIFE COMMAND LINE EDITION
 * Will Sumner
 * University of Pittsburgh
 * Oct 15, 2016
 */
#include <stdio.h>      // Standard Input/Ouput
#include <stdlib.h>     // Standard C Library
#include <unistd.h>     // Delay
#include <time.h>       // Randomizing numbers
#define WIDTH  29 // for 89x49, use 26 and 24 for standard terminal window
#define HEIGHT 48 // these are the height and width in CELLS, not spaces
#define DELAY  70000
#define CHAR1  "[*]"
#define CHAR2  "[ ]"
// RAND_MAX usually 32767
// COLORED CONSOLE OUPUT!!
#define ANSI_BLACK   "\x1b[30m" // black with white background [30;47m
#define ANSI_RED     "\x1b[31m"
#define ANSI_GREEN   "\x1b[32m"
#define ANSI_YELLOW  "\x1b[33m"
#define ANSI_BLUE    "\x1b[34m"
#define ANSI_MAGENTA "\x1b[35m"
#define ANSI_CYAN    "\x1b[36m"
#define ANSI_WHITE   "\x1b[37m"
#define ANSI_RESET   "\x1b[0m"

void insertPattern(int x, int y, int h, int w, int* pattern, int length, int grid[HEIGHT][WIDTH][2], int s) { // inserts a pattern of a given type with top left coordinate
    if (h*w != length)
        printf(ANSI_RED "ERROR MALFORMED INSERT PATTERN: DIMENSION MISMATCH" ANSI_RESET);
    for (int i = 0; i < h; i++) {
        if (i+h < 1000) {
            for (int j = 0; j < w;j++) {
                if (j+w < 1000) {
                    grid[x+i][y+j][s] = pattern[i*w+j];
                }

            }
        }
    }
}

void startGrid(int grid[HEIGHT][WIDTH][2],int s) {
    int x = 0;
    for (int i= 0; i < HEIGHT;i++){
       for (int j=0;j < WIDTH; j++){
        x = rand();
        if (x%2 == 0) { grid[i][j][s] = 0; }
        else { grid[i][j][s] = 1; }
        }
    }
}

int interact(int grid[HEIGHT][WIDTH][2], int i,int j,int s){
    int num = 0;
    for (int x = -1; x < 2; x++) {
        for (int y = -1; y < 2; y++) {
            if (x+i < 0 || x+i >= HEIGHT || y+j < 0 || y+j >= WIDTH ||(x==0 && y==0)) { continue; }
            else { num += grid[x+i][y+j][s]; }
        }
    }
    if (num < 2 || num > 3){return 0;}
    if (num == 3 && grid[i][j][s]==0){return 1;}
    if ((num ==3 || num == 2) && grid[i][j][s]==1){return 1;}
    return 0;
}

void updateGrid(int grid[HEIGHT][WIDTH][2],int s) {
    int newLife = 1; // if there should be life added
    int didChange = 0;
    for (int i=0; i < HEIGHT; i++) {
        for (int j=0; j < WIDTH; j++) {
            int oldValue = grid[i][j][!(s)];

            grid[i][j][!(s)] = interact(grid,i,j,s);
            if (oldValue != grid[i][j][!(s)]) {
                didChange = 1;
            }
        }
    }

    if (didChange==0 && newLife == 1) { // lowest chance 32719
        int x = rand()%WIDTH;
        int y = rand()%HEIGHT;
        int patt[24] = { 1,1,1,1,  // interesting 1,1,1,1 \n 0,1,1,1
                         0,1,1,1};
        insertPattern(x,y,2,4,patt,8,grid,!(s));
        newLife = 0;
    }

}

void showGrid(int grid[HEIGHT][WIDTH][2],int s) {
    for (int i=0; i < HEIGHT;i++) {
        for (int j=0; j < WIDTH;j++) {
            if (grid[i][j][s]==1){printf(ANSI_GREEN CHAR1 ANSI_RESET);}
            else {printf(ANSI_BLACK CHAR2 ANSI_RESET);}
        }
        printf("\n");
    }
}

int main() {
    srand(time(NULL));
    int g;
    int grid[HEIGHT][WIDTH][2] ={0};
    int sw = 0;
    startGrid(grid,sw);
    showGrid(grid,sw);

    printf("Generations: ");
    scanf("%d", &g);
    if (g > 0 && g <= 3000) {
        for (int gg = 0; gg < g; gg++) {
            updateGrid(grid,sw);
            system("clear");
            showGrid(grid,sw);
            sw = !(sw);
            usleep(DELAY);
        }
    }
    showGrid(grid,sw);
    return 0;
}
