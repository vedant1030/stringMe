#include "../include/vyasVedantA2.h"

char * readFile (char * filename) 
{
    FILE * fptr;
    char * fileContent; //pointer to the memory where the file content will be stored.
    int num = 0; //counter to keep track of number of characters read from file.

    fptr = fopen(filename, "r"); //open the file in read mode.

    if (fptr == NULL) //check if file could not be opened.
    {
        printf("File could not be opened!");
        exit(1);
    }
    else
    {
        while (!feof(fptr)) //loop until end of file is reached.
        {
            if (num == 0) //if this is the first character, allocate memory for the file content.
            {
                fileContent = calloc(1, sizeof(char));
            }
            else //otherwise, resize the memory to accommodate the new character.
            {
                fileContent = realloc(fileContent, sizeof(char*)*(num + 1));
            }
            fgets(fileContent + num, 2, fptr); //read one character at a time and store it in the allocated memory.
            num++; //increment the counter.
        }
        num--; //decrement the counter to exclude the null character.
        return fileContent; //return the pointer to the file content.
    }
}

void dejaVu (char * aString, int * numWords, int * numSentences) 
{
    int numChars = 0; //initialize a counter for the number of characters in a word.
    *numWords = 0; //initialize the number of words to 0.
    *numSentences = 0; //initialize the number of sentences to 0.

    for (int i = 0; aString[i] != '\0'; i++) //loop through each character in the string until the end of string character is reached.
    {
        char current = aString[i]; //get the current character.
        numChars++; //increment the character counter.

        if (current == '.' || current == ':' || current == ';' || current == '?' || current == '!') //if the current character is a sentence-ending punctuation mark, increment the sentence counter.
        {
            (*numSentences)++; 
        }
        if (current == ' ' || current == '\t' || current == '\n' || current == '\r') //if the current character is a space, tab, newline, or carriage return, it marks the end of a word.
        {
            if (numChars > 1) //if the word has more than one character, increment the word counter.
            {
                (*numWords)++; 
            }
            numChars = 0; //reset the character counter for the next word.
        }
    }
    if (numChars > 0) //if there are characters remaining after the loop has finished, increment the word counter for the last word.
    {
        (*numWords)++; 
    }
}

char * goBig (char * aString) 
{
    int length = strlen(aString)-1; //length of the input string.
    char * stretchedString = malloc(length + 1); //allocate memory for the stretched string.
    int stretchFactor; //factor by which each character will be repeated.
    int index = 0; //index to keep track of current position in the stretched string

    for (int i = 0; i < length; i++) 
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
    char ** words; //pointer to an array of strings that will contain the words found in the input string.
    int length; //length of the current word being processed.
    *numWordsReturned = 0; //pointer to the number of words found in the input string.

    for (int i = 0; i < strlen(aString); i++) //loop through every character in the input string.
    {
        if (aString[i] == ' ' || aString[i] == '\n' || i == strlen(aString)-1) //check if the current character is a delimiter (space, newline) or end of string.
        {
            if (aString[i-1] == ' ' || aString[i-1] == '\n') //check if there are consecutive delimiters.
            {
                //do nothing because of consecutive delimiters.
            }
            else
            {
                if (*numWordsReturned == 0) //allocate or reallocate memory for words array based on number of words found.
                {
                    words = calloc(1, sizeof(char*));
                }
                else
                {
                    words = realloc(words, sizeof(char*)*(*numWordsReturned+1));
                }
                length = 0;

                for (int j = i-1; j >- 1; j--) //count the number of characters in the current word.
                {
                    if (aString[j] == ' ' || aString[j] == '\n')
                    {
                        break;
                    }
                    else
                    {
                        length++;
                    }
                }
                if (i == strlen(aString)-1) //if the current character is the end of the string, add one more character to length.
                {
                    length++;
                }
                words[*numWordsReturned] = calloc(length, sizeof(char)); //allocate memory for the current word and add it to the words array.

                for (int j = 0; j < length; j++) //copy the characters of the current word into the allocated memory.
                {
                    if (i == strlen(aString)-1)
                    {
                        words[*numWordsReturned][length-j-1] = aString[i-j];
                    }
                    else
                    {
                        words[*numWordsReturned][length-j-1] = aString[i-j-1];
                    }
                }
                *numWordsReturned = *numWordsReturned + 1; //increment the number of words found.
            }
        } 
    }
    return words;
}

char * breathless (char * aString) 
{
    int length = strlen(aString); //find length of the given string.
    int newLength = 0; //initialize length of modified string to zero.
    char *newString = malloc(length + 1); //allocate memory for modified string.

    for (int i = 0; i < length; i++) //loop through each character of the given string and copy non-punctuation marks to modified string.
    {
        if (aString[i] != '.' && aString[i] != ':' && aString[i] != ';' && aString[i] != '?' && aString[i] != '!') 
        {
            newString[newLength++] = aString[i]; //increment newLength each time a non-punctuation character is copied.
        }
    }
    newString[newLength] = '\0'; //add null-terminator at the end of modified string.
    return newString; //return modified string.
}

void tail (char * aString, int whichWord, char * desiredSuffix) 
{
    int numWords = 0; //initialize the word count.
    char * word; //pointer to the current word.
    int length = 0; //initialize the length of the current word.
    char * temp; //temporary pointer used for string operations.

    //loop through each character of the input string.
    for (int i = 0; i < strlen(aString); i++) 
    { 
        //check if the current character is a whitespace or end of line character.
        if (aString[i] == ' ' || aString[i] == '\n' || i == strlen(aString)-1) 
        { 
            //check if the previous character is also a whitespace or end of line character.
            if (aString[i-1] == ' ' || aString[i-1] == '\n') 
            { 
                //do nothing.
            }
            else 
            { 
	            numWords++; //increment the word count.

	            //check if the current word is the one we want to process.
	            if (whichWord == numWords) 
                    { 
	                //loop through the current word in reverse order.
	                for (int j = i; j >= 0; j--) 
                        { 
	                    //check if the current character is a delimiter.
	                    if (aString[j] == ' ' || aString[j] == '\n' || aString[j] == '.' || aString[j] == ':' || aString[j]== ';' || aString[j] == '?' || aString[j] == '!' || aString[j] == ',') 
                            { 
	                        //do nothing.
	                    }
	                    else 
                            { 
	                        length++; //increment the length of the current word.

	                        //allocate memory for the current word.
	                        if (length == 1) 
                                { 
		                        word = calloc(length, sizeof(char));
	                        }
	                        else 
                                { 
		                        word = realloc(word, sizeof(char)*(length));
	                        }

	                        *(word + length - 1) = aString[j]; //initialize each character of the current word.
	                    }

	                    //check if the previous character is also a whitespace or end of line character.
	                    if (aString[j-1] == ' ' || aString[j-1] == '\n') 
                            { 
	                        break; //exit the loop.
	                    }
	                }

	                //reverse the current word.
	                temp = calloc(strlen(word), sizeof(char)); 
	                strcpy(temp, word); 

                    for (int j = 0; j < strlen(word); j++) 
                    { 
                        *(word + j) = *(temp + strlen(word)-1-j);
                    }

                    //print the current word with the desired suffix.
                    for (int j = 0; j < strlen(word); j++) 
                    {
                        printf("%c", *(word + j));
                        printf(desiredSuffix);
                        printf("\n");
                    }
                }
            } 
        }
    }

    //check if the specified word index is valid.
    if (whichWord < 1 || whichWord > numWords) 
    {
        printf("Invalid value for whichWord\n");
    }
}

