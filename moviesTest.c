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
char** formatLanguageStringArray(char* token) {
	char* languageSavePtr;
	char* unformattedArrayToken;
	char** languageArray = (char**)calloc(5,sizeof(char*));
	int i = 0;

	unformattedArrayToken = strtok_r(token, "[", &languageSavePtr);

	unformattedArrayToken = strtok_r(NULL, "]", &languageSavePtr);

	/*
	token[strlen(token) - 1] = '\0';

	strcpy(token, token + 1);

	printf("Here is the array before formatting: %s\n", token);
	*/
	while (i != 4) {
		if (i == 0) {
			unformattedArrayToken = strtok_r(NULL, ";", &languageSavePtr);
			languageArray[i] = unformattedArrayToken;
		}

		else {
			unformattedArrayToken = strtok_r(NULL, ";", &languageSavePtr);
			languageArray[i] = unformattedArrayToken;
		}

		i++;
	}

	printf("Here is the language array of the helper function: %s\n", token);
	return languageArray;
}

int main(int argc, char* argv[]) {
	int i = 0;
	char** languageArray;

	char* token = "[English;Spanish;Chinese;Portugese]";

	languageArray = formatLanguageStringArray(token);

	printf("Here is the language array: \n");

	for (i = 0; i < 4; i++) {
		printf("%s ", languageArray[i]);
	}

	printf("\n");

	free(languageArray);

	return 0;
}