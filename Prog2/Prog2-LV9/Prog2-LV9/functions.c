#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define N 500

int seqSteps, binSteps, counter = 0;

void task1(void) {
	system("cls");
	int* writeArr, * readArr, n, tempIndx;
	writeArr = malloc(N * sizeof(int));
	if (!writeArr) exit(EXIT_FAILURE);
	readArr = malloc(N * sizeof(int));
	if (!readArr) exit(EXIT_FAILURE);
	task1And2FillArray(writeArr);
	task1And2WriteToFile(writeArr);
	readArr = task1And2ReadFromFile(readArr);
	do {
		printf("Unesite n [0, 1000]: ");
		if (scanf("%d", &n) <= 0) exit(EXIT_FAILURE);
	} while (n < 0 || n > 1000);
	tempIndx = task1And2SeqSearch(readArr, n);
	if (tempIndx != (-1)) printf("\nBroj %d je pronadjen nakon %d koraka na indeksu %d.\n", n, seqSteps, tempIndx);
	else printf("\nBroj %d nije pronadjen.\n", n);
	free(writeArr);
	free(readArr);
	if (_getch() <= 0) exit(EXIT_FAILURE);
	_CrtDumpMemoryLeaks();
	return;
}

void task1And2FillArray(int* arr) {
	for (int i = 0; i < N; i++) *(arr + i) = (rand() % (1000 - 0 + 1)) + 0;
}

void task1And2WriteToFile(int* arr) {
	FILE* ptr = NULL;
	ptr = fopen("dat.txt", "w");
	if (!ptr) exit(EXIT_FAILURE);
	for (int i = 0; i < N; i++) if (fprintf(ptr, "%d ", *(arr + i)) <= 0) exit(EXIT_FAILURE);
	if (fclose(ptr) != 0) exit(EXIT_FAILURE);
}

int* task1And2ReadFromFile(int* arr) {
	FILE* ptr = NULL;
	ptr = fopen("dat.txt", "r");
	if (!ptr) exit(EXIT_FAILURE);
	for (int i = 0; i < N; i++) if (fscanf(ptr, "%d ", &(*(arr + i))) <= 0) exit(EXIT_FAILURE);
	if (fclose(ptr) != 0) exit(EXIT_FAILURE);
	return arr;
}

int task1And2SeqSearch(int* arr, int n) {
	seqSteps = 0;
	for (int i = 0; i < N; i++) {
		seqSteps++;
		if (*(arr + i) == n) return i;
	}
	return (-1);
}

void task2(void) {
	system("cls");
	int* writeArr, * readArr, * searchArr;
	writeArr = malloc(N * sizeof(int));
	if (!writeArr) exit(EXIT_FAILURE);
	readArr = malloc(N * sizeof(int));
	if (!readArr) exit(EXIT_FAILURE);
	task1And2FillArray(writeArr);
	task1And2WriteToFile(writeArr);
	readArr = task1And2ReadFromFile(readArr);
	searchArr = malloc(5 * sizeof(int));
	if (!searchArr) exit(EXIT_FAILURE);
	task2GetSearchNumbers(searchArr);
	task2BubbleSort(readArr);
	task2PrintResult(readArr, searchArr);
	free(writeArr);
	free(readArr);
	free(searchArr);
	if (_getch() <= 0) exit(EXIT_FAILURE);
	_CrtDumpMemoryLeaks();
	return;
}

void task2GetSearchNumbers(int* searchArr) {
	for (int i = 0; i < 5; i++) {
		do {
			system("cls");
			printf("Unesite [%d.] broj [0, 1000]: ", (i + 1));
			if (scanf("%d", &(*(searchArr + i))) <= 0) exit(EXIT_FAILURE);
		} while (*(searchArr + i) < 0 || *(searchArr + i) > 1000);
	}
}

void task2BubbleSort(int* arr) {
	for (int i = 0; i < N - 1; i++) {
		for (int j = 0; j < N - 1 - i; j++) if (arr[j + 1] < arr[j]) task2Swap(&arr[j + 1], &arr[j]);
	}
}

void task2Swap(int* const bigger, int* const smaller) {
	int temp = 0;
	temp = *smaller;
	*smaller = *bigger;
	*bigger = temp;
}

int task2BinSearch(int* arr, int n) {
	binSteps = 0;
	int ll = 0, ul = n - 1, mid = -1;
	while (ll <= ul) {
		mid = (ll + ul) / 2;
		binSteps++;
		if (arr[mid] == n) return mid;
		else if (arr[mid] > n) ul = mid - 1;
		else ll = mid + 1;
	}
	return -1;
}

void task2PrintResult(int* readArr, int* searchArr) {
	int i, tempIndx, seqCounter = 0, binCounter = 0;
	float binAvg = 0.0f, seqAvg = 0.0f;
	system("cls");
	printf("Uneseni brojevi [");
	for (i = 0; i < 5; i++) {
		if (i != 4) printf("%d, ", *(searchArr + i));
		if (i == 4) printf("%d].\n\n\t", *(searchArr + i));
	}
	printf("REZULTATI:\n\nSekvencijalno:\n");
	for (i = 0; i < 5; i++) {
		tempIndx = task1And2SeqSearch(readArr, *(searchArr + i));
		if (tempIndx != (-1)) {
			printf("%d. broj %d je pronadjen u %d koraka.\n", (i + 1), *(searchArr + i), seqSteps);
			seqAvg += seqSteps;
			seqCounter++;
		}
		else printf("%d. broj %d nije pronadjnen.\n", (i + 1), *(searchArr + i));
	}
	printf("\nBinarno:\n");
	for (i = 0; i < 5; i++) {
		tempIndx = task2BinSearch(readArr, *(searchArr + i));
		if (tempIndx != (-1)) {
			printf("%d. broj %d je pronadjen u %d koraka.\n", (i + 1), *(searchArr + i), binSteps);
			binAvg += binSteps;
			binCounter++;
		}
		else printf("%d. broj %d nije pronadjnen.\n", (i + 1), *(searchArr + i));
	}
	printf("\nSrednji broj koraka za sekvencijalno pretrazivanje je: %.2f\n", (seqAvg / seqCounter));
	printf("Srednji broj koraka za binarno pretrazivanje je: %.2f\n", (binAvg / binCounter));
}