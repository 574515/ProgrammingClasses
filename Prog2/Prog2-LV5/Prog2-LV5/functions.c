#include "header.h"
#include <stdio.h>
#include <stdlib.h>

short** arrayAllocation(int m) {
	short** arr;
	arr = malloc(m * sizeof(short*));
	if (!arr) exit(EXIT_FAILURE);
	for (int i = 0; i < m; i++) {
		*(arr + i) = malloc(m * sizeof(short));
		if (!*(arr + i)) exit(EXIT_FAILURE);
	}
	return arr;
}

void fillArray(short** arr, int m) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) *(*(arr + i) + j) = rand() % (250 + 1 - (-1550)) + (-1550);
	}
}

short biggestEvenNumber(short** arr, int m) {
	short biggestEven = SHRT_MIN;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) if ((i + j) >= m && (*(*(arr + i) + j) % 2 == 0) && *(*(arr + i) + j) > biggestEven) biggestEven = *(*(arr + i) + j);
	}
	return biggestEven;
}

void newArray(short** arr, int m, short num) {
	for (int i = 0; i < m; i++) {
		for(int j = 0; j < m; j++) if((i + j) < (m - 1)) * (*(arr + i) + j) = num;
	}
}

void printArray(short** arr, int m) {
	for (int i = 0; i < m; i++) {
		for(int j = 0; j < m; j++) printf("%5d ", *(*(arr + i) + j));
		printf("\n");
	}
}

void arrayDeallocation(short** arr, int m) {
	for (int i = 0; i < m; i++) free(*(arr + i));
	free(arr);
}