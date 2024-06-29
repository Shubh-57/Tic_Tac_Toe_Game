#include <iostream>
#include <cstdlib>
#include <limits.h>
using namespace std;

// printing the board
void print_board(char board[][3]){
    for (int i=0;i<3;i++){
        for (int j=0;j<3;j++){
            if(j!=2)
            cout<<" "<<board[i][j]<<" |";
            else
            cout<<" "<<board[i][j]<<" ";
        }
        if(i!=2)
        cout<<"\n---|---|---\n";
        else
        cout<<endl;
    }
}

// Restarting the match
void empty_board(char board[][3]){
    for(int row=0;row<3;row++){
        for(int col=0;col<3;col++){
            board[row][col]=' ';
        }
    }
}

// checking for "Game Over"
int isGameOver(char board[][3],char val){
    // win
    if( board[0][0] == val && board[0][1] == val && board[0][2] == val ||
        board[1][0] == val && board[1][1] == val && board[1][2] == val ||
        board[2][0] == val && board[2][1] == val && board[2][2] == val ||
        board[0][0] == val && board[1][0] == val && board[2][0] == val ||
        board[0][1] == val && board[1][1] == val && board[2][1] == val ||
        board[0][2] == val && board[1][2] == val && board[2][2] == val ||
        board[0][0] == val && board[1][1] == val && board[2][2] == val ||
        board[0][2] == val && board[1][1] == val && board[2][0] == val ){

        return 1;
    }

    // incomplete
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(board[i][j] == ' '){
                return 2;
            }
        }
    }

    // draw
    return 3;
}

// to get the score
int evaluate(char board[][3], int level){
    int check_x = isGameOver(board,'X');
    int check_o = isGameOver(board,'O');
    if(check_o == 1){
        int rand_num = rand() % 10;
        switch(level) {
            case 1: // Easy
                return (rand_num < 5) ? 1 : -2;
            case 2: // Hard
                return (rand_num < 9) ? 1 : -2;
        }
    }
    else if(check_x == 1){
        return -1;
    }
    else if(check_o == 3 || check_x == 3){
        return 0;
    }
    else{
        return 2;
    }
}

// Mini-Max algorithm
int miniMax(char board[][3], int level, bool isComp){
    // base case (match completed)
    int score = evaluate(board, level);
    if(score != 2){
        return score;
    }

    // computer's turn
    if(isComp){
        int bestScore = INT_MIN;
        bool immediate_win = false;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(board[i][j] == ' '){
                    board[i][j] = 'O';
                    int currentScore = miniMax(board, level, false);
                    bestScore = max(currentScore,bestScore);
                    board[i][j] = ' ';
                }
            }
        }
        return bestScore;
    }

    // player's turn
    else{
        int bestScore = INT_MAX;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(board[i][j] == ' '){
                    board[i][j] = 'X';
                    int currentScore = miniMax(board, level, true);
                    bestScore = min(currentScore,bestScore);
                    board[i][j] = ' ';
                }
            }
        }
        return bestScore;
    }
}

// to get the optimal move
pair<int,int> optimalMove(char board[][3], int level){
    int bestScore = INT_MIN;
    pair<int,int> bestMove;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(board[i][j] == ' '){
                board[i][j] = 'O';

                // Check for Immediate/Obvious winning move
                if(isGameOver(board, 'O') == 1){
                    board[i][j] = ' ';
                    return make_pair(i, j);
                }

                int currentScore = miniMax(board, level, false);
                if(currentScore > bestScore){
                    bestScore = currentScore;
                    bestMove.first = i;
                    bestMove.second = j;
                }
                board[i][j] = ' ';
            }
        }
    }
    return bestMove;
}

int main()
{
    cout<<"Welcome to !! TIC TAC TOE !!"<<endl<<endl;
    char board[3][3]={{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};
    cout<<"   |   |\n---|---|---\n   |   |\n---|---|---\n   |   |"<<endl<<endl;

    int mode;
    cout<<"Enter 1 for computer mode and 2 for 2 player mode : ";
    cin>>mode;

    // computer mode
    if(mode == 1){
        int level;
        cout<<"Enter 1 for Easy level and 2 for Hard level : ";
        cin>>level;
        cout<<"You : X"<<endl;
        cout<<"Computer : O"<<endl;
        while(true) {
            int row,col,choice;
            cout<<endl<<"Your's Turn"<<endl;
            cout<<"Enter row(0-2) & col(0-2) : ";
            cin>>row>>col;

            // Checking for wrong position
            while(!(row>=0 && row<=2) || !(col>=0 && col<=2) || board[row][col]!=' '){
                cout<<"Wrong entry\nEnter again"<<endl;
                cout<<"Enter row(0-2) & col(0-2) : ";
                cin>>row>>col;
            }
            board[row][col]='X';

            // Viewing the board
            print_board(board);

            int decision = isGameOver(board,'X');

            // Checking for winner
            if (decision == 1){
                cout<<"You Win !!"<<endl<<endl;
                cout<<"Want to Play Another Round ?"<<endl;
                cout<<"Enter 1 for YES and 0 for NO : ";
                cin>>choice;
                if (choice==0){
                    break;
                }
                else{
                    // Reinitializing all the positions with ' '
                    empty_board(board);
                    cout<<endl<<endl<<"   |   |\n---|---|---\n   |   |\n---|---|---\n   |   |"<<endl<<endl;
                    cout<<"Enter 1 for Easy level and 2 for Hard level : ";
                    cin>>level;
                    cout<<"You : X"<<endl;
                    cout<<"Computer : O"<<endl;
                    continue;
                }
            }

            // Checking for match draw
            else if(decision == 3){
                cout<<"Match Draws !!"<<endl<<endl;
                cout<<"Want to Play Another Round ?"<<endl;
                cout<<"Enter 1 for YES and 0 for NO : ";
                cin>>choice;
                if (choice==0){
                    break;
                }
                else{
                    // Reinitializing all the positions with ' '
                    empty_board(board);
                    cout<<endl<<endl<<"   |   |\n---|---|---\n   |   |\n---|---|---\n   |   |"<<endl<<endl;
                    cout<<"Enter 1 for Easy level and 2 for Hard level : ";
                    cin>>level;
                    cout<<"You : X"<<endl;
                    cout<<"Computer : O"<<endl;
                    continue;
                }
            }

            pair<int,int> bestMove;
            bestMove = optimalMove(board, level);
            board[bestMove.first][bestMove.second] = 'O';

            cout<<"Opponent's Turn : "<<bestMove.first<<" "<<bestMove.second<<endl;

            // Viewing the board
            print_board(board);

            // Checking for winner
            if (isGameOver(board,'O') == 1){
                cout<<"You lost !!"<<endl<<endl;
                cout<<"Want to Play Another Round ?"<<endl;
                cout<<"Enter 1 for YES and 0 for NO : ";
                cin>>choice;
                if (choice==0){
                    break;
                }
                else{
                    // Reinitializing all the positions with ' '
                    empty_board(board);
                    cout<<endl<<endl<<"   |   |\n---|---|---\n   |   |\n---|---|---\n   |   |"<<endl<<endl;
                    cout<<"Enter 1 for Easy level and 2 for Hard level : ";
                    cin>>level;
                    cout<<"You : X"<<endl;
                    cout<<"Computer : O"<<endl;
                    continue;
                }
            }
        }
    }

    // 2 player mode
    else{
        cout<<"Player 1 : X"<<endl;
        cout<<"Player 2 : O"<<endl;
        while(true) {
            int row,col,choice;
            cout<<endl<<"Player 1's Turn"<<endl;
            cout<<"Enter row(0-2) & col(0-2) : ";
            cin>>row>>col;

            // Checking for wrong position
            while(!(row>=0 && row<=2) || !(col>=0 && col<=2) || board[row][col]!=' '){
                cout<<"Wrong entry\nEnter again"<<endl;
                cout<<"Enter row(0-2) & col(0-2) : ";
                cin>>row>>col;
            }
            board[row][col]='X';

            // Viewing the board
            print_board(board);

            int decision = isGameOver(board,'X');

            // Checking for winner
            if (decision == 1){
                cout<<"Player 1 Wins !!"<<endl<<endl;
                cout<<"Want to Play Another Round ?"<<endl;
                cout<<"Enter 1 for YES and 0 for NO : ";
                cin>>choice;
                if (choice==0){
                    break;
                }
                else{
                    // Reinitializing all the positions with ' '
                    empty_board(board);
                    cout<<endl<<endl<<"   |   |\n---|---|---\n   |   |\n---|---|---\n   |   |"<<endl<<endl;
                    continue;
                }
            }

            // Checking for match draw
            if(decision == 3){
                cout<<"Match Draws !!"<<endl<<endl;
                cout<<"Want to Play Another Round ?"<<endl;
                cout<<"Enter 1 for YES and 0 for NO : ";
                cin>>choice;
                if (choice==0){
                    break;
                }
                else{
                    // Reinitializing all the positions with ' '
                    empty_board(board);
                    cout<<endl<<endl<<"   |   |\n---|---|---\n   |   |\n---|---|---\n   |   |"<<endl<<endl;
                    continue;
                }
            }

            cout<<endl<<"Player 2's Turn"<<endl;
            cout<<"Enter row(0-2) & col(0-2) : ";
            cin>>row>>col;

            // Checking for wrong position
            while(!(row>=0 && row<=2) || !(col>=0 && col<=2) || board[row][col]!=' '){
                cout<<"Wrong entry\nEnter again"<<endl;
                cout<<"Enter row(0-2) & col(0-2) : ";
                cin>>row>>col;
            }
            board[row][col]='O';

            // Viewing the board
            print_board(board);

            // Checking for winner
            if (isGameOver(board,'O') == 1){
                cout<<"Player 2 Wins !!"<<endl<<endl;
                cout<<"Want to Play Another Round ?"<<endl;
                cout<<"Enter 1 for YES and 0 for NO : ";
                cin>>choice;
                if (choice==0){
                    break;
                }
                else{
                    // Reinitializing all the positions with ' '
                    empty_board(board);
                    cout<<endl<<endl<<"   |   |\n---|---|---\n   |   |\n---|---|---\n   |   |"<<endl<<endl;
                    continue;
                }
            }
        }
    }
    return 0;
}
