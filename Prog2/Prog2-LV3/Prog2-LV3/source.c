#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <float.h>

/*	1. Napisati C program u kojemu treba napraviti novi složeni tip podatka struct kompleksni pod nazivom KOMPLEKSNI i
	kreirati strukturne varijable br1, br2, rez. Struktura KOMPLEKSNI treba sadržavati sljedeće realne članove: re i im.
	Omogućiti unos dva kompleksna broja. Izračunati i ispisati zbroj, razliku, produkt, količnik dva kompleksna broja u
	obliku re + im*i, pripaziti na predznak ako je imaginarna komponenta negativna, te izračunati modul svakog kompleksnog
	broja.
	2. Napisati C program koji omogućuje unos podataka o programerima jedne IT tvrtke, kao što je ime, prezime, OIB, plaća
	i datum rođenja, od ukupno 15 programera. Tražiti od korisnika unos broj n (1 ≤ 𝑛 < 16), ponavljati sve dok unos ne
	odgovara traženom intervalu. Popuniti informacije o onoliko programera ovisno o broju n, pronaći programera koji ima
	najbolju plaću, te ispisati sve informacije o tome programeru. S obzirom na navedene podatke o programeru, formirati
	strukturu koristeći ključnu riječ typedef i pripaziti na ispis formata za datum kako bi bio u obliku DD.MM.GGGG. */

typedef struct kompleksni {
	float re, im;
}KOMPLEKSNI;

typedef struct zaposlenik {
	char fname[21], lname[21], OIB[12];
	float salary;
	int day, month, year;
}ZAPOSLENIK;

void task1(void);
void task1PrintResult(KOMPLEKSNI, KOMPLEKSNI);
void task2(void);
void task2PrintMaxSalaryEmployee(ZAPOSLENIK*, int);

int main(void) {
	int choice;
	while (1) {
		do {
			system("cls");
			printf("Unesite broj zadatka [1, 2] ili [0] za izlaz: ");
			if (scanf("%d", &choice) <= 0) exit(EXIT_FAILURE);
		} while (choice < 0 || choice > 2);
		switch (choice) {
		case 0: exit(EXIT_SUCCESS);
		case 1: task1(); break;
		case 2: task2(); break;
		}
	}
	return 0;
}

void task1(void) {
	system("cls");
	KOMPLEKSNI num1, num2;
	printf("Unesite reaelni dio 1. broja: ");
	if (scanf("%f", &num1.re) <= 0) exit(EXIT_FAILURE);
	printf("Unesite imaginarni dio 1. broja: ");
	if (scanf("%f", &num1.im) <= 0) exit(EXIT_FAILURE);
	printf("Unesite reaelni dio 2. broja: ");
	if (scanf("%f", &num2.re) <= 0) exit(EXIT_FAILURE);
	printf("Unesite imaginarni dio 2. broja: ");
	if (scanf("%f", &num2.im) <= 0) exit(EXIT_FAILURE);
	task1PrintResult(num1, num2);
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

void task1PrintResult(KOMPLEKSNI num1, KOMPLEKSNI num2) {
	KOMPLEKSNI res;
	res.re = num1.re + num2.re;
	res.im = num1.im + num2.im;
	if (res.im >= 0) printf("\nZbroj kompleksnih brojeva: %.2f + %.2fi\n", res.re, res.im);
	else printf("\nZbroj kompleksnih brojeva: %.2f %.2fi\n", res.re, res.im);
	res.re = num1.re - num2.re;
	res.im = num1.im - num2.im;
	if (res.im >= 0) printf("Razlika kompleksnih brojeva: %.2f + %.2fi\n", res.re, res.im);
	else printf("Razlika kompleksnih brojeva: %.2f %.2fi\n", res.re, res.im);
	res.re = num1.re * num2.re - num1.im * num2.im;
	res.im = num1.im * num2.re + num1.re * num2.im;
	if (res.im >= 0) printf("Umnozak kompleksnih brojeva: %.2f + %.2fi\n", res.re, res.im);
	else printf("Umnozak kompleksnih brojeva: %.2f %.2fi\n", res.re, res.im);
	res.re = (num1.re * num2.re + num1.im * num2.im) / (num2.re * num2.re + num2.im * num2.im);
	res.im = (num1.im * num2.re - num1.re * num2.im) / (num2.re * num2.re + num2.im * num2.im);
	if (res.im > 0) printf("Kolicnik kompleksnih brojeva: %.2f + %.2fi\n", res.re, res.im);
	else if (res.im < 0) printf("Kolicnik kompleksnih brojeva: %.2f %.2fi\n", res.re, res.im);
	else printf("Dijeljenje s nulom nije dozvoljeno.\n");
}

void task2(void) {
	system("cls");
	int n, i, tmpIndx = 0;
	float maxSalary = FLT_MIN;
	do {
		printf("Koliko zaposlenika zelite unijeti [1, 15]: ");
		if (scanf("%d", &n) <= 0) exit(EXIT_FAILURE);
	} while (n < 1 || n > 15);
	ZAPOSLENIK* zap = NULL;
	zap = malloc(n * sizeof(ZAPOSLENIK));
	if (!zap) exit(EXIT_FAILURE);
	for (i = 0; i < n; i++) {
		system("cls");
		printf("\tUnos [%d.] zaposlenik\n\nUnesite ime: ", (i + 1));
		if (getchar() <= 0) exit(EXIT_FAILURE);
		if (fgets((zap + i)->fname, 21, stdin) == NULL) exit(EXIT_FAILURE);
		printf("Unesite prezime: ");
		if (fgets((zap + i)->lname, 21, stdin) == NULL) exit(EXIT_FAILURE);
		printf("Unesite OIB [11]: ");
		if (fgets((zap + i)->OIB, 12, stdin) == NULL) exit(EXIT_FAILURE);
		printf("Unesite placu: ");
		if (scanf("%f", &(zap + i)->salary) <= 0) exit(EXIT_FAILURE);
		if ((zap + i)->salary > maxSalary) {
			maxSalary = (zap + i)->salary;
			tmpIndx = i;
		}
		do {
			printf("Unesite dan rodjenja: ");
			if (scanf("%d", &(zap + i)->day) <= 0) exit(EXIT_FAILURE);
		} while ((zap + i)->day < 1 || (zap + i)->day > 31);
		do {
			printf("Unesite mjesec rodjenja: ");
			if (scanf("%d", &(zap + i)->month) <= 0) exit(EXIT_FAILURE);
		} while ((zap + i)->month < 1 || (zap + i)->month > 12);
		printf("Unesite godinu rodjenja: ");
		if (scanf("%d", &(zap + i)->year) <= 0) exit(EXIT_FAILURE);
	}
	task2PrintMaxSalaryEmployee(zap, tmpIndx);
	free(zap);
	if (_getch() <= 0) exit(EXIT_FAILURE);
	_CrtDumpMemoryLeaks();
	return;
}

void task2PrintMaxSalaryEmployee(ZAPOSLENIK* zap, int tmpIndx) {
	system("cls");
	printf("\tZaposlenik sa najvecom placom\n\n");
	printf("Ime: %sPrezime: %sOIB: %s\nPlaca: %.2f\n", (zap + tmpIndx)->fname, (zap + tmpIndx)->lname, (zap + tmpIndx)->OIB, (zap + tmpIndx)->salary);
	if ((zap + tmpIndx)->day < 10 && (zap + tmpIndx)->month < 10) printf("Datum rodjenja: 0%d.0%d.%d.\n", (zap + tmpIndx)->day, (zap + tmpIndx)->month, (zap + tmpIndx)->year);
	else if ((zap + tmpIndx)->day > 10 && (zap + tmpIndx)->month < 10) printf("Datum rodjenja: %d.0%d.%d.\n", (zap + tmpIndx)->day, (zap + tmpIndx)->month, (zap + tmpIndx)->year);
	else if ((zap + tmpIndx)->day < 10 && (zap + tmpIndx)->month > 10) printf("Datum rodjenja: 0%d.%d.%d.\n", (zap + tmpIndx)->day, (zap + tmpIndx)->month, (zap + tmpIndx)->year);
	else if ((zap + tmpIndx)->day > 10 && (zap + tmpIndx)->month > 10) printf("Datum rodjenja: %d.%d.%d.\n", (zap + tmpIndx)->day, (zap + tmpIndx)->month, (zap + tmpIndx)->year);
}