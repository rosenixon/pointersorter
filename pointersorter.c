// CS 214 Assignment 0
// Take a single input string, separate into words, and returned sorted words.
// Abdall Ahmed, Rose Nixon

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// This function counts the number of words (as separated by non-alphabetic delimiters) in the input string. 
// Returns wordcount (the number of words).

int countWords(char* string){
	
	int i =0;
	int wordcount = 0;
	
	for (i = 0; i < strlen(string); i++)
	{
		//checks if it is a letter
		if(isalpha(string[i]) != 0 )
		{
			//checks if the next character is not a letter, increases word count because we found a delimiter
			if(isalpha(string[i+1]) == 0)
			{
				wordcount++;
			}	
		} 
	}
	return wordcount;
}

// This function finds and separates each word, then inserts it into the next open spot in the array. 
// Returns the filled array of words.
char** splitAndShove(char** arrOfWords, char* string)
{
	
	int i = 0;
	int lettercount=0;
	int countWords=0; //keeps track of what "word" we are on in the input string
	int len = strlen(string); //length of input string

	for(i=0; i < len; i++) 
	{
		//checks if it is a letter
		if(isalpha(string[i]) != 0)
		{
			//letter count keeps track of how many letters are in a row
			lettercount++;
			
			//checks if it is not a letter
			if(isalpha(string[i+1]) == 0)
			{
				//allocate enough space to store all characters of the word plus space for the null character
				char * word = (char *)(malloc((lettercount+1)*sizeof(char))); 
				
				//safety check on the malloc call
				if(word == NULL)
				{
					printf("Malloc call on line 55 was unable to allocate space, exiting program \n");
					exit(1);
				}
				
				//initializes all values from the malloc call
				int j = 0;
				for(j = 0; j < lettercount+1; j++)
				{
					word[j] = 0;
				}
					
				int x = i - (lettercount-1); //x is the index of first letter of "word"
				int n=0;
				for(; x < i+1; x++) 
				{
					word[n] = string[x]; //copy chars from the input string for the specific word into the char array called word
					n++;
				}

				word[lettercount] = '\0'; //end the char array to signal it is a string
				arrOfWords[countWords] = word; //add word to the array of words
				countWords++;
				lettercount = 0;
			}	
		}
	}
	
	return arrOfWords;
}

// This function sorts all the words in the array arrOfWords. 
// Returns the sorted array.
char** sortItOut(char** arrOfWords, int numOfWords)
{
	int i = 1;

	//this is an implementation of the insertion sort algorithm
	//insertion sort relies on an "sorted" and "unsorted" section. This is why we start at index 1 and not 0.
	for(i = 1; i < numOfWords; i++)
	{
		char * curr = arrOfWords[i];
		int j = i;
		char* strToCompare = arrOfWords[j-1];
		
		//compares the current word in the array with the one before it
		//if it is "smaller" then move the previous word one index to the right (increase its index)
		while(j > 0 && strcmp(arrOfWords[j-1],curr) > 0)
		{
			arrOfWords[j] = arrOfWords[j-1];
			j = j-1;
		}

		arrOfWords[j] = curr;
	}
	return arrOfWords;
}

int main(int argc, char* argv[]) {
 	
 	//makes sure program receives the correct # of input arguments 
 	if (argc != 2) 
 	{
 		printf("Incorrect number of inputs, exiting program \n");
 		exit(1);
 	}
 	
 	//gets the length of the input string
	int len = strlen(argv[1]);
	
	//calls countWords to see how many words are in the input string
	int numOfWords = countWords(argv[1]);
	
	//there are no words in the input string (all non-letters)
	if(numOfWords == 0)
	{
		printf("\n");
		return 0;
	}
	//allocate array of char* to hold the words
	char ** arrOfWords = (char **)(malloc(numOfWords * sizeof(char*))); 
	
	//safety check on malloc call
	if(arrOfWords == NULL)
	{
		printf("Malloc call on line 139 was unable to allocate space, exiting program \n");
		exit(1);
	}
	
	// make sure array values are NULL
	int x = 0;
	for(x = 0; x < numOfWords; x++) 
	{
		arrOfWords[x] = NULL;
	}

	//see comments above for function explanation
	arrOfWords = splitAndShove(arrOfWords, argv[1]);
	arrOfWords = sortItOut(arrOfWords, numOfWords);


	//print out sorted list of words
	for(x = 0; x < numOfWords; x++) 
	{
		printf("%s \n", arrOfWords[x]);
	}

	//free all memory to prevent memory leaks
    for(x = 0; x < numOfWords; x++) 
	{
	   free(arrOfWords[x]);
	}
	free(arrOfWords);

	return 0;
}
