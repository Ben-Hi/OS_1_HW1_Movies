/********************************************************************************************************************
* Author: Benjamin Hillen
* Date:   2 October 2020
* 
* Description: contains the main() function of the Movies program. This program reads a CSV file with movie data and
*			   creates a linked list of structs containing data for each movie. The program then presents a menu and
*			   asks the user to choose to filter and view movie data or to exit the program. The CSV file must be
*			   comma delimited and data must be stored in the file according to Assignment 1's formatting. 
*			   
*			   main() is used as flow control: implementation of the filtering and creation functions is done within
*			   movies.c nd declared in movies.h.
********************************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "movies.h"

#define FILTER_BY_YEAR 1
#define FILTER_BY_HIGHEST_RATING 2
#define FILTER_BY_LANGUAGE 3
#define EXIT 4

/***********************************
*		main(arc, argv[])
* Opens the movie .csv file for 
* reading and calls functions from
* movies.c to implement the
* Assignment 1 requirements.
***********************************/
int main(int argc, char* argv[]) {
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