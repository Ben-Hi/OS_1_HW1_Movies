/********************************************************************************************************************
* Author: Benjamin Hillen
* Date:   11 October 2020
*
* Description: Implementation of the Movies assignment. Contains functions that implement the menu, linked list and
*			   node creation, memory management, file parsing, and filtering.
********************************************************************************************************************/
#include "movies.h"

/****************************************************
* name: removeNodeFromList(struct movie*)
* desc: frees the memory allocated to a movie struct
*       node in a linked list.
* input: pointer to the movie node to be freed.
*****************************************************/
void removeNodeFromList(struct movie* movieNode) {
	int i;

	free(movieNode->title);

	/* Free the memory allocated to each language string*/
	for (i = 0; i < movieNode->numLanguages; i++) {
		free(movieNode->languages[i]);
	}

	free(movieNode->languages);
	free(movieNode);
}

/****************************************************
* name: freeLinkedList(struct movie*)
* desc: frees the memory allocated to a linked list.
* input: head pointer of the linked list.
*****************************************************/
void freeLinkedList(struct movie* head) {
	struct movie* temp = head;

	/* Free each node in the list*/
	while (temp != NULL) {
		head = head->next;
		removeNodeFromList(temp);
		temp = head;
	}
}

/****************************************************
* name: setMovieTitleFromString(struct movie*, char*)
* desc: sets the title string member of a movie 
*		struct.
* input: movie node to be set, title string.
*****************************************************/
void setMovieTitleFromString(struct movie* movieNode, char* titleString) {
	movieNode->title = (char*)calloc(strlen(titleString) + 1, sizeof(char));
	strcpy(movieNode->title, titleString);
}

/****************************************************
* name: setMovieYearFromString(struct movie*, char*)
* desc: sets the year int member of a movie
*		struct.
* input: movie node to be set, year string.
*****************************************************/
void setMovieYearFromString(struct movie* movieNode, char* movieYearString) {
	movieNode->year = atoi(movieYearString);
}

/****************************************************
* name: setMovieRatingFromString(struct movie*, char*)
* desc: sets the rating double member of a movie
*		struct.
* input: movie node to be set, rating string.
*****************************************************/
void setMovieRatingFromString(struct movie* movieNode, char* ratingString) {
	movieNode->rating = strtod(ratingString, NULL);
}

/****************************************************
* name: setMovieLanguagesFromString(struct movie*, char*)
* desc: sets the languages string array of a movie
*		struct.
* input: movie pointer to be set, language string.
*****************************************************/
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

	/* Allocate memory to the movie node language array*/
	movieNode->languages = (char**)calloc(count, sizeof(char*));
	movieNode->numLanguages = count;

	/* Parse the languages using "[:]" as delimiters, allocating memory to the language string*/
	token = strtok_r(currLine, "[;]", &languageSavePtr);
	while (token != NULL) {
		movieNode->languages[i] = (char*)calloc(strlen(token) + 1, sizeof(char));
		strcpy(movieNode->languages[i], token);

		i++;
		token = strtok_r(NULL, ";]", &languageSavePtr);
	}
}


/****************************************************
* name: creatMovieFromLine(char*)
* desc: takes a comma-delimited line and fills a new
*		movie node with data from the line. Returns
*		a pointer to the new node.
* input: comma-delimited string containing movie data.
****************************************************/
struct movie *createMovieFromLine(char* fileLine) {
	struct movie* movieNode = (struct movie*)malloc(sizeof(struct movie));

	char* savePtr;

	/* Retrieve the title token*/
	char* token = strtok_r(fileLine, ",", &savePtr);
	setMovieTitleFromString(movieNode, token);

	/* Retrieve the year token*/
	token = strtok_r(NULL, ",", &savePtr);
	setMovieYearFromString(movieNode, token);

	/* Retrieve the languages token*/
	token = strtok_r(NULL, ",", &savePtr);
	setMovieLanguagesFromString(movieNode, token);

	/* Retrieve the rating token*/
	token = strtok_r(NULL, "\n", &savePtr);
	setMovieRatingFromString(movieNode, token);

	movieNode->next = NULL;

	return movieNode;
}

/****************************************************
* name: createLinkedListMoviesFromCSV(FILE*, char*)
* desc: creates a singly linked list of movie pointers
*		from a .csv file. Returns a pointer to the
*		head of the linked list.
* input: pointer to .csv file opened to "r", name of
*		the .csv file.
****************************************************/
struct movie *createLinkedListMoviesFromCSV(FILE* movieFile, char* fileName) {
	int numMoviesRead = 0;

	char* nextFileLine = NULL;
	size_t len = 0;
	ssize_t numberOfCharsRead;

	struct movie* head = NULL;
	struct movie* tail = NULL;

	/* The first line has no movies, skip it*/
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

/****************************************************
* name: menu()
* desc: presents a menu to the user and prompts them
*		for input. Returns an int representing the
*		users choice.
****************************************************/
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

/****************************************************
* name: filterPrintYear(struct movie*)
* desc: asks the user for a year and prints the 
*		movies released in that year or informs them
*		if no movies were released in that year.
*input: head pointer of the movie linked list.
****************************************************/
void filterPrintYear(struct movie* head) {
	int yearFilter;
	int foundMoviesInYear = 0;

	struct movie* copy = head;

	/* Get user input*/
	printf("Enter the year for which you want to see movies: ");
	scanf("%d", &yearFilter);

	/* Iterate through the list and print any movies whose year matches the yearFilter*/
	while (copy != NULL) {

		if (copy->year == yearFilter) {
			printf("%s\n", copy->title);

			foundMoviesInYear = 1;
		}

		copy = copy->next;
	}

	/* Inform the user if no movies were found*/
	if (foundMoviesInYear == 0) {
		printf("No data about movies released in the year %d\n", yearFilter);
	}

	printf("\n");
}

/****************************************************
* name: filterPrintHighestRating(struct movie*)
* desc: prints the highest rated movie from every
*		year in the linked list.
*input: head pointer of the movie linked list.
****************************************************/
void filterPrintHighestRating(struct movie* head) {
	int i;
	int foundYearInArray;
	int numberOfUniqueYears = 0;
	int uniqueYearArr[120] = { 0 };
	struct movie* index = head;
	struct movie* highestRatedMovie;

	/* Find every unique year in the movie list and place it in the uniqueYearArr array*/
	while (index != NULL) {
		foundYearInArray = 0;

		/* The year was already in the array, move to the next node*/
		for (i = 0; i < 120; i++) {
			if (index->year == uniqueYearArr[i]) {
				foundYearInArray = 1;
				break;
			}
		}

		/* The year was not in the array, add it and move to the next node*/
		if (foundYearInArray == 0) {
			uniqueYearArr[numberOfUniqueYears] = index->year;
			numberOfUniqueYears++;
		}

		index = index->next;
	}

	index = head;

	/* Filter the list by each unique year and print the highest rated movie among the unique years*/
	for (i = 0; i < numberOfUniqueYears; i++) {
		highestRatedMovie = NULL;
		index = head;

		/* Check for the unique year*/
		while (index != NULL) {

			/* The first time the unique year is encountered, set highestRatedMovie to that node*/
			if (index->year == uniqueYearArr[i] && highestRatedMovie == NULL) {
				highestRatedMovie = index;
				index = index->next;
			}

			/* If a higher rated movie in the unique year is found, change highestRatedMovie to that movie*/
			else if (index->year == uniqueYearArr[i] && index->rating > highestRatedMovie->rating) {
				highestRatedMovie = index;
				index = index->next;
			}

			else {
				index = index->next;
			}
		}

		/* Print the highestRatedMovie*/
		printf("%d %.1f %s\n", highestRatedMovie->year, highestRatedMovie->rating, highestRatedMovie->title);
	}

	printf("\n");
}

/****************************************************
* name: filterPrintLanguage(struct movie*)
* desc: asks the user for a language and prints 
*		the movies released in that language.
*input: head pointer of the movie linked list.
****************************************************/
void filterPrintLanguage(struct movie* head) {
	struct movie* copy = head;
	copy = head;
	char languageFilter[20];
	int foundMovieWithLanguage = 0;
	int i;

	printf("Enter the language for which you want to see movies (note, the maximum length of a language is 20 characters: ");
	scanf("%s", languageFilter);

	/* Iterate through the list, print the year and title of movies with a language matching the languageFilter*/
	while (copy != NULL) {
		/* Check each language that the movie has*/
		for (i = 0; i < copy->numLanguages; i++) {
			if (strcmp(copy->languages[i], languageFilter) == 0) {
				printf("%d %s\n", copy->year, copy->title);

				foundMovieWithLanguage = 1;
			}
		}

		copy = copy->next;
	}

	if (foundMovieWithLanguage == 0) {
		printf("No data about movies released in %s\n", languageFilter);
	}

	printf("\n");
}