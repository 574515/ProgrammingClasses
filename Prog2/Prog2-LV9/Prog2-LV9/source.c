#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*	1. Napisati C program koji će kreirati tekstualnu datoteku pod imenom dat.txt i u koju će se spremiti 500 cijelih brojeva
	koje je potrebno pseudo-slučajno generirati unutar intervala [0, 1000]. Učitati broj n s tipkovnice koji također mora biti
	unutar intervala [0, 1000]. Pročitati sve podatke iz tekstualne datoteke dat.txt u cjelobrojno polje, te provjeriti
	sekvencijalnim pretraživanjem nalazi li se taj broj n u ranije učitanom polju. Ukoliko je broj pronađen ispisati poruku
	"Broj %d je pronadjen nakon %d koraka na indeksu %d." Ukoliko broj nije pronađen ispisati poruku "Broj %d nije pronadjen.".
	2. Napisati C program koji će kreirati tekstualnu datoteku pod imenom dat.txt i u koju će se spremiti 500 cijelih brojeva
	koje je potrebno pseudo-slučajno generirati unutar intervala [0, 1000]. S tipkovnice učitava 5 cijelih brojeva iz intervala
	[1, 1000]. Zatim se učitava 500 cijelih brojeva iz datoteke dat.txt. Izvršiti pretragu svakog od unesenih brojeva s tipkovnice
	u učitanom polju koristeći algoritme sekvencijalnog i binarnog pretraživanja. Na kraju je potrebno izračunati i ispisati
	srednji broj pretraživanja za svaki algoritam pojedinačno (pri izračunu srednjeg broja pretraživanja uzeti u obzir samo ona
	pretraživanja koja su bila uspješna). Ispis na ekran prilagoditi formatu prema sljedećem primjeru:
		Za unesene brojeve 23, 67, 45, 89, 347
		REZULTATI:
		Sekvencijalno:
		1. broj 23 je pronadjen u 377 koraka.
		2. broj 67 nije pronadjen.
		3. broj 45 nije pronadjen.
		4. broj 89 nije pronadjen.
		5. broj 347 nije pronadjen.
		Binarno:
		1. broj 23 je pronadjen u 9 koraka.
		2. broj 67 nije pronadjen.
		3. broj 45 nije pronadjen.
		4. broj 89 nije pronadjen.
		5. broj 347 nije pronadjen.
		Srednji broj koraka za sekvencijalno pretrazivanje je: 377.00
		Srednji broj koraka za binarno pretrazivanje je: 9.00 */

int main(void) {
	int choice;
	srand((unsigned)time(NULL));
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