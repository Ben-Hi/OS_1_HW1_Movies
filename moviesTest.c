/**************************************************************
* Author: Benjamin Hillen
* Date:   2 October 2020
*
* Description: Test bench for functions declared in movies.h
**************************************************************/

#include "movies.h"

int main(int argc, char* argv[]) {
	int choice = menu();

	printf("You chose %d\n", choice);

	return 0;
}