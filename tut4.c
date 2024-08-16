#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

char computerOutput(char userChoice, char str[3][3]) {
    srand(time(NULL));
    int random, compRow, compCol;
    char computerChoice = (userChoice == 'O') ? 'X' : 'O';
    do {
        random = (rand() % 9) + 1;
        compRow = (random - 1) / 3;
        compCol = (random - 1) % 3;
    } while (str[compRow][compCol] != ' ');

    str[compRow][compCol] = computerChoice;
    return computerChoice;
}

bool process(char userChoice, int userInput, char str[3][3]) {
    if (userInput < 1 || userInput > 9) {
        printf("Enter a valid position (1-9)\n");
        return false;
    }

    int row = (userInput - 1) / 3;
    int col = (userInput - 1) % 3;
    
    if (str[row][col] == ' ') {
        str[row][col] = userChoice;
        return true;
    } else {
        printf("Position occupied\n");
        return false;
    }
}

char result(char str[3][3]) {
    for (int i = 0; i < 3; i++) {
        if (str[i][0] == str[i][1] && str[i][1] == str[i][2] && str[i][0] != ' ')
            return str[i][0];
        if (str[0][i] == str[1][i] && str[1][i] == str[2][i] && str[0][i] != ' ')
            return str[0][i];
    }


    if ((str[0][0] == str[1][1] && str[1][1] == str[2][2] && str[0][0] != ' ') ||
        (str[0][2] == str[1][1] && str[1][1] == str[2][0] && str[0][2] != ' '))
        return str[1][1];

    
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (str[i][j] == ' ')
                return ' '; 

    return 'D';  
}

void printBoard(char str[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf(" %c ", str[i][j]);
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf("-----------\n");
    }
    printf("\n");
}

int main() {
    int userInput;
    char userChoice;
    char str[3][3] = { {' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '} };
    
    printf("Type X for setting value to X, else O: ");
    scanf(" %c", &userChoice);
    
    if (userChoice != 'X' && userChoice != 'O') {
        printf("Invalid choice. Defaulting to X.\n");
        userChoice = 'X';
    }

    char gameResult;
    while (1) {
        printBoard(str);
        printf("Enter your Value (1-9): ");
        scanf("%d", &userInput);

        if (process(userChoice, userInput, str)) {
            gameResult = result(str);
            if (gameResult != ' ') break;

            printf("Computer's turn:\n");
            computerOutput(userChoice, str);
            gameResult = result(str);
            if (gameResult != ' ') break;
        }
    }

    printBoard(str);
    if (gameResult == 'D')
        printf("It's a draw!\n");
    else if (gameResult == userChoice)
        printf("You win!\n");
    else
        printf("Computer wins!\n");

    return 0;
}