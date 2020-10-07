/**************************************************************
* Author: Benjamin Hillen
* Date:   2 October 2020
*
* Description: Implementation of functions defined in movies.h
**************************************************************/
#include "movies.h"


createMovieFromLine(char* fileLine) {
	/* //create new movie node
	*     //parse line into tokens
	*     //put tokens into new movie node
	*/
}

void readMoviesFromCSV(FILE* movieFile) {
	/* //Get movie info from .csv file
	*    //create movie nodes from each file line
	*/

	char* nextFileLine = NULL;
	size_t len = 0;
	ssize_t numberOfCharsRead;
	char* token;

	while ((numberOfCharsRead = getline(&nextFileLine, &len, movieFile)) != -1) {
		struct movie* newMovieNode = createMovieFromLine(nextFileLine);
	}
}

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
}