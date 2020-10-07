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

/*Each movie has a title, a year, a list of languages, and a rating*/
struct movie {
	char* title;
	int year;
	char* languages;
	int rating;
};

struct movie *createMovieFromLine(char* currentLine);

void readMoviesFromCSV(FILE* movieFile);

int menu();


#endif