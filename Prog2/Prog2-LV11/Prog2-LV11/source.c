#include "header.h"
#include <stdio.h>
#include <stdlib.h>

/*	1. Potrebno je napisati C program u kojemu se kreira jednostruki povezani popis. Potrebno je kreirati strukturu koja
	opisuje studenta: (kreirano pod typedef struct student{};). Napisati funkciju unosImenaPrezime(), pomoću koje se treba
	dohvatiti posebno ime i prezime. Podatkovni član id, također je potrebno dohvatiti sa standardnog ulaza. Dodati
	četiri studenta na početak povezano popisa. Ispisati cijeli povezani popisi ispisati koliko ima elemenata, a nakon toga
	izbrisati studenta kojega se prvi puta kreiralo i to tako da ga se potraži preko id - a. Nakon što se obriše student,
	potrebno je ponovno ispisati cijeli povezani popis i ispisati koliko ima elemenata. Na kraju je potrebno obrisati cijeli
	povezani popis. */

int main(void) {
	STUDENT* root = NULL;
	int i, id, temp;
	for (i = 0; i < 4; i++) {
		system("cls");
		printf("\t[%d. student]\n\nUnesite ID: ", (i + 1));
		if (scanf("%d", &id) <= 0) exit(EXIT_FAILURE);
		if (i == 0) temp = id;
		insertBeginning(&root, id);
	}
	system("cls");
	printStudents(root);
	printStudentCount(root);
	removeStudent(&root, temp);
	helpingPrint(temp, 'p');
	printStudents(root);
	printStudentCount(root);
	deallocate(&root);
	helpingPrint(temp, 'r');
	_CrtDumpMemoryLeaks();
	return 0;
}