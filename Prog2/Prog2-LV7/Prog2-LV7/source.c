#include "header.h"
#include <stdlib.h>
#include <time.h>

/*	1. Napisati C program koji će pročitati cijeli broj iz datoteke "dat.txt" i toliko puta tražiti unos imena i prezimena
	studenta sa standardnog ulaza. Sva učitana imena i prezimena zapisati u datoteku "studenti.txt" koju je potrebno kreirati
	iz programa i to tako da zapis bude u formatu: "Student broj: %d.\tIme: %s\t Prezime: %s\n", svaki zapis u novi red.
	Datoteku "dat.txt" kreirati na računalu pomoću Notepad-a, te upisati cijeli broj i spremiti sadržaj datoteke. Prilikom
	otvaranja datoteke "dat.txt" navesti apsolutnu putanju do sam datoteke.
	Pojedine dijelove programa razdijeliti u funkcije.
	Organizirati kôd u različite datoteke.
	2. Napisati C program koji će iz datoteke "in.txt" učitati dva cijela broja. Popuniti realnu matricu A pseudo-slučajnim
	vrijednostima iz intervala [-125.5, 65.8]. U datoteku "out.txt" i na ekran ispisati dio matrice, u matričnom obliku, koja
	se dobije tako da se izostavi prvi stupac i zadnji redak. Datoteku "out.txt" treba kreirati iz programa. Datoteku "in.txt"
	kreirati na računalu pomoću Notepad-a, te upisati dva cijela broja svaki u svoj red i spremiti sadržaj datoteke. Prilikom
	otvaranja datoteke "in.txt" navesti apsolutnu putanju do sam datoteke.
	Pojedine dijelove programa razdijeliti u funkcije.
	Koristiti dinamičko zauzimanje memorije (u potpunosti rukovati memorijom).
	Primijeniti isključivo pokazivačku notaciju.
	Organizirati kôd u različite datoteke.
	3. Napisati C program koji kopira sadržaj jedne tekstualne datoteku u drugu pri čemu se mijenjaju mala slova u velika.
	Datoteka iz koje se kopira sadržaj zove se "prva.txt" i pripremljena je samo za čitanje. Datoteku pod imenom "druga.txt"
	potrebno je kreirati iz programa i u nju se zapisuje sadržaj iz datoteke "prva.txt". Datoteku "prva.txt" kreirati na
	računalu pomoću Notepad-a, te upisati generirani sadržaj sa stranice https://baconipsum.com/, te spremiti sadržaj datoteke.
	Prilikom otvaranja datoteke "prva.txt" navesti apsolutnu putanju do sam datoteke.
	Pojedine dijelove programa razdijeliti u funkcije.
	Organizirati kôd u različite datoteke. */


int main(void) {
	int choice;
	srand((unsigned)time(NULL));
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