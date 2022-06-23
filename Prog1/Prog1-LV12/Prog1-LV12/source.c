#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <float.h>

/*	1. Napisati funkciju koja će vrijednost varijable (cijeli broj) koja joj se preda kao argument uvećati za jedan, u slučaju
	da je pozitivna ili umanjiti za jedan u slučaju da je negativna. Funkcija ne treba ništa vratiti nego treba promjenu
	načiniti na predanoj joj varijabli. Na primjeru u main() funkciji pokazati uporabu napisane funkcije.
	2. Napisati funkciju koja će izračunati i vratiti srednju vrijednost elemenata polja realnih brojeva. Na primjeru u main()
	funkciji pokazati uporabu napisane funkcije.
	3. Napisati funkciju koja će pronaći i vratiti najveću vrijednost elementa polja realnih brojeva. Na primjeru u main()
	funkciji pokazati uporabu napisane funkcije.
	4. Napisati funkciju koja će odrediti i vratiti koliko se puta u danom stringu pojavljuje traženo slovo. Traženo slovo
	također se predaje kao argument funkciji. Na primjeru u main() funkciji pokazati uporabu napisane funkcije. */

void first(void);
void incrementOrDecrement(int*);
void second(void);
float findAverage(float*, int);
void third(void);
float findMax(float*, int);
void fourth(void);
int letterOccurrence(char*, char);

int main(void) {
	srand((unsigned)time(NULL));
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
	int n;
	printf("Unesite n: ");
	if (scanf("%d", &n) <= 0) exit(EXIT_FAILURE);
	incrementOrDecrement(&n);
	printf("\nUneseni broj je promijenjen na %d.\n", n);
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

void incrementOrDecrement(int* ptr) {
	if (*ptr < 0) (*ptr)--;
	else if (*ptr > 0) (*ptr)++;
}

void second(void) {
	system("cls");
	float* arr, dg = (-20.0f), gg = 20.0f;
	int i, n = 100;
	arr = malloc(n * sizeof(float));
	if (!arr) exit(EXIT_FAILURE);
	for (i = 0; i < n; i++) *(arr + i) = dg + (float)rand() / RAND_MAX * (gg - dg);
	printf("\n\nSrednja vrijednost polja je %.2f.\n", findAverage(arr, n));
	free(arr);
	_CrtDumpMemoryLeaks();
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

float findAverage(float* arr, int n) {
	float avg = 0.0f;
	for (int i = 0; i < n; i++) avg += *(arr + i);
	return (avg / n);
}

void third(void) {
	system("cls");
	float* arr, dg = (-50.0f), gg = 50.0f;
	int i, n = 1000;
	arr = malloc(n * sizeof(float));
	if (!arr) exit(EXIT_FAILURE);
	for (i = 0; i < n; i++) *(arr + i) = dg + (float)rand() / RAND_MAX * (gg - dg);
	printf("\n\nNajveca vrijednost polja je %.2f.\n", findMax(arr, n));
	free(arr);
	_CrtDumpMemoryLeaks();
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

float findMax(float* arr, int n) {
	float max = FLT_MIN;
	for (int i = 0; i < n; i++) if (*(arr + i) > max) max = *(arr + i);
	return max;
}

void fourth(void) {
	system("cls");
	char arr[101], letter = 'c';
	printf("Unesite string <0, 100]: ");
	if (getchar() <= 0) exit(EXIT_FAILURE);
	if (fgets(arr, 100, stdin) == NULL) exit(EXIT_FAILURE);
	printf("\nU unesenm stringu se slovo %c pojavljuje %d puta.\n", letter, letterOccurrence(arr, letter));
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

int letterOccurrence(char* arr, char letter) {
	int i, counter = 0;
	for (i = 0; *(arr + i) != '\0'; i++) if (*(arr + i) == letter) counter++;
	return counter;
}