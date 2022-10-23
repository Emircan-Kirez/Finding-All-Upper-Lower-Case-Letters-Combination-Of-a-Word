/* Emircan KİREZ - Ch3rry */
/* Last Update: 18/09/2022 */
/*
----------------------- INFORMATION ---------------------------
• It is recommended to read the README.md file before proceeding to the project.
• For any questions and suggestions related to the project, via the e-mail address "emircan200123@hotmail.com", you can contact me by
typing "Github | C-EN / Finding All Upper & Lower Case Letters Combination Of a Word" to the subject line 
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int *createIndexArray(int size);
char *createLettersArray(char *word);
void printFile(char *letters, int *index, int size, FILE *fPtr);
void checkAndUpdate(int i, int *index, int size);

int main(){
	char word[20];
	printf("Write a word: ");
	scanf("%s", word);

	int size = strlen(word);
	char *letters = createLettersArray(word); // array where I store the word in both lowercase and uppercase letters
	int *index = createIndexArray(size); // It stores which indexes we will use from the letters array
	
	FILE *fPtr = fopen("combinations.txt", "w"); 

	int i;
	int limit = pow(2, size);
	for(i = 1; i <= limit; i++){
		printFile(letters, index, size, fPtr);
		checkAndUpdate(i, index, size);	
	}

	// Final actions to be taken
	fclose(fPtr);
	free(index);
	free(letters);
	return 0;
}

int *createIndexArray(int size){
	int i;
	int *array = (int *)malloc(sizeof(int) * size);
	for(i = 0; i < size; i++){
		array[i] = i;
	}
	return array;
}

char *createLettersArray(char *word){
	int i, size = strlen(word), limit = size * 2;
	char *array = (char *)malloc(sizeof(char) * limit);
	
	for(i = 0; i < size; i++){ // add lowercase letters
		array[i] = word[i];
	}

	for(; i < limit; i++){ // capitalize letters and add to the array
		array[i] = toupper(word[i % size]);
	}
	return array;
}

void printFile(char *letters, int *index, int size, FILE *fPtr){
	int i;
	for(i = 0; i < size; i++)
		fputc(letters[index[i]], fPtr); // writes to a file char by char
	fprintf(fPtr, "\n");
}

void checkAndUpdate(int iteration, int *index, int size){
	// I thought of the logic we used to construct the truth table and I used it here
	/* 
       	0 0 0 // The ones digit changes with each iteration
		0 0 1 // The 2's digit changes every 2 iterations
		0 1 0 // The 4's digit changes every 4 iterations and so on
		0 1 1
		1 0 0
	*/

	int multiplier = 1;
	int j;
	for(j = size - 1; j >= 0; j--){ // check whether change is needed for all indexes
		if(iteration % multiplier == 0) // iteration check for each index - if true then change time
			if(index[j] == j) // if it's itself, make it uppercase - so I created an array of lowercase and uppercase letters (letters).
				index[j] += size;
			else // if it's not, make it lowercase
				index[j] = j;
		multiplier *= 2;
	}
}
