//Tic-tac-toe playing AI. Exhaustive tree-search (MinMax)
//Matthew Steel 2009, www.www.repsilat.com

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

char gridChar(int i) {
    switch(i) {
        case -1:
            return 'X';
        case 0:
            return ' ';
        case 1:
            return 'O';
    }
    return 0;
}

void draw(int b[9]) {
    printf(" %c | %c | %c\n",gridChar(b[0]),gridChar(b[1]),gridChar(b[2]));
    printf("---+---+---\n");
    printf(" %c | %c | %c\n",gridChar(b[3]),gridChar(b[4]),gridChar(b[5]));
    printf("---+---+---\n");
    printf(" %c | %c | %c\n",gridChar(b[6]),gridChar(b[7]),gridChar(b[8]));
}

int win(const int board[9]) {
    //determines if a player has won, returns 0 otherwise.
    unsigned wins[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    int i;
    for(i = 0; i < 8; ++i) {
        if(board[wins[i][0]] != 0 &&
           board[wins[i][0]] == board[wins[i][1]] &&
           board[wins[i][0]] == board[wins[i][2]])
            return board[wins[i][2]];
    }
    return 0;
}

int minimax(int board[9], int player) {
    //How is the position like for player (their turn) on board?
    int winner = win(board);
    if(winner != 0) return winner*player;
    
    int move = -1;
    int score = -2;//Losing moves are preferred to no move
    int i;
    for(i = 0; i < 9; ++i) {//For all moves,
        if(board[i] == 0) {//If legal,
            board[i] = player;//Try the move
            int thisScore = -minimax(board, player*-1);
            if(thisScore > score) {
                score = thisScore;
                move = i;
            }//Pick the one that's worst for the opponent
            board[i] = 0;//Reset board after try
        }
    }
    if(move == -1) return 0;
    return score;
}

void computerMove(int board[9]) {
    int move = -1;
    int score = -2;
    int i;
    
    for(i = 0; i < 9; ++i) {
        if(board[i] == 0) {
            board[i] = 1; // assume that computer did move to i
            int tempScore = -minimax(board, -1);
            board[i] = 0; // reset it back to "empty"
            
            // BEGINNING OF MODIFYING AI TO MAKE MISTAKES
            
            int CHANCE = 3; // the larger the chance, the less likely is that the AI will choose best move.
            int r = ((rand() % (CHANCE+1)) > 0) ? 3 : 0; // 3, because worst move is -1, neutral move is 0, and good move is 1. -1+3 = 2, which means that even the worst move will be considered best move, if rand renturns anything but 0.
            
            // Promoting bad moves as best moves:
            // if the score is not the best, lets make it the best
            if (tempScore < score) {
                // if this is a loosing move, sometimes deceive AI to think it is a winning move
                tempScore +=r;
            }

            // END OF MODIFYING AI TO MAKE MISTAKES
            
            if (tempScore > score) { // find max score, and, consequently, best move
                score = tempScore;
                move = i;
            }
        }
    }
    //move to the position that has highest score from minmax.
    printf("\nAI moved to %d\n\n", move);
    board[move] = 1;
}

void playerMove(int board[9]) {
    int move = 0;
    do {
        printf("\nInput move ([0..8]): ");
        scanf("%d", &move);
        printf("\n");
    } while (move >= 9 || move < 0 || board[move] != 0);
    board[move] = -1;
}

int main() {
    srand((unsigned int)time(NULL)); // initalize pseudo-random number generator
    int board[9] = {0,0,0,0,0,0,0,0,0};
    //computer squares are market 1, player squares are market -1.
    printf("Computer: O, You: X\nPlay (1)st or (2)nd? ");
    // order of playing. If 1, player starts, if 2, AI starts
    int player = 0;
    scanf("%d",&player);
    printf("\n");
    unsigned turn;
    for(turn = 0; turn < 9 && win(board) == 0; ++turn) {
        // if computer plays
        if((turn+player) % 2 == 0) {
            // introducing delay in thinking...
            // AI is too fast, which is not human-like.
            printf("\nAI is thinking...\n");
            usleep(((rand() % 3 )+1) * 1000000);
            computerMove(board);
        }
        else {
            playerMove(board);
        }
        draw(board);


    }
    
    switch(win(board)) {
        case 0:
            printf("A draw. How droll.\n");
            break;
        case 1:
            printf("You lose.\n");
            break;
        case -1:
            printf("You win. Inconceivable!\n");
            break;
    }
    draw(board);
}

