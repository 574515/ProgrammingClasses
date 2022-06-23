#ifndef HEADER_H
#define HEADER_H
#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdbool.h>

typedef struct member {
	char fName[21], lName[21], address[51], phoneNum[15];
	int ID, numOfMovies;
}MEM;

typedef struct movie {
	char title[41];
	int ID, memberID, date;
}MOV;

void addMembers(void);
void searchMembers(void);
void listMember(MEM*);
void rentAMovie(void);
bool memberExists(int);
int numberOfMovies(int);
void addMovies(int);
void increaseMemberMovieNum(int);
void closeProgram(void);

#endif