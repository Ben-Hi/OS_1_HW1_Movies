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
	int year;
	char** languages;
	double rating;
	struct movie* next;
};

void setMovieTitle(struct movie* movieNode, char* token) {
	movieNode->title = (char*)calloc(strlen(token) + 1, sizeof(char));
	strcpy(movieNode->title, token);

}

void setMovieYear(struct movie* movieNode, char* movieYear) {
	movieNode->year = atoi(movieYear);
}

void setMovieRating(struct movie* movieNode, char* ratingString) {
	movieNode->rating = strtod(ratingString, NULL);
}

int main(int argc, char* argv[]) {
	char* token = "The Avengers";
	char* year = "2015";
	char* rating = "9.5";

	struct movie* movieNode = (struct movie*)malloc(sizeof(struct movie));

	setMovieTitle(movieNode, token);
	setMovieYear(movieNode, year);
	setMovieRating(movieNode, rating);

	printf("The movie title is: %s\n", movieNode->title);
	printf("The movie year is: %d\n", movieNode->year);
	printf("The movie rating is: %.1f\n", movieNode->rating);

	free(movieNode->title);
	free(movieNode);

	return 0;
}

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

void test_formatLanguageStringArray() {
	int i = 0;
	char** languageArray = (char**)calloc(5, sizeof(char*));
	FILE* textFile = fopen("test.txt", "r");

	char* currLine = NULL;
	size_t len = 0;

	/* getline allocates memory to currLine*/
	getline(&currLine, &len, textFile);

	languageArray = formatLanguageStringArray(currLine, languageArray);

	printf("Here is the language array: \n");

	for (i = 0; i < 5; i++) {
		printf("%s ", languageArray[i]);
	}

	printf("\n");

	fclose(textFile);
	free(currLine);
	free(languageArray);
}