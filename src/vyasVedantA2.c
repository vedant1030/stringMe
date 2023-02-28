#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * readFile (char * filename) 
{
    FILE * fptr;
    char * fileContent;
    int num = 0;

    fptr = fopen(filename, "r");

    if(fptr == NULL)
    {
        printf("File could not be opened!");
        exit(1);
    }
    else
    {
        while(!feof(fptr))
        {
            if(num == 0)
            {
                fileContent = calloc(1, sizeof(char));
            }
            else
            {
                fileContent = realloc(fileContent, sizeof(char*)*(num + 1));
            }
            fgets(fileContent + num, 2, fptr);
            num++;
        }
        num--;
        return fileContent;
    }
}

void dejaVu (char * aString, int * numWords, int * numSentences) 
{
    int length = strlen(aString);
    int i;
    *numWords = 0;
    *numSentences = 0;
    int inWord = 0;

    for (i = 0; i < length; i++) 
    {
        if (aString[i] == ' ' || aString[i] == '\t' || aString[i] == '\n') 
        {
            inWord = 0;
        } 
        else if (aString[i] == '.' || aString[i] == ':' || aString[i] == ';' || aString[i] == '?' || aString[i] == '!') 
        {
            if (inWord) 
            {
                *numWords += 1;
                inWord = 0;
            }
            *numSentences += 1;
        } 
        else 
        {
            if (!inWord) 
            {
                *numWords += 1;
                inWord = 1;
            }
        }
    }
}

char * goBig (char * aString) 
{
    int len = strlen(aString);
    char * stretchedString = malloc(len + 1);  //allocate memory for the stretched string.
    int stretchFactor;
    int index = 0;

    for (int i = 0; i < len; i++) 
    {
        printf("Enter a positive integer for position %d: ", i + 1);
        scanf("%d", &stretchFactor);

        //if user enters invalid input, print error message and allow user to re-enter value for the same position.

        if (stretchFactor <= 0) 
        {
            printf("Invalid input, please enter a positive integer.\n");
            i--;  //decrement the index so that the same position can be entered again.
            continue;
        }

        //repeat the character at the current position in the input string stretchFactor times.
        
        for (int j = 0; j < stretchFactor; j++) 
        {
            stretchedString[index++] = aString[i];
        }
    }
    stretchedString[index] = '\0'; //null-terminate the stretched string.
    return stretchedString; //return pointer to the stretched string.
}

char ** goAway (char * aString, int * numWordsReturned) 
{
    int i = 0, j = 0, k = 0;
    int len = strlen(aString);
    int numWords = 0;
    char ** words = (char**) malloc(sizeof(char*));
    words[0] = (char*) malloc(sizeof(char));
    
    while (i < len) 
    {
        while (aString[i] == ' ' || aString[i] == '\n') 
        {
            i++;
        }
        j = i;

        while (aString[j] != ' ' && aString[j] != '\n' && j < len) 
        {
            j++;
        }
        if (j > i) 
        {
            numWords++;
            words = (char**) realloc(words, sizeof(char*) * numWords);
            words[numWords - 1] = (char*) malloc(sizeof(char) * (j - i + 1));
            k = 0;

            for (int p = i; p < j; p++) 
            {
                words[numWords - 1][k++] = aString[p];
            }
            words[numWords - 1][k] = '\0';
            i = j;
        }
    } 
    *numWordsReturned = numWords;
    return words;
}

char * breathless (char * aString) 
{
    int len = strlen(aString); //find length of the given string.
    int newLen = 0; //initialize length of modified string to zero.
    char *newString = malloc(len + 1); //allocate memory for modified string.

    //loop through each character of the given string and copy non-punctuation marks to modified string.

    for (int i = 0; i < len; i++) 
    {
        if (aString[i] != '.' && aString[i] != ',' && aString[i] != ';' && aString[i] != '?' && aString[i] != '!') 
        {
            newString[newLen++] = aString[i];
        }
    }
    newString[newLen] = '\0'; //add null-terminator at the end of modified string.
    return newString; //return modified string.
}

void tail (char * aString, int whichWord, char * desiredSuffix)
{
    int i, j, k;
    int wordCount = 0; 
    int suffixLen = strlen(desiredSuffix);
    char word[100];

    for (i = 0; aString[i] != '\0'; i++)
    {
        if (aString[i] != ' ')
        {
            word[j++] = aString[i];
        }
        else
        {
            word[j] = '\0';
            j = 0;
            wordCount++;

            if (wordCount == whichWord)
            {
                for (k = 0; k < strlen(word); k++)
                {
                    printf("%c", word[k]);
                    printf("%s\n", desiredSuffix);
                }
            }
        }
    }
    wordCount++;

    if (wordCount == whichWord)
    {
        for (k = 0; k < strlen(word); k++)
        {
            printf("%c", word[k]);
            printf("%s\n", desiredSuffix);
        }
    }
}

