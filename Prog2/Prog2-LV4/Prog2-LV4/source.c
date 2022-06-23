#include "header.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int choice;
	while (1) {
		do {
			system("cls");
			printf("Unesite broj zadatka [1, 3] ili [0] za izlaz: ");
			if (scanf("%d", &choice) <= 0) exit(EXIT_FAILURE);
		} while (choice < 0 || choice > 3);
		switch (choice) {
		case 0: exit(EXIT_SUCCESS);
		case 1: task1(); break;
		case 2: task2(); break;
		case 3: task3(); break;
		}
	}
	return 0;
}