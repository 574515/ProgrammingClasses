#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*	1. Napisati C program koji omogućuje unos dva broja m i n sa standardnog ulaza, omogućiti unos duljine polja pomoću funkcije
	unosDuljine(). Uzeti u obzir interval za m (4 < m <= 100) i za n (3 <= n < 16). Na temelju broj m i n dinamički zauzeti
	memorijski prostor za m struktura točka i n struktura trokut (u potpunosti rukovati memorijom), pomoću funkcija
	zauzimanjeTocaka() i zauzimanjeTrokutova(). Struktura tocka sadrži dva cjelobrojna člana, a struktura trokut sadrži tri
	člana koji su pokazivači na strukturu tocka. Popuniti koordinate točaka pseudo-slučajnim odabirom iz intervala [0, m],
	koristeći funkciju popunjavanjeKoordinata(). Pseudo-slučajnim odabirom dodijeliti točke pojedinim vrhovima trokuta,
	koristeći funkciju odabirVrha(). Napisati funkciju duljinaStranice() pomoću koje se pronalazi udaljenost između dviju točaka.
	Napisati funkciju opsegTrokuta() pomoću koje se računa opseg trokuta. Pronaći i ispisati trokut koji ima najveći opseg.
	Organizirati program u više datoteka!
	Koristiti isključivo pokazivačku notaciju!
	
	2. Napisati C program koji omogućuje unos broja m sa standardnog ulaza koji predstavlja duljinu polja, unos broj m omogućiti
	pomoću funkcije unosDuljine(), gdje je (0 < m <= 60). Dinamički zauzeti memorijsku prostor za polje artikala pomoću funkcije
	kreiranjeArtikala(), u potpunosti rukovati memorijom. Struktura artikl ima članove ime, cijena i kolicina. Unos artikala
	napraviti pomoću funkcije unosArtikla(). Pomoću funkcije pretragaArtikla(), pronaći najskuplji artikl i vratiti njegovu
	memorijsku adresu. Ispisati ime, cijenu i količinu najskupljeg artikla pomoću funkcije ispisArtikla().
	Organizirati program u više datoteka!
	Koristiti isključivo pokazivačku notaciju! */

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