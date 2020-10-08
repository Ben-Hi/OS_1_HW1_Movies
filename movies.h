/**************************************************************
* Author: Benjamin Hillen
* Date:   2 October 2020
*
* Description: Declaration of functions required to implement
*			   Assignment 1.
**************************************************************/
#ifndef MOVIES_H
#define MOVIES_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Each movie has a title, a year, a list of languages, a rating,
 * and a pointer to the next movie in the list
 */
struct movie {
	char* title;
	int year;
	char** languages;
	double rating;
	struct movie* next;
};

void setMovieTitleFromString(struct movie* movieNode, char* token);

void setMovieYearFromString(struct movie* movieNode, char* movieYear);

void setMovieRatingFromString(struct movie* movieNode, char* ratingString);

char** formatLanguageStringArray(char*, char**);

struct movie *createMovieFromLine(char*);

struct movie *createLinkedListMoviesFromCSV(FILE*);

int menu();


#endif