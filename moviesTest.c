/**************************************************************
* Author: Benjamin Hillen
* Date:   2 October 2020
*
* Description: Test bench for functions declared in movies.h
**************************************************************/

#include "movies.h"



int main(int argc, char* argv[]) {
	if (argc != 2){
		printf("Please provide a csv file\n");
		return 0;
	}

	FILE* csvFile = fopen(argv[1], "r");

	struct movie* head = createLinkedListMoviesFromCSV(csvFile);
	struct movie* temp = head;

	fclose(csvFile);

	while (temp != NULL) {
		printf("%s, %d, %.1f\n", temp->title, temp->year, temp->rating);
		head = head->next;
		removeNodeFromList(temp);
		temp = head;
	}

	return 0;
}
