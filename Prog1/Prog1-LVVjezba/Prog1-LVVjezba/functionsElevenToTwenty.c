#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <float.h>

/*	Napisati C program koji će učitati string. U zadanom stringu pronaći koliko ima riječi koje počinju s
	velikim slovom (riječi su razdvojene razmakom). */

void task11(void) {
	system("cls");
	char* arr;
	int i, counter = 0;
	arr = calloc(101, sizeof(char));
	if (!arr) exit(EXIT_FAILURE);
	printf("Unesite string [1, 100]: ");
	if (getchar() <= 0) exit(EXIT_FAILURE);
	if (fgets(arr, 100, stdin) == NULL) exit(EXIT_FAILURE);
	if (*(arr + 0) > 64 && *(arr + 0) < 91) counter++;
	for (i = 1; *(arr + i) != '\0'; i++) if (*(arr + i) == ' ' && (*(arr + i + 1) > 64 && *(arr + i + 1) < 91)) counter++;
	printf("\nBroj rijeci u zadanom stringu koje pocinju velikim slovom je %d.\n", counter);
	free(arr);
	_CrtDumpMemoryLeaks();
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

/*	Napisati C program koji će učitati string. Izračunati i na ekran ispisati koliko različitih znakova je
	korišteno u tom stringu. 32-126*/

void task12(void) {
	system("cls");
	char* arr;
	int i, j, counter = 0;
	arr = calloc(101, sizeof(char));
	if (!arr) exit(EXIT_FAILURE);
	printf("Unesite string [1, 100]: ");
	if (getchar() <= 0) exit(EXIT_FAILURE);
	if (fgets(arr, 100, stdin) == NULL) exit(EXIT_FAILURE);
	for (i = 32; i < 127; i++) {
		for (j = 0; *(arr + j) != '\0'; j++) {
			if (*(arr + j) == i) {
				counter++;
				break;
			}
		}
	}
	printf("\nU zadanom stringu je koristeno %d razlicitih znakova.\n", counter);
	free(arr);
	_CrtDumpMemoryLeaks();
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

/*	Napisati C program koji će učitati string. U string treba učitavati samo znakove 'a' i 'b'. Na ekran ispisati
	postoji li u zadanom stringu podstring “abba” i ako postoji na kojem mjestu u stringu se on pojavljuje. Ako se
	pojavi u stringu bilo koji drugi znak, ispisati na ekran poruku o grešci. */

void task13(void) {
	system("cls");
	char* arr, c;
	int i = 0, tempIndx = (-1);
	arr = calloc(21, sizeof(char));
	if (!arr) exit(EXIT_FAILURE);
	printf("Unesite string od 20 znakova: ");
	if (getchar() <= 0) exit(EXIT_FAILURE);
	do {
		c = _getch();
		putchar(c);
		if (c == 'a' || c == 'b') {
			*(arr + i) = c;
			i++;
		}
		else printf("\nNetocan unos. Ponovite: ");
	} while (i < 20);
	for (int i = 0; i < 18; i++) {
		if (*(arr + i) == 'a' && *(arr + i + 1) == 'b' && *(arr + i + 2) == 'b' && *(arr + i + 3) == 'a') {
			tempIndx = i;
			break;
		}
	}
	if (tempIndx != (-1)) printf("\n\nPodstring \"abba\" pronadjen na indeksu %d.\n", tempIndx);
	else printf("\n\nPodstring \"abba\" nije pronadjen u unesenom stringu.\n");
	free(arr);
	_CrtDumpMemoryLeaks();
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

/*	Napisati C program koji će s tipkovnice prvo učitati prirodni broj m koji mora biti između 2 i 10. Nakon toga
	učitati mxm realnih brojeva u matricu A. Pretpostaviti da u matricu može stati najviše 10x10 brojeva. Pronaći
	i na ekran ispisati sumu svakog retka matrice i produkt svakog stupca matrice. */

void task14(void) {
	system("cls");
	int i, j, m;
	float** arr, sum, product;
	do {
		printf("Unesite m [2, 10]: ");
		if (scanf("%d", &m) <= 0) exit(EXIT_FAILURE);
	} while (m < 2 || m > 10);
	arr = malloc(m * sizeof(float*));
	if (!arr)exit(EXIT_FAILURE);
	for (i = 0; i < m; i++) {
		*(arr + i) = malloc(m * sizeof(float));
		if (!*(arr + i)) exit(EXIT_FAILURE);
	}
	for (i = 0; i < m; i++) {
		for (j = 0; j < m; j++) {
			printf("Unos [%d, %d]: ", i, j);
			if (scanf("%f", &(*(*(arr + i) + j))) <= 0) exit(EXIT_FAILURE);
		}
	}
	printf("\n");
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) printf("%.2f ", *(*(arr + i) + j));
		printf("\n");
	}
	printf("\n");
	for (i = 0; i < m; i++) {
		sum = 0.0f;
		for (j = 0; j < m; j++) sum += *(*(arr + i) + j);
		printf("Suma %d. retka je %.2f.\n", (i + 1), sum);
	}
	printf("\n");
	for (i = 0; i < m; i++) {
		product = 1.0f;
		for (j = 0; j < m; j++) product *= *(*(arr + j) + i);
		printf("Produkt %d. stupca je %.2f.\n", (i + 1), product);
	}
	for (i = 0; i < m; i++) free(*(arr + i));
	free(arr);
	_CrtDumpMemoryLeaks();
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

/*	Napisati C program koji će učitati 20 realnih brojeva u vektor. Izračunati i ispisati na ekran aritmetičku
	i geometrijsku sredinu ovih brojeva. Također ispisati i sve brojeve u vektoru koji su u intervalu između
	aritmetičke i geometrijske sredine. */

void task15(void) {
	system("cls");
	int i;
	double* arr, arithmeticMean = 0, geometricMean = 1, tempAM, tempGM;
	arr = malloc(20 * sizeof(double));
	if (!arr)exit(EXIT_FAILURE);
	for (i = 0; i < 20; i++) {
		system("cls");
		printf("Unos [%d / 20]: ", (i + 1));
		if (scanf("%lf", &(*(arr + i))) <= 0) exit(EXIT_FAILURE);
		arithmeticMean += *(arr + i);
		geometricMean *= *(arr + i);
	}
	tempAM = arithmeticMean / 20;
	tempGM = pow(geometricMean, (float)1 / 20);
	printf("\nGeometrijska sredina je %lf.", tempGM);
	printf("\nAritmeticka sredina je %lf.\n\nBrojevi koji su u intervalu <GM, AM>:\n", tempAM);
	for (i = 0; i < 20; i++) if ((*(arr + i) > tempGM) && (*(arr + i) < tempAM)) printf("%lf ", *(arr + i));
	free(arr);
	_CrtDumpMemoryLeaks();
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

/*	Napisati C program koji će s tipkovnice prvo učitati prirodni broj m koji mora biti između 2 i 10. Nakon toga
	učitati mxm realnih brojeva u matricu A. Pretpostaviti da u matricu može stati najviše 10x10 brojeva. Pronaći
	i na ekran ispisati najveći broj u matrici A i njegovo mjesto u matrici (broj retka i stupca). */

void task16(void) {
	system("cls");
	int i, j, m, tempI, tempJ;
	float** arr, maxNum = FLT_MIN;
	do {
		printf("Unesite m [2, 10]: ");
		if (scanf("%d", &m) <= 0) exit(EXIT_FAILURE);
	} while (m < 2 || m > 10);
	arr = malloc(m * sizeof(float*));
	if (!arr) exit(EXIT_FAILURE);
	for (i = 0; i < m; i++) {
		*(arr + i) = malloc(m * sizeof(float));
		if (!*(arr + i)) exit(EXIT_FAILURE);
	}
	for (i = 0; i < m; i++) {
		for (j = 0; j < m; j++) {
			system("cls");
			printf("Unos [%d, %d]: ", i, j);
			if (scanf("%f", &(*(*(arr + i) + j))) <= 0) exit(EXIT_FAILURE);
			if (*(*(arr + i) + j) > maxNum) {
				maxNum = *(*(arr + i) + j);
				tempI = i;
				tempJ = j;
			}
		}
	}
	printf("\nNajveci broj u matrici [%f] se nalazi na indeksu [%d, %d].\n", maxNum, tempI, tempJ);
	for (i = 0; i < m; i++) free(*(arr + i));
	free(arr);
	_CrtDumpMemoryLeaks();
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

/*	Napisati C program koji s tipkovnice učitava cijeli broj m. Učitavanje treba ponavljati sve dok je učitani
	broj m manji od 2 ili veći od 10. Nakon toga s tipkovnice učitati m x m realnih brojeva u dvodimenzionalno
	polje (matricu) A. Pronaći i na ekran ispisati produkt elemenata na glavnoj dijagonali i sumu elemenata
	svakog retka matrice A. */

void task17(void) {
	system("cls");
	int i, j, m;
	float** arr, product = 1.0f, sum;
	do {
		printf("Unesite m [2, 10]: ");
		if (scanf("%d", &m) <= 0) exit(EXIT_FAILURE);
	} while (m < 2 || m > 10);
	arr = malloc(m * sizeof(float*));
	if (!arr) exit(EXIT_FAILURE);
	for (i = 0; i < m; i++) {
		*(arr + i) = malloc(m * sizeof(float));
		if (!*(arr + i)) exit(EXIT_FAILURE);
	}
	printf("\n");
	for (i = 0; i < m; i++) {
		for (j = 0; j < m; j++) {
			system("cls");
			printf("Unos [%d, %d]: ", i, j);
			if (scanf("%f", &(*(*(arr + i) + j))) <= 0) exit(EXIT_FAILURE);
			if (i == j) product *= *(*(arr + i) + j);
		}
	}
	printf("\nUmnozak glavne dijagonale je %.2f.\n\n", product);
	for (i = 0; i < m; i++) {
		sum = 0.0f;
		for (j = 0; j < m; j++) sum += *(*(arr + i) + j);
		printf("Suma %d. retka je %.2f.\n", (i + 1), sum);
	}
	for (i = 0; i < m; i++) free(*(arr + i));
	free(arr);
	_CrtDumpMemoryLeaks();
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

/*	Omogućiti korisniku unos 5 < p < 25 vrijednosti u polje realnih brojeva. Odrediti i ispisati na ekran
	aritmetičku sredinu elemenata koji su manji od aritmetičke sredine svih elemenata polja i aritmetičku
	sredinu elemenata koji su veći od aritmetičke sredine svih elemenata polja. */

void task18(void) {
	system("cls");
	int i, p, counterSmaller = 0, counterBigger = 0;
	float* arr, arrAM = 0, smallerAM = 0, biggerAM = 0;
	do {
		printf("Unesite p <5, 25>: ");
		if (scanf("%d", &p) <= 0) exit(EXIT_FAILURE);
	} while (p < 6 || p > 24);
	arr = malloc(p * sizeof(float));
	if (!arr) exit(EXIT_FAILURE);
	for (i = 0; i < p; i++) {
		system("cls");
		printf("Unos [%d]: ", i);
		if (scanf("%f", &(*(arr + i))) <= 0) exit(EXIT_FAILURE);
		arrAM += *(arr + i);
	}
	arrAM /= p;
	system("cls");
	for (i = 0; i < p; i++) printf("%.2f ", *(arr + i));
	printf("\n\nAritmeticka sredina polja je %.2f.\n", arrAM);
	for (i = 0; i < p; i++) {
		if (*(arr + i) > arrAM) {
			biggerAM += *(arr + i);
			counterBigger++;			
		}
		else {
			smallerAM += *(arr + i);
			counterSmaller++;
		}
	}
	printf("Aritmeticka sredina manjih je %.2f\nAritmeticka sredina vecih je %.2f.\n", (smallerAM / counterSmaller), (biggerAM / counterBigger));
	free(arr);
	_CrtDumpMemoryLeaks();
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

/*	Omogućiti korisniku unos 3 < n < 27 vrijednosti u polje realnih brojeva. Izračunati srednju vrijednost elemenata
	polja. Potom, izračunati produkt svih vrijednosti elemenata koju su strogo veći od srednje vrijednosti i strogo
	manji od najveće vrijednosti u polju. */

void task19(void) {
	system("cls");
	int n, i;
	float* arr, arrAM = 0, arrMax = FLT_MIN, product = 1.0f;
	do {
		printf("Unesite n <3, 27>: ");
		if (scanf("%d", &n) <= 0) exit(EXIT_FAILURE);
	} while (n < 4 || n > 26);
	arr = malloc(n * sizeof(float));
	if (!arr) exit(EXIT_FAILURE);
	for (i = 0; i < n; i++) {
		system("cls");
		printf("Unos [%d]: ", i);
		if (scanf("%f", &(*(arr + i))) <= 0) exit(EXIT_FAILURE);
		arrAM += *(arr + i);
		if (*(arr + i) > arrMax) arrMax = *(arr + i);
	}
	arrAM /= n;
	for (i = 0; i < n; i++) if ((*(arr + i) > arrAM) && (*(arr + i) < arrMax)) product *= *(arr + i);
	system("cls");
	for (i = 0; i < n; i++) printf("%.2f ", *(arr + i));
	printf("\n\nAritmeticka sredina polja je %.2f.\nProdukt elemenata iznosi %.2f.\n", arrAM, product);
	free(arr);
	_CrtDumpMemoryLeaks();
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

/*	Omogućiti korisniku unos 10 ≤ n ≤ 25 vrijednosti u polje realnih brojeva. Pronaći medu unesenim brojevima
	onaj koji je najbliži najvećem elementu polja. */

void task20(void) {
	system("cls");
	int i, n;
	float* arr, arrMax, arrSecondMax;
	arrMax = arrSecondMax = FLT_MIN;
	do {
		printf("Unesite n [10, 25]: ");
		if (scanf("%d", &n) <= 0)exit(EXIT_FAILURE);
	} while (n < 10 || n > 25);
	arr = malloc(n * sizeof(float));
	if (!arr) exit(EXIT_FAILURE);
	for (i = 0; i < n; i++) {
		system("cls");
		printf("Unos [%d]: ", i);
		if (scanf("%f", &(*(arr + i))) <= 0) exit(EXIT_FAILURE);
		if (*(arr + i) > arrMax) {
			arrSecondMax = arrMax;
			arrMax = *(arr + i);
		}
		else if ((*(arr + i) > arrSecondMax) && (*(arr + i) < arrMax)) arrSecondMax = *(arr + i);
	}
	system("cls");
	for (i = 0; i < n; i++) printf("%.2f ", *(arr + i));
	printf("\n\nDrugi najveci broj u polju je %.2f.\n", arrSecondMax);
	free(arr);
	_CrtDumpMemoryLeaks();
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}