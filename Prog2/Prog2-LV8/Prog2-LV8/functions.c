#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

void addMembers(void) {
	MEM* memberStruct = NULL;
	memberStruct = (MEM*)calloc(1, sizeof(MEM));
	if (!memberStruct) exit(EXIT_FAILURE);
	FILE* ptr = NULL;
	ptr = fopen("clanovi.bin", "r+b");
	if (!ptr) {
		ptr = fopen("clanovi.bin", "wb");
		if (!ptr) exit(EXIT_FAILURE);
		system("cls");
		printf("\n\tUnos 1. clana.\n\nUnesite ID: ");
		if (scanf("%d", &memberStruct->ID) <= 0) exit(EXIT_FAILURE);
		printf("Unesite ime: ");
		if (getchar() <= 0) exit(EXIT_FAILURE);
		if (fgets(memberStruct->fName, 20, stdin) == NULL) exit(EXIT_FAILURE);
		printf("Unesite prezime: ");
		if (fgets(memberStruct->lName, 20, stdin) == NULL) exit(EXIT_FAILURE);
		printf("Unesite adresu: ");
		if (fgets(memberStruct->address, 50, stdin) == NULL) exit(EXIT_FAILURE);
		printf("Unesite broj telefona: ");
		if (fgets(memberStruct->phoneNum, 14, stdin) == NULL) exit(EXIT_FAILURE);
		memberStruct->numOfMovies = 0;
		int memNum = 1;
		if (fwrite(&memNum, sizeof(int), 1, ptr) <= 0) exit(EXIT_FAILURE);
		if (fwrite(memberStruct, sizeof(MEM), 1, ptr) <= 0) exit(EXIT_FAILURE);
		if (fclose(ptr) != 0) exit(EXIT_FAILURE);
		free(memberStruct);
		_CrtDumpMemoryLeaks();
		return;
	}
	else {
		int memNum;
		if (fread(&memNum, sizeof(int), 1, ptr) <= 0) exit(EXIT_FAILURE);
		memNum++;
		system("cls");
		printf("\n\tUnos %d. clana.\n\nUnesite ID: ", memNum);
		if (scanf("%d", &memberStruct->ID) <= 0) exit(EXIT_FAILURE);
		printf("Unesite ime: ");
		if (getchar() <= 0) exit(EXIT_FAILURE);
		if (fgets(memberStruct->fName, 20, stdin) == NULL) exit(EXIT_FAILURE);
		printf("Unesite prezime: ");
		if (fgets(memberStruct->lName, 20, stdin) == NULL) exit(EXIT_FAILURE);
		printf("Unesite adresu: ");
		if (fgets(memberStruct->address, 50, stdin) == NULL) exit(EXIT_FAILURE);
		printf("Unesite broj telefona: ");
		if (fgets(memberStruct->phoneNum, 14, stdin) == NULL) exit(EXIT_FAILURE);
		memberStruct->numOfMovies = 0;
		rewind(ptr);
		if (fwrite(&memNum, sizeof(int), 1, ptr) <= 0) exit(EXIT_FAILURE);
		if (fseek(ptr, sizeof(int) + ((memNum - 1) * sizeof(MEM)), SEEK_SET) != 0) exit(EXIT_FAILURE);
		if (fwrite(memberStruct, sizeof(MEM), 1, ptr) <= 0) exit(EXIT_FAILURE);
		if (fclose(ptr) != 0) exit(EXIT_FAILURE);
		free(memberStruct);
		_CrtDumpMemoryLeaks();
		return;
	}
}

void searchMembers(void) {
	FILE* search = NULL;
	search = fopen("clanovi.bin", "rb");
	if (!search) {
		system("cls");
		printf("Trenutno nema clanova.");
		if (_getch() <= 0) exit(EXIT_FAILURE);
		return;
	}
	int choice;
	do {
		system("cls");
		printf("\tPretraga clanova\n\n[1] ID\n[2] Ime\n[3] Prezime\n[4] Adresa\n[5] Broj telefona\n[6] Povratak\n\nIzbor: ");
		if (scanf("%d", &choice) <= 0) exit(EXIT_FAILURE);
	} while (choice < 1 || choice > 6);

	MEM* memberStruct = NULL;
	int i, memNum;
	fread(&memNum, sizeof(int), 1, search);
	memberStruct = (MEM*)calloc(memNum, sizeof(MEM));
	if (!memberStruct) exit(EXIT_FAILURE);

	switch (choice) {
	case 1: {
		int flag = 0, searchID;
		system("cls");
		printf("\nUnesite ID: ");
		if (scanf("%d", &searchID) <= 0) exit(EXIT_FAILURE);
		for (i = 0; i < memNum; i++) {
			if (fread(memberStruct, sizeof(MEM), 1, search) <= 0) exit(EXIT_FAILURE);
			if (memberStruct->ID == searchID) {
				listMember(memberStruct);
				flag = 1;
				break;
			}
		}
		if (flag == 0) printf("\nNe postoji clan sa ID-om: [%d].\n", searchID);
		if (_getch() <= 0) exit(EXIT_FAILURE);
		free(memberStruct);
		if (fclose(search) != 0) exit(EXIT_FAILURE);
		_CrtDumpMemoryLeaks();
		return;
	}
	case 2: {
		int flag = 0;
		char* searchFName;
		searchFName = calloc(21, sizeof(char));
		if (!searchFName) exit(EXIT_FAILURE);
		system("cls");
		printf("\nUnesite ime: ");
		if (getchar() <= 0) exit(EXIT_FAILURE);
		if (fgets(searchFName, 20, stdin) == NULL) exit(EXIT_FAILURE);
		for (i = 0; i < memNum; i++) {
			if (fread(memberStruct, sizeof(MEM), 1, search) <= 0) exit(EXIT_FAILURE);
			if (strcmp(memberStruct->fName, searchFName) == 0) {
				listMember(memberStruct);
				flag = 1;
				break;
			}
		}
		*(searchFName + (strlen(searchFName) - 1)) = 0;
		if (flag == 0) printf("\nNe postoji clan sa imenom: [%s].\n", searchFName);
		if (_getch() <= 0) exit(EXIT_FAILURE);
		free(memberStruct);
		free(searchFName);
		if (fclose(search) != 0) exit(EXIT_FAILURE);
		_CrtDumpMemoryLeaks();
		return;
	}
	case 3: {
		int flag = 0;
		char* searchLName;
		searchLName = calloc(21, sizeof(char));
		if (!searchLName) exit(EXIT_FAILURE);
		system("cls");
		printf("\nUnesite prezime: ");
		if (getchar() <= 0) exit(EXIT_FAILURE);
		if (fgets(searchLName, 20, stdin) == NULL) exit(EXIT_FAILURE);
		for (i = 0; i < memNum; i++) {
			if (fread(memberStruct, sizeof(MEM), 1, search) <= 0) exit(EXIT_FAILURE);
			if (strcmp(memberStruct->lName, searchLName) == 0) {
				listMember(memberStruct);
				flag = 1;
				break;
			}
		}
		*(searchLName + (strlen(searchLName) - 1)) = 0;
		if (flag == 0) printf("\nNe postoji clan sa prezimenom: [%s].\n", searchLName);
		if (_getch() <= 0) exit(EXIT_FAILURE);
		free(memberStruct);
		free(searchLName);
		if (fclose(search) != 0) exit(EXIT_FAILURE);
		_CrtDumpMemoryLeaks();
		return;
	}
	case 4: {
		int flag = 0;
		char* searchAddress;
		searchAddress = calloc(51, sizeof(char));
		if (!searchAddress) exit(EXIT_FAILURE);
		system("cls");
		printf("\nUnesite adresu: ");
		if (getchar() <= 0) exit(EXIT_FAILURE);
		if (fgets(searchAddress, 50, stdin) == NULL) exit(EXIT_FAILURE);
		for (i = 0; i < memNum; i++) {
			if (fread(memberStruct, sizeof(MEM), 1, search) <= 0) exit(EXIT_FAILURE);
			if (strcmp(memberStruct->address, searchAddress) == 0) {
				listMember(memberStruct);
				flag = 1;
				break;
			}
		}
		*(searchAddress + (strlen(searchAddress) - 1)) = 0;
		if (flag == 0) printf("\nNe postoji clan sa adresom: [%s].\n", searchAddress);
		if (_getch() <= 0) exit(EXIT_FAILURE);
		free(memberStruct);
		free(searchAddress);
		if (fclose(search) != 0) exit(EXIT_FAILURE);
		_CrtDumpMemoryLeaks();
		return;
	}
	case 5: {
		int flag = 0;
		char* searchPhNum;
		searchPhNum = calloc(15, sizeof(char));
		if (!searchPhNum) exit(EXIT_FAILURE);
		system("cls");
		printf("\nUnesite broj telefona: ");
		if (getchar() <= 0) exit(EXIT_FAILURE);
		if (fgets(searchPhNum, 14, stdin) == NULL) exit(EXIT_FAILURE);
		for (i = 0; i < memNum; i++) {
			if (fread(memberStruct, sizeof(MEM), 1, search) <= 0) exit(EXIT_FAILURE);
			if (strcmp(memberStruct->phoneNum, searchPhNum) == 0) {
				listMember(memberStruct);
				flag = 1;
				break;
			}
		}
		*(searchPhNum + (strlen(searchPhNum) - 1)) = 0;
		if (flag == 0) printf("\nNe postoji clan sa br. telefona: [%s].\n", searchPhNum);
		if (_getch() <= 0) exit(EXIT_FAILURE);
		free(memberStruct);
		free(searchPhNum);
		if (fclose(search) != 0) exit(EXIT_FAILURE);
		_CrtDumpMemoryLeaks();
		return;
	}
	case 6: {
		free(memberStruct);
		if (fclose(search) != 0) exit(EXIT_FAILURE);
		_CrtDumpMemoryLeaks();
		return;
	}
	}
}

void listMember(MEM* member) {
	if (fprintf(stdout, "\nID: %d\n", member->ID) <= 0) exit(EXIT_FAILURE);
	if (fprintf(stdout, "Ime: %s", member->fName) <= 0) exit(EXIT_FAILURE);
	if (fprintf(stdout, "Prezime: %s", member->lName) <= 0) exit(EXIT_FAILURE);
	if (fprintf(stdout, "Adresa: %s", member->address) <= 0) exit(EXIT_FAILURE);
	if (fprintf(stdout, "Br. telefona: %s", member->phoneNum) <= 0) exit(EXIT_FAILURE);
	if (fprintf(stdout, "Broj posudjenih filmova: %d\n", member->numOfMovies) <= 0) exit(EXIT_FAILURE);
	FILE* movFile;
	movFile = fopen("posudbe.bin", "rb");
	if (movFile) {
		MOV* movies;
		int i, numOfMovies;
		fread(&numOfMovies, sizeof(int), 1, movFile);
		movies = calloc(numOfMovies, sizeof(MOV));
		if (!movies) exit(EXIT_FAILURE);
		printf("\n\tPOSUDBE\n");
		for (i = 0; i < numOfMovies; i++) {
			if (fread(movies, sizeof(MOV), 1, movFile) <= 0) exit(EXIT_FAILURE);
			if (movies->memberID == member->ID) {
				if (fprintf(stdout, "ID: %d\n", movies->ID) <= 0) exit(EXIT_FAILURE);
				if (fprintf(stdout, "Naziv: %s", movies->title) <= 0) exit(EXIT_FAILURE);
				if (fprintf(stdout, "Datum: %d\n\n", movies->date) <= 0) exit(EXIT_FAILURE);
			}
		}
		free(movies);
		if (fclose(movFile) != 0) exit(EXIT_FAILURE);
	}
	_CrtDumpMemoryLeaks();
	return;
}

void rentAMovie(void) {
	system("cls");
	int i, howMany, numOfMoviesInMem, maxMovies, memID;
	bool checkMem;
	do {
		system("cls");
		printf("ID clana: ");
		if (scanf("%d", &memID) <= 0) exit(EXIT_FAILURE);
		checkMem = memberExists(memID);
		if (!checkMem) {
			printf("Clan ne postoji. Ponovite unos.");
			if (_getch() <= 0) exit(EXIT_FAILURE);
			memID = (-1);
		}
	} while (!checkMem);
	numOfMoviesInMem = numberOfMovies(memID);
	maxMovies = (4 - numOfMoviesInMem);
	if (numOfMoviesInMem == 4) {
		printf("Clan sa ID [%d] ne moze posuditi vise filmova.\n", memID);
		if (_getch() <= 0) exit(EXIT_FAILURE);
		_CrtDumpMemoryLeaks();
		return;
	}
	else {
		do {
			system("cls");
			printf("Broj filmova za posudbu [0 za povratak | preostalo: %d]: ", maxMovies);
			if (scanf("%d", &howMany) <= 0) exit(EXIT_FAILURE);
		} while (howMany < 0 || howMany > maxMovies);
	}
	if (howMany != 0) for (i = 0; i < howMany; i++) addMovies(memID);
	_CrtDumpMemoryLeaks();
	return;
}

bool memberExists(int memID) {
	FILE* search = NULL;
	search = fopen("clanovi.bin", "rb");
	if (!search) exit(EXIT_FAILURE);
	MEM* memberStruct = NULL;
	int i, memNum;
	bool flag = false;
	fread(&memNum, sizeof(int), 1, search);
	memberStruct = (MEM*)calloc(memNum, sizeof(MEM));
	if (!memberStruct) exit(EXIT_FAILURE);
	for (i = 0; i < memNum; i++) {
		if (fread(memberStruct, sizeof(MEM), 1, search) <= 0) exit(EXIT_FAILURE);
		if (memberStruct->ID == memID) {
			flag = true;
			break;
		}
	}
	free(memberStruct);
	if (fclose(search) != 0) exit(EXIT_FAILURE);
	_CrtDumpMemoryLeaks();
	return flag;
}

int numberOfMovies(int memID) {
	FILE* search = NULL;
	search = fopen("clanovi.bin", "rb");
	if (!search) exit(EXIT_FAILURE);
	MEM* memberStruct = NULL;
	int i, memNum, numOfMovies = 0;
	fread(&memNum, sizeof(int), 1, search);
	memberStruct = (MEM*)calloc(memNum, sizeof(MEM));
	if (!memberStruct) exit(EXIT_FAILURE);
	for (i = 0; i < memNum; i++) {
		if (fread(memberStruct, sizeof(MEM), 1, search) <= 0) exit(EXIT_FAILURE);
		if (memberStruct->ID == memID) {
			numOfMovies = memberStruct->numOfMovies;
			break;
		}
	}
	free(memberStruct);
	if (fclose(search) != 0) exit(EXIT_FAILURE);
	_CrtDumpMemoryLeaks();
	return numOfMovies;
}

void addMovies(int memID) {
	MOV* movieStruct;
	movieStruct = calloc(1, sizeof(MOV));
	if (!movieStruct) exit(EXIT_FAILURE);
	FILE* ptr;
	ptr = fopen("posudbe.bin", "r+b");
	if (!ptr) {
		ptr = fopen("posudbe.bin", "wb");
		if (!ptr) exit(EXIT_FAILURE);
		printf("\nUnesite ID: ");
		if (scanf("%d", &movieStruct->ID) <= 0) exit(EXIT_FAILURE);
		printf("Unesite naziv: ");
		if (getchar() <= 0) exit(EXIT_FAILURE);
		if (fgets(movieStruct->title, 40, stdin) == NULL) exit(EXIT_FAILURE);
		do {
			printf("Unesite datum: ");
			if (scanf("%d", &movieStruct->date) <= 0) exit(EXIT_FAILURE);
		} while (movieStruct->date < 1 || movieStruct->date > 365);
		movieStruct->memberID = memID;
		increaseMemberMovieNum(memID);
		int movieNum = 1;
		if (fwrite(&movieNum, sizeof(int), 1, ptr) <= 0) exit(EXIT_FAILURE);
		if (fwrite(movieStruct, sizeof(MOV), 1, ptr) <= 0) exit(EXIT_FAILURE);
		if (fclose(ptr) != 0) exit(EXIT_FAILURE);
		free(movieStruct);
		_CrtDumpMemoryLeaks();
		return;
	}
	else {
		int movieNum;
		if (fread(&movieNum, sizeof(int), 1, ptr) <= 0) exit(EXIT_FAILURE);
		movieNum++;
		printf("\nUnesite ID: ");
		if (scanf("%d", &movieStruct->ID) <= 0) exit(EXIT_FAILURE);
		printf("Unesite naziv: ");
		if (getchar() <= 0) exit(EXIT_FAILURE);
		if (fgets(movieStruct->title, 40, stdin) == NULL) exit(EXIT_FAILURE); do {
			printf("Unesite datum: ");
			if (scanf("%d", &movieStruct->date) <= 0) exit(EXIT_FAILURE);
		} while (movieStruct->date < 1 || movieStruct->date > 365);
		movieStruct->memberID = memID;
		increaseMemberMovieNum(memID);
		rewind(ptr);
		if (fwrite(&movieNum, sizeof(int), 1, ptr) <= 0) exit(EXIT_FAILURE);
		if (fseek(ptr, sizeof(int) + ((movieNum - 1) * sizeof(MOV)), SEEK_SET) != 0) exit(EXIT_FAILURE);
		if (fwrite(movieStruct, sizeof(MOV), 1, ptr) <= 0) exit(EXIT_FAILURE);
		if (fclose(ptr) != 0) exit(EXIT_FAILURE);
		free(movieStruct);
		_CrtDumpMemoryLeaks();
		return;
	}
}

void increaseMemberMovieNum(int memID) {
	FILE* readMem, * tmpPntr;
	int num;
	readMem = fopen("clanovi.bin", "rb");
	if (!readMem) return;
	tmpPntr = fopen("tmp.bin", "wb");
	if (!tmpPntr) exit(EXIT_FAILURE);
	if (fread(&num, sizeof(int), 1, readMem) <= 0) exit(EXIT_FAILURE);
	MEM* member = NULL;
	member = calloc(num, sizeof(MEM));
	if (!member) exit(EXIT_FAILURE);
	if (fwrite(&num, sizeof(int), 1, tmpPntr) <= 0) exit(EXIT_FAILURE);
	for (int i = 0; i < num; i++) {
		if (fread(member, sizeof(MEM), 1, readMem) <= 0) exit(EXIT_FAILURE);
		if (member->ID == memID) member->numOfMovies++;
		if (fwrite(member, sizeof(MEM), 1, tmpPntr) <= 0) exit(EXIT_FAILURE);
	}
	if (fclose(readMem) != 0) exit(EXIT_FAILURE);
	if (fclose(tmpPntr) != 0) exit(EXIT_FAILURE);
	free(member);
	if (remove("clanovi.bin") != 0) exit(EXIT_FAILURE);
	if (rename("tmp.bin", "clanovi.bin") != 0) exit(EXIT_FAILURE);
	_CrtDumpMemoryLeaks();
	return;
}

void closeProgram(void) {
	int flag = 0;
	char* answer;
	answer = calloc(4, sizeof(char));
	if (!answer) exit(EXIT_FAILURE);
	do {
		system("cls");
		printf("Jeste li sigurni da zelite izaci [da / ne]: ");
		if (getchar() <= 0) exit(EXIT_FAILURE);
		if (fgets(answer, 3, stdin) == NULL) exit(EXIT_FAILURE);
		if ((strcmp(answer, "da") == 0) || (strcmp(answer, "DA") == 0) || (strcmp(answer, "Da") == 0) || (strcmp(answer, "dA") == 0)) {
			flag = 1;
			break;
		}
		else if ((strcmp(answer, "ne") == 0) || (strcmp(answer, "NE") == 0) || (strcmp(answer, "Ne") == 0) || (strcmp(answer, "nE") == 0)) {
			flag = 2;
			break;
		}
		else {
			printf("Nepoznat unos. Ponovite. ");
			if (_getch() <= 0) exit(EXIT_FAILURE);
			flag = 0;
			memset(answer, 0, 3);
		}
	} while (flag == 0);
	free(answer);
	_CrtDumpMemoryLeaks();
	if (flag == 1) exit(EXIT_SUCCESS);
	else return;
}