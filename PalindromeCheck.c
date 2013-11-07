#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char* getUserInput();
int checkPalindrome(char*);

int main()
{
    char *str = NULL;
    printf("Please input your words/sentences to be checked for palindromes.\n"
           "Separate each entity with a comma.\n\n");
    str = getUserInput(str);
    char *part;
    part = strtok(str, ",");

    printf("\n\nPalindromes:\n-------------------\n");
    while(part != NULL)
    {
        printf(part);

        if(checkPalindrome(str))
            printf("\tpalindrome\n\n");
        else
            printf("\tnot a palindrome\n\n");

        part = strtok(NULL, ",");
    }
    printf("\n\n-------------------\n");
	free(str);
    getchar();
    return 0;
}

int checkPalindrome(char* str)
{
    char *startPointer = str;
    char *endPointer = str + strlen(str) - 1;

    while(startPointer < endPointer)
    {
        while(*startPointer == ' ')
            startPointer++;

        while(*endPointer == ' ')
            endPointer--;

        if(tolower(*startPointer) != tolower(*endPointer))
            return 0;

        startPointer++;
        endPointer--;
    }

    return 1;
}

char* getUserInput()
{
    char *temp = NULL;
    int i = 0, totalChars = 0;
    int nextChar = 1;

    while(nextChar)
    {
        nextChar = getchar();
        if(nextChar == '\n')
            nextChar = 0;

        if(totalChars <= i)
        {
            totalChars++;
            temp = realloc(temp, totalChars);
        }
        temp[i++] = nextChar;
    }
    return temp;
}
