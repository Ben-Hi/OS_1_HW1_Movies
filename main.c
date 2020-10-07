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
	* //Get movie info from .csv file
	*   //open file
	* 
	*   //read file line by line
	*     //create new movie node
	*     //parse line into tokens
	*     //put tokens into new movie node
	*     //place node into linked list
	*     //move to next line
	* 
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
	int choice = 0;
	FILE* movieFile;

	/*Check if file can be opened*/
	if (!(movieFile = open(argv[1]))) {
		printf("Could not open file.\n");
		return 0;
	}

	readMoviesFromCSV(movieFile);

	while ((choice = menu()) != EXIT) {

		switch (choice) {

		case FILTER_BY_YEAR:
			printMoviesInYear();
			break;

		case FILTER_BY_HIGHEST_RATING:
			printHighestRatingPerYear();
			break;

		case FILTER_BY_LANGUAGE:
			printMoviesInSpecifiedLanguage();
			break;

		case EXIT:
			break;
		}
	}

	return 0;
}