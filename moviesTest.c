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

	int i;

	FILE* csvFile = fopen(argv[1], "r");

	struct movie* head = createLinkedListMoviesFromCSV(csvFile, argv[1]);
	struct movie* temp = head;

	fclose(csvFile);

	while (temp != NULL) {
		printf("%s, %d, %.1f ", temp->title, temp->year, temp->rating);

		for (i = 0; i < temp->numLanguages; i++) {
			printf("%s ", temp->languages[i]);
		}

		printf("\n");
		head = head->next;
		removeNodeFromList(temp);
		temp = head;
	}

	return 0;
}
