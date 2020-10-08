/**************************************************************
* Author: Benjamin Hillen
* Date:   2 October 2020
*
* Description: Test bench for functions declared in movies.h
**************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*#include "movies.h"
*/

struct movie {
	char* title;
	int* year;
	char** languages;
	double* rating;
	struct movie* next;
};

char** formatLanguageStringArray(char* currLine, char** languageArray) {
	int i;
	char* languageSavePtr;
	char* savePtrTwo;

	char* token = strtok_r(currLine, "[", &languageSavePtr);

	char* formattedLine = strtok_r(token, "]", &savePtrTwo);


	for (i = 0; i < 5; i++) {
		if (i == 0) {
			token = strtok_r(token, ";", &savePtrTwo);
		}
		else {
			token = strtok_r(NULL, ";", &savePtrTwo);
		}

		languageArray[i] = token;
	}

	return languageArray;
}

int main(int argc, char* argv[]) {
	int i = 0;
	char** languageArray = (char**)calloc(5, sizeof(char*));
	FILE* textFile = fopen("test.txt", "r");

	char* currLine = NULL;
	size_t len = 0;
	ssize_t nread;

	nread = getline(&currLine, &len, textFile);
	
	languageArray = formatLanguageStringArray(currLine, languageArray);

	printf("Here is the language array: \n");

	for (i = 0; i < 5; i++) {
		printf("%s ", languageArray[i]);
	}

	printf("\n");

	fclose(textFile);
	free(languageArray);

	return 0;
}