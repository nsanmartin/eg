#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
// Pieces definition
#define NUM_OF_PIECES 7
#define PIECE_SIZE 5
char Pieces [7 /*kind */ ][PIECE_SIZE /* horizontal blocks */ ][PIECE_SIZE /* vertical blocks */ ] =
{
// Square
    {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 2, 1, 0},
        {0, 0, 1, 1, 0},
        {0, 0, 0, 0, 0}
    },
// I
    {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 1, 2, 1, 1},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    },
// L
    {
        {0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 2, 0, 0},
        {0, 0, 1, 1, 0},
        {0, 0, 0, 0, 0}
    },
// L mirrored
    {
        {0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 2, 0, 0},
        {0, 1, 1, 0, 0},
        {0, 0, 0, 0, 0}
    },
// N
    {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0},
        {0, 0, 2, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}
    },
// N mirrored
   {
    {0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 2, 1, 0},
    {0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0}
   },
// T
   {
    {0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 2, 1, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0}
   }
};


struct vector {
    int x, y;
    void rotate(int rot);
};

int rotation_sin[] = {0, 1, 0, -1};
int rotation_cos[] = {1, 0, -1, 0};

void vector::rotate(int rot) {
    int x2 = x - 2;
    int y2 = y - 2;
    int cos = rotation_cos[rot];
    int sin = rotation_sin[rot];
    x = x2*cos - y2*sin + 2;
    y = x2*sin + y2*cos + 2;
    
    // angulos: pi/2, pi, 3pi/2
    return;
}


void print_piece(char  pc[][5]) {
    //std::cout << "12345" << std:: endl;
    for (int i = 0; i < PIECE_SIZE; i++) {
        for (int j = 0; j < PIECE_SIZE; j++) {
            std::cout << (pc[i][j] ? "*" : " " ) << " ";
        }
        std::cout << std::endl;
    }
}

void print_piece_rotation(int n, int r) {
    for (int i = 0; i < PIECE_SIZE; i++) {
        for (int j = 0; j < PIECE_SIZE; j++) {
            vector v = {.x = i, .y=j};
            v.rotate(r);
            std::cout << (Pieces[n][v.x][v.y] ? "*" : " " ) << " ";
        }
        std::cout << std::endl;
    }
}


#define TIMES 3
void random_piece(char piece[][5]) {
    for (int i = 0; i < PIECE_SIZE; i++)
        for (int j = 0; j < PIECE_SIZE; j++)
            piece[i][j] = 0;
    vector puntos[2] = {{2,2},{2,2}};
    piece[2][2] = 1;
    int idx;
    int sign;
    for (int i = 0; i < TIMES; i++ ) {
        idx = rand() % 2;
        sign = rand() % 2 ? -1 : 1;
        bool test = rand() % 2 == 0;

        if (test) {
            if ((int)piece[puntos[idx].x + sign][puntos[idx].y] == 0) {
                puntos[idx].x += sign;
                piece[puntos[idx].x][puntos[idx].y] = 1;
            } else if ((int)piece[puntos[idx].x - sign][puntos[idx].y] == 0) {
                puntos[idx].x -= sign;
                piece[puntos[idx].x][puntos[idx].y] = 1;
            } else {
                test = false;
            }
        }
        if (!test) {
            if ((int)piece[puntos[idx].x][puntos[idx].y + sign] == 0) {
                puntos[idx].y += sign;
                piece[puntos[idx].x][puntos[idx].y] = 1;
            } else if ((int)piece[puntos[idx].x][puntos[idx].y - sign] == 0) {
                puntos[idx].y -= sign;
                piece[puntos[idx].x][puntos[idx].y] = 1;
            } else {
                print_piece(piece);

                assert(false);
            }
        }
    }
        
    return;
}
char vacia[][5] =  {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
};

int main () {
    srand(time(NULL));
    // for (int i = 0; i < NUM_OF_PIECES; i++)
    //     for (int j = 0; j < 4; j++) {
    //         std::cout << "12345" << std::endl;
    //         print_piece_rotation(i, j);
    //         std::cout << "12345" << std::endl << std::endl;
    //     }
    print_piece(vacia);

    random_piece (vacia);
    std::cout << "despues" << std::endl;
    print_piece(vacia);
    return 0;
}
