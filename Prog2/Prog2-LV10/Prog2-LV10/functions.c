#include "header.h"
#include <stdlib.h>
#include <conio.h>

void task1(void) {
	system("cls");
	int n;
	do {
		system("cls");
		printf("Unesite n <0, inf.>: ");
		if (scanf("%d", &n) <= 0) exit(EXIT_FAILURE);
	} while (n < 1);
	FILE* ptr;
	ptr = fopen("suma.txt", "w");
	if (!ptr) exit(EXIT_FAILURE);
	if (fprintf(ptr, "%d", task1FindSumOfDigits(n)) <= 0)exit(EXIT_FAILURE);
	if (fclose(ptr) != 0) exit(EXIT_FAILURE);
	printf("Gotovo.\n");
	if (_getch() <= 0)exit(EXIT_FAILURE);
	return;
}

int task1FindSumOfDigits(int n) {
	if (n < 1) return 0;
	return ((n % 10) + task1FindSumOfDigits(n / 10));
}

void task2(void) {
	system("cls");
	int n;
	do {
		system("cls");
		printf("Unesite n [1, 20]: ");
		if (scanf("%d", &n) <= 0) exit(EXIT_FAILURE);
	} while (n < 1 || n > 20);
	int* arr = task2AllocateArr(n);
	task2GenerateArr(arr, n, -50, 100);
	task2PrintBiggest(task2FindBiggestInArr(arr, n, *(arr + 0)));
	free(arr);
	if (_getch() <= 0)exit(EXIT_FAILURE);
	_CrtDumpMemoryLeaks();
	return;
}

int* task2AllocateArr(int n) {
	int* arr = malloc(n * sizeof(float*));
	if (!arr) exit(EXIT_FAILURE);
	return arr;
}

void task2GenerateArr(int* arr, int n, int ll, int ul) {
	for (int i = 0; i < n; i++) *(arr + i) = (rand() % (ul - ll + 1)) + ll;
}

int task2FindBiggestInArr(int* arr, int n, int biggest) {
	if (n == 0) return biggest;
	if (arr[n] > biggest) biggest = arr[n];
	return task2FindBiggestInArr(arr, n - 1, biggest);
}

void task2PrintBiggest(int temp) {
	FILE* ptr;
	ptr = fopen("najveci.txt", "w");
	if (!ptr) exit(EXIT_FAILURE);
	if (fprintf(ptr, "%d", temp) <= 0) exit(EXIT_FAILURE);
	if (fprintf(stdout, "\nNajveci broj u polju je %d.\n", temp) <= 0) exit(EXIT_FAILURE);
	if (fclose(ptr) != 0) exit(EXIT_FAILURE);
}

void task3(void) {
	system("cls");
	char* arr = task3AllocateArr(51);
	task3GetString(arr);
	task3PrintString(arr);
	free(arr);
	if (_getch() <= 0)exit(EXIT_FAILURE);
	_CrtDumpMemoryLeaks();
	return;
}

char* task3AllocateArr(int n) {
	char* arr = malloc(n * sizeof(float*));
	if (!arr) exit(EXIT_FAILURE);
	return arr;
}

void task3GetString(char* arr) {
	printf("Unesite string: ");
	if (getchar() <= 0) exit(EXIT_FAILURE);
	if (fgets(arr, 50, stdin) == NULL) exit(EXIT_FAILURE);
}

void task3PrintString(char* arr) {
	FILE* ptr;
	ptr = fopen("string.txt", "w");
	if (!ptr) exit(EXIT_FAILURE);
	printf("\n");
	task3ReverseString(arr, ptr);
	if (fclose(ptr) != 0) exit(EXIT_FAILURE);
}

void task3ReverseString(char* arr, FILE* ptr) {
	if (*arr) {
		task3ReverseString(arr + 1, ptr);
		if (*arr != '\n') {
			if (fprintf(stdout, "%c", *arr) <= 0) exit(EXIT_FAILURE);
			if (fprintf(ptr, "%c", *arr) <= 0) exit(EXIT_FAILURE);
		}
	}
}