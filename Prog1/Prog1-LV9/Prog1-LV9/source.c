#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#define PI 3.1415926535897932384626433832795028841971693993751058209749445923

/*	1. Napisati funkciju koja će izračunati i vratiti obujam valjka zadanog s polumjerom i visinom. U main() funkciji na primjeru
	prikazati uporabu napisane funkciju.
	2. Napisati funkciju koja će izračunati i vratiti srednju vrijednost prvih n neparnih prirodnih brojeva. U main() funkciji na
	primjeru prikazati uporabu napisane funkciju.
	3. Napisati funkciju koja će izračunati i vratiti srednju vrijednost svih cijelih brojeva između m i n (m < n). U main()
	funkciji na primjeru prikazati uporabu napisane funkciju.
	4. Napisati funkciju koja će izračunati i vratiti površinu trokuta zadanog duljinama stranica. Uzeti u obzir i situaciju kada
	predane stranice ne čine trokut. U main() funkciji na primjeru prikazati uporabu napisane funkciju. Za izračun površine trokuta
	koristiti Heronovu formulu: 𝑃 = √𝑠(𝑠 − 𝑎)(𝑠 − 𝑏)(𝑠 − 𝑐),
	gdje je s = (a+b+c)/2 poluopseg, a a, b i c su duljine stranica trokuta. Za izračun korjena koristiti funkciju sqrt() za koju je
	potrebno uključiti zaglavlje math.h, čiji je prototip: double sqrt(double); */

void first(void);
double obujam(float, float);
void second(void);
float drugiSrednjaVrijednost(int);
void third(void);
float treciSrednjaVrijednost(int, int);
void fourth(void);
double cetvrtiPovrsinaTrokuta(int, int, int);

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
	float polumjer, visina;
	do {
		printf("Unesite polumjer: ");
		if (scanf("%f", &polumjer) <= 0) exit(EXIT_FAILURE);
	} while (polumjer < 0.0f);
	do {
		printf("Unesite visinu: ");
		if (scanf("%f", &visina) <= 0) exit(EXIT_FAILURE);
	} while (visina < 0.0f);
	printf("\nObujam valjka visine [%.2f] i polumjera [%.2f] je %.2lf.\n", visina, polumjer, obujam(polumjer, visina));
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

double obujam(float polumjer, float visina) { return ((PI * pow(polumjer, 2)) * visina); }

void second(void) {
	system("cls");
	int n;
	do {
		printf("Unesite n <0, inf.>: ");
		if (scanf("%d", &n) <= 0) exit(EXIT_FAILURE);
	} while (n <= 0);
	printf("\nSrednja vrijednost prvih %d neparnih prirodnih brojeva je %.2f.\n", n, drugiSrednjaVrijednost(n));
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

float drugiSrednjaVrijednost(int n) {
	int i, brojac = 0;
	float srednja = 0;
	for (i = 1; i <= n; i++) {
		if ((i % 2) != 0) {
			srednja += i;
			brojac++;
		}
	}
	return (srednja / brojac);
}

void third(void) {
	system("cls");
	int m, n;
	do {
		printf("Unesite m <0, inf.>: ");
		if (scanf("%d", &m) <= 0) exit(EXIT_FAILURE);
	} while (m < 0);
	do {
		printf("Unesite n (n > m): ");
		if (scanf("%d", &n) <= 0) exit(EXIT_FAILURE);
	} while (n <= m);
	printf("\nSrednja vrijednost cijelih brojeva izmedju %d i %d je %.2f.\n", m, n, treciSrednjaVrijednost(m, n));
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

float treciSrednjaVrijednost(int m, int n) {
	int i, brojac = 0;
	float srednja = 0;
	for (i = m; i <= n; i++) {
		srednja += i;
		brojac++;
	}
	return (srednja / brojac);
}

void fourth(void) {
	system("cls");
	int a, b, c;
	do {
		system("cls");
		printf("Unesite starnicu a: ");
		if (scanf("%d", &a) <= 0) exit(EXIT_FAILURE);
		printf("Unesite starnicu b: ");
		if (scanf("%d", &b) <= 0) exit(EXIT_FAILURE);
		printf("Unesite starnicu c: ");
		if (scanf("%d", &c) <= 0) exit(EXIT_FAILURE);
	} while (!((a + b) > c) || !((a + c) > b) || !((b + c) > a));
	printf("\nPovrsina trokuta stranica [%d, %d, %d] je %lf.\n", a, b, c, cetvrtiPovrsinaTrokuta(a, b, c));
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

double cetvrtiPovrsinaTrokuta(int a, int b, int c) {
	double s = ((double)a + b + c) / 2;
	return sqrt(s * (s - a) * (s - b) * (s - c));	
}