#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define POSSIBLE_COMBS (19683)
#define NUM_SQUARES    (9)
#define CLA_FLAG_COMPLETE ("-c")
#define CLA_FLAG_PLAY     ("-p")

typedef unsigned char byte;

enum ValidationState {
    VALIDATE_NONE = 0,
    VALIDATE_COMPLETE,
    VALIDATE_PLAY
};

int multiplicity(byte board[NUM_SQUARES], int element);
bool verifyBoard(byte board[NUM_SQUARES], enum ValidationState v);
void outputBoard(byte board[NUM_SQUARES]);
bool validWinningStates(byte board[NUM_SQUARES]);

int main(int argc, char *argv[]) {
    byte c[NUM_SQUARES] = {0};
    int k = 0;
    enum ValidationState v = VALIDATE_NONE;

    if(argc > 1) {
        if(!strcmp(argv[1], CLA_FLAG_COMPLETE)) { v = VALIDATE_COMPLETE; }
        else if(!strcmp(argv[1], CLA_FLAG_PLAY)) { v = VALIDATE_PLAY; }
    }

    for(int i = 0, state = i; i < POSSIBLE_COMBS; i++, state = i) {
        for(int j = 0; j < NUM_SQUARES; j++, state /= 3) {
            c[j] = state % 3;
        }

        if(verifyBoard(c, v)) {
            k++;
            outputBoard(c); 
            putc('\n', stdout);
        }
    } 
    printf("[%d]\n", k);
}

int multiplicity(byte board[NUM_SQUARES], int element) {
    int m = 0;
    for(int i = 0; i < NUM_SQUARES; i++) { m += (board[i] == element); }
    return m;
}

bool verifyBoard(byte board[NUM_SQUARES], enum ValidationState v) {
    if(v == VALIDATE_NONE) { return true; }

    int m1 = multiplicity(board, 1),
        m2 = multiplicity(board, 2);

    //Simple checks
    //1. Number of Xs vs number of Os (difference must be one)
    //   --> 1 -> O, 2 -> X
    if(m1 - m2 != 1 && m1 - m2 != 0) {
        return false;
    }

    //For a complete board at least O or X should have a multiplicity that is a factor of 3
    if(v == VALIDATE_COMPLETE) {
        if(m1 % 3 != 0 || m2 % 3 != 0) { return false; }
    }
    //2. Only one winning pattern
    if(!validWinningStates(board)) {
        return false;
    }

    return true;
}

void outputBoard(byte board[NUM_SQUARES]) {
    int spec = 0;
    char c;
    for(int i = 0; i < NUM_SQUARES; i++) {
        spec = i % 3 == 2;

        if(board[i] == 0) { c = ' '; }
        else { c = board[i] == 1 ? 'O' : 'X'; }

        printf(" %c %c", c, spec ? '\n' : '|');
        if(spec && i != NUM_SQUARES - 1) {
            printf("---+---+---\n");
        }
    }
}

bool validWinningStates(byte b[NUM_SQUARES]) {
    int states = 0;
    int board[NUM_SQUARES];
    for(int i = 0; i < NUM_SQUARES; i++) { board[i] = b[i]; }

    for(int i = 0, j = 0; i < NUM_SQUARES; i += 3, j /= 3) {
        //Horizontal cases
        if(board[i] == board[i+1] && board[i] == board[i+2] && board[i] != 0) {
            board[i] = 0;
            board[i + 1] = 0;
            board[i + 2] = 0;
            states += 1;
        }

        //Vertical cases
        if(board[j] == board[j + 3] && board[i/3] == board[j + 6] && board[i] != 0) {
            board[j] = 0;
            board[j + 3] = 0;
            board[j + 6] = 0;
            states += 1;
        } 
    } 

    //Seperately do diagonals
    if(board[0] == board[4] && board[0] == board[8]) { states += 1; }
    if(board[2] == board[4] && board[2] == board[6]) { states += 1; }

    return states < 2;
}

