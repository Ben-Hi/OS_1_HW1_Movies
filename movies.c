/**************************************************************
* Author: Benjamin Hillen
* Date:   2 October 2020
*
* Description: Implementation of functions defined in movies.h
**************************************************************/
#include "movies.h"

char** formatLanguageStringArray(char* token) {
	char* languageSavePtr;
	char* unformattedArrayToken;
	char** languageArray;
	int i = 0;

	/* Remove the '[' character*/
	strcpy(unformattedArrayToken, token + 1);

	/* Remove the ']' character*/
	unformattedArrayToken[strlen(unformattedArrayToken) - 1] = '\0';

	while (token != NULL) {
		if (i == 0) {
			token = strtok_r(unformattedArrayToken, ";", &languageSavePtr);
			languageArray[i] = &token;
		}

		else {
			token = strtok_r(NULL, ";", &languageSavePtr);
			languageArray[i] = &token;
		}

		i++;
	}
}


struct movie *createMovieFromLine(char* fileLine) {
	/* //create new movie node
	*     //parse line into tokens
	*     //put tokens into new movie node
	*/
	struct movie* movieNode = (struct movie*)malloc(sizeof(struct movie));
	char* savePtr;

	/* Retrieve the title token*/
	char* token = strtok_r(fileLine, ",", &savePtr);
	movieNode->title = (struct movie*)calloc(strlen(token) + 1, sizeof(char));
	strcpy(movieNode->title, token);

	/* Retrieve the Year token*/
	token = strtok_r(NULL, ",", &savePtr);
	movieNode->year = (int*)malloc(sizeof(int));
	movieNode->year = atoi(token);

	/* Retrieve the Languages token*/
	movieNode->languages = (char**)malloc(5 * sizeof(char*));

	for (int i = 0; i < 5; i++) {
		movieNode->languages[i] = (char*)malloc(20 * sizeof(char));
	}

	token = strtok_r(NULL, ",", &savePtr);

	movieNode->languages = formatLanguageStringArray(token);

	/* Retrieve the Rating token*/
	token = strtok_r(NULL, "\n", &savePtr);
	movieNode->rating = (double*)malloc(sizeof(double));
	movieNode->rating = strtod(token, NULL);

	movieNode->next = NULL;

	return movieNode;
}

struct movie *createLinkedListMoviesFromCSV(FILE* movieFile) {
	/* //Get movie info from .csv file
	*    //create movie nodes from each file line
	*/

	char* nextFileLine = NULL;
	size_t len = 0;
	ssize_t numberOfCharsRead;
	char* token;

	struct movie* head = NULL;
	struct movie* tail = NULL;

	/* The first line has no movies*/
	getline(&nextFileLine, &len, movieFile);

	/* Make movie nodes and link them until there are no more lines in the file*/
	while ((numberOfCharsRead = getline(&nextFileLine, &len, movieFile)) != -1) {
		struct movie* newMovieNode = createMovieFromLine(nextFileLine);

		/*This is the first node of the linked list*/
		if (head == NULL) {
			head = newMovieNode;
			tail = head;
		}

		/*Add the new node to the list and adjust the tail*/
		else {
			tail->next = newMovieNode;
			tail = newMovieNode;
		}
	}

	free(nextFileLine);
	fclose(movieFile);

	return head;
}

/*
* menu()
* desc: presents a menu to the user and prompts for input
* pre:
* input:
* output: int from 1 to 4 representing user choice
* 
*/
int menu() {
	/* //Present Menu and get input
	*   //1. Show movies released in the specified year
	*     //filter linked list for movie.year == specified year
	*     //print "movie.title"
	* 
	*   //2. Show highest rated movie for each year
	*     //loop through each year
	*       //loop through each movie, find movie.rating == max
	*       //print "movie.year movie.rating movie.title"
	* 
	*   //3. Show movies and their year of release for a specific language
	*     //filter linked list for movie.language == specified language
	*     //print "movie.year movie.title"
	* 
	*   //4. Exit
	*/
	int choice;

	printf("1. Show movies released in the specified year\n");
	printf("2. Show highest rated movie for each year\n");
	printf("3. Show movies and their year of release for a specific language\n");
	printf("4. Exit\n\n");

	printf("Enter a choice from 1 to 4: ");
	scanf("%d", &choice);
	printf("\n");

	return choice;
}