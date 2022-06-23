#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

void kreirajAdmin(void) {

	ADMIN* adminS = NULL;
	adminS = alocirajAdmin(adminS, 1);
	FILE* adminF = NULL;

	if (!(adminF = fopen("admini.bin", "r+b"))) {
		if (!(adminF = fopen("admini.bin", "wb"))) {
			exit(EXIT_FAILURE);
		}
		system("cls");
		printf("\n\tUnos 1. admina.\n\nUnesite ID: ");
		if (scanf("%d", &adminS->ID) <= 0) {
			exit(EXIT_FAILURE);
		}
		printf("Unesite korisnicko ime: ");
		c = getchar();
		if (fgets(adminS->korIme, 19, stdin) == NULL) {
			exit(EXIT_FAILURE);
		}
		printf("Unesite lozinku: ");
		if (fgets(adminS->lozinka, 19, stdin) == NULL) {
			exit(EXIT_FAILURE);
		}
		printf("Unesite ime: ");
		if (fgets(adminS->ime, 19, stdin) == NULL) {
		exit(EXIT_FAILURE);
		}
		printf("Unesite prezime: ");
		if (fgets(adminS->prezime, 19, stdin) == NULL) {
		exit(EXIT_FAILURE);
		}
		printf("Unesite kontakt: ");
		if (fgets(adminS->kontakt, 29, stdin) == NULL) {
		exit(EXIT_FAILURE);
		}
		int brojAdmina = 1;
		fwrite(&brojAdmina, sizeof(int), 1, adminF);
		fwrite(adminS, sizeof(ADMIN), 1, adminF);
		free(adminS);
		fclose(adminF);
		pocetni();
	}
	else {
		int brojAdmina;
		fread(&brojAdmina, sizeof(int), 1, adminF);
		ADMIN* adminPomocna = NULL;
		adminPomocna = alocirajAdmin(adminS, brojAdmina);
		fread(adminPomocna, sizeof(ADMIN), brojAdmina, adminF);
		brojAdmina++;
		system("cls");
		printf("\n\tUnos %d. admina.\n\nUnesite ID: ", brojAdmina);
		if (scanf("%d", &adminS->ID) <= 0) {
			exit(EXIT_FAILURE);
		}
		for (int i = 0; i < (brojAdmina - 1); i++) {
			if ((adminPomocna + i)->ID == adminS->ID) {
				printf("\n\tAdmin sa tim ID-om postoji!\n");
				c = _getch();
				return;
			}
		}
		printf("Unesite korisnicko ime: ");
		c = getchar();
		if(fgets(adminS->korIme, 19, stdin) == NULL) {
		exit(EXIT_FAILURE);
		}
		for (int i = 0; i < (brojAdmina - 1); i++) {
			if (strcmp((adminPomocna + i)->korIme, adminS->korIme) == 0) {
				printf("\n\tAdmin sa tim korisnickim imenom postoji!\n");
				c = _getch();
				return;
			}
		}
		printf("Unesite lozinku: ");
		if (fgets(adminS->lozinka, 19, stdin) == NULL) {
		exit(EXIT_FAILURE);
		}
		printf("Unesite ime: ");
		if (fgets(adminS->ime, 19, stdin) == NULL) {
		exit(EXIT_FAILURE);
		}
		printf("Unesite prezime: ");
		if (fgets(adminS->prezime, 19, stdin) == NULL) {
		exit(EXIT_FAILURE);
		}
		printf("Unesite kontakt: ");
		if(fgets(adminS->kontakt, 29, stdin) == NULL) {
		exit(EXIT_FAILURE);
		}
		rewind(adminF);
		fwrite(&brojAdmina, sizeof(int), 1, adminF);
		fseek(adminF, sizeof(int) + ((brojAdmina - 1) * sizeof(ADMIN)), SEEK_SET);
		fwrite(adminS, sizeof(ADMIN), 1, adminF);
		free(adminS);
		free(adminPomocna);
		fclose(adminF);
		return;
	}
}

void obrisiAdmin(void) {
	FILE* adminF = NULL;
	if (!(adminF = fopen("admini.bin", "rb"))) {
		system("cls");
		printf("\n\t\tPogreska!\nNema admina!\n");
		c = _getch();
		return;
	}

	int odabir, brojAdmina, obrisiID, pomocna, i;

	do {
		system("cls");
		printf("\tUlogiran: [%s]\n\n\tIT Skladiste - Brisanje admina\n\n", logiran);
		printf("1 -> Obrisi po ID\n2 -> Obrisi po korisnickom imenu\n3 -> Povratak\n\nIzbor: ");
		if (scanf("%d", &odabir) <= 0) {
			exit(EXIT_FAILURE);
		}
	} while (odabir < 1 || odabir > 3);

	FILE* privremeniF = NULL;
	if (!(privremeniF = fopen("tmp.bin", "wb"))) {
		exit(EXIT_FAILURE);
	}

	fread(&brojAdmina, sizeof(int), 1, adminF);
	ADMIN* brisanjeS = NULL;
	brisanjeS = alocirajAdmin(brisanjeS, brojAdmina);

	switch (odabir) {
		case 1: {
			int pronadjen = 0;
			printf("\nUnesite ID za brisanje: ");
			if (scanf("%d", &obrisiID) <= 0) {
				exit(EXIT_FAILURE);
			}

			pomocna = brojAdmina - 1;
			fwrite(&pomocna, sizeof(int), 1, privremeniF);

			for (i = 0; i < brojAdmina; i++) {
				fread(brisanjeS, sizeof(ADMIN), 1, adminF);
				if (brisanjeS->ID == obrisiID) {
					pronadjen = 1;
				}
				else {
					fwrite(brisanjeS, sizeof(ADMIN), 1, privremeniF);
				}
			}

			if (pronadjen != 1) {
				system("cls");
				printf("\n\tAdmin sa ID [%d] nije pronadjen!\n", obrisiID);
				fclose(adminF);
				fclose(privremeniF);
				free(brisanjeS);
				c = _getch();
			}
			else {
				system("cls");
				printf("\n\tAdmin sa ID [%d] je uklonjen.\n", obrisiID);
				c = _getch();
				if (pomocna == 0) {
					fclose(adminF);
					fclose(privremeniF);
					free(brisanjeS);
					if (remove("admini.bin") != 0) {
						exit(EXIT_FAILURE);
					}
					if(remove("tmp.bin") != 0) {
						exit(EXIT_FAILURE);
					}
					printf("\n\tNema admina! Izlazak iz programa...\n");
					c = _getch();
					exit(EXIT_SUCCESS);
				}
				else {
					fclose(adminF);
					fclose(privremeniF);
					free(brisanjeS);
					if(remove("admini.bin") != 0) {
						exit(EXIT_FAILURE);
					}
					if (rename("tmp.bin", "admini.bin") != 0) {
						exit(EXIT_FAILURE);
					}
				}
			}
			return;
		}
		case 2: {
			char* obrisiKorIme;
			int pronadjen = 0;		
			if (!(obrisiKorIme = (char*)calloc(20, sizeof(char)))) {
				exit(EXIT_FAILURE);
			}
			c = getchar();
			printf("\nUnesite korisnicko ime za brisanje: ");
			if(fgets(obrisiKorIme, 19, stdin) == NULL) {
				exit(EXIT_FAILURE);
			}
			pomocna = brojAdmina - 1;
			fwrite(&pomocna, sizeof(int), 1, privremeniF);
			for (i = 0; i < brojAdmina; i++) {
				fread(brisanjeS, sizeof(ADMIN), 1, adminF);
				if (strcmp(brisanjeS->korIme, obrisiKorIme) == 0) {
					pronadjen = 1;
				}
				else {
					fwrite(brisanjeS, sizeof(ADMIN), 1, privremeniF);
				}
			}

			if (pronadjen != 1) {
				system("cls");
				*(obrisiKorIme + (strlen(obrisiKorIme) - 1)) = 0;
				printf("\n\tAdmin sa korisnickim imenom [%s] nije pronadjen.\n", obrisiKorIme);
				fclose(adminF);
				fclose(privremeniF);
				free(brisanjeS);
				free(obrisiKorIme);
				c = _getch();
			}
			else {
				system("cls");
				*(obrisiKorIme + (strlen(obrisiKorIme) - 1)) = 0;
				printf("\n\tAdmin sa korisnickim imenom [%s] je uklonjen.\n", obrisiKorIme);
				c = _getch();
				fclose(adminF);
				fclose(privremeniF);
				free(brisanjeS);
				free(obrisiKorIme);
				if (pomocna == 0) {
					if(remove("admini.bin") != 0) {
						exit(EXIT_FAILURE);
					}
					if(remove("tmp.bin") != 0) {
						exit(EXIT_FAILURE);
					}
					printf("\n\tNema admina! Izlazak iz programa...\n");
					c = _getch();
					exit(EXIT_SUCCESS);
				}
				else {
					if(remove("admini.bin") != 0) {
						exit(EXIT_FAILURE);
					}
					if (rename("tmp.bin", "admini.bin") != 0) {
						exit(EXIT_FAILURE);
					}
				}
			}
			return;
		}
		case 3: {
			fclose(adminF);
			fclose(privremeniF);
			free(brisanjeS);
			return;
		}
	}
}

void listajAdmin(void) {

	FILE* adminiF = NULL;
	if (!(adminiF = fopen("admini.bin", "rb"))) {
		system("cls");
		printf("\n\t\tPogreska!\nNema admina!\n");
		c = _getch();
		return;
	}

	int odabir, brojAdmina, i, uzlSil = 0;

	do {
		system("cls");
		printf("\tUlogiran: [%s]\n\n\tIT Skladiste - Listanje admina\n\n", logiran);
		printf("1 -> ID\n2 -> Korisnicko ime\n3 -> Ime\n4 -> Povratak\n\nIzbor: ");
		if (scanf("%d", &odabir) <= 0) {
			exit(EXIT_FAILURE);
		}
	} while (odabir < 1 || odabir > 4);

	ADMIN* adminS = NULL;
	fread(&brojAdmina, sizeof(int), 1, adminiF);
	adminS = alocirajAdmin(adminS, brojAdmina);

	switch (odabir) {
		case 1: {
			do {
				system("cls");
				printf("\tUlogiran: [%s]\n\n\tIT Skladiste - Listanje admina po ID-u\n\n", logiran);
				printf("1 -> Uzlazno\n2 -> Silazno\n\nIzbor: ");
				if (scanf("%d", &uzlSil) <= 0) {
					exit(EXIT_FAILURE);
				}
			} while (uzlSil < 1 || uzlSil > 2);
			fseek(adminiF, sizeof(int), SEEK_SET);
			fread(adminS, sizeof(ADMIN), brojAdmina, adminiF);
			if (uzlSil == 1) {
				qsort(adminS, brojAdmina, sizeof(ADMIN), adminPoIDUzlazno);
			}
			else {
				qsort(adminS, brojAdmina, sizeof(ADMIN), adminPoIDSilazno);
			}

			system("cls");
			printf("\n\tBroj admina: %d\n\n", brojAdmina);
			for (i = 0; i < brojAdmina; i++) {
				fprintf(stdout, "[%d] ID: %d\n", i + 1, (adminS + i)->ID);
				fprintf(stdout, "[%d] Korisnicko ime: %s", i + 1, (adminS + i)->korIme);
				fprintf(stdout, "[%d] Lozinka: %s", i + 1, (adminS + i)->lozinka);
				fprintf(stdout, "[%d] Ime: %s", i + 1, (adminS + i)->ime);
				fprintf(stdout, "[%d] Prezime: %s", i + 1, (adminS + i)->prezime);
				fprintf(stdout, "[%d] Kontakt: %s\n", i + 1, (adminS + i)->kontakt);
			}
			fprintf(stdout, "\nKraj liste.\n");
			c = _getch();
			fclose(adminiF);
			free(adminS);
			return;
		}
		case 2: {
			do {
				system("cls");
				printf("\tUlogiran: [%s]\n\n\tIT Skladiste - Listanje admina po korisnickom imenu\n\n", logiran);
				printf("1 -> Uzlazno\n2 -> Silazno\n\nIzbor: ");
				if (scanf("%d", &uzlSil) <= 0) {
					exit(EXIT_FAILURE);
				}
			} while (uzlSil < 1 || uzlSil > 2);

			fseek(adminiF, sizeof(int), SEEK_SET);
			fread(adminS, sizeof(ADMIN), brojAdmina, adminiF);
			if (uzlSil == 1) {
				qsort(adminS, brojAdmina, sizeof(ADMIN), adminPoKorImeUzlazno);
			}
			else {
				qsort(adminS, brojAdmina, sizeof(ADMIN), adminPoKorImeSilazno);
			}

			system("cls");
			printf("\n\tBroj admina: %d\n\n", brojAdmina);
			for (i = 0; i < brojAdmina; i++) {
				fprintf(stdout, "[%d] ID: %d\n", i + 1, (adminS + i)->ID);
				fprintf(stdout, "[%d] Korisnicko ime: %s", i + 1, (adminS + i)->korIme);
				fprintf(stdout, "[%d] Lozinka: %s", i + 1, (adminS + i)->lozinka);
				fprintf(stdout, "[%d] Ime: %s", i + 1, (adminS + i)->ime);
				fprintf(stdout, "[%d] Prezime: %s", i + 1, (adminS + i)->prezime);
				fprintf(stdout, "[%d] Kontakt: %s\n", i + 1, (adminS + i)->kontakt);
			}
			fprintf(stdout, "\nKraj liste.\n");
			c = _getch();
			fclose(adminiF);
			free(adminS);
			return;
		}
		case 3: {
			do {
				system("cls");
				printf("\tUlogiran: [%s]\n\n\tIT Skladiste - Listanje admina po imenu\n\n", logiran);
				printf("1 -> Uzlazno\n2 -> Silazno\n\nIzbor: ");
				if (scanf("%d", &uzlSil) <= 0) {
					exit(EXIT_FAILURE);
				}
			} while (uzlSil < 1 || uzlSil > 2);

			fseek(adminiF, sizeof(int), SEEK_SET);
			fread(adminS, sizeof(ADMIN), brojAdmina, adminiF);
			if (uzlSil == 1) {
				qsort(adminS, brojAdmina, sizeof(ADMIN), adminPoImeUzlazno);
			}
			else {
				qsort(adminS, brojAdmina, sizeof(ADMIN), adminPoImeSilazno);
			}

			system("cls");
			printf("\n\tBroj admina: %d\n\n", brojAdmina);
			for (i = 0; i < brojAdmina; i++) {
				fprintf(stdout, "[%d] ID: %d\n", i + 1, (adminS + i)->ID);
				fprintf(stdout, "[%d] Korisnicko ime: %s", i + 1, (adminS + i)->korIme);
				fprintf(stdout, "[%d] Lozinka: %s", i + 1, (adminS + i)->lozinka);
				fprintf(stdout, "[%d] Ime: %s", i + 1, (adminS + i)->ime);
				fprintf(stdout, "[%d] Prezime: %s", i + 1, (adminS + i)->prezime);
				fprintf(stdout, "[%d] Kontakt: %s\n", i + 1, (adminS + i)->kontakt);
			}
			fprintf(stdout, "\nKraj liste.\n");
			c = _getch();
			fclose(adminiF);
			free(adminS);
			return;
		}
		case 4: {
			fclose(adminiF);
			free(adminS);
			return;
		}
	}
}

void traziAdmin(void) {

	FILE* trazi = NULL;
	if (!(trazi = fopen("admini.bin", "rb"))) {
		system("cls");
		printf("\n\t\tPogreska!\nNema admina!\n");
		c = _getch();
		return;
	}

	int odabir, i, brojAdmina, traziID, flag = 0;

	do {
		system("cls");
		printf("\tUlogiran: [%s]\n\n\tIT Skladiste - Trazenje admina\n\n", logiran);
		printf("1 -> ID\n2 -> Korisnicko ime\n3 -> Povratak\n\nIzbor: ");
		if (scanf("%d", &odabir) <= 0) {
			exit(EXIT_FAILURE);
		}
	} while (odabir < 1 || odabir > 3);

	ADMIN* adminS = NULL;
	fread(&brojAdmina, sizeof(int), 1, trazi);
	adminS = alocirajAdmin(adminS, brojAdmina);

	switch (odabir) {
	case 1: {
		system("cls");
		printf("\nUnesite ID: ");
		if (scanf("%d", &traziID) <= 0) {
			exit(EXIT_FAILURE);
		}
		for (i = 0; i < brojAdmina; i++) {
			fread(adminS, sizeof(ADMIN), 1, trazi);
			if (adminS->ID == traziID) {
				fprintf(stdout, "\n[%d] ID: %d\n", i + 1, adminS->ID);
				fprintf(stdout, "[%d] Korisnicko ime: %s", i + 1, adminS->korIme);
				fprintf(stdout, "[%d] Lozinka: %s", i + 1, adminS->lozinka);
				fprintf(stdout, "[%d] Ime: %s", i + 1, adminS->ime);
				fprintf(stdout, "[%d] Prezime: %s", i + 1, adminS->prezime);
				fprintf(stdout, "[%d] Kontakt: %s", i + 1, adminS->kontakt);
				flag = 1;
				c = _getch();
				break;
			}
		}
		if (flag == 0) {
			printf("\nNe postji admin sa ID: [%d].\n", traziID);
			c = _getch();
		}
		free(adminS);
		fclose(trazi);
		return;
	}
	case 2: {
		char* traziKIme;
		if (!(traziKIme = (char*)calloc(20, sizeof(char)))) {
			exit(EXIT_FAILURE);
		}
		system("cls");
		c = getchar();
		printf("\nUnesite korisnicko ime: ");
		if(fgets(traziKIme, 19, stdin) == NULL) {
			exit(EXIT_FAILURE);
		}
		for (i = 0; i < brojAdmina; i++) {
			fread(adminS, sizeof(ADMIN), 1, trazi);
			if (strcmp(adminS->korIme, traziKIme) == 0) {
				fprintf(stdout, "\n[%d] ID: %d\n", i + 1, adminS->ID);
				fprintf(stdout, "[%d] Korisnicko ime: %s", i + 1, adminS->korIme);
				fprintf(stdout, "[%d] Lozinka: %s", i + 1, adminS->lozinka);
				fprintf(stdout, "[%d] Ime: %s", i + 1, adminS->ime);
				fprintf(stdout, "[%d] Prezime: %s", i + 1, adminS->prezime);
				fprintf(stdout, "[%d] Kontakt: %s", i + 1, adminS->kontakt);
				flag = 1;
				c = _getch();
				break;
			}
		}
		if (flag == 0) {
			*(traziKIme + (strlen(traziKIme) - 1)) = 0;
			printf("\nNe postoji admin sa korisnickim imenom: [%s].\n", traziKIme);
			c = _getch();
		}
		free(adminS);
		free(traziKIme);
		fclose(trazi);
		return;
	}
	case 3: {
		free(adminS);
		fclose(trazi);
		return;
	}
	}
}

void kreirajInventar(void) {

	INV* inventarS = NULL;
	inventarS = alocirajInventar(inventarS, 1);
	FILE* inventarF = NULL;
	if (!(inventarF = fopen("inventar.bin", "r+b"))) {		
		if (!(inventarF = fopen("inventar.bin", "wb"))) {
			exit(EXIT_FAILURE);
		}
		system("cls");
		printf("\n\tUnos 1. objekta.\n\nUnesite serijski broj: ");
		if (scanf("%d", &inventarS->serijskiBroj) <= 0) {
			exit(EXIT_FAILURE);
		}
		printf("Unesite naziv: ");
		c = getchar();
		if (fgets(inventarS->naziv, 49, stdin) == NULL) {
			exit(EXIT_FAILURE);
		}
		printf("Unesite tip: ");
		if(fgets(inventarS->tip, 29, stdin) == NULL) {
			exit(EXIT_FAILURE);
		}
		printf("Unesite kolicinu: ");
		if (scanf("%d", &inventarS->kolicina) <= 0) {
			exit(EXIT_FAILURE);
		}
		printf("Unesite nabavnu cijenu: ");
		if (scanf("%f", &inventarS->nabavnCijena) <= 0) {
			exit(EXIT_FAILURE);
		}
		printf("Unesite prodajnu cijenu: ");
		if (scanf("%f", &inventarS->prodajnaCijena) <= 0) {
			exit(EXIT_FAILURE);
		}
		int brojInventara = 1;
		fwrite(&brojInventara, sizeof(int), 1, inventarF);
		fwrite(inventarS, sizeof(INV), 1, inventarF);
		free(inventarS);
		fclose(inventarF);
		return;
	}
	else {
		int brojInventara;
		fread(&brojInventara, sizeof(int), 1, inventarF);
		INV* inventarPomocna = NULL;
		inventarPomocna = alocirajInventar(inventarS, brojInventara);
		fread(inventarPomocna, sizeof(INV), brojInventara, inventarF);
		brojInventara++;
		system("cls");
		printf("\n\tUnos %d. objekta.\n\nUnesite serijski broj: ", brojInventara);
		if (scanf("%d", &inventarS->serijskiBroj) <= 0) {
			exit(EXIT_FAILURE);
		}
		printf("Unesite naziv: ");
		c = getchar();
		if(fgets(inventarS->naziv, 49, stdin) == NULL) {
			exit(EXIT_FAILURE);
		}
		printf("Unesite tip: ");
		if(fgets(inventarS->tip, 29, stdin) == NULL) {
			exit(EXIT_FAILURE);
		}
		printf("Unesite kolicinu: ");
		if (scanf("%d", &inventarS->kolicina) <= 0) {
			exit(EXIT_FAILURE);
		}
		printf("Unesite nabavnu cijenu: ");
		if (scanf("%f", &inventarS->nabavnCijena) <= 0) {
			exit(EXIT_FAILURE);
		}
		printf("Unesite prodajnu cijenu: ");
		if (scanf("%f", &inventarS->prodajnaCijena) <= 0) {
			exit(EXIT_FAILURE);
		}
		rewind(inventarF);
		fwrite(&brojInventara, sizeof(int), 1, inventarF);
		fseek(inventarF, sizeof(int) + ((brojInventara - 1) * sizeof(INV)), SEEK_SET);
		fwrite(inventarS, sizeof(INV), 1, inventarF);
		free(inventarS);
		free(inventarPomocna);
		fclose(inventarF);
		return;
	}
}

void obrisiInventar(void) {

	FILE* inventarF = NULL;	
	if (!(inventarF = fopen("inventar.bin", "rb"))) {
		system("cls");
		printf("\n\t\tPogreska!\nInventar prazan!\n");
		c = _getch();
		return;
	}

	int odabir, brojInventara, obrisiID, pomocna, i;

	do {
		system("cls");
		printf("\tUlogiran: [%s]\n\n\tIT Skladiste - Brisanje inventara\n\n", logiran);
		printf("1 -> Serijski broj\n2 -> Naziv\n3 -> Povratak\n\nIzbor: ");
		if (scanf("%d", &odabir) <= 0) {
			exit(EXIT_FAILURE);
		}
	} while (odabir < 1 || odabir > 3);

	FILE* privremeniF = NULL;	
	if (!(privremeniF = fopen("tmp.bin", "wb"))) {
		exit(EXIT_FAILURE);
	}

	fread(&brojInventara, sizeof(int), 1, inventarF);
	INV* brisanjeS = NULL;
	brisanjeS = alocirajInventar(brisanjeS, brojInventara);

	switch (odabir) {
		case 1: {
			printf("\nUnesite ID za brisanje: ");
			if (scanf("%d", &obrisiID) <= 0) {
				exit(EXIT_FAILURE);
			}
			int pronadjen = 0;
			pomocna = brojInventara - 1;
			fwrite(&pomocna, sizeof(int), 1, privremeniF);

			for (i = 0; i < brojInventara; i++) {
				fread(brisanjeS, sizeof(INV), 1, inventarF);
				if (brisanjeS->serijskiBroj == obrisiID) {
					pronadjen = 1;
				}
				else {
					fwrite(brisanjeS, sizeof(INV), 1, privremeniF);
				}
			}

			if (pronadjen != 1) {
				system("cls");
				printf("\n\tObjekt sa ID [%d] nije pronadjena.\n", obrisiID);
				fclose(inventarF);
				fclose(privremeniF);
				free(brisanjeS);
				c = _getch();
			}
			else {
				system("cls");
				printf("\n\tObjekt sa ID [%d] je uklonjena.\n", obrisiID);
				c = _getch();
				if (pomocna == 0) {
					fclose(inventarF);
					fclose(privremeniF);
					free(brisanjeS);
					if(remove("inventar.bin") != 0) {
						exit(EXIT_FAILURE);
					}
					if(remove("tmp.bin") != 0) {
						exit(EXIT_FAILURE);
					}
					printf("\n\tInventar prazan.\n");
					c = _getch();
				}
				else {
					fclose(inventarF);
					fclose(privremeniF);
					free(brisanjeS);
					if(remove("inventar.bin") != 0) {
						exit(EXIT_FAILURE);
					}
					if (rename("tmp.bin", "inventar.bin") != 0) {
						exit(EXIT_FAILURE);
					}
				}
			}
			return;
		}
		case 2: {
			char* obrisiNaziv;
			int pronadjen = 0;		
			if (!(obrisiNaziv = (char*)calloc(20, sizeof(char)))) {
				exit(EXIT_FAILURE);
			}
			c = getchar();
			printf("\nUnesite naziv za brisanje: ");
			if(fgets(obrisiNaziv, 19, stdin) == NULL) {
				exit(EXIT_FAILURE);
			}
			pomocna = brojInventara - 1;
			fwrite(&pomocna, sizeof(int), 1, privremeniF);
			for (i = 0; i < brojInventara; i++) {
				fread(brisanjeS, sizeof(INV), 1, inventarF);
				if (strcmp(brisanjeS->naziv, obrisiNaziv) == 0) {
					pronadjen = 1;
				}
				else {
					fwrite(brisanjeS, sizeof(INV), 1, privremeniF);
				}
			}
			if (pronadjen != 1) {
				system("cls");
				*(obrisiNaziv + (strlen(obrisiNaziv) - 1)) = 0;
				printf("\n\tObjekt naziva [%s] nije pronadjena.\n", obrisiNaziv);
				fclose(inventarF);
				fclose(privremeniF);
				free(brisanjeS);
				free(obrisiNaziv);
				c = _getch();
			}
			else {
				system("cls");
				*(obrisiNaziv + (strlen(obrisiNaziv) - 1)) = 0;
				printf("\n\tObjekt naziva [%s] je uklonjena.\n", obrisiNaziv);
				c = _getch();
				fclose(inventarF);
				fclose(privremeniF);
				free(brisanjeS);
				free(obrisiNaziv);
				if (pomocna == 0) {
					if(remove("inventar.bin") != 0) {
						exit(EXIT_FAILURE);
					}
					if(remove("tmp.bin") != 0) {
						exit(EXIT_FAILURE);
					}
					printf("\n\tInventar prazan.\n");
					c = _getch();
				}
				else {
					if(remove("inventar.bin") != 0) {
						exit(EXIT_FAILURE);
					}
					if (rename("tmp.bin", "inventar.bin") != 0) {
						exit(EXIT_FAILURE);
					}
				}
			}
			return;
		}
		case 3: {
			fclose(inventarF);
			fclose(privremeniF);
			free(brisanjeS);
			return;
		}
	}
}

void listajInventar(void) {

	FILE* inventarF = NULL;
	if (!(inventarF = fopen("inventar.bin", "rb"))) {
		system("cls");
		printf("\n\t\tPogreska!\nInventar prazan!\n");
		c = _getch();
		return;
	}

	int odabir, brojInventara, uzlSil, i;

	do {
		system("cls");
		printf("\tUlogiran: [%s]\n\n\tIT Skladiste - Listanje inventara\n\n", logiran);
		printf("1 -> Serijski broj\n2 -> Tip\n3 -> Nabavna cijena\n4 -> Prodajna cijena\n5 -> Povratak\n\nIzbor: ");		
		if (scanf("%d", &odabir) <= 0) {
			exit(EXIT_FAILURE);
		}
	} while (odabir < 1 || odabir > 5);

	INV* inventarS = NULL;
	fread(&brojInventara, sizeof(int), 1, inventarF);
	inventarS = alocirajInventar(inventarS, brojInventara);

	switch (odabir) {
		case 1: {
			do {
				system("cls");
				printf("\tUlogiran: [%s]\n\n\tIT Skladiste - Listanje inventara po serijskom broju\n\n", logiran);
				printf("1 -> Uzlazno\n2 -> Silazno\n\nIzbor: ");
				if (scanf("%d", &uzlSil) <= 0) {
					exit(EXIT_FAILURE);
				}
			} while (uzlSil < 1 || uzlSil > 2);

			fseek(inventarF, sizeof(int), SEEK_SET);
			fread(inventarS, sizeof(INV), brojInventara, inventarF);
			if (uzlSil == 1) {
				qsort(inventarS, brojInventara, sizeof(INV), inventarPoSBUzlazno);
			}
			else {
				qsort(inventarS, brojInventara, sizeof(INV), inventarPoSBSilazno);
			}

			system("cls");
			printf("\n\tBroj objekata: %d\n\n", brojInventara);
			for (i = 0; i < brojInventara; i++) {
				fprintf(stdout, "[%d] Serijski broj: %d\n", i + 1, (inventarS + i)->serijskiBroj);
				fprintf(stdout, "[%d] Naziv: %s", i + 1, (inventarS + i)->naziv);
				fprintf(stdout, "[%d] Tip: %s", i + 1, (inventarS + i)->tip);
				fprintf(stdout, "[%d] Nabavna cijena: %.2f\n", i + 1, (inventarS + i)->nabavnCijena);
				fprintf(stdout, "[%d] Prodajna cijena: %.2f\n", i + 1, (inventarS + i)->prodajnaCijena);
				fprintf(stdout, "[%d] Kolicina: %d\n\n", i + 1, (inventarS + i)->kolicina);			
			}
			fprintf(stdout, "\nKraj liste.\n");
			c = _getch();
			fclose(inventarF);
			free(inventarS);
			return;
		}
		case 2: {
			do {
				system("cls");
				printf("\tUlogiran: [%s]\n\n\tIT Skladiste - Listanje inventara po tipu\n\n", logiran);
				printf("1 -> Uzlazno\n2 -> Silazno\n\nIzbor: ");
				if (scanf("%d", &uzlSil) <= 0) {
					exit(EXIT_FAILURE);
				}
			} while (uzlSil < 1 || uzlSil > 2);

			fseek(inventarF, sizeof(int), SEEK_SET);
			fread(inventarS, sizeof(INV), brojInventara, inventarF);
			if (uzlSil == 1) {
				qsort(inventarS, brojInventara, sizeof(INV), inventarPoTipUzlazno);
			}
			else {
				qsort(inventarS, brojInventara, sizeof(INV), inventarPoTipSilazno);
			}

			system("cls");
			printf("\n\tBroj objekata: %d\n\n", brojInventara);
			for (i = 0; i < brojInventara; i++) {
				fprintf(stdout, "[%d] Serijski broj: %d\n", i + 1, (inventarS + i)->serijskiBroj);
				fprintf(stdout, "[%d] Naziv: %s", i + 1, (inventarS + i)->naziv);
				fprintf(stdout, "[%d] Tip: %s", i + 1, (inventarS + i)->tip);
				fprintf(stdout, "[%d] Nabavna cijena: %.2f\n", i + 1, (inventarS + i)->nabavnCijena);
				fprintf(stdout, "[%d] Prodajna cijena: %.2f\n", i + 1, (inventarS + i)->prodajnaCijena);
				fprintf(stdout, "[%d] Kolicina: %d\n\n", i + 1, (inventarS + i)->kolicina);
			}
			fprintf(stdout, "\nKraj liste.\n");
			c = _getch();
			fclose(inventarF);
			free(inventarS);
			return;
		}
		case 3: {
			do {
				system("cls");
				printf("\tUlogiran: [%s]\n\n\tIT Skladiste - Listanje inventara po nabavnoj cijeni\n\n", logiran);
				printf("1 -> Uzlazno\n2 -> Silazno\n\nIzbor: ");
				if (scanf("%d", &uzlSil) <= 0) {
					exit(EXIT_FAILURE);
				}
			} while (uzlSil < 1 || uzlSil > 2);

			fseek(inventarF, sizeof(int), SEEK_SET);
			fread(inventarS, sizeof(INV), brojInventara, inventarF);
			if (uzlSil == 1) {
				qsort(inventarS, brojInventara, sizeof(INV), inventarPoNabCUzlazno);
			}
			else {
				qsort(inventarS, brojInventara, sizeof(INV), inventarPoNabCSilazno);
			}

			system("cls");
			printf("\n\tBroj objekata: %d\n\n", brojInventara);
			for (i = 0; i < brojInventara; i++) {
				fprintf(stdout, "[%d] Serijski broj: %d\n", i + 1, (inventarS + i)->serijskiBroj);
				fprintf(stdout, "[%d] Naziv: %s", i + 1, (inventarS + i)->naziv);
				fprintf(stdout, "[%d] Tip: %s", i + 1, (inventarS + i)->tip);
				fprintf(stdout, "[%d] Nabavna cijena: %.2f\n", i + 1, (inventarS + i)->nabavnCijena);
				fprintf(stdout, "[%d] Prodajna cijena: %.2f\n", i + 1, (inventarS + i)->prodajnaCijena);
				fprintf(stdout, "[%d] Kolicina: %d\n\n", i + 1, (inventarS + i)->kolicina);
			}
			fprintf(stdout, "\nKraj liste.\n");
			c = _getch();
			fclose(inventarF);
			free(inventarS);
			return;
		}
		case 4: {
			do {
				system("cls");
				printf("\tUlogiran: [%s]\n\n\tIT Skladiste - Listanje inventara po prodajnoj cijeni\n\n", logiran);
				printf("1 -> Uzlazno\n2 -> Silazno\n\nIzbor: ");
				if (scanf("%d", &uzlSil) <= 0) {
					exit(EXIT_FAILURE);
				}
			} while (uzlSil < 1 || uzlSil > 2);

			fseek(inventarF, sizeof(int), SEEK_SET);
			fread(inventarS, sizeof(INV), brojInventara, inventarF);
			if (uzlSil == 1) {
				qsort(inventarS, brojInventara, sizeof(INV), inventarPoProdCUzlazno);
			}
			else {
				qsort(inventarS, brojInventara, sizeof(INV), inventarPoProdCSilazno);
			}

			system("cls");
			printf("\n\tBroj objekata: %d\n\n", brojInventara);
			for (i = 0; i < brojInventara; i++) {
				fprintf(stdout, "[%d] Serijski broj: %d\n", i + 1, (inventarS + i)->serijskiBroj);
				fprintf(stdout, "[%d] Naziv: %s", i + 1, (inventarS + i)->naziv);
				fprintf(stdout, "[%d] Tip: %s", i + 1, (inventarS + i)->tip);
				fprintf(stdout, "[%d] Nabavna cijena: %.2f\n", i + 1, (inventarS + i)->nabavnCijena);
				fprintf(stdout, "[%d] Prodajna cijena: %.2f\n", i + 1, (inventarS + i)->prodajnaCijena);
				fprintf(stdout, "[%d] Kolicina: %d\n\n", i + 1, (inventarS + i)->kolicina);
			}
			fprintf(stdout, "\nKraj liste.\n");
			c = _getch();
			fclose(inventarF);
			free(inventarS);
			return;
		}
		case 5: {
			fclose(inventarF);
			free(inventarS);
			return;
		}
	}
}

void traziInventar(void) {

	FILE* trazi = NULL;
	if (!(trazi = fopen("inventar.bin", "rb"))) {
		system("cls");
		printf("\n\t\tPogreska!\nInventar prazan!\n");
		c = _getch();
		return;
	}

	int odabir, i, brojInventara, traziID, flag = 0;
	char* traziTip;

	do {
		system("cls");
		printf("\tUlogiran: [%s]\n\n\tIT Skladiste - Pretrazi inventara\n\n", logiran);
		printf("1 -> Serijski broj\n2 -> Tip\n3 -> Povratak\n\nIzbor: ");
		if (scanf("%d", &odabir) <= 0) {
			exit(EXIT_FAILURE);
		}
	} while (odabir < 1 || odabir > 3);

	INV* inventarS = NULL;
	fread(&brojInventara, sizeof(int), 1, trazi);
	inventarS = alocirajInventar(inventarS, brojInventara);

	switch (odabir) {
		case 1: {
			system("cls");
			printf("\nUnesite serijski broj: ");
			if (scanf("%d", &traziID) <= 0) {
				exit(EXIT_FAILURE);
			}
			for (i = 0; i < brojInventara; i++) {
				fread(inventarS, sizeof(INV), 1, trazi);
				if (inventarS->serijskiBroj == traziID) {
					fprintf(stdout, "[%d] Serijski broj: %d\n", i + 1, inventarS->serijskiBroj);
					fprintf(stdout, "[%d] Naziv: %s", i + 1, inventarS->naziv);
					fprintf(stdout, "[%d] Tip: %s", i + 1, inventarS->tip);
					fprintf(stdout, "[%d] Nabavna cijena: %.2f\n", i + 1, inventarS->nabavnCijena);
					fprintf(stdout, "[%d] Prodajna cijena: %.2f\n", i + 1, inventarS->prodajnaCijena);
					fprintf(stdout, "[%d] Kolicina: %d\n\n", i + 1, inventarS->kolicina);
					flag = 1;
					c = _getch();
					break;
				}
			}
			if (flag == 0) {
				printf("\nNe postji objekt sa serijskim brojem: [%d].\n", traziID);
				c = _getch();
			}
			free(inventarS);
			fclose(trazi);
			return;
		}
		case 2: {
			if (!(traziTip = calloc(30, sizeof(char)))) {
				exit(EXIT_FAILURE);
			}
			system("cls");
			c = getchar();
			printf("\nUnesite tip: ");
			if(fgets(traziTip, 29, stdin) == NULL) {
				exit(EXIT_FAILURE);
			}
			for (i = 0; i < brojInventara; i++) {
				fread(inventarS, sizeof(INV), 1, trazi);
				if (strcmp(inventarS->tip, traziTip) == 0) {
					fprintf(stdout, "[%d] Serijski broj: %d\n", i + 1, inventarS->serijskiBroj);
					fprintf(stdout, "[%d] Naziv: %s", i + 1, inventarS->naziv);
					fprintf(stdout, "[%d] Tip: %s", i + 1, inventarS->tip);
					fprintf(stdout, "[%d] Nabavna cijena: %.2f\n", i + 1, inventarS->nabavnCijena);
					fprintf(stdout, "[%d] Prodajna cijena: %.2f\n", i + 1, inventarS->prodajnaCijena);
					fprintf(stdout, "[%d] Kolicina: %d\n\n", i + 1, inventarS->kolicina);
					flag = 1;
				}
			}
			c = _getch();
			if (flag == 0) {
				*(traziTip + (strlen(traziTip) - 1)) = 0;
				printf("\nNe postoji objekt tipa: [%s].\n", traziTip);
				c = _getch();
			}
			free(inventarS);
			free(traziTip);
			fclose(trazi);
			return;
		}
		case 3: {
			free(inventarS);
			fclose(trazi);
			return;
		}
	}
}