#include "header.h"
#include <stdlib.h>
#include <conio.h>
#include <string.h>

void task1(void) {
	system("cls");
	FILE* readPtr;
	int num;
	char* path = "C:\\Users\\User\\source\\repos\\Prog2\\Prog2-LV7\\Prog2-LV7\\dat.txt";
	readPtr = fopen(path, "r");
	if (!readPtr) exit(EXIT_FAILURE);
	if (fscanf(readPtr, "%d", &num) <= 0) exit(EXIT_FAILURE);
	if (fclose(readPtr) != 0) exit(EXIT_FAILURE);
	task1EnterStudents(num);
	if (_getch() <= 0) exit(EXIT_FAILURE);
	_CrtDumpMemoryLeaks();
	return;
}

void task1EnterStudents(int num) {
	FILE* writePtr;
	char* fName, * lName;
	int i, studNum;
	fName = calloc(21, sizeof(char));
	if (!fName) exit(EXIT_FAILURE);
	lName = calloc(21, sizeof(char));
	if (!lName) exit(EXIT_FAILURE);
	writePtr = fopen("student.txt", "a");
	if (!writePtr) exit(EXIT_FAILURE);
	for (i = 0; i < num; i++) {
		system("cls");
		printf("[%d. student] Broj studenta: ", (i + 1));
		if (scanf("%d", &studNum) <= 0) exit(EXIT_FAILURE);
		if (getchar() <= 0) exit(EXIT_FAILURE);
		printf("[%d. student] Ime studenta: ", (i + 1));
		if (fgets(fName, 20, stdin) == NULL) exit(EXIT_FAILURE);
		printf("[%d. student] Prezime studenta: ", (i + 1));
		if (fgets(lName, 20, stdin) == NULL) exit(EXIT_FAILURE);
		if (fprintf(writePtr, "Student broj: %d.\tIme: %s\tPrezime: %s\n", studNum, fName, lName) <= 0) exit(EXIT_FAILURE);
		memset(fName, 0, sizeof(char));
		memset(lName, 0, sizeof(char));
	}
	system("cls");
	printf("Gotovo!");
	free(fName);
	free(lName);
	if (fclose(writePtr) != 0) exit(EXIT_FAILURE);
}

void task2(void) {
	system("cls");
	char* path = "C:\\Users\\User\\source\\repos\\Prog2\\Prog2-LV7\\Prog2-LV7\\in.txt";
	FILE* readPtr;
	int m, n;
	readPtr = fopen(path, "r");
	if (!readPtr) exit(EXIT_FAILURE);
	if (fscanf(readPtr, "%d\n%d", &m, &n) <= 0) exit(EXIT_FAILURE);
	if (fclose(readPtr) != 0) exit(EXIT_FAILURE);
	float** arr = task2AllocateArr(m, n);
	task2GenerateArr(arr, m, n);
	task2PrintAndSaveArr(arr, m, n);
	task2DeallocateArr(arr, m);
	if (_getch() <= 0) exit(EXIT_FAILURE);
	_CrtDumpMemoryLeaks();
	return;
}

float** task2AllocateArr(int m, int n) {
	float** arr = malloc(m * sizeof(float*));
	if (!arr) exit(EXIT_FAILURE);
	for (int i = 0; i < m; i++) {
		*(arr + i) = malloc(n * sizeof(float));
		if (!*(arr + i)) exit(EXIT_FAILURE);
	}
	return arr;
}

void task2GenerateArr(float** arr, int m, int n) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) *(*(arr + i) + j) = (-125.5f) + (float)rand() / RAND_MAX * (65.8f - (-125.5f));
	}
}

void task2PrintAndSaveArr(float** arr, int m, int n) {
	FILE* writePtr;
	writePtr = fopen("out.txt", "w");
	if (!writePtr) exit(EXIT_FAILURE);
	for (int i = 0; i < (m - 1); i++) {
		for (int j = 1; j < n; j++) {
			if (fprintf(stdout, "%15f ", *(*(arr + i) + j)) <= 0) exit(EXIT_FAILURE);
			if (fprintf(writePtr, "%15f ", *(*(arr + i) + j)) <= 0) exit(EXIT_FAILURE);
		}
		if (fprintf(stdout, "\n") <= 0) exit(EXIT_FAILURE);
		if (fprintf(writePtr, "\n") <= 0) exit(EXIT_FAILURE);
	}
	if (fclose(writePtr) != 0) exit(EXIT_FAILURE);
}

void task2DeallocateArr(float** arr, int m) {
	for (int i = 0; i < m; i++) free(*(arr + i));
	free(arr);
}

void task3(void) {
	system("cls");
	char* path = "C:\\Users\\User\\source\\repos\\Prog2\\Prog2-LV7\\Prog2-LV7\\prva.txt";
	FILE* readPtr;
	readPtr = fopen(path, "r");
	if (!readPtr) exit(EXIT_FAILURE);
	task3CopyFile(readPtr);
	if (fclose(readPtr) != 0) exit(EXIT_FAILURE);
	if (_getch() <= 0) exit(EXIT_FAILURE);
	_CrtDumpMemoryLeaks();
	return;
}

void task3CopyFile(FILE* readPtr) {
	FILE* writePtr;
	writePtr = fopen("druga.txt", "w");
	int read = (-1);
	if (!writePtr) exit(EXIT_FAILURE);
	while ((read = fgetc(readPtr)) != EOF) read >= 97 && read <= 122 ? fputc(read - 32, writePtr) : fputc(read, writePtr);
	if (fclose(writePtr) != 0) exit(EXIT_FAILURE);
}