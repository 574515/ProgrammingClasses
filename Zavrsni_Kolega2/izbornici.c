#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

void pocetni(void) {

	FILE* provjeriAdminF = NULL;
	if (!(provjeriAdminF = fopen("admini.bin", "rb"))) {
		system("cls");
		printf("\n\tTrenutno nema admina.\n\tPritisnite tipku da biste ga kreirali.\n");
		c = _getch();
		kreirajAdmin();
	}
	else {
		int brojAdmina, i, flag = 0;
		fread(&brojAdmina, sizeof(int), 1, provjeriAdminF);
		ADMIN* adminS = NULL;
		adminS = alocirajAdmin(adminS, brojAdmina);
		char* korIme, *lozinka;
		if (!(korIme = calloc(20, sizeof(char)))) {
			exit(EXIT_FAILURE);
		}			
		if (!(lozinka = calloc(20, sizeof(char)))) {
			exit(EXIT_FAILURE);
		}
		system("cls");
		printf("\n\t- Ulogirajte se -\n\nKorisnicko ime: ");
		fgets(korIme, 19, stdin);
		printf("Lozinka: ");
		for(i = 0; *(lozinka + i - 1) != '\r'; i++) {
			*(lozinka + i) = _getch();
			printf("*");
		}
		*(lozinka + i - 1) = '\n';
		fread(adminS, sizeof(ADMIN), brojAdmina, provjeriAdminF);
		for (i = 0; i < brojAdmina; i++) {
			if (strcmp((adminS + i)->korIme, korIme) == 0) {
				if (strcmp((adminS + i)->lozinka, lozinka) == 0) {
					flag = 2;
					break;
				}
				else {
					flag = 1;
					break;
				}
			}
			else {
				flag = 0;
			}
		}
		if (flag == 2) {
			int broj = 0;
			while (*(korIme + broj) != '\n') {
				broj++;
			}
			if (!(logiran = calloc(broj + 2, sizeof(char)))) {
				exit(EXIT_FAILURE);
			}
			strncpy(logiran, korIme, broj);
			*(logiran + strlen(logiran)) = '\0';
			free(korIme);
			free(lozinka);
			free(adminS);
			fclose(provjeriAdminF);
			glavniIzbornik();
		}
		else if (flag == 1) {
			free(korIme);
			free(lozinka);
			free(adminS);
			fclose(provjeriAdminF);
			printf("\n\tPogresna lozinka!\n");
			c = _getch();
			return;
		}
		else if (flag == 0) {
			free(korIme);
			free(lozinka);
			free(adminS);
			fclose(provjeriAdminF);
			printf("\n\tAdmin ne postoji!\n");
			c = _getch();
			return;
		}
	}
}

void glavniIzbornik(void) {

	int izbor;

	while (1) {
		do {
			system("cls");
			printf("\tUlogiran: [%s]\n\n\tIT Skladiste - Glavni izbornik\n\n", logiran);
			printf("1 -> Inventar\n2 -> Admini\n3 -> Izlaz\n\nIzbor: ");
			if (scanf("%d", &izbor) <= 0) {
				exit(EXIT_FAILURE);
			}
		} while (izbor < 1 || izbor > 3);
		switch (izbor) {
			case 1: {
				inventarIzbornik();
				break;
			}
			case 2: {
				adminIzbornik();
				break;
			}
			case 3: {
				if (logiran != NULL) {
					free(logiran);
				}
				exit(EXIT_SUCCESS);
			}
		}
	}
}

void inventarIzbornik(void) {

	int izbor;

	while (1) {
		do {
			system("cls");
			printf("\tUlogiran: [%s]\n\n\tIT Skladiste - Izbornik inventara\n\n", logiran);
			printf("1 -> Dodaj inventar\n2 -> Odjavi inventar\n3 -> Trazi inventar\n4 -> Izlistaj inventar\n5 -> Povratak\n\nIzbor: ");
			if (scanf("%d", &izbor) <= 0) {
				exit(EXIT_FAILURE);
			}
		} while (izbor < 1 || izbor > 5);
		switch (izbor) {
			case 1: {
				kreirajInventar();
				break;
			}
			case 2: {
				obrisiInventar();
				break;
			}
			case 3: {
				traziInventar();
				break;
			}
			case 4: {
				listajInventar();
				break;
			}
			case 5: {
				return;
			}
		}
	}
}

void adminIzbornik(void) {

	int izbor;

	while (1) {
		do {
			system("cls");
			printf("\tUlogiran: [%s]\n\n\tIT Skladiste - Izbornik admina\n\n", logiran);
			printf("1 -> Dodaj admina\n2 -> Obrisi admina\n3 -> Trazi admina\n4 -> Izlistaj admine\n5 -> Povratak\n\nIzbor: ");
			if (scanf("%d", &izbor) <= 0) {
				exit(EXIT_FAILURE);
			}
		} while (izbor < 1 || izbor > 5);
		switch (izbor) {
			case 1: {
				kreirajAdmin();
				break;
			}
			case 2: {
				obrisiAdmin();
				break;
			}
			case 3: {
				traziAdmin();
				break;
			}
			case 4: {
				listajAdmin();
				break;
			}
			case 5: {
				return;
			}
		}
	}
}