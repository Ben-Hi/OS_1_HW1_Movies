/********************************************************************************************************************
* Author: Benjamin Hillen
* Date:   11 October 2020
*
* Description: Declaration of functions required to implement Assignment 1. Contains functions that implement the menu,
*			   linked list and node creation, memory management, file parsing, and filtering.
********************************************************************************************************************/
#ifndef MOVIES_H
#define MOVIES_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***************************************************************** 
*							struct movie
 * Each movie has a title, a year, a list of languages, a rating,
 * and a pointer to the next movie in the list. Serves as a node
 * in the linked list.
 ****************************************************************/
struct movie {
	char* title;
	int year;
	char** languages;
	int numLanguages;
	double rating;
	struct movie* next;
};

/******************************************
*			Setter Functions
******************************************/
void setMovieTitleFromString(struct movie*, char*);
void setMovieYearFromString(struct movie*, char*);
void setMovieRatingFromString(struct movie*, char*);
void setMovieLanguagesFromString(struct movie*, char*);

/******************************************
*			Memory Management
******************************************/
void removeNodeFromList(struct movie*);
void freeLinkedList(struct movie*);

/******************************************
*			Linked List Creation
******************************************/
struct movie *createMovieFromLine(char*);
struct movie *createLinkedListMoviesFromCSV(FILE*, char*);

/******************************************
*				Filters
******************************************/
void filterPrintYear(struct movie*);
void filterPrintHighestRating(struct movie*);
void filterPrintLanguage(struct movie*);

/******************************************
*				  Menu
******************************************/
int menu();

#endif