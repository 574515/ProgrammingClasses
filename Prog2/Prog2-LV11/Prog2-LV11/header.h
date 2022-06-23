#ifndef HEADER_H
#define HEADER_H
#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

typedef struct student {
	char ime[31];
	char prezime[31];
	int id;
	struct student* next;
}STUDENT;

void insertBeginning(STUDENT**, int);
void enterFirstAndLastName(STUDENT*);
void printStudents(STUDENT*);
void printStudentCount(STUDENT*);
int countStudents(STUDENT*);
void removeStudent(STUDENT**, int);
void helpingPrint(int, char);
void deallocate(STUDENT**);

#endif