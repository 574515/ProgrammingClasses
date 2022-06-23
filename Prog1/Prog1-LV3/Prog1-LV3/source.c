#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define RYDBERG 10973731.568160

/*	1. Omogućiti korisniku unos dva znaka. Ispisati ih potom na ekran i njihove ASCII vrijednosti u oktalnom i
	heksadecimalnom brojevnom sustavu.
	2. Inicijalizirati četiri varijable različitih tipova podataka. Ispisati im vrijednosti na ekran i koliko
	bajta memorije zauzimaju.
	3. Kreirati na dva različita načina različite realne simboličke konstante napisane znanstvenom notacijom.
	Ispisati na ekran njihove vrijednosti i koliko bajta memorije zauzimaju. */

void first(void);
void second(void);
void third(void);

int main(void) {
	int choice;
	while (1) {
		do {
			system("cls");
			printf("[1] Prvi zadatak\n[2] Drugi zadatak\n[3] Treci zadatak\n[4] Izlaz\n\nIzbor: ");
			if (scanf("%d", &choice) <= 0) exit(EXIT_FAILURE);
		} while (choice < 1 || choice > 4);
		switch (choice) {
		case 1: first(); break;
		case 2: second(); break;
		case 3: third(); break;
		case 4: exit(EXIT_SUCCESS);
		}
	}
	return 0;
}

void first(void) {
	char x, y;
	system("cls");
	printf("Unesite prvi znak: ");
	if (scanf(" %c", &x) <= 0) exit(EXIT_FAILURE);
	printf("Unesite drugi znak: ");
	if (scanf(" %c", &y) <= 0) exit(EXIT_FAILURE);
	printf("\nZNAK\tASCII\n%c\t%x\n%c\t%x\n", x, x, y, y);
	if(_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

void second(void) {
	system("cls");
	char letter = 'X';
	short shrt = 32757;
	int number = 423;
	double decimal = 5311234.214;
	printf("Size of \"char\": %lu\nSize of \"short\": %lu\nSize of \"int\": %lu\nSize of \"double\": %lu\n", sizeof(letter), sizeof(shrt), sizeof(number), sizeof(decimal));
	if(_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

void third(void) {
	system("cls");
	const double faraday = 96485.33212;
	printf("VRIJEDNOST\t\tZAUZECE\n%E\t\t%lu\n%E\t\t%lu\n", RYDBERG, sizeof(RYDBERG), faraday, sizeof(faraday));
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}