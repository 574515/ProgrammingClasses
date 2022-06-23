#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define DRUGIMAX 15
#define TRECIMAX 20
#define CETVRTIMAX 12

/*	1. Omogućiti korisniku unos vrijednosti elemenata u polje od 10 cijelih brojeva. Potom ispisati na ekran sve indekse
	kod kojih je vrijednost elemenata djeljiva s 5.
	2. Omogućiti korisniku unos n (5 ≤ n ≤ 15) vrijednosti elemenata u polje realnih brojeva. Potom odrediti i na ekran
	ispisati koliko je vrijednosti veće od srednje vrijednosti svih elemenata.
	3. Omogućiti korisniku unos n (4 ≤ n < 21) vrijednosti elemenata u polje realnih brojeva. Povećati vrijednost svakog
	elemenata većeg od srednje vrijednosti za 10%, a ostalim smanjiti vrijednost za 10%.
	4. Omogućiti korisniku unos q (4 < q ≤ 12) vrijednosti elemenata u polje realnih brojeva. Podijeliti vrijednost svakog
	elementa polja koji ima neparni indeks s vrijednosti 2 te nakon toga na ekran ispisati polje. */

void first(void);
void second(void);
void third(void);
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
	int i, arr[10];
	for (i = 0; i < 10; i++) {
		printf("Unesite %d. broj: ", (i + 1));
		if (scanf("%d", &arr[i]) <= 0) exit(EXIT_FAILURE);
	}
	printf("\n\n");
	for (i = 0; i < 10; i++) if ((arr[i] % 5) == 0) printf("%d ", i);
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

void second(void) {
	system("cls");
	int i, n, brojac = 0;
	float arr[DRUGIMAX], prosjek = 0;
	do {
		printf("Unesite n [5, 15]: ");
		if (scanf("%d", &n) <= 0) exit(EXIT_FAILURE);
	} while (n < 5 || n > DRUGIMAX);
	for (i = 0; i < n; i++) {
		printf("Unesite %d. broj: ", (i + 1));
		if (scanf("%f", &arr[i]) <= 0) exit(EXIT_FAILURE);
		prosjek += arr[i];
	}
	prosjek /= n;
	for (i = 0; i < n; i++) if (arr[i] > prosjek) brojac++;
	printf("\nUkupno je %d vrijednosti vece od srednje vrijednosti svih elemenata [%.2f].\n", brojac, prosjek);
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

void third(void) {
	system("cls");
	int i, n, brojac = 0;
	float arr[TRECIMAX], prosjek = 0;
	do {
		printf("Unesite n [4, 21>: ");
		if (scanf("%d", &n) <= 0) exit(EXIT_FAILURE);
	} while (n < 4 || n > TRECIMAX);
	for (i = 0; i < n; i++) {
		printf("Unesite %d. broj: ", (i + 1));
		if (scanf("%f", &arr[i]) <= 0) exit(EXIT_FAILURE);
		prosjek += arr[i];
	}
	prosjek /= n;
	printf("\nPROSJEK [%.2f] - Polje:\n\n", prosjek);
	for (i = 0; i < n; i++) {
		if (arr[i] > prosjek) arr[i] *= 1.1f;
		else arr[i] *= 0.9f;
		printf("%.2f ", arr[i]);
	}
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

void fourth(void) {
	system("cls");
	int i, n, brojac = 0;
	float arr[CETVRTIMAX], prosjek = 0;
	do {
		printf("Unesite n <4, 12]: ");
		if (scanf("%d", &n) <= 0) exit(EXIT_FAILURE);
	} while (n < 5 || n > CETVRTIMAX);
	for (i = 0; i < n; i++) {
		printf("Unesite %d. broj: ", (i + 1));
		if (scanf("%f", &arr[i]) <= 0) exit(EXIT_FAILURE);
		if ((i % 2) != 0) arr[i] /= 2;
	}
	printf("\nNovo polje nako podjele elemenata neparnih indeksa sa brojem 2:\n");
	for (i = 0; i < n; i++) printf("%.2f ", arr[i]);
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}