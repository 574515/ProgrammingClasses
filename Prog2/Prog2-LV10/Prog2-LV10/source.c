#include "header.h"
#include <stdlib.h>
#include <time.h>

/*	1. Napisati C program koji će od korisnika tražiti unos cijelog broja n te u datoteku naziva suma.txt upisati sumu
	njegovih znamenaka.Za traženje sume znamenaka broja koristiti rekurziju.
	2. Napisati C program koji će od korisnika tražiti unos broj n (0 < n <= 20), zatim je potrebno dinamički zauzeti
	polje ukupne duljine n elemenata i to polje popuniti sa pseudo - slučajnim vrijednostima unutar intervala [-50, 100].
	Pronaći najveći element unutar polja i zapisati ga u datoteku najveci.txt te ispisati ga na standardni izlaz. Za
	pronalazak najvećeg elementa unutar polja koristiti rekurziju.
	3. Napisati C program koji od korisnika traži unos stringa.Uneseni string predati funkciji koja će obrnutim
	redoslijedom zapisati string u datoteku string.txt i ispisati ga na standardni izlaz.Za promjenu redoslijeda stringa
	koristiti rekurzivnu funkciju. */

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