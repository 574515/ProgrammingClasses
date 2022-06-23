#include "header.h"
#include <stdio.h>
#include <stdlib.h>

/*	1. Napisati C program kojim će se omogućiti vođenje evidencije članova jedne videoteke. Program treba omogućiti korisniku
	izbornik unutar kojeg će korisnik moći odabrati neku od radnji. Program treba kreirati datoteku clanovi.bin, ukoliko
	datoteka ne postoji na disku (prvi puta kada se pokrene program). Članovi videoteke predstavljeni su strukturom CLAN s
	članovima strukture koji su stringovi: ID, ime, prezime, adresa i broj mobitela. Na početku programa ponuditi korisniku
	izbornik za odabir željene radnje:
		1. Dodavanje novih članova u datoteku clanovi.bin
		2. Čitanje iz datoteke clanovi.bin
		3. Završetak programa
	Ako se želi unijeti novi korisnik, svaki puta je potrebno odabrati opciju br. 1 i s tipkovnice unijeti podatke o korisniku,
	također je potrebno brojati koliko se novih korisnika unijelo, te svakim novim unosom korisnika potrebno je zapisati
	korisnika u datoteku. Voditi evidenciju broja unesenih korisnika. Broj korisnika je potrebno zapisati na početku datoteke,
	a tek poslije cijele vrijednosti je potrebno zapisati strukturu CLAN. Ako je potreba za čitanjem korisnika iz datoteke
	potrebno je odabrati opciju br. 2. Potrebno je prvo pročitati cijelu vrijednost koja predstavlja ukupni broj spremljenih
	korisnika unutar datoteke, te pronaći korisnika po određenom kriteriju pretraživanja, može biti po bilo kojem članu
	strukture CLAN. Ako je potrebno završiti s programom, potrebno je odabrati opciju br. 3, nakon kojeg će se korisnika upitati
	s porukom "Da li ste sigurni kako zelite zavrsiti program?" popraćeno s opcijom da/ne koju je potrebno utipkati. Ako je
	odabrana opcija "da" zatvoriti program, ako je odabrana opcija "ne" ponuditi ponovni izbor radnji.
	Operacije za rad s datotekom izvesti s funkcijama!
	Organizirati kôd u više datoteka!

	2. Iskoristiti prethodni zadataka, no dodati jednu više operaciju (posudba filma) u izbornik:
		1. Dodavanje novih članova u datoteku clanovi.bin
		2. Čitanje iz datoteke clanovi.bin
		3. Posudba filma
		4. Završetak programa
	Kreirati strukturu FILM koja sadrži sljedeće članove koji su stringovi: ID, ime, datum. Ukoliko se odabere opcija 3, trebaju
	se izvršiti sljedeće operacije:
		- Pitati koliko se filmova želi posuditi (ne više od 4 – novi član u strukturi CLAN).
		- Za svaki film unijeti: ime filma, datum posudbe (broj manji od 365 koji označava dan u godini) i ID člana koji je
		  posudio film.
		- Sve podatke o posuđenom filmu spremiti u datoteku posudbe.bin
	Ako je korisnik već posuđivao filmove, ima pravo posuditi nove filmove dok god je broj posuđenih filmova manji od 4. Ukoliko
	ne postoji datoteka posudbe.bin, potrebno ju je kreirati, u suprotnom je otvaramo i dodajemo nove posuđene filmove, također
	je potrebno pratiti broj unesenih filmova. */

int main(void) {
	int choice;
	while (1) {
		do {
			system("cls");
			printf("\tVideoteka\n\n[1] Dodaj novog clana\n[2] Trazi clanove\n[3] Posudi film\n[4] Izlaz\n\nIzbor: " );
			if (scanf("%d", &choice) <= 0) exit(EXIT_FAILURE);
		} while (choice < 1 || choice > 4);
		switch (choice) {
		case 1: addMembers(); break;
		case 2: searchMembers(); break;
		case 3: rentAMovie(); break;
		case 4: closeProgram(); break;
		}
	}
	_CrtDumpMemoryLeaks();
	return 0;
}