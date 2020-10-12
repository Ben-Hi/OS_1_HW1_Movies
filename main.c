/**************************************************************
* Author: Benjamin Hillen
* Date:   2 October 2020
* 
* Description: contains the main() function of the Movies
*			   program. Implements the Assignment requirements.
**************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "movies.h"

#define FILTER_BY_YEAR 1
#define FILTER_BY_HIGHEST_RATING 2
#define FILTER_BY_LANGUAGE 3
#define EXIT 4

int main(int argc, char* argv[]) {
	/****************************************
	*   //close file
	*   //"Processed file XYZ and parsed data for M movies"
	*  
	* //Present Menu and get input
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
	struct movie* head;

	int choice = 0;
	FILE* movieFile;

	/* Check if user provided a single file to parse*/
	if (argc != 2) {
		printf("Please enter a .csv file when running the program.\n");
		return 0;
	}
	
	/* Check if the file can be opened*/
	if (!(movieFile = fopen(argv[1], "r"))) {
		printf("Could not open file.\n");
		return 0;
	}

	/* Parse the file and get the linked list*/
	head = createLinkedListMoviesFromCSV(movieFile, argv[1]);
	fclose(movieFile);

	/* Present the menu until the user chooses to exit*/
	while (1) {
		choice = menu();

		/* Check if the user entered an invalid option*/
		if (choice > EXIT || choice < FILTER_BY_YEAR) {
			printf("That is not a valid menu option, please try again\n");
		}

		/* Perform the desired operation*/
		else{
			switch (choice) {

			case FILTER_BY_YEAR:
				filterPrintYear(head);
				break;

			case FILTER_BY_HIGHEST_RATING:
				filterPrintHighestRating(head);
				break;

			case FILTER_BY_LANGUAGE:
				filterPrintLanguage(head);
				break;

			case EXIT:
				freeLinkedList(head);
				return 0;
			}
		}
	}
}