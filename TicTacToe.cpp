#include<iostream>
#include <cstdlib>
#include<time.h>
using namespace std;

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

void empty_board(char board[][3]){
    for(int row=0;row<3;row++){
        for(int col=0;col<3;col++){
            board[row][col]=' ';
        }
    }
}

bool win_check(char board[][3],char val){
    if( board[0][0] == val && board[0][1] == val && board[0][2] == val ||
        board[1][0] == val && board[1][1] == val && board[1][2] == val ||
        board[2][0] == val && board[2][1] == val && board[2][2] == val ||
        board[0][0] == val && board[1][0] == val && board[2][0] == val ||
        board[0][1] == val && board[1][1] == val && board[2][1] == val ||
        board[0][2] == val && board[1][2] == val && board[2][2] == val ||
        board[0][0] == val && board[1][1] == val && board[2][2] == val ||
        board[0][2] == val && board[1][1] == val && board[2][0] == val ){

        return true;
    }
    return false;
}

int main()
{
    cout<<"TIC TAC TOE"<<endl<<endl;
    char board[3][3]={{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};
    cout<<"   |   |\n---|---|---\n   |   |\n---|---|---\n   |   |"<<endl<<endl;

    int mode;
    cout<<"Enter 1 for 1 player mode or 2 for 2 player mode : ";
    cin>>mode;

    if(mode == 1){
        // Computer mode
        cout<<"You : X"<<endl;
        cout<<"Computer : O"<<endl;
        int count = 0;
        do{
            int row,col,choice;
            cout<<endl<<"Your's Turn"<<endl;
            cout<<"Enter row & col : ";
            cin>>row>>col;

            // Checking for wrong position
            while(board[row][col]!=' '){
                cout<<"Wrong entry\nEnter agan"<<endl;
                cout<<"Enter row & col : ";
                cin>>row>>col;
            }
            board[row][col]='X';
            count ++;

            // Viewing the board
            print_board(board);

            // Checking for winner
            if (win_check(board,'X')){
                cout<<"You Win"<<endl;
                cout<<"Want to Play Another Round ?"<<endl;
                cout<<"Enter 1 for YES and 0 for NO : ";
                cin>>choice;
                if (choice==0){
                    break;
                }
                else{
                    // Reinitializing all the positions with ' '
                    empty_board(board);
                    count = 0;
                    cout<<endl<<endl<<"   |   |\n---|---|---\n   |   |\n---|---|---\n   |   |"<<endl<<endl;
                    continue;
                }
            }

            // Checking for match draw
            if(count == 9){
                cout<<"Match Draws"<<endl;
                cout<<"Want to Play Another Round ?"<<endl;
                cout<<"Enter 1 for YES and 0 for NO : ";
                cin>>choice;
                if (choice==0){
                    break;
                }
                else{
                    // Reinitializing all the positions with ' '
                    empty_board(board);
                    count = 0;
                    cout<<endl<<endl<<"   |   |\n---|---|---\n   |   |\n---|---|---\n   |   |"<<endl<<endl;
                    continue;
                }
            }

            // to generate different sequence of random numbers on every program run
            srand(time(0));

            row=rand()%3;
            col=rand()%3;

            // Checking for wrong position
            while(board[row][col]!=' '){
                row=rand()%3;
                col=rand()%3;
            }
            board[row][col]='O';
            count ++;
            cout<<endl<<"Computer's Turn : "<<row<<" "<<col<<endl;

            // Viewing the board
            print_board(board);

            // Checking for winner
            if (win_check(board,'O')){
                cout<<"Computer Wins"<<endl;
                cout<<"Want to Play Another Round ?"<<endl;
                cout<<"Enter 1 for YES and 0 for NO : ";
                cin>>choice;
                if (choice==0){
                    break;
                }
                else{
                    // Reinitializing all the positions with ' '
                    empty_board(board);
                    count = 0;
                    cout<<endl<<endl<<"   |   |\n---|---|---\n   |   |\n---|---|---\n   |   |"<<endl<<endl;
                    continue;
                }
            }
        }while(1);
    }

    else{
        // 2 player mode
        cout<<"Player 1 : X"<<endl;
        cout<<"Player 2 : O"<<endl;
        int count = 0;
        do{
            int row,col,choice;
            cout<<endl<<"Player 1's Turn"<<endl;
            cout<<"Enter row & col : ";
            cin>>row>>col;

            // Checking for wrong position
            while(board[row][col]!=' '){
                cout<<"Wrong entry\nEnter again"<<endl;
                cout<<"Enter row & col : ";
                cin>>row>>col;
            }
            board[row][col]='X';
            count ++;

            // Viewing the board
            print_board(board);

            // Checking for winner
            if (win_check(board,'X')){
                cout<<"Player 1 Wins"<<endl;
                cout<<"Want to Play Another Round ?"<<endl;
                cout<<"Enter 1 for YES or 0 for NO : ";
                cin>>choice;
                if (choice==0){
                    break;
                }
                else{
                    // Reinitializing all the positions with ' '
                    empty_board(board);
                    count = 0;
                    cout<<endl<<endl<<"   |   |\n---|---|---\n   |   |\n---|---|---\n   |   |"<<endl<<endl;
                    continue;
                }
            }

            // Checking for match draw
            if(count == 9){
                cout<<"Match Draws"<<endl;
                cout<<"Want to Play Another Round ?"<<endl;
                cout<<"Enter 1 for YES and 0 for NO : ";
                cin>>choice;
                if (choice==0){
                    break;
                }
                else{
                    // Reinitializing all the positions with ' '
                    empty_board(board);
                    count = 0;
                    cout<<endl<<endl<<"   |   |\n---|---|---\n   |   |\n---|---|---\n   |   |"<<endl<<endl;
                    continue;
                }
            }

            cout<<endl<<"Player 2's Turn"<<endl;
            cout<<"Enter row & col : ";
            cin>>row>>col;

            // Checking for wrong position
            while(board[row][col]!=' '){
                cout<<"Wrong entry\nEnter again"<<endl;
                cout<<"Enter row & col : ";
                cin>>row>>col;
            }
            board[row][col]='O';
            count ++;

            // Viewing the board
            print_board(board);

            // Checking for winner
            if (win_check(board,'O')){
                cout<<"Player 2 Wins"<<endl;
                cout<<"Want to Play Another Round ?"<<endl;
                cout<<"Enter 1 for YES or 0 for NO : ";
                cin>>choice;
                if (choice==0){
                    break;
                }
                else{
                    // Reinitializing all the positions with ' '
                    empty_board(board);
                    count = 0;
                    cout<<endl<<endl<<"   |   |\n---|---|---\n   |   |\n---|---|---\n   |   |"<<endl<<endl;
                    continue;
                }
            }
        }while(1);
    }
    
    return 0;
}