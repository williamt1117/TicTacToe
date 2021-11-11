#include <stdio.h>

/*
 x | o | x  COORD SYSTEM O---> +x
---+---+---              |
 o | o |                \/ +y
---+---+---
   | x | o 
*/

//Given a baord input, prints a Tic-Tac-Toe board with entries corresponding to the array
void PrintBoard(int b[3][3])
{
    for (int i = 0; i < 5; i++)
    {
        if (i % 2 == 0)
        {
            //print row with corresponding entries
            int entries[3];
            char chars[3];
            for (int j = 0; j < 3; j++)
            {
                entries[j] = b[j][i/2];
                switch (b[j][i/2])
                {
                    case 0:
                        chars[j] = ' ';
                        break;

                    case 1:
                        chars[j] = 'x';
                        break;

                    case 2:
                        chars[j] = 'o';
                        break;
                }
            }
            if (entries[0] == 1) printf("\033[0;31m");
            else if (entries[0] == 2) printf("\033[0;94m");
            printf(" %c ", chars[0]);
            printf("\033[0m");
            printf("║");
            if (entries[1] == 1) printf("\033[0;31m");
            else if (entries[1] == 2) printf("\033[0;94m");
            printf(" %c ", chars[1]);
            printf("\033[0m");
            printf("║");
            if (entries[2] == 1) printf("\033[0;31m");
            else if (entries[2] == 2) printf("\033[0;94m");
            printf(" %c ", chars[2]);
            printf("\033[0m");

        }
        else
        {
            //print dividing row
            printf("═══╬═══╬═══");
        }
        printf("\n");
    }
}

//given a player (0 = p1, 1 = p2), a number (1 - 9) and a board, converts the number to an index of the
//board and places the corresponding players entry into the board.
void NumberToBoardEntry (int b[3][3], int num, int player)
{
    int index = num - 1;
    int yIndex = index / 3;
    int xIndex = index % 3;

    b[xIndex][yIndex] = player;
}

//given a board, returns an integer corresponding to p1 winning (1), p2 winning (2), or a tie (3), if none
//of these cases are encountered the game is continues (0)
int CheckForGameFinish(int b[3][3])
{
    //Check for win (brute force method)
    if (b[0][0] == b[0][1] && b[0][1] == b[0][2] && b[0][0] != 0) //win left column
        return b[0][0];
    if (b[1][0] == b[1][1] && b[1][1] == b[1][2] && b[1][0] != 0) //win middle column
        return b[1][0];
    if (b[2][0] == b[2][1] && b[2][1] == b[2][2] && b[2][0] != 0) //win right column
        return b[2][0];
    if (b[0][0] == b[1][0] && b[1][0] == b[2][0] && b[2][0] != 0) //win top row
        return b[2][0];
    if (b[0][1] == b[1][1] && b[1][1] == b[2][1] && b[2][1] != 0) //win middle row
        return b[2][1];
    if (b[0][2] == b[1][2] && b[1][2] == b[2][2] && b[2][2] != 0) //win bottom row
        return b[2][2];
    if (b[0][0] == b[1][1] && b[1][1] == b[2][2] && b[2][2] != 0) //win TL diagonal
        return b[2][2];
    if (b[2][0] == b[1][1] && b[1][1] == b[0][2] && b[0][2] != 0) //win TR diagonal
        return b[0][2];

    for (int x = 0; x < 3; x++)
        for (int y = 0; y < 3; y++)
            if (b[x][y] == 0) return 0;

    return 3;
    
}

int main()
{
    //Create board entry 2d array
    int board[3][3];
    for (int x = 0; x < 3; x++)
        for (int y = 0; y < 3; y++)
            board[x][y] = 0;

    int gameEnd = 0;

    for(int i = 0; !gameEnd; i++)
    {
        int player = i%2 + 1;
        PrintBoard(board);

        int choice = -1;
        int validEntry = 0;

        printf("Player %i: Enter a spot to play (1 - 9): ", player);
        
        while (!validEntry)
        {
            if (scanf("%i", &choice) != 1)
            {
                printf("Error: Alpha entry. Exiting program.\n");
                return 0;
            }

            if (choice > 0 && choice < 10 && !board[(choice-1)%3][(choice-1)/3])
            {
                validEntry = 1;
            }
            else
            {
                printf("Invalid entry. Player %i: Enter a spot to play (1 - 9): ", player);
            }
        }
        
        NumberToBoardEntry(board, choice, player);

        if (CheckForGameFinish(board)) gameEnd = 1;  
    }

    PrintBoard(board);
    switch (CheckForGameFinish(board))
    {
        case 1:
            printf("Player 1 wins!\n");
            break;

        case 2: 
            printf("Player 2 wins!\n");
            break;
        case 3:
            printf("It's a tie!\n");
            break;
    }   
    
    return 0;
}