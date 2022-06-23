#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*	1. Napisati C program koji će omogućiti zauzimanje memorije za dvodimenzionalno polje polje2d cjelobrojnih vrijednosti
	tipa short duljine m redova i stupaca. Unutar dvodimenzionalnog polja potrebno je ispod sporedne dijagonale pronaći
	najveći parni broj i tim parnim brojem prepisati sve vrijednosti iznad sporedne dijagonale. Ispisati novonastalo
	dvodimenzionalno polje. Popuniti dvodimenzionalno polje pseudo-slučajnim vrijednostima, kao i varijablu m.
		1.1. U main() funkciji (u glavnom dijelu programa) postaviti m na pseudo-slučajnu vrijednost iz traženog intervala,
		(3<m<=18) i pozvati sve ostale funkcije za upravljanjem dvodimenzionalnim poljem.
		1.2. Napisati funkciju zauzimanjeMatrice() pomoću koje se dinamički zauzima memorijski prostor da dvodimenzionalno
		polje (u potpunosti rukovati memorijom). Funkcija zauzimanjeMatrice() vraća zauzeto dvodimenzionalno polje, a za
		parametre prima broj redova i stupaca.
		1.3. Napisati funkciji popunjavanjeMatrice() pomoću koje treba popuniti dvodimenzionalno polje pseudo-slučajnim
		vrijednostima iz intervala [-1550, 250]. Funkcija popunjavanjeMatrice() ne vraća vrijednost, a kao parametar prima
		dvodimenzionalno polje, te broj redova i stupaca.
		1.4. Napisati funkciju najveciParniBroj() pomoću koje je potrebno pronaći najveći parni broj ispod sporedne	dijagonale
		dvodimenzionalnog polja. Funkcija najveciParniBroj() vraća vrijednost, a kao parametar prima dvodimenzionalno polje,
		broj redova i stupaca.
		1.5. Napisati funkciju novaMatrica() pomoću koje treba najvećim parnim brojem prepisati sve vrijednosti iznad sporedne
		dijagonale. Funkcija novaMatrica() ne vraća vrijednost, a kao parametar prima dvodimenzionalno polje, broj redova i
		stupaca, te najveći parni broj.
		1.6. Napisati funkciju ispisMatrice() pomoću koje treba ispisati dvodimenzionalno polje u matričnom obliku. Funkcija
		ispisMatrice() ne vraća vrijednost, a kao parametar prima dvodimenzionalno polje, te broj redova i stupaca.
		1.7. Napisati funkciju brisanjeMatrice() pomoću koje se treba osloboditi memorija. Funkcija brisanjeMatrice() vraća
		NULL vrijednost, a kao parametar prima dvodimenzionalno polje, te broj redova.
	Program organizirati u više datoteka!
	Koristiti isključivo pokazivačku notaciju! */

int main(void) {
	srand((unsigned)time(NULL));
	int m = (rand() % (18 - 3 + 1)) + 3;
	short** arr = arrayAllocation(m);
	fillArray(arr, m);
	newArray(arr, m, biggestEvenNumber(arr, m));
	printArray(arr, m);
	arrayDeallocation(arr, m);
	_CrtDumpMemoryLeaks();
	return 0;
}