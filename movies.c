/**************************************************************
* Author: Benjamin Hillen
* Date:   2 October 2020
*
* Description: Implementation of functions defined in movies.h
**************************************************************/
#include "movies.h"

#define LANGUAGE_ARR_SIZE 5

void removeNodeFromList(struct movie* movieNode) {
	int i;

	free(movieNode->title);

	for (i = 0; i < movieNode->numLanguages; i++) {
		free(movieNode->languages[i]);
	}

	free(movieNode->languages);
	free(movieNode);
}

void freeLinkedList(struct movie* head) {
	struct movie* temp = head;

	while (temp != NULL) {
		head = head->next;
		removeNodeFromList(temp);
		temp = head;
	}
}

void setMovieTitleFromString(struct movie* movieNode, char* titleString) {
	movieNode->title = (char*)calloc(strlen(titleString) + 1, sizeof(char));
	strcpy(movieNode->title, titleString);
}

void setMovieYearFromString(struct movie* movieNode, char* movieYearString) {
	movieNode->year = atoi(movieYearString);
}

void setMovieRatingFromString(struct movie* movieNode, char* ratingString) {
	movieNode->rating = strtod(ratingString, NULL);
}

/*
* name: formatLanguageStringArray(char*, char**)
* desc: takes the raw movie language string and a dynamic array of strings
*		and parses the languages to construct an array of strings for the
*		movie node.
* pre: movie language string enclosed by [], allocated array of strings
* return: array of language strings
*/
void setMovieLanguagesFromString(struct movie* movieNode, char* currLine) {
	int i;
	int count = 0;
	char* languageSavePtr;
	char* token;

	/* If the language line has more characters than '[' and ']', check how many languages there are*/
	if (strlen(currLine) > 2) {
		count = 1;

		for (i = 0; i < strlen(currLine); i++) {
			char element = currLine[i];

			if (element == ';') {
				count++;
			}
		}
	}

	/* If the movie has no languages, note that and return*/
	else {
		movieNode->numLanguages = 0;
		return;
	}

	i = 0;

	/* Allocate memory to the movie node language arra*/
	movieNode->languages = (char**)calloc(count, sizeof(char*));
	movieNode->numLanguages = count;

	/* Parse the languages using ";}" as delimiters, allocating memory to the language string*/
	token = strtok_r(currLine, "[;]", &languageSavePtr);
	while (token != NULL) {
		movieNode->languages[i] = (char*)calloc(strlen(token) + 1, sizeof(char));
		strcpy(movieNode->languages[i], token);

		i++;
		token = strtok_r(NULL, ";]", &languageSavePtr);
	}
}


/*
* name: creatMovieFromLine(char*)
* desc: takes a comma-delimited line and fills a new movie node
*		with data from the line
* pre:  comma-delimited string from .csv file
* return: new movie node with next pointing to NULL
*/
struct movie *createMovieFromLine(char* fileLine) {
	struct movie* movieNode = (struct movie*)malloc(sizeof(struct movie));

	char* savePtr;

	/* Retrieve the title token*/
	char* token = strtok_r(fileLine, ",", &savePtr);
	setMovieTitleFromString(movieNode, token);

	/* Retrieve the Year token*/
	token = strtok_r(NULL, ",", &savePtr);
	setMovieYearFromString(movieNode, token);

	/* Retrieve the Languages token*/
	token = strtok_r(NULL, ",", &savePtr);
	setMovieLanguagesFromString(movieNode, token);

	/* Retrieve the Rating token*/
	token = strtok_r(NULL, "\n", &savePtr);
	setMovieRatingFromString(movieNode, token);

	movieNode->next = NULL;

	return movieNode;
}

/*
* name: createLinkedListMoviesFromCSV(FILE*)
* desc: forms a singly linked list of struct movie pointers
*		from a specifically formatted .csv file
* pre:  .csv file opened in read-only mode
* return: pointer to head of linked list of movie structs
*/
struct movie *createLinkedListMoviesFromCSV(FILE* movieFile, char* fileName) {
	/* //Get movie info from .csv file
	*    //create movie nodes from each file line
	*/

	int numMoviesRead = 0;

	char* nextFileLine = NULL;
	size_t len = 0;
	ssize_t numberOfCharsRead;

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

		numMoviesRead++;
	}

	printf("Processed file %s and parsed data for %d movies\n\n", fileName, numMoviesRead);

	free(nextFileLine);

	return head;
}

/*
* name: menu()
* desc: presents a menu to the user and prompts for input
* pre:
* return: int from 1 to 4 representing user choice
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

void filterPrintYear(struct movie* head) {
	int yearFilter;

	struct movie* copy = head;

	printf("Here are all the movies I have in the list: \n\n");

	while (copy != NULL) {
		printf("%s, %d\n", copy->title, copy->year);

		copy = copy->next;
	}

	printf("\n");
	copy = head;

	printf("Enter the year for which you want to see movies: ");
	scanf("%d", &yearFilter);

	/* Iterate through the list and print any movies whose year matches the yearFilter*/
	while (copy != NULL) {

		if (copy->year == yearFilter) {
			printf("%s\n", copy->title);
		}

		copy = copy->next;
	}

	printf("\n");
}

void filterPrintHighestRating(struct movie* head) {

}

void filterPrintLanguage(struct movie* head) {
	struct movie* copy = head;

	int i;

	char languageFilter[20];

	while (copy != NULL) {
		printf("%s, %s %s %s %s %s\n", copy->title, copy->languages[0], copy->languages[1], copy->languages[2], copy->languages[3], copy->languages[4]);

		copy = copy->next;
	}

	copy = head;
	printf("Enter the language for which you want to see movies (note, the maximum length of a language is 20 characters: ");
	scanf("%s", languageFilter);

	/* Iterate through the list, print the year and title of movies with a language matching the languageFilter*/
	while (copy != NULL) {
		for (i = 0; i < LANGUAGE_ARR_SIZE; i++) {
			if (strcmp(copy->languages[i], languageFilter) == 0) {
				printf("%d %s\n", copy->year, copy->title);
			}
		}

		copy = copy->next;
	}

	printf("\n");
}