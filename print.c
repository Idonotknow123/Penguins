#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "print.h"

int wheres_letter(char word[]) {
    int position = 0;
    for (int i = 0; i < strlen(word); i++) {
        if ((int)word[i] >= 'A' && (int)word[i] <= 'z') {
            position = i; // store position (1-based index)
            break; // stop searching after the first occurrence
        }
    }
    return position;
}

int string_to_integer(const char word[]) {
    int result = 0;
    int i = 0;
    // iterate through the array until the null terminator is reached
    while (word[i] != '\0') {
        // convert the character to a digit and build the number
        if((int)word[i] >= '0' && (int)word[i] <= '9') {
            result = result * 10 + (word[i] - '0');
        }
        i++;
    }
    return result;
}

void clear_background()
{
    system("cls");
}

void enter_values(int *xp, int *yp) {
    char sttr[31];
    scanf("%s", sttr);
    int pos = wheres_letter(sttr);
    if (pos == 0 && sttr[0] == '\0') {
        printf("Invalid input: no letter found\n");
        *xp = -1;
        *yp = -1;
        return;
    }
    int row_number = string_to_integer(sttr);
    *xp = (int)sttr[pos] - 'A';
    *yp = row_number - 1;
}