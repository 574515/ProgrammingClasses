#include "header.h"
#include <stdio.h>
#include <stdlib.h>

void insertBeginning(STUDENT** root, int id) {
	STUDENT* tempNode = malloc(sizeof(STUDENT));
	if (!tempNode) exit(EXIT_FAILURE);
	enterFirstAndLastName(tempNode);
	tempNode->id = id;
	tempNode->next = *root;
	*root = tempNode;
}

void enterFirstAndLastName(STUDENT* tempNode) {
	if (fprintf(stdout, "Unesite ime: ") <= 0) exit(EXIT_FAILURE);
	if (getchar() <= 0) exit(EXIT_FAILURE);
	if (fgets(tempNode->ime, 30, stdin) == NULL) exit(EXIT_FAILURE);
	if (fprintf(stdout, "Unesite prezime: ") <= 0) exit(EXIT_FAILURE);
	if (getchar() <= 0) exit(EXIT_FAILURE);
	if (fgets(tempNode->prezime, 30, stdin) == NULL) exit(EXIT_FAILURE);
}

void printStudents(STUDENT* root) {
	for (STUDENT* tempNode = root; tempNode != NULL; tempNode = tempNode->next) {
		if (fprintf(stdout, "Ime: %s", tempNode->ime) <= 0) exit(EXIT_FAILURE);
		if (fprintf(stdout, "Prezime: %s", tempNode->prezime) <= 0) exit(EXIT_FAILURE);
		if (fprintf(stdout, "ID: %d\n\n", tempNode->id) <= 0) exit(EXIT_FAILURE);
	}
}

void printStudentCount(STUDENT* root) {
	int temp = countStudents(root);
	if (temp == 1) printf("Unesen je %d student.\n", temp);
	else if (temp >= 2 || temp <= 4) printf("Unesena su %d studenta.\n", temp);
	else printf("Uneseno je %d studenata.\n", temp);
}

int countStudents(STUDENT* root) {
	int count = 0;
	for (STUDENT* tempNode = root; tempNode != NULL; tempNode = tempNode->next) count++;
	return count;
}

void removeStudent(STUDENT** root, int id) {
	if (*root == NULL) return;
	if ((*root)->id == id) {
		STUDENT* tempNode = *root;
		*root = (*root)->next;
		free(tempNode);
		return;
	}
	for (STUDENT* tempNode = *root; tempNode->next != NULL; tempNode = tempNode->next) {
		if (tempNode->next->id == id) {
			STUDENT* toRemove = tempNode->next;
			tempNode->next = tempNode->next->next;
			free(toRemove);
			return;
		}
	}
}

void helpingPrint(int primaryID, char arg) {
	printf("\n-------------------------------------\n");
	if (arg == 'p') printf("   Student sa ID [%d] je uklonjen.", primaryID);
	else if (arg == 'r') printf("Lista studenata je uspjesno obrisana.");
	printf("\n-------------------------------------\n\n");
}

void deallocate(STUDENT** root) {
	STUDENT* tempNode = *root;
	while (tempNode != NULL) {
		STUDENT* remNode = tempNode;
		tempNode = tempNode->next;
		free(remNode);
	}
	*root = NULL;
}