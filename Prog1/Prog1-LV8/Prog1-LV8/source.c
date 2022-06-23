#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>

/*	1. Tražiti od korisnika unos jedne rečenice od maksimalno 200 znakova. Odrediti i na ekran ispisati broj riječi u rečenici.
	2. Tražiti od korisnika unos jednog stringa od maksimalno 50 znakova. Provjeriti i na ekran ispisati koliko se puta
	pojavljuje neka znamenka te na kojim mjestima.
	3. Omogućiti korisniku unos dva stringa od maksimalno 100 znakova. Ispisati na ekran onaj koji sadrži više samoglasnika.
	4. Omogućiti korisniku unos jednog stringa od maksimalno 75 znakova. Provjeriti i na ekran ispisati odgovarajuću poruku,
	ima li string oblik adrese e-pošte (sadrži znak @ i nakon njega tučku) */

void first(void);
void second(void);
void third(void);
int pobroji(char*);
void fourth(void);

int main(void) {
	int choice;
	while (1) {
		do {
			system("cls");
			printf("[1] Prvi zadatak\n[2] Drugi zadatak\n[3] Treci zadatak\n[4] Cetvrti zadatak\n[5] Izlaz\n\nIzbor: ");
			if (scanf("%d", &choice) <= 0) exit(EXIT_FAILURE);
		} while (choice < 1 || choice > 5);
		switch (choice) {
		case 1: first(); break;
		case 2: second(); break;
		case 3: third(); break;
		case 4: fourth(); break;
		case 5: exit(EXIT_SUCCESS);
		}
	}
	return 0;
}

void first(void) {	
	system("cls");
	int brojac = 0;
	char arr[201];
	printf("Unesite recenicu <0, 200]: ");
	if(getchar() <= 0) exit(EXIT_FAILURE);
	if(fgets(arr, 200, stdin) == NULL) exit(EXIT_FAILURE);
	for (int i = 0; arr[i] != '\0'; i++) if (arr[i] == ' ') brojac++;
	printf("\nRecenica ima %d rijeci.\n", (brojac + 1));
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

void second(void) {
	system("cls");
	char arr[51], trazenoLower = 'n', trazenoUpper = 'N';
	int i, brojac = 0;
	printf("Unesite string <0, 50]: ");
	if (getchar() <= 0) exit(EXIT_FAILURE);
	if(fgets(arr, 50, stdin) == NULL) exit(EXIT_FAILURE);
	for (i = 0; arr[i] != '\0'; i++) if (arr[i] == trazenoLower || arr[i] == trazenoUpper) brojac++;
	printf("\nZnak [%c / %c] se pojavljuje %d puta.\n", trazenoUpper, trazenoLower, brojac);
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

void third(void) {	
	system("cls");
	char firstOne[101], secondOne[101];
	printf("Unesite prvu recenicu <0, 100]: ");
	if (getchar() <= 0) exit(EXIT_FAILURE);
	if(fgets(firstOne, 100, stdin) == NULL) exit(EXIT_FAILURE);
	printf("Unesite drugu recenicu <0, 100]: ");
	if(fgets(secondOne, 100, stdin) == NULL) exit(EXIT_FAILURE);
	if (pobroji(firstOne) > pobroji(secondOne)) printf("\n%s", firstOne);
	else printf("\n%s", secondOne);
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

int pobroji(char* polje) {
	int i, j, brojac = 0;
	char samoglasnici[10] = { 'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U' };
	for (i = 0; polje[i] != '\0'; i++) {
		for (j = 0; j < 10; j++) {
			if (polje[i] == samoglasnici[j]) {
				brojac++;
				break;
			}
		}
	}
	return brojac;
}

void fourth(void) {
	system("cls");
	char arr[76];
	int i, monkey = (-1), tocka = (-1);
	printf("Unesite string <0, 75]: ");
	if (getchar() <= 0) exit(EXIT_FAILURE);
	if(fgets(arr, 75, stdin) == NULL) exit(EXIT_FAILURE);
	for (i = 0; arr[i] != '\0'; i++) {
		if (arr[i] == '@') monkey = i;
		if (arr[i] == '.') tocka = i;
	}
	if (tocka != (-1) && monkey != (-1) && tocka > monkey) printf("\nString je e-mail adresa.\n");
	else printf("\nString NIJE e-mail adresa.\n");
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}