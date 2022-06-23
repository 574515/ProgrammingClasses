#include "header.h"
#include "colors.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>
#include <string.h>

//characters functions
void chars_Edit_Menu(void) {

	//enter from library_Edit_Board
	int choice;
	while (1) {
		system("cls");
		printf("\t  Logged in as: "RED"[%s]"ESC"\n\n\t"BRED"Characters editing\n\n"ESC"[1] Add a character\n[2] Remove a character\n[3] List characters\n[4] Search a character\n[5] Return\n\nChoice: ", logged_As);
		scanf("%d", &choice);

		switch (choice) {
			case 1: {
				chars_Add();
				break;
			}
			case 2: {
				del_Chars();
				break;
			}
			case 3: {
				chars_List();
				break;
			}
			case 4: {
				search_Chars();
				break;
			}
			case 5: {
				return;
			}
		}
	}
}

void chars_Add(void) {

	//enter from chars_Edit_Menu
	CHARACTERS* chars = NULL;
	chars = (CHARACTERS*)calloc(1, sizeof(CHARACTERS));
	if (chars == NULL) {
		perror("Struct error");
		exit(EXIT_FAILURE);
	}
	FILE* char_File = NULL;
	char_File = fopen("characters.bin", "r+b");
	if (char_File == NULL) {
		char_File = fopen("characters.bin", "wb");
		if (char_File == NULL) {
			perror("File error");
			exit(EXIT_FAILURE);
		}
		int alive;
		system("cls");
		printf("\n\tCurrently entering 1. "RED"character"ESC".\n\nEnter character ID: ");
		scanf("%d", &chars->ID);
		printf("Enter first name: ");
		getchar();
		fgets(chars->first_N, 99, stdin);
		printf("Enter last name: ");
		fgets(chars->last_N, 99, stdin);
		printf("Enter species: ");
		fgets(chars->species, 499, stdin);
		printf("Is character alive [1 / 0]: ");
		scanf("%d", &alive);
		chars->alive = alive;
		getchar();
		printf("Titles: ");
		fgets(chars->titles, 999, stdin);
		printf("Occupation: ");
		fgets(chars->occupation, 999, stdin);
		printf("Affiliation: ");
		fgets(chars->affiliation, 999, stdin);
		printf("Family relations: ");
		fgets(chars->family, 999, stdin);
		printf("Portrayed by: ");
		fgets(chars->portrayed, 999, stdin);
		int char_Num = 1;
		fwrite(&char_Num, sizeof(int), 1, char_File);
		fwrite(chars, sizeof(CHARACTERS), 1, char_File);
		fclose(char_File);
		free(chars);
		return;
	}
	else {
		int char_Num;
		fread(&char_Num, sizeof(int), 1, char_File);
		char_Num++;
		int alive;
		system("cls");
		printf("\n\tCurrently entering %d. "RED"character"ESC".\n\nEnter character ID: ", char_Num);
		scanf("%d", &chars->ID);
		printf("Enter first name: ");
		getchar();
		fgets(chars->first_N, 99, stdin);
		printf("Enter last name: ");
		fgets(chars->last_N, 99, stdin);
		printf("Enter species: ");
		fgets(chars->species, 499, stdin);
		printf("Is character alive [1 / 0]: ");
		scanf("%d", &alive);
		chars->alive = alive;
		getchar();
		printf("Titles: ");
		fgets(chars->titles, 999, stdin);
		printf("Occupation: ");
		fgets(chars->occupation, 999, stdin);
		printf("Affiliation: ");
		fgets(chars->affiliation, 999, stdin);
		printf("Family relations: ");
		fgets(chars->family, 999, stdin);
		printf("Portrayed by: ");
		fgets(chars->portrayed, 999, stdin);
		rewind(char_File);
		fwrite(&char_Num, sizeof(int), 1, char_File);
		fseek(char_File, sizeof(int) + ((char_Num - 1) * sizeof(CHARACTERS)), SEEK_SET);
		fwrite(chars, sizeof(CHARACTERS), 1, char_File);
		fclose(char_File);
		free(chars);
		return;
	}
}

void del_Chars(void) {

	//enter from chars_Edit_Menu
	int rem_By, num;
	do {
		system("cls");
		printf("\t  Logged in as: "RED"[%s]"ESC"\n\n\tRemoving characters "RED"[BE CAREFUL!]\n\n"ESC"[1] Remove by ID\n[2] Remove by first name\n[3] Remove by species [bulk]\n[4] Return\n\nChoice: ", logged_As);
		scanf("%d", &rem_By);
	} while (rem_By < 1 || rem_By > 4);

	FILE* read_Chars = NULL;
	read_Chars = fopen("characters.bin", "rb");
	if (read_Chars == NULL) {
		perror("File error");
		exit(EXIT_FAILURE);
	}

	FILE* tmp_Pntr = NULL;
	tmp_Pntr = fopen("tmp.bin", "wb");
	if (tmp_Pntr == NULL) {
		printf("File error");
		exit(EXIT_FAILURE);
	}

	fread(&num, sizeof(int), 1, read_Chars);
	CHARACTERS* deletion = NULL;
	deletion = (CHARACTERS*)calloc(num, sizeof(CHARACTERS));
	if (deletion == NULL) {
		perror("Struct error");
		exit(EXIT_FAILURE);
	}

	switch (rem_By) {
	case 1: {
		int dlt_ID, found = 0, helping;
		printf("\nEnter ID to delete: ");
		scanf("%d", &dlt_ID);

		helping = num - 1;
		fwrite(&helping, sizeof(int), 1, tmp_Pntr);

		for (int i = 0; i < num; i++) {
			fread(deletion, sizeof(CHARACTERS), 1, read_Chars);
			if (deletion->ID == dlt_ID) {
				found = 1;
			}
			else {
				fwrite(deletion, sizeof(CHARACTERS), 1, tmp_Pntr);
			}
		}

		if (found != 1) {
			system("cls");
			printf("\n\tCharacter with ID [%d] was not found.\n", dlt_ID);
			fclose(read_Chars);
			fclose(tmp_Pntr);
			free(deletion);
			_getch();
		}
		else {
			system("cls");
			printf("\n\tCharacter with ID [%d] was "BRED"removed"ESC".\n", dlt_ID);
			_getch();
			fclose(read_Chars);
			fclose(tmp_Pntr);
			free(deletion);
			if (helping == 0) {
				remove("characters.bin");
				remove("tmp.bin");
				printf("\n\tThere are no "BRED"characters"ESC" left.\n");
				_getch();
				return;
			}
			else {
				remove("characters.bin");
				rename("tmp.bin", "characters.bin");
			}
		}
		return;
	}
	case 2: {
		char* dlt_Fn;
		int found = 0, helping;
		dlt_Fn = (char*)calloc(30, sizeof(char));
		if (dlt_Fn == NULL) {
			perror("Memory error");
			exit(EXIT_FAILURE);
		}
		getchar();
		printf("\nEnter first name to delete: ");
		fgets(dlt_Fn, 29, stdin);

		helping = num - 1;
		fwrite(&helping, sizeof(int), 1, tmp_Pntr);

		for (int i = 0; i < num; i++) {
			fread(deletion, sizeof(CHARACTERS), 1, read_Chars);
			if (strcmp(deletion->first_N, dlt_Fn) == 0) {
				found = 1;
			}
			else {
				fwrite(deletion, sizeof(CHARACTERS), 1, tmp_Pntr);
			}
		}

		if (found != 1) {
			system("cls");
			*(dlt_Fn + (strlen(dlt_Fn) - 1)) = 0;
			printf("\n\tCharacter with first name [%s] was not found.\n", dlt_Fn);
			fclose(read_Chars);
			fclose(tmp_Pntr);
			free(deletion);
			free(dlt_Fn);
			_getch();
		}
		else {
			system("cls");
			*(dlt_Fn + (strlen(dlt_Fn) - 1)) = 0;
			printf("\n\tCharacter with first name [%s] was "BRED"removed"ESC".\n", dlt_Fn);
			_getch();
			fclose(read_Chars);
			fclose(tmp_Pntr);
			free(deletion);
			free(dlt_Fn);
			if (helping == 0) {
				remove("characters.bin");
				remove("tmp.bin");
				printf("\n\tThere are no "BRED"characters"ESC" left.\n");
				_getch();
				return;
			}
			else {
				remove("characters.bin");
				rename("tmp.bin", "characters.bin");
			}
		}
		return;
	}
	case 3: {
		char* dlt_Spec;
		int found = 0, helping = 0, count_Del = 0;
		dlt_Spec = (char*)calloc(30, sizeof(char));
		if (dlt_Spec == NULL) {
			perror("Memory error");
			exit(EXIT_FAILURE);
		}
		getchar();
		printf("\nEnter species [bulk] to delete: ");
		fgets(dlt_Spec, 29, stdin);

		helping = num;
		fwrite(&helping, sizeof(int), 1, tmp_Pntr);

		for (int i = 0; i < num; i++) {
			fread(deletion, sizeof(CHARACTERS), 1, read_Chars);
			if (strcmp(deletion->species, dlt_Spec) == 0) {
				found = 1;
				count_Del++;
			}
			else {
				fwrite(deletion, sizeof(CHARACTERS), 1, tmp_Pntr);
			}
		}

		helping = num - count_Del;
		rewind(tmp_Pntr);
		fwrite(&helping, sizeof(int), 1, tmp_Pntr);

		if (found != 1) {
			system("cls");
			*(dlt_Spec + (strlen(dlt_Spec) - 1)) = 0;
			printf("\n\tSpecis of [%s] were not found.\n", dlt_Spec);
			fclose(read_Chars);
			fclose(tmp_Pntr);
			free(deletion);
			free(dlt_Spec);
			_getch();
		}
		else {
			system("cls");
			*(dlt_Spec + (strlen(dlt_Spec) - 1)) = 0;
			printf("\n\tSpecies of [%s] were "BRED"removed"ESC".\n", dlt_Spec);
			_getch();
			fclose(read_Chars);
			fclose(tmp_Pntr);
			free(deletion);
			free(dlt_Spec);
			if (helping == 0) {
				remove("characters.bin");
				remove("tmp.bin");
				printf("\n\tThere are no "BRED"characters"ESC" left.\n");
				_getch();
				return;
			}
			else {
				remove("characters.bin");
				rename("tmp.bin", "characters.bin");
			}
		}

		return;
	}
	case 4: {
		fclose(read_Chars);
		fclose(tmp_Pntr);
		free(deletion);
		return;
	}
	}

}

void chars_List(void) {

	//enter from chars_Edit_Menu
	int list_Choice, char_Num;
	do {

		system("cls");
		printf("\t  Logged in as: "RED"[%s]"ESC"\n\n\t"BRED"List characters by:\n\n"ESC"[1] ID\n[2] First name\n[3] Last name\n[4] Species\n[5] Default order\n[6] Return to edit panel\n\nChoice: ", logged_As);
		scanf("%d", &list_Choice);
	} while (list_Choice < 1 || list_Choice > 6);

	FILE* read = NULL;
	read = fopen("characters.bin", "rb");
	if (read == NULL) {
		perror("File error");
		exit(EXIT_FAILURE);
	}

	CHARACTERS* read_St = NULL;
	fread(&char_Num, sizeof(int), 1, read);
	read_St = (CHARACTERS*)calloc(char_Num, sizeof(CHARACTERS));
	if (read_St == NULL) {
		perror("Struct error");
		exit(EXIT_FAILURE);
	}

	switch (list_Choice) {
	case 1: {
		int asc_Desc, i;
		do {
			system("cls");
			printf("\n\t"BRED"Sort characters by ID:\n\n"ESC"[1] Ascending\n[2] Descending\n\nChoice: ");
			scanf("%d", &asc_Desc);
		} while (asc_Desc < 1 || asc_Desc > 2);

		fseek(read, sizeof(int), SEEK_SET);
		fread(read_St, sizeof(CHARACTERS), char_Num, read);
		if (asc_Desc == 1)
			qsort(read_St, char_Num, sizeof(CHARACTERS), compare_ID_Asc_Chars);
		else
			qsort(read_St, char_Num, sizeof(CHARACTERS), compare_ID_Desc_Chars);
		system("cls");
		printf("\n\tNumber of "RED"characters"ESC": [%d]\n\n", char_Num);
		for (i = 0; i < char_Num; i++) {
			fprintf(stdout, BMNG"\n[%d] ID:"ESC" %d\n", i + 1, (read_St + i)->ID);
			fprintf(stdout, BMNG"[%d] First name:"ESC" %s", i + 1, (read_St + i)->first_N);
			fprintf(stdout, BMNG"[%d] Last name:"ESC" %s", i + 1, (read_St + i)->last_N);
			fprintf(stdout, BMNG"[%d] Species:"ESC" %s", i + 1, (read_St + i)->species);
			if ((read_St + i)->alive == true) {
				fprintf(stdout, BMNG"[%d]"ESC" Alive\n", i + 1);
			}
			else {
				fprintf(stdout, BMNG"[%d]"ESC" Deceased\n", i + 1);
			}
			fprintf(stdout, BMNG"[%d] Titles:"ESC" %s", i + 1, (read_St + i)->titles);
			fprintf(stdout, BMNG"[%d] Occupation:"ESC" %s", i + 1, (read_St + i)->occupation);
			fprintf(stdout, BMNG"[%d] Affiliation:"ESC" %s", i + 1, (read_St + i)->affiliation);
			fprintf(stdout, BMNG"[%d] Family:"ESC" %s", i + 1, (read_St + i)->family);
			fprintf(stdout, BMNG"[%d] Portrayed by:"ESC" %s\n", i + 1, (read_St + i)->portrayed);
		}
		_getch();
		fclose(read);
		free(read_St);
		return;
	}
	case 2: {
		int asc_Desc, i;
		do {
			system("cls");
			printf("\n\t"BRED"Sort characters by first name:\n\n"ESC"[1] Ascending\n[2] Descending\n\nChoice: ");
			scanf("%d", &asc_Desc);
		} while (asc_Desc < 1 || asc_Desc > 2);

		fseek(read, sizeof(int), SEEK_SET);
		fread(read_St, sizeof(CHARACTERS), char_Num, read);
		if (asc_Desc == 1)
			qsort(read_St, char_Num, sizeof(CHARACTERS), comp_Fn_Chars_Asc);
		else
			qsort(read_St, char_Num, sizeof(CHARACTERS), comp_Fn_Chars_Desc);
		system("cls");
		printf("\n\tNumber of "RED"characters"ESC": [%d]\n\n", char_Num);
		for (i = 0; i < char_Num; i++) {
			fprintf(stdout, BMNG"\n[%d] ID:"ESC" %d\n", i + 1, (read_St + i)->ID);
			fprintf(stdout, BMNG"[%d] First name:"ESC" %s", i + 1, (read_St + i)->first_N);
			fprintf(stdout, BMNG"[%d] Last name:"ESC" %s", i + 1, (read_St + i)->last_N);
			fprintf(stdout, BMNG"[%d] Species:"ESC" %s", i + 1, (read_St + i)->species);
			if ((read_St + i)->alive == true) {
				fprintf(stdout, BMNG"[%d]"ESC" Alive\n", i + 1);
			}
			else {
				fprintf(stdout, BMNG"[%d]"ESC" Deceased\n", i + 1);
			}
			fprintf(stdout, BMNG"[%d] Titles:"ESC" %s", i + 1, (read_St + i)->titles);
			fprintf(stdout, BMNG"[%d] Occupation:"ESC" %s", i + 1, (read_St + i)->occupation);
			fprintf(stdout, BMNG"[%d] Affiliation:"ESC" %s", i + 1, (read_St + i)->affiliation);
			fprintf(stdout, BMNG"[%d] Family:"ESC" %s", i + 1, (read_St + i)->family);
			fprintf(stdout, BMNG"[%d] Portrayed by:"ESC" %s\n", i + 1, (read_St + i)->portrayed);
		}
		_getch();
		fclose(read);
		free(read_St);
		return;
	}
	case 3: {
		int asc_Desc, i;
		do {
			system("cls");
			printf("\n\t"BRED"Sort characters by last name:\n\n"ESC"[1] Ascending\n[2] Descending\n\nChoice: ");
			scanf("%d", &asc_Desc);
		} while (asc_Desc < 1 || asc_Desc > 2);

		fseek(read, sizeof(int), SEEK_SET);
		fread(read_St, sizeof(CHARACTERS), char_Num, read);
		if (asc_Desc == 1)
			qsort(read_St, char_Num, sizeof(CHARACTERS), comp_Ln_Chars_Asc);
		else
			qsort(read_St, char_Num, sizeof(CHARACTERS), comp_Ln_Chars_Desc);
		system("cls");
		printf("\n\tNumber of "RED"characters"ESC": [%d]\n\n", char_Num);
		for (i = 0; i < char_Num; i++) {
			fprintf(stdout, BMNG"\n[%d] ID:"ESC" %d\n", i + 1, (read_St + i)->ID);
			fprintf(stdout, BMNG"[%d] First name:"ESC" %s", i + 1, (read_St + i)->first_N);
			fprintf(stdout, BMNG"[%d] Last name:"ESC" %s", i + 1, (read_St + i)->last_N);
			fprintf(stdout, BMNG"[%d] Species:"ESC" %s", i + 1, (read_St + i)->species);
			if ((read_St + i)->alive == true) {
				fprintf(stdout, BMNG"[%d]"ESC" Alive\n", i + 1);
			}
			else {
				fprintf(stdout, BMNG"[%d]"ESC" Deceased\n", i + 1);
			}
			fprintf(stdout, BMNG"[%d] Titles:"ESC" %s", i + 1, (read_St + i)->titles);
			fprintf(stdout, BMNG"[%d] Occupation:"ESC" %s", i + 1, (read_St + i)->occupation);
			fprintf(stdout, BMNG"[%d] Affiliation:"ESC" %s", i + 1, (read_St + i)->affiliation);
			fprintf(stdout, BMNG"[%d] Family:"ESC" %s", i + 1, (read_St + i)->family);
			fprintf(stdout, BMNG"[%d] Portrayed by:"ESC" %s\n", i + 1, (read_St + i)->portrayed);
		}
		_getch();
		fclose(read);
		free(read_St);
		return;
	}
	case 4: {
		int asc_Desc, i;
		do {
			system("cls");
			printf("\n\t"BRED"Sort characters by species:\n\n"ESC"[1] Ascending\n[2] Descending\n\nChoice: ");
			scanf("%d", &asc_Desc);
		} while (asc_Desc < 1 || asc_Desc > 2);

		fseek(read, sizeof(int), SEEK_SET);
		fread(read_St, sizeof(CHARACTERS), char_Num, read);
		if (asc_Desc == 1)
			qsort(read_St, char_Num, sizeof(CHARACTERS), comp_Species_Chars_Asc);
		else
			qsort(read_St, char_Num, sizeof(CHARACTERS), comp_Species_Chars_Desc);
		system("cls");
		printf("\n\tNumber of "RED"characters"ESC": [%d]\n\n", char_Num);
		for (i = 0; i < char_Num; i++) {
			fprintf(stdout, BMNG"\n[%d] ID:"ESC" %d\n", i + 1, (read_St + i)->ID);
			fprintf(stdout, BMNG"[%d] First name:"ESC" %s", i + 1, (read_St + i)->first_N);
			fprintf(stdout, BMNG"[%d] Last name:"ESC" %s", i + 1, (read_St + i)->last_N);
			fprintf(stdout, BMNG"[%d] Species:"ESC" %s", i + 1, (read_St + i)->species);
			if ((read_St + i)->alive == true) {
				fprintf(stdout, BMNG"[%d]"ESC" Alive\n", i + 1);
			}
			else {
				fprintf(stdout, BMNG"[%d]"ESC" Deceased\n", i + 1);
			}
			fprintf(stdout, BMNG"[%d] Titles:"ESC" %s", i + 1, (read_St + i)->titles);
			fprintf(stdout, BMNG"[%d] Occupation:"ESC" %s", i + 1, (read_St + i)->occupation);
			fprintf(stdout, BMNG"[%d] Affiliation:"ESC" %s", i + 1, (read_St + i)->affiliation);
			fprintf(stdout, BMNG"[%d] Family:"ESC" %s", i + 1, (read_St + i)->family);
			fprintf(stdout, BMNG"[%d] Portrayed by:"ESC" %s\n", i + 1, (read_St + i)->portrayed);
		}
		_getch();
		fclose(read);
		free(read_St);
		return;
	}
	case 5: {
		int i;
		fseek(read, sizeof(int), SEEK_SET);
		system("cls");
		printf("\n\tNumber of "RED"characters"ESC": [%d]\n\n", char_Num);
		for (i = 0; i < char_Num; i++) {
			fread(read_St, sizeof(CHARACTERS), 1, read);
			fprintf(stdout, BMNG"\n[%d] ID:"ESC" %d\n", i + 1, read_St->ID);
			fprintf(stdout, BMNG"[%d] First name:"ESC" %s", i + 1, read_St->first_N);
			fprintf(stdout, BMNG"[%d] Last name:"ESC" %s", i + 1, read_St->last_N);
			fprintf(stdout, BMNG"[%d] Species:"ESC" %s", i + 1, read_St->species);
			if (read_St->alive == true) {
				fprintf(stdout, BMNG"[%d]"ESC" Alive\n", i + 1);
			}
			else {
				fprintf(stdout, BMNG"[%d]"ESC" Deceased\n", i + 1);
			}
			fprintf(stdout, BMNG"[%d] Titles:"ESC" %s", i + 1, read_St->titles);
			fprintf(stdout, BMNG"[%d] Occupation:"ESC" %s", i + 1, read_St->occupation);
			fprintf(stdout, BMNG"[%d] Affiliation:"ESC" %s", i + 1, read_St->affiliation);
			fprintf(stdout, BMNG"[%d] Family:"ESC" %s", i + 1, read_St->family);
			fprintf(stdout, BMNG"[%d] Portrayed by:"ESC" %s\n", i + 1, read_St->portrayed);
		}
		_getch();
		fclose(read);
		free(read_St);
		return;
	}
	case 6: {
		fclose(read);
		free(read_St);
		return;
	}
	}
}

void search_Chars(void) {

	//enter from chars_Edit_Menu
	int search_Choice, chars_Num, i;

	do {
		system("cls");
		printf("\t  Logged in as: "RED"[%s]"ESC"\n\n\t"BRED"Search characters by:\n\n"ESC"[1] ID\n[2] First name\n[3] Last name\n[4] Species\n[5] Status (alive / deceased)\n[6] Return to edit panel\n\nChoice: ", logged_As);
		scanf("%d", &search_Choice);
	} while (search_Choice < 1 || search_Choice > 6);

	FILE* search = NULL;
	search = fopen("characters.bin", "rb");
	if (search == NULL) {
		perror("File error");
		exit(EXIT_FAILURE);
	}

	CHARACTERS* read_St = NULL;
	fread(&chars_Num, sizeof(int), 1, search);
	read_St = (CHARACTERS*)calloc(chars_Num, sizeof(CHARACTERS));
	if (read_St == NULL) {
		perror("Struct error");
		exit(EXIT_FAILURE);
	}

	switch (search_Choice) {
	case 1: {
		int id_Srch, flag = 0;
		system("cls");
		printf("\nEnter ID: ");
		scanf("%d", &id_Srch);
		for (i = 0; i < chars_Num; i++) {
			fread(read_St, sizeof(CHARACTERS), 1, search);
			if (read_St->ID == id_Srch) {
				fprintf(stdout, BMNG"\n[%d] ID:"ESC" %d\n", i + 1, read_St->ID);
				fprintf(stdout, BMNG"[%d] First name:"ESC" %s", i + 1, read_St->first_N);
				fprintf(stdout, BMNG"[%d] Last name:"ESC" %s", i + 1, read_St->last_N);
				fprintf(stdout, BMNG"[%d] Species:"ESC" %s", i + 1, read_St->species);
				if (read_St->alive == true) {
					fprintf(stdout, BMNG"[%d]"ESC" Alive\n", i + 1);
				}
				else {
					fprintf(stdout, BMNG"[%d]"ESC" Deceased\n", i + 1);
				}
				fprintf(stdout, BMNG"[%d] Titles:"ESC" %s", i + 1, read_St->titles);
				fprintf(stdout, BMNG"[%d] Occupation:"ESC" %s", i + 1, read_St->occupation);
				fprintf(stdout, BMNG"[%d] Affiliation:"ESC" %s", i + 1, read_St->affiliation);
				fprintf(stdout, BMNG"[%d] Family:"ESC" %s", i + 1, read_St->family);
				fprintf(stdout, BMNG"[%d] Portrayed by:"ESC" %s\n", i + 1, read_St->portrayed);
				flag = 1;
				_getch();
				break;
			}
		}
		printf("End of list.");
		_getch();
		if (flag == 0) {
			printf("\nNo character with ID: [%d].\n", id_Srch);
			_getch();
		}
		free(read_St);
		fclose(search);
		return;
	}
	case 2: {
		int flag = 0;
		char* srch_Fnm;
		srch_Fnm = (char*)calloc(30, sizeof(char));
		if (srch_Fnm == NULL) {
			perror("Memory error");
			exit(EXIT_FAILURE);
		}
		system("cls");
		getchar();
		printf("\nEnter first name: ");
		fgets(srch_Fnm, 29, stdin);
		for (i = 0; i < chars_Num; i++) {
			fread(read_St, sizeof(CHARACTERS), 1, search);
			if (strcmp(read_St->first_N, srch_Fnm) == 0) {
				fprintf(stdout, BMNG"\n[%d] ID:"ESC" %d\n", i + 1, read_St->ID);
				fprintf(stdout, BMNG"[%d] First name:"ESC" %s", i + 1, read_St->first_N);
				fprintf(stdout, BMNG"[%d] Last name:"ESC" %s", i + 1, read_St->last_N);
				fprintf(stdout, BMNG"[%d] Species:"ESC" %s", i + 1, read_St->species);
				if (read_St->alive == true) {
					fprintf(stdout, BMNG"[%d]"ESC" Alive\n", i + 1);
				}
				else {
					fprintf(stdout, BMNG"[%d]"ESC" Deceased\n", i + 1);
				}
				fprintf(stdout, BMNG"[%d] Titles:"ESC" %s", i + 1, read_St->titles);
				fprintf(stdout, BMNG"[%d] Occupation:"ESC" %s", i + 1, read_St->occupation);
				fprintf(stdout, BMNG"[%d] Affiliation:"ESC" %s", i + 1, read_St->affiliation);
				fprintf(stdout, BMNG"[%d] Family:"ESC" %s", i + 1, read_St->family);
				fprintf(stdout, BMNG"[%d] Portrayed by:"ESC" %s\n", i + 1, read_St->portrayed);
				flag = 1;
				_getch();
				break;
			}
		}
		printf("End of list.");
		_getch();
		if (flag == 0) {
			*(srch_Fnm + (strlen(srch_Fnm) - 1)) = 0;
			printf("\nNo character with first name: [%s].\n", srch_Fnm);
			_getch();
		}
		free(read_St);
		free(srch_Fnm);
		fclose(search);
		return;
	}
	case 3: {
		int flag = 0;
		char* srch_Lnm;
		srch_Lnm = (char*)calloc(30, sizeof(char));
		if (srch_Lnm == NULL) {
			perror("Memory error");
			exit(EXIT_FAILURE);
		}
		system("cls");
		getchar();
		printf("\nEnter last name: ");
		fgets(srch_Lnm, 29, stdin);
		for (i = 0; i < chars_Num; i++) {
			fread(read_St, sizeof(CHARACTERS), 1, search);
			if (strcmp(read_St->last_N, srch_Lnm) == 0) {
				fprintf(stdout, BMNG"\n[%d] ID:"ESC" %d\n", i + 1, read_St->ID);
				fprintf(stdout, BMNG"[%d] First name:"ESC" %s", i + 1, read_St->first_N);
				fprintf(stdout, BMNG"[%d] Last name:"ESC" %s", i + 1, read_St->last_N);
				fprintf(stdout, BMNG"[%d] Species:"ESC" %s", i + 1, read_St->species);
				if (read_St->alive == true) {
					fprintf(stdout, BMNG"[%d]"ESC" Alive\n", i + 1);
				}
				else {
					fprintf(stdout, BMNG"[%d]"ESC" Deceased\n", i + 1);
				}
				fprintf(stdout, BMNG"[%d] Titles:"ESC" %s", i + 1, read_St->titles);
				fprintf(stdout, BMNG"[%d] Occupation:"ESC" %s", i + 1, read_St->occupation);
				fprintf(stdout, BMNG"[%d] Affiliation:"ESC" %s", i + 1, read_St->affiliation);
				fprintf(stdout, BMNG"[%d] Family:"ESC" %s", i + 1, read_St->family);
				fprintf(stdout, BMNG"[%d] Portrayed by:"ESC" %s\n", i + 1, read_St->portrayed);
				_getch();
				flag = 1;
			}
		}
		printf("End of list.");
		_getch();
		if (flag == 0) {
			*(srch_Lnm + (strlen(srch_Lnm) - 1)) = 0;
			printf("\nNo character with last name: [%s].\n", srch_Lnm);
			_getch();
		}

		free(read_St);
		free(srch_Lnm);
		fclose(search);
		return;
	}
	case 4: {
		int flag = 0;
		char* srch_Spec;
		srch_Spec = (char*)calloc(30, sizeof(char));
		if (srch_Spec == NULL) {
			perror("Memory error");
			exit(EXIT_FAILURE);
		}
		system("cls");
		getchar();
		printf("\nEnter species: ");
		fgets(srch_Spec, 29, stdin);
		for (i = 0; i < chars_Num; i++) {
			fread(read_St, sizeof(CHARACTERS), 1, search);
			if (strcmp(read_St->species, srch_Spec) == 0) {
				fprintf(stdout, BMNG"\n[%d] ID:"ESC" %d\n", i + 1, read_St->ID);
				fprintf(stdout, BMNG"[%d] First name:"ESC" %s", i + 1, read_St->first_N);
				fprintf(stdout, BMNG"[%d] Last name:"ESC" %s", i + 1, read_St->last_N);
				fprintf(stdout, BMNG"[%d] Species:"ESC" %s", i + 1, read_St->species);
				if (read_St->alive == true) {
					fprintf(stdout, BMNG"[%d]"ESC" Alive\n", i + 1);
				}
				else {
					fprintf(stdout, BMNG"[%d]"ESC" Deceased\n", i + 1);
				}
				fprintf(stdout, BMNG"[%d] Titles:"ESC" %s", i + 1, read_St->titles);
				fprintf(stdout, BMNG"[%d] Occupation:"ESC" %s", i + 1, read_St->occupation);
				fprintf(stdout, BMNG"[%d] Affiliation:"ESC" %s", i + 1, read_St->affiliation);
				fprintf(stdout, BMNG"[%d] Family:"ESC" %s", i + 1, read_St->family);
				fprintf(stdout, BMNG"[%d] Portrayed by:"ESC" %s\n", i + 1, read_St->portrayed);
				_getch();
				flag = 1;
			}
		}
		printf("End of list.");
		_getch();
		if (flag == 0) {
			*(srch_Spec + (strlen(srch_Spec) - 1)) = 0;
			printf("\nNo character of species: [%s].\n", srch_Spec);
			_getch();
		}

		free(read_St);
		free(srch_Spec);
		fclose(search);
		return;
	}
	case 5: {
		int status, flag = 0;
		system("cls");
		do {
			printf("\nEnter status (alive [1] / deceased [0]): ");
			scanf("%d", &status);
		} while (status < 0 || status > 1);
		for (i = 0; i < chars_Num; i++) {
			fread(read_St, sizeof(CHARACTERS), 1, search);
			if (read_St->alive == status) {
				fprintf(stdout, BMNG"\n[%d] ID:"ESC" %d\n", i + 1, read_St->ID);
				fprintf(stdout, BMNG"[%d] First name:"ESC" %s", i + 1, read_St->first_N);
				fprintf(stdout, BMNG"[%d] Last name:"ESC" %s", i + 1, read_St->last_N);
				fprintf(stdout, BMNG"[%d] Species:"ESC" %s", i + 1, read_St->species);
				if (read_St->alive == true) {
					fprintf(stdout, BMNG"[%d]"ESC" Alive\n", i + 1);
				}
				else {
					fprintf(stdout, BMNG"[%d]"ESC" Deceased\n", i + 1);
				}
				fprintf(stdout, BMNG"[%d] Titles:"ESC" %s", i + 1, read_St->titles);
				fprintf(stdout, BMNG"[%d] Occupation:"ESC" %s", i + 1, read_St->occupation);
				fprintf(stdout, BMNG"[%d] Affiliation:"ESC" %s", i + 1, read_St->affiliation);
				fprintf(stdout, BMNG"[%d] Family:"ESC" %s", i + 1, read_St->family);
				fprintf(stdout, BMNG"[%d] Portrayed by:"ESC" %s\n", i + 1, read_St->portrayed);
				flag = 1;
			}
		}
		printf("End of list.");
		_getch();
		if (flag == 0) {
			if (status == 1) {
				printf("\nNo alive characters on the list.\n");
				_getch();
			}
			else {
				printf("\nNo deceased characters on the list.\n");
				_getch();
			}
		}
		free(read_St);
		fclose(search);
		search_Chars();
		return;
	}
	case 6: {
		free(read_St);
		fclose(search);
		return;
	}
	}
}

//locations functions
void locs_Edit_Menu(void) {

	//enter from library_Edit_Board
	int choice = 0;

	while (1) {
		system("cls");
		printf("\t  Logged in as: "RED"[%s]"ESC"\n\n\t"CYN"Locations editing\n\n"ESC"[1] Add a location\n[2] Remove a location\n[3] List locations\n[4] Search a location\n[5] Return\n\nChoice: ", logged_As);
		scanf(" %d", &choice);

		switch (choice) {
			case 1: {
				locs_Add();
				break;
			}
			case 2: {
				locs_Del();
				break;
			}
			case 3: {
				locs_List();
				break;
			}
			case 4: {
				search_Locs();
				break;
			}
			case 5: {
				return;
			}
		}
	}
}

void locs_Add(void) {

	//enter from locs_Edit_Menu
	LOCATIONS* locs = NULL;
	locs = (LOCATIONS*)calloc(1, sizeof(LOCATIONS));
	if (locs == NULL) {
		perror("Struct error");
		exit(EXIT_FAILURE);
	}
	FILE* locs_File = NULL;
	locs_File = fopen("locations.bin", "r+b");
	if (locs_File == NULL) {
		locs_File = fopen("locations.bin", "wb");
		if (locs_File == NULL) {
			perror("File error");
			exit(EXIT_FAILURE);
		}
		system("cls");
		printf("\n\tEntering 1. "CYN"location"ESC".\n\nEnter season: ");
		scanf("%d", &locs->season);
		printf("Enter episode name: "); getchar();
		fgets(locs->episode_Name, 99, stdin);
		printf("Enter location: ");
		fgets(locs->location, 249, stdin);
		int locs_Num = 1;
		fwrite(&locs_Num, sizeof(int), 1, locs_File);
		fwrite(locs, sizeof(LOCATIONS), 1, locs_File);
		fclose(locs_File);
		free(locs);
		return;
	}
	else {
		int locs_Num;
		fread(&locs_Num, sizeof(int), 1, locs_File);
		locs_Num++;
		system("cls");
		printf("\n\tEntering %d. "CYN"location"ESC".\n\nEnter season: ", locs_Num);
		scanf("%d", &locs->season);
		printf("Enter episode name: "); getchar();
		fgets(locs->episode_Name, 99, stdin);
		printf("Enter location: ");
		fgets(locs->location, 249, stdin);
		rewind(locs_File);
		fwrite(&locs_Num, sizeof(int), 1, locs_File);
		fseek(locs_File, sizeof(int) + ((locs_Num - 1) * sizeof(LOCATIONS)), SEEK_SET);
		fwrite(locs, sizeof(LOCATIONS), 1, locs_File);
		fclose(locs_File);
		free(locs);
		return;
	}
}

void locs_Del(void) {

	//enter from locs_Edit_Menu
	int rem_By, num;
	do {
		system("cls");
		printf("\t  Logged in as: "RED"[%s]"ESC"\n\n\tRemoving locations "RED"[BE CAREFUL!]\n\n"ESC"[1] Remove by season [bulk]\n[2] Remove by episode\n[3] Remove by location\n[4] Return\n\nChoice: ", logged_As);
		scanf("%d", &rem_By);
	} while (rem_By < 1 || rem_By > 4);

	FILE* read_Locs = NULL;
	read_Locs = fopen("locations.bin", "rb");
	if (read_Locs == NULL) {
		perror("File error");
		exit(EXIT_FAILURE);
	}

	FILE* tmp_Pntr = NULL;
	tmp_Pntr = fopen("tmp.bin", "wb");
	if (tmp_Pntr == NULL) {
		printf("File error");
		exit(EXIT_FAILURE);
	}

	fread(&num, sizeof(int), 1, read_Locs);
	LOCATIONS* deletion = NULL;
	deletion = (LOCATIONS*)calloc(num, sizeof(LOCATIONS));
	if (deletion == NULL) {
		perror("Struct error");
		exit(EXIT_FAILURE);
	}

	switch (rem_By) {
	case 1: {
		int dlt_Seas, found = 0, helping = 0, count_Del = 0;
		printf("\nEnter season to delete: ");
		scanf("%d", &dlt_Seas);

		helping = num;
		fwrite(&helping, sizeof(int), 1, tmp_Pntr);

		for (int i = 0; i < num; i++) {
			fread(deletion, sizeof(LOCATIONS), 1, read_Locs);
			if (deletion->season == dlt_Seas) {
				found = 1;
				count_Del++;
			}
			else {
				fwrite(deletion, sizeof(LOCATIONS), 1, tmp_Pntr);
			}
		}

		helping = num - count_Del;
		rewind(tmp_Pntr);
		fwrite(&helping, sizeof(int), 1, tmp_Pntr);

		if (found != 1) {
			system("cls");
			printf("\n\tSeason [%d] was not found.\n", dlt_Seas);
			fclose(read_Locs);
			fclose(tmp_Pntr);
			free(deletion);
			_getch();
		}
		else {
			system("cls");
			printf("\n\tWhole season [%d] was "CYN"removed"ESC".\n", dlt_Seas);
			_getch();
			fclose(read_Locs);
			fclose(tmp_Pntr);
			free(deletion);
			if (helping == 0) {
				remove("locations.bin");
				remove("tmp.bin");
				printf("\n\tThere are no "CYN"seasons"ESC" left.\n");
				_getch();
				return;
			}
			else {
				remove("locations.bin");
				rename("tmp.bin", "locations.bin");
			}
		}
		return;
	}
	case 2: {
		char* dlt_By_Name;
		int found = 0, helping = 0, count_Del = 0;
		dlt_By_Name = (char*)calloc(100, sizeof(char));
		if (dlt_By_Name == NULL) {
			perror("Memory error");
			exit(EXIT_FAILURE);
		}
		getchar();
		printf("\nEnter episode name to delete: ");
		fgets(dlt_By_Name, 99, stdin);

		helping = num;
		fwrite(&helping, sizeof(int), 1, tmp_Pntr);

		for (int i = 0; i < num; i++) {
			fread(deletion, sizeof(LOCATIONS), 1, read_Locs);
			if (strstr(deletion->episode_Name, dlt_By_Name)) {
				found = 1;
				count_Del++;
			}
			else {
				fwrite(deletion, sizeof(LOCATIONS), 1, tmp_Pntr);
			}
		}

		helping = num - count_Del;
		rewind(tmp_Pntr);
		fwrite(&helping, sizeof(int), 1, tmp_Pntr);

		if (found != 1) {
			system("cls");
			*(dlt_By_Name + (strlen(dlt_By_Name) - 1)) = 0;
			printf("\n\tEpisode [%s] was not found.\n", dlt_By_Name);
			fclose(read_Locs);
			fclose(tmp_Pntr);
			free(deletion);
			free(dlt_By_Name);
			_getch();
		}
		else {
			system("cls");
			*(dlt_By_Name + (strlen(dlt_By_Name) - 1)) = 0;
			printf("\n\tEpisode [%s] was "CYN"removed"ESC".\n", dlt_By_Name);
			_getch();
			fclose(read_Locs);
			fclose(tmp_Pntr);
			free(dlt_By_Name);
			free(deletion);

			if (helping == 0) {
				remove("locations.bin");
				remove("tmp.bin");
				printf("\n\tThere are no "CYN"episodes"ESC" left.\n");
				_getch();
				return;
			}
			else {
				remove("locations.bin");
				rename("tmp.bin", "locations.bin");
			}
		}
		return;
	}
	case 3: {
		char* dlt_By_Location;
		int found = 0, helping = 0, count_Del = 0;
		dlt_By_Location = (char*)calloc(100, sizeof(char));
		if (dlt_By_Location == NULL) {
			perror("Memory error");
			exit(EXIT_FAILURE);
		}
		getchar();
		printf("\nEnter location name to delete: ");
		fgets(dlt_By_Location, 99, stdin);

		fread(&num, sizeof(int), 1, read_Locs);
		LOCATIONS* deletion = NULL;
		deletion = (LOCATIONS*)calloc(num, sizeof(LOCATIONS));
		if (!deletion) {
			perror("Struct fail");
			exit(EXIT_FAILURE);
		}

		helping = num;
		fwrite(&helping, sizeof(int), 1, tmp_Pntr);

		for (int i = 0; i < num; i++) {
			fread(deletion, sizeof(LOCATIONS), 1, read_Locs);
			if (strstr(deletion->location, dlt_By_Location)) {
				found = 1;
				count_Del++;
			}
			else {
				fwrite(deletion, sizeof(LOCATIONS), 1, tmp_Pntr);
			}
		}

		helping = num - count_Del;
		rewind(tmp_Pntr);
		fwrite(&helping, sizeof(int), 1, tmp_Pntr);

		if (found != 1) {
			system("cls");
			*(dlt_By_Location + (strlen(dlt_By_Location) - 1)) = 0;
			printf("\n\tEpisode [%s] was not found.\n", dlt_By_Location);
			fclose(read_Locs);
			fclose(tmp_Pntr);
			free(deletion);
			free(dlt_By_Location);
			_getch();
		}
		else {
			system("cls");
			*(dlt_By_Location + (strlen(dlt_By_Location) - 1)) = 0;
			printf("\n\tEpisode [%s] was "CYN"removed"ESC".\n", dlt_By_Location);
			_getch();
			fclose(read_Locs);
			fclose(tmp_Pntr);
			free(deletion);
			free(dlt_By_Location);

			if (helping == 0) {
				remove("locations.bin");
				remove("tmp.bin");
				printf("\n\tThere are no "CYN"episodes"ESC" left.\n");
				_getch();
				return;
			}
			else {
				remove("locations.bin");
				rename("tmp.bin", "locations.bin");
			}
		}
		return;
	}
	case 4: {
		fclose(read_Locs);
		fclose(tmp_Pntr);
		free(deletion);
		return;
	}
	}
}

void locs_List(void) {

	//enter from locs_Edit_Menu
	int list_Choice, locs_Num;
	do {

		system("cls");
		printf("\t  Logged in as: "RED"[%s]"ESC"\n\n\t"CYN"List locations by:\n\n"ESC"[1] Season\n[2] Episode\n[3] Location\n[4] Return to edit panel\n\nChoice: ", logged_As);
		scanf("%d", &list_Choice);
	} while (list_Choice < 1 || list_Choice > 4);

	FILE* read = NULL;
	read = fopen("locations.bin", "rb");
	if (read == NULL) {
		perror("File error");
		exit(EXIT_FAILURE);
	}

	LOCATIONS* read_St = NULL;
	fread(&locs_Num, sizeof(int), 1, read);
	read_St = (LOCATIONS*)calloc(locs_Num, sizeof(LOCATIONS));
	if (read_St == NULL) {
		perror("Struct error");
		exit(EXIT_FAILURE);
	}

	switch (list_Choice) {
	case 1: {
		int asc_Desc, i;
		do {
			system("cls");
			printf("\n\t"CYN"Sort locations by seasons:\n\n"ESC"[1] Ascending\n[2] Descending\n\nChoice: ");
			scanf("%d", &asc_Desc);
		} while (asc_Desc < 1 || asc_Desc > 2);

		fseek(read, sizeof(int), SEEK_SET);
		fread(read_St, sizeof(LOCATIONS), locs_Num, read);
		if (asc_Desc == 1)
			qsort(read_St, locs_Num, sizeof(LOCATIONS), compare_Season_Asc_Locs);
		else
			qsort(read_St, locs_Num, sizeof(LOCATIONS), compare_Season_Desc_Locs);
		system("cls");
		printf("\n\tNumber of "CYN"locations"ESC": [%d]\n\n", locs_Num);
		for (i = 0; i < locs_Num; i++) {
			fprintf(stdout, BMNG"\n[%d] Season:"ESC" %d\n", i + 1, (read_St + i)->season);
			fprintf(stdout, BMNG"[%d] Episode name:"ESC" %s", i + 1, (read_St + i)->episode_Name);
			fprintf(stdout, BMNG"[%d] Location:"ESC" %s\n", i + 1, (read_St + i)->location);
		}
		_getch();
		fclose(read);
		free(read_St);
		return;
	}
	case 2: {
		int asc_Desc, i;
		do {
			system("cls");
			printf("\n\t"CYN"Sort locations by episode:\n\n"ESC"[1] Ascending\n[2] Descending\n\nChoice: ");
			scanf("%d", &asc_Desc);
		} while (asc_Desc < 1 || asc_Desc > 2);

		fseek(read, sizeof(int), SEEK_SET);
		fread(read_St, sizeof(LOCATIONS), locs_Num, read);
		if (asc_Desc == 1)
			qsort(read_St, locs_Num, sizeof(LOCATIONS), comp_Episode_Asc_Locs);
		else
			qsort(read_St, locs_Num, sizeof(LOCATIONS), comp_Episode_Desc_Locs);
		system("cls");
		printf("\n\tNumber of "CYN"locations"ESC": [%d]\n\n", locs_Num);
		for (i = 0; i < locs_Num; i++) {
			fprintf(stdout, BMNG"\n[%d] Season:"ESC" %d\n", i + 1, (read_St + i)->season);
			fprintf(stdout, BMNG"[%d] Episode name:"ESC" %s", i + 1, (read_St + i)->episode_Name);
			fprintf(stdout, BMNG"[%d] Location:"ESC" %s\n", i + 1, (read_St + i)->location);
		}
		_getch();
		fclose(read);
		free(read_St);
		return;
	}
	case 3: {
		int asc_Desc, i;
		do {
			system("cls");
			printf("\n\t"CYN"Sort locations by location:\n\n"ESC"[1] Ascending\n[2] Descending\n\nChoice: ");
			scanf("%d", &asc_Desc);
		} while (asc_Desc < 1 || asc_Desc > 2);

		fseek(read, sizeof(int), SEEK_SET);
		fread(read_St, sizeof(LOCATIONS), locs_Num, read);
		if (asc_Desc == 1)
			qsort(read_St, locs_Num, sizeof(LOCATIONS), comp_Location_Asc_Locs);
		else
			qsort(read_St, locs_Num, sizeof(LOCATIONS), comp_Location_Desc_Locs);
		system("cls");
		printf("\n\tNumber of "CYN"locations"ESC": [%d]\n\n", locs_Num);
		for (i = 0; i < locs_Num; i++) {
			fprintf(stdout, BMNG"\n[%d] Season:"ESC" %d\n", i + 1, (read_St + i)->season);
			fprintf(stdout, BMNG"[%d] Episode name:"ESC" %s", i + 1, (read_St + i)->episode_Name);
			fprintf(stdout, BMNG"[%d] Location:"ESC" %s\n", i + 1, (read_St + i)->location);
		}
		_getch();
		fclose(read);
		free(read_St);
		return;
	}
	case 4: {
		fclose(read);
		free(read_St);
		return;
	}
	}
}

void search_Locs(void) {

	//enter from locs_Edit_Menu
	int search_Choice;
	do {
		system("cls");
		printf("\t  Logged in as: "RED"[%s]"ESC"\n\n\t"BRED"Search locations by:\n\n"ESC"[1] Season\n[2] Episode name\n[3] Location\n[4] Return to edit panel\n\nChoice: ", logged_As);
		scanf("%d", &search_Choice);
	} while (search_Choice < 1 || search_Choice > 4);

	FILE* search = NULL;
	search = fopen("locations.bin", "rb");
	if (search == NULL) {
		perror("File error");
		exit(EXIT_FAILURE);
	}

	LOCATIONS* read_St = NULL;
	int i, locs_Num;
	fread(&locs_Num, sizeof(int), 1, search);
	read_St = (LOCATIONS*)calloc(locs_Num, sizeof(LOCATIONS));
	if (read_St == NULL) {
		perror("Struct error");
		exit(EXIT_FAILURE);
	}

	switch (search_Choice) {
	case 1: {
		int id_Srch, flag = 0;
		system("cls");
		printf("\nEnter season: ");
		scanf("%d", &id_Srch);
		for (i = 0; i < locs_Num; i++) {
			fread(read_St, sizeof(LOCATIONS), 1, search);
			if (read_St->season == id_Srch) {
				fprintf(stdout, BMNG"\n[%d] Season:"ESC" %d\n", i + 1, read_St->season);
				fprintf(stdout, BMNG"[%d] Episode name:"ESC" %s", i + 1, read_St->episode_Name);
				fprintf(stdout, BMNG"[%d] Location:"ESC" %s\n", i + 1, read_St->location);
				flag = 1;
				_getch();
				break;
			}
		}
		printf("End of list.");
		_getch();
		if (flag == 0) {
			printf("\nNo locations on season: [%d].\n", id_Srch);
			_getch();
		}
		free(read_St);
		fclose(search);
		return;
	}
	case 2: {
		int flag = 0;
		char* srch_Enm;
		srch_Enm = (char*)calloc(100, sizeof(char));
		if (srch_Enm == NULL) {
			perror("Memory error");
			exit(EXIT_FAILURE);
		}
		system("cls");
		getchar();
		printf("\nEnter episode name: ");
		fgets(srch_Enm, 99, stdin);
		for (i = 0; i < locs_Num; i++) {
			fread(read_St, sizeof(LOCATIONS), 1, search);
			if (strcmp(read_St->episode_Name, srch_Enm) == 0) {
				fprintf(stdout, BMNG"\n[%d] Season:"ESC" %d\n", i + 1, read_St->season);
				fprintf(stdout, BMNG"[%d] Episode name:"ESC" %s", i + 1, read_St->episode_Name);
				fprintf(stdout, BMNG"[%d] Location:"ESC" %s\n", i + 1, read_St->location);
				flag = 1;
				_getch();
				break;
			}
		}
		printf("End of list.");
		_getch();
		if (flag == 0) {
			*(srch_Enm + (strlen(srch_Enm) - 1)) = 0;
			printf("\nNo location within episode name: [%s].\n", srch_Enm);
			_getch();
		}
		free(read_St);
		free(srch_Enm);
		fclose(search);
		return;
	}
	case 3: {
		int flag = 0;
		char* srch_Loc;
		srch_Loc = (char*)calloc(249, sizeof(char));
		if (srch_Loc == NULL) {
			perror("Memory error");
			exit(EXIT_FAILURE);
		}
		system("cls");
		getchar();
		printf("\nEnter location name: ");
		fgets(srch_Loc, 249, stdin);
		for (i = 0; i < locs_Num; i++) {
			fread(read_St, sizeof(LOCATIONS), 1, search);
			if (strcmp(read_St->location, srch_Loc) == 0) {
				fprintf(stdout, BMNG"\n[%d] Season:"ESC" %d\n", i + 1, read_St->season);
				fprintf(stdout, BMNG"[%d] Episode name:"ESC" %s", i + 1, read_St->episode_Name);
				fprintf(stdout, BMNG"[%d] Location:"ESC" %s\n", i + 1, read_St->location);
				flag = 1;
				_getch();
			}
		}
		printf("End of list.");
		_getch();
		if (flag == 0) {
			*(srch_Loc + (strlen(srch_Loc) - 1)) = 0;
			printf("\nNo location named: [%s].\n", srch_Loc);
			_getch();
		}

		free(read_St);
		free(srch_Loc);
		fclose(search);
		return;
	}
	case 4: {
		free(read_St);
		fclose(search);
		return;
	}
	}
}

//music functions
void music_Edit_Menu(void) {

	//enter from library_Edit_Board
	int choice;
	while (1) {
		system("cls");
		printf("\t  Logged in as: "RED"[%s]"ESC"\n\n\t"BMNG"Music editing\n\n"ESC"[1] Add music\n[2] Remove music\n[3] List music\n[4] Search music\n[5] Return\n\nChoice: ", logged_As);
		scanf("%d", &choice);

		switch (choice) {
			case 1: {
				music_Add();
				break;
			}
			case 2: {
				del_Music();
				break;
			}
			case 3: {
				music_List();
				break;
			}
			case 4: {
				search_Music();
				break;
			}
			case 5: {
				return;
			}
		}
	}
}

void music_Add(void) {

	//enter from music_Edit_Menu
	MUSIC* mus_Struc = NULL;
	mus_Struc = (MUSIC*)calloc(1, sizeof(MUSIC));
	if (mus_Struc == NULL) {
		perror("Struct error");
		exit(EXIT_FAILURE);
	}
	FILE* music_File = NULL;
	music_File = fopen("music.bin", "r+b");
	if (music_File == NULL) {
		music_File = fopen("music.bin", "wb");
		if (music_File == NULL) {
			perror("File error");
			exit(EXIT_FAILURE);
		}
		system("cls");
		printf("\n\tEntering 1. "BMNG"music track"ESC".\n\nEnter season: ");
		scanf("%d", &mus_Struc->season);
		printf("Enter episode name: "); getchar();
		fgets(mus_Struc->episode_Name, 99, stdin);
		printf("Enter song name: ");
		fgets(mus_Struc->song_Name, 99, stdin);
		printf("Enter author: ");
		fgets(mus_Struc->author, 99, stdin);
		int music_Num = 1;
		fwrite(&music_Num, sizeof(int), 1, music_File);
		fwrite(mus_Struc, sizeof(MUSIC), 1, music_File);
		fclose(music_File);
		free(mus_Struc);
		return;
	}
	else {
		int music_Num;
		fread(&music_Num, sizeof(int), 1, music_File);
		music_Num++;
		system("cls");
		printf("\n\tEntering %d. "BMNG"music track"ESC".\n\nEnter season: ", music_Num);
		scanf("%d", &mus_Struc->season);
		printf("Enter episode name: "); getchar();
		fgets(mus_Struc->episode_Name, 99, stdin);
		printf("Enter song name: ");
		fgets(mus_Struc->song_Name, 99, stdin);
		printf("Enter author: ");
		fgets(mus_Struc->author, 99, stdin);
		rewind(music_File);
		fwrite(&music_Num, sizeof(int), 1, music_File);
		fseek(music_File, sizeof(int) + ((music_Num - 1) * sizeof(MUSIC)), SEEK_SET);
		fwrite(mus_Struc, sizeof(MUSIC), 1, music_File);
		fclose(music_File);
		free(mus_Struc);
		return;
	}
}

void del_Music(void) {

	//enter from music_Edit_Menu
	int rem_By, num;
	do {
		system("cls");
		printf("\t  Logged in as: "RED"[%s]"ESC"\n\n\tRemoving music "RED"[BE CAREFUL!]\n\n"ESC"[1] Remove by season [bulk]\n[2] Remove by episode name\n[3] Remove by song name\n[4] Remove by author\n[5] Return\n\nChoice: ", logged_As);
		scanf("%d", &rem_By);
	} while (rem_By < 1 || rem_By > 5);

	FILE* read_Music = NULL;
	read_Music = fopen("music.bin", "rb");
	if (read_Music == NULL) {
		perror("File error");
		exit(EXIT_FAILURE);
	}

	FILE* tmp_Pntr = NULL;
	tmp_Pntr = fopen("tmp.bin", "wb");
	if (tmp_Pntr == NULL) {
		printf("File error");
		exit(EXIT_FAILURE);
	}

	fread(&num, sizeof(int), 1, read_Music);
	MUSIC* deletion = NULL;
	deletion = (MUSIC*)calloc(num, sizeof(MUSIC));
	if (deletion == NULL) {
		perror("Struct fail");
		exit(EXIT_FAILURE);
	}

	switch (rem_By) {
	case 1: {
		int dlt_Seas, found = 0, helping = 0, count_Del = 0;
		printf("\nEnter season to delete: ");
		scanf("%d", &dlt_Seas);

		helping = num;
		fwrite(&helping, sizeof(int), 1, tmp_Pntr);

		for (int i = 0; i < num; i++) {
			fread(deletion, sizeof(MUSIC), 1, read_Music);
			if (deletion->season == dlt_Seas) {
				found = 1;
				count_Del++;
			}
			else {
				fwrite(deletion, sizeof(MUSIC), 1, tmp_Pntr);
			}
		}

		helping = num - count_Del;
		rewind(tmp_Pntr);
		fwrite(&helping, sizeof(int), 1, tmp_Pntr);

		if (found != 1) {
			system("cls");
			printf("\n\tSeason [%d] was not found.\n", dlt_Seas);
			fclose(read_Music);
			fclose(tmp_Pntr);
			free(deletion);
			_getch();
		}
		else {
			system("cls");
			printf("\n\tWhole season [%d] was "BMNG"removed"ESC".\n", dlt_Seas);
			_getch();
			fclose(read_Music);
			fclose(tmp_Pntr);
			free(deletion);
			if (helping == 0) {
				remove("music.bin");
				remove("tmp.bin");
				printf("\n\tThere is no "BMNG"music"ESC" left.\n");
				_getch();
				return;
			}
			else {
				remove("music.bin");
				rename("tmp.bin", "music.bin");
			}
		}
		return;
	}
	case 2: {
		char* dlt_By_Ep_Name;
		int found = 0, helping = 0, count_Del = 0;
		dlt_By_Ep_Name = (char*)calloc(100, sizeof(char));
		if (dlt_By_Ep_Name == NULL) {
			perror("Memory error");
			exit(EXIT_FAILURE);
		}
		getchar();
		printf("\nEnter episode name to delete music from: ");
		fgets(dlt_By_Ep_Name, 99, stdin);

		helping = num;
		fwrite(&helping, sizeof(int), 1, tmp_Pntr);

		for (int i = 0; i < num; i++) {
			fread(deletion, sizeof(MUSIC), 1, read_Music);
			if (strstr(deletion->episode_Name, dlt_By_Ep_Name)) {
				found = 1;
				count_Del++;
			}
			else {
				fwrite(deletion, sizeof(MUSIC), 1, tmp_Pntr);
			}
		}

		helping = num - count_Del;
		rewind(tmp_Pntr);
		fwrite(&helping, sizeof(int), 1, tmp_Pntr);

		if (found != 1) {
			system("cls");
			*(dlt_By_Ep_Name + (strlen(dlt_By_Ep_Name) - 1)) = 0;
			printf("\n\tEpisode [%s] was not found.\n", dlt_By_Ep_Name);
			fclose(read_Music);
			fclose(tmp_Pntr);
			free(deletion);
			free(dlt_By_Ep_Name);
			_getch();
		}
		else {
			system("cls");
			*(dlt_By_Ep_Name + (strlen(dlt_By_Ep_Name) - 1)) = 0;
			printf("\n\tEpisode [%s] was "BMNG"removed"ESC".\n", dlt_By_Ep_Name);
			_getch();
			fclose(read_Music);
			fclose(tmp_Pntr);
			free(dlt_By_Ep_Name);
			free(deletion);

			if (helping == 0) {
				remove("music.bin");
				remove("tmp.bin");
				printf("\n\tThere is no "BMNG"music"ESC" left.\n");
				_getch();
				return;
			}
			else {
				remove("music.bin");
				rename("tmp.bin", "music.bin");
			}
		}
		return;
	}
	case 3: {
		char* dlt_By_Sng_Nm;
		int found = 0, helping = 0, count_Del = 0;
		dlt_By_Sng_Nm = (char*)calloc(100, sizeof(char));
		if (dlt_By_Sng_Nm == NULL) {
			perror("Memory error");
			exit(EXIT_FAILURE);
		}
		getchar();
		printf("\nEnter song name to delete: ");
		fgets(dlt_By_Sng_Nm, 99, stdin);

		helping = num;
		fwrite(&helping, sizeof(int), 1, tmp_Pntr);

		for (int i = 0; i < num; i++) {
			fread(deletion, sizeof(MUSIC), 1, read_Music);
			if (strstr(deletion->song_Name, dlt_By_Sng_Nm)) {
				found = 1;
				count_Del++;
			}
			else {
				fwrite(deletion, sizeof(MUSIC), 1, tmp_Pntr);
			}
		}

		helping = num - count_Del;
		rewind(tmp_Pntr);
		fwrite(&helping, sizeof(int), 1, tmp_Pntr);

		if (found != 1) {
			system("cls");
			*(dlt_By_Sng_Nm + (strlen(dlt_By_Sng_Nm) - 1)) = 0;
			printf("\n\tSong [%s] was not found.\n", dlt_By_Sng_Nm);
			fclose(read_Music);
			fclose(tmp_Pntr);
			free(deletion);
			free(dlt_By_Sng_Nm);
			_getch();
		}
		else {
			system("cls");
			*(dlt_By_Sng_Nm + (strlen(dlt_By_Sng_Nm) - 1)) = 0;
			printf("\n\tSong [%s] was "BMNG"removed"ESC".\n", dlt_By_Sng_Nm);
			_getch();
			fclose(read_Music);
			fclose(tmp_Pntr);
			free(deletion);
			free(dlt_By_Sng_Nm);

			if (helping == 0) {
				remove("music.bin");
				remove("tmp.bin");
				printf("\n\tThere is no "BMNG"music"ESC" left.\n");
				_getch();
				return;
			}
			else {
				remove("music.bin");
				rename("tmp.bin", "music.bin");
			}
		}
		return;
	}
	case 4: {
		char* dlt_By_Author;
		int found = 0, helping = 0, count_Del = 0;
		dlt_By_Author = (char*)calloc(100, sizeof(char));
		if (dlt_By_Author == NULL) {
			perror("Memory error");
			exit(EXIT_FAILURE);
		}
		getchar();
		printf("\nEnter author to delete: ");
		fgets(dlt_By_Author, 99, stdin);

		helping = num;
		fwrite(&helping, sizeof(int), 1, tmp_Pntr);

		for (int i = 0; i < num; i++) {
			fread(deletion, sizeof(MUSIC), 1, read_Music);
			if (strstr(deletion->author, dlt_By_Author)) {
				found = 1;
				count_Del++;
			}
			else {
				fwrite(deletion, sizeof(MUSIC), 1, tmp_Pntr);
			}
		}

		helping = num - count_Del;
		rewind(tmp_Pntr);
		fwrite(&helping, sizeof(int), 1, tmp_Pntr);

		if (found != 1) {
			system("cls");
			*(dlt_By_Author + (strlen(dlt_By_Author) - 1)) = 0;
			printf("\n\tAuthor [%s] was not found.\n", dlt_By_Author);
			fclose(read_Music);
			fclose(tmp_Pntr);
			free(deletion);
			free(dlt_By_Author);
			_getch();
		}
		else {
			system("cls");
			*(dlt_By_Author + (strlen(dlt_By_Author) - 1)) = 0;
			printf("\n\tAuthor [%s] was "BMNG"removed"ESC".\n", dlt_By_Author);
			_getch();
			fclose(read_Music);
			fclose(tmp_Pntr);
			free(deletion);
			free(dlt_By_Author);

			if (helping == 0) {
				remove("music.bin");
				remove("tmp.bin");
				printf("\n\tThere is no "BMNG"music"ESC" left.\n");
				_getch();
				return;
			}
			else {
				remove("music.bin");
				rename("tmp.bin", "music.bin");
			}
		}
		return;
	}
	case 5: {
		fclose(read_Music);
		fclose(tmp_Pntr);
		free(deletion);
		return;
	}
	}
}

void music_List(void) {

	//enter from music_Edit_Menu
	int list_Choice, music_Num;
	do {
		system("cls");
		printf("\t  Logged in as: "RED"[%s]"ESC"\n\n\t"CYN"List music by:\n\n"ESC"[1] Season\n[2] Song name\n[3] Author\n[4] Return to edit panel\n\nChoice: ", logged_As);
		scanf("%d", &list_Choice);
	} while (list_Choice < 1 || list_Choice > 4);

	FILE* read = NULL;
	read = fopen("music.bin", "rb");
	if (read == NULL) {
		perror("File error");
		exit(EXIT_FAILURE);
	}

	MUSIC* read_St = NULL;
	fread(&music_Num, sizeof(int), 1, read);
	read_St = (MUSIC*)calloc(music_Num, sizeof(MUSIC));
	if (read_St == NULL) {
		perror("Struct error");
		exit(EXIT_FAILURE);
	}

	switch (list_Choice) {
		case 1: {
			int asc_Desc, i;
			do {
				system("cls");
				printf("\n\t"BMNG"Sort music by seasons:\n\n"ESC"[1] Ascending\n[2] Descending\n\nChoice: ");
				scanf("%d", &asc_Desc);
			} while (asc_Desc < 1 || asc_Desc > 2);

			fseek(read, sizeof(int), SEEK_SET);
			fread(read_St, sizeof(MUSIC), music_Num, read);
			if (asc_Desc == 1)
				qsort(read_St, music_Num, sizeof(MUSIC), compare_Season_Asc_Music);
			else
				qsort(read_St, music_Num, sizeof(MUSIC), compare_Season_Desc_Music);
			system("cls");
			printf("\n\tNumber of "BMNG"music tracks"ESC": [%d]\n\n", music_Num);
			for (i = 0; i < music_Num; i++) {
				fprintf(stdout, BMNG"\n[%d] Season:"ESC" %d\n", i + 1, (read_St + i)->season);
				fprintf(stdout, BMNG"[%d] Episode name:"ESC" %s", i + 1, (read_St + i)->episode_Name);
				fprintf(stdout, BMNG"[%d] Song name:"ESC" %s", i + 1, (read_St + i)->song_Name);
				fprintf(stdout, BMNG"[%d] Author:"ESC" %s\n", i + 1, (read_St + i)->author);
			}
			_getch();
			fclose(read);
			free(read_St);
			return;
		}
		case 2: {
			int asc_Desc, i;
			do {
				system("cls");
				printf("\n\t"BMNG"Sort music by song name:\n\n"ESC"[1] Ascending\n[2] Descending\n\nChoice: ");
				scanf("%d", &asc_Desc);
			} while (asc_Desc < 1 || asc_Desc > 2);

			fseek(read, sizeof(int), SEEK_SET);
			fread(read_St, sizeof(MUSIC), music_Num, read);
			if (asc_Desc == 1)
				qsort(read_St, music_Num, sizeof(MUSIC), comp_Song_Name_Asc_Music);
			else
				qsort(read_St, music_Num, sizeof(MUSIC), comp_Song_Name_Desc_Music);
			system("cls");
			printf("\n\tNumber of "BMNG"music tracks"ESC": [%d]\n\n", music_Num);
			for (i = 0; i < music_Num; i++) {
				fprintf(stdout, BMNG"\n[%d] Season:"ESC" %d\n", i + 1, (read_St + i)->season);
				fprintf(stdout, BMNG"[%d] Episode name:"ESC" %s", i + 1, (read_St + i)->episode_Name);
				fprintf(stdout, BMNG"[%d] Song name:"ESC" %s", i + 1, (read_St + i)->song_Name);
				fprintf(stdout, BMNG"[%d] Author:"ESC" %s\n", i + 1, (read_St + i)->author);
			}
			_getch();
			fclose(read);
			free(read_St);
			return;
		}
		case 3: {
			int asc_Desc, i;
			do {
				system("cls");
				printf("\n\t"BMNG"Sort music by author:\n\n"ESC"[1] Ascending\n[2] Descending\n\nChoice: ");
				scanf("%d", &asc_Desc);
			} while (asc_Desc < 1 || asc_Desc > 2);

			fseek(read, sizeof(int), SEEK_SET);
			fread(read_St, sizeof(MUSIC), music_Num, read);
			if (asc_Desc == 1)
				qsort(read_St, music_Num, sizeof(MUSIC), comp_Author_Asc_Music);
			else
				qsort(read_St, music_Num, sizeof(MUSIC), comp_Author_Desc_Music);
			system("cls");
			printf("\n\tNumber of "BMNG"music tracks"ESC": [%d]\n\n", music_Num);
			for (i = 0; i < music_Num; i++) {
				fprintf(stdout, BMNG"\n[%d] Season:"ESC" %d\n", i + 1, (read_St + i)->season);
				fprintf(stdout, BMNG"[%d] Episode name:"ESC" %s", i + 1, (read_St + i)->episode_Name);
				fprintf(stdout, BMNG"[%d] Song name:"ESC" %s", i + 1, (read_St + i)->song_Name);
				fprintf(stdout, BMNG"[%d] Author:"ESC" %s\n", i + 1, (read_St + i)->author);
			}
			_getch();
			fclose(read);
			free(read_St);
			return;
		}
		case 4: {
			fclose(read);
			free(read_St);
			return;
		}
	}
}

void search_Music(void) {

	//enter from music_Edit_Menu
	int search_Choice, i, music_Num;
	do {
		system("cls");
		printf("\t  Logged in as: "RED"[%s]"ESC"\n\n\t"BMNG"Search music by:\n\n"ESC"[1] Season\n[2] Song name\n[3] Author\n[4] Return to edit panel\n\nChoice: ", logged_As);
		scanf("%d", &search_Choice);
	} while (search_Choice < 1 || search_Choice > 4);

	FILE* search = NULL;
	search = fopen("music.bin", "rb");
	if (search == NULL) {
		perror("File error");
		exit(EXIT_FAILURE);
	}

	MUSIC* read_St = NULL;
	fread(&music_Num, sizeof(int), 1, search);
	read_St = (MUSIC*)calloc(music_Num, sizeof(MUSIC));
	if (read_St == NULL) {
		perror("Struct error");
		exit(EXIT_FAILURE);
	}

	switch (search_Choice) {
	case 1: {
		int id_Srch, flag = 0;
		system("cls");
		printf("\nEnter season: ");
		scanf("%d", &id_Srch);
		for (i = 0; i < music_Num; i++) {
			fread(read_St, sizeof(MUSIC), 1, search);
			if (read_St->season == id_Srch) {
				fprintf(stdout, BMNG"\n[%d] Season:"ESC" %d\n", i + 1, read_St->season);
				fprintf(stdout, BMNG"[%d] Episode name:"ESC" %s", i + 1, read_St->episode_Name);
				fprintf(stdout, BMNG"[%d] Song name:"ESC" %s", i + 1, read_St->song_Name);
				fprintf(stdout, BMNG"[%d] Author:"ESC" %s\n", i + 1, read_St->author);
				flag = 1;
				_getch();
			}
		}
		printf("End of list.");
		_getch();
		if (flag == 0) {
			printf("\nNo music on season: [%d].\n", id_Srch);
			_getch();
		}
		free(read_St);
		fclose(search);
		return;
	}
	case 2: {
		int flag = 0;
		char* srch_Sng_Nm;
		srch_Sng_Nm = (char*)calloc(100, sizeof(char));
		if (srch_Sng_Nm == NULL) {
			perror("Memory error");
			exit(EXIT_FAILURE);
		}
		system("cls");
		getchar();
		printf("\nEnter song name: ");
		fgets(srch_Sng_Nm, 99, stdin);
		for (i = 0; i < music_Num; i++) {
			fread(read_St, sizeof(MUSIC), 1, search);
			if (strcmp(read_St->song_Name, srch_Sng_Nm) == 0) {
				fprintf(stdout, BMNG"\n[%d] Season:"ESC" %d\n", i + 1, read_St->season);
				fprintf(stdout, BMNG"[%d] Episode name:"ESC" %s", i + 1, read_St->episode_Name);
				fprintf(stdout, BMNG"[%d] Song name:"ESC" %s", i + 1, read_St->song_Name);
				fprintf(stdout, BMNG"[%d] Author:"ESC" %s\n", i + 1, read_St->author);
				flag = 1;
				_getch();
				break;
			}
		}
		printf("End of list.");
		_getch();
		if (flag == 0) {
			*(srch_Sng_Nm + (strlen(srch_Sng_Nm) - 1)) = 0;
			printf("\nNo song with name: [%s].\n", srch_Sng_Nm);
			_getch();
		}
		free(read_St);
		free(srch_Sng_Nm);
		fclose(search);
		return;
	}
	case 3: {
		int flag = 0;
		char* srch_Author;
		srch_Author = (char*)calloc(100, sizeof(char));
		if (srch_Author == NULL) {
			perror("Memory error");
			exit(EXIT_FAILURE);
		}
		system("cls");
		getchar();
		printf("\nEnter author: ");
		fgets(srch_Author, 99, stdin);
		for (i = 0; i < music_Num; i++) {
			fread(read_St, sizeof(MUSIC), 1, search);
			if (strcmp(read_St->author, srch_Author) == 0) {
				fprintf(stdout, BMNG"\n[%d] Season:"ESC" %d\n", i + 1, read_St->season);
				fprintf(stdout, BMNG"[%d] Episode name:"ESC" %s", i + 1, read_St->episode_Name);
				fprintf(stdout, BMNG"[%d] Song name:"ESC" %s", i + 1, read_St->song_Name);
				fprintf(stdout, BMNG"[%d] Author:"ESC" %s\n", i + 1, read_St->author);
				flag = 1;
				_getch();
			}
		}
		printf("End of list.");
		_getch();
		if (flag == 0) {
			*(srch_Author + (strlen(srch_Author) - 1)) = 0;
			printf("\nNo author(s) named: [%s].\n", srch_Author);
			_getch();
		}

		free(read_St);
		free(srch_Author);
		fclose(search);
		return;
	}
	case 4: {
		free(read_St);
		fclose(search);
		return;
	}
	}
}

//objects functions
void object_Edit_Menu(void) {

	//enter from library_Edit_Board
	int choice;
	while (1) {
		system("cls");
		printf("\t  Logged in as: "RED"[%s]"ESC"\n\n\t"BMNG"Objects editing\n\n"ESC"[1] Add objects\n[2] Remove objects\n[3] List objects\n[4] Search objects\n[5] Return\n\nChoice: ", logged_As);
		scanf("%d", &choice);

		switch (choice) {
			case 1: {
				objects_Add();
				break;
			}
			case 2: {
				del_Objects();
				break;
			}
			case 3: {
				objects_List();
				break;
			}
			case 4: {
				search_Objects();
				break;
			}
			case 5: {
				return;
			}
		}
	}
}

void objects_Add(void) {

	//enter from music_Edit_Menu
	OBJECTS* obj_Struc = NULL;
	obj_Struc = (OBJECTS*)calloc(1, sizeof(OBJECTS));
	if (obj_Struc == NULL) {
		perror("Struct error");
		exit(EXIT_FAILURE);
	}
	FILE* obj_File = NULL;
	obj_File = fopen("objects.bin", "r+b");
	if (obj_File == NULL) {
		obj_File = fopen("objects.bin", "wb");
		if (obj_File == NULL) {
			perror("File error");
			exit(EXIT_FAILURE);
		}
		system("cls");
		printf("\n\tEntering 1. "YLW"object"ESC".\n\nEnter season: ");
		scanf("%d", &obj_Struc->season);
		printf("Enter name: "); getchar();
		fgets(obj_Struc->name, 99, stdin);
		printf("Enter manufacturer: ");
		fgets(obj_Struc->manufacturer, 39, stdin);
		printf("Enter use: ");
		fgets(obj_Struc->use, 99, stdin);
		printf("Enter powers: ");
		fgets(obj_Struc->powers, 99, stdin);
		printf("Enter location / stauts: ");
		fgets(obj_Struc->location_Status, 99, stdin);
		int obj_Num = 1;
		fwrite(&obj_Num, sizeof(int), 1, obj_File);
		fwrite(obj_Struc, sizeof(OBJECTS), 1, obj_File);
		fclose(obj_File);
		free(obj_Struc);
		return;
	}
	else {
		int obj_Num;
		fread(&obj_Num, sizeof(int), 1, obj_File);
		obj_Num++;
		system("cls");
		printf("\n\tEntering %d. "YLW"object"ESC".\n\nEnter season: ", obj_Num);
		scanf("%d", &obj_Struc->season);
		printf("Enter name: "); getchar();
		fgets(obj_Struc->name, 99, stdin);
		printf("Enter manufacturer: ");
		fgets(obj_Struc->manufacturer, 39, stdin);
		printf("Enter use: ");
		fgets(obj_Struc->use, 99, stdin);
		printf("Enter powers: ");
		fgets(obj_Struc->powers, 99, stdin);
		printf("Enter location / stauts: ");
		fgets(obj_Struc->location_Status, 99, stdin);
		rewind(obj_File);
		fwrite(&obj_Num, sizeof(int), 1, obj_File);
		fseek(obj_File, sizeof(int) + ((obj_Num - 1) * sizeof(OBJECTS)), SEEK_SET);
		fwrite(obj_Struc, sizeof(OBJECTS), 1, obj_File);
		fclose(obj_File);
		free(obj_Struc);
		return;
	}
}

void del_Objects(void) {

	//enter from music_Edit_Menu
	int rem_By, num;
	do {
		system("cls");
		printf("\t  Logged in as: "RED"[%s]"ESC"\n\n\tRemoving objects "RED"[BE CAREFUL!]\n\n"ESC"[1] Remove by season [bulk]\n[2] Remove by name\n[3] Remove by manufacturer\n[4] Return\n\nChoice: ", logged_As);
		scanf("%d", &rem_By);
	} while (rem_By < 1 || rem_By > 4);

	FILE* read_Objs = NULL;
	read_Objs = fopen("objects.bin", "rb");
	if (read_Objs == NULL) {
		perror("File error");
		exit(EXIT_FAILURE);
	}

	FILE* tmp_Pntr = NULL;
	tmp_Pntr = fopen("tmp.bin", "wb");
	if (tmp_Pntr == NULL) {
		printf("File error");
		exit(EXIT_FAILURE);
	}

	fread(&num, sizeof(int), 1, read_Objs);
	OBJECTS* deletion = NULL;
	deletion = (OBJECTS*)calloc(num, sizeof(OBJECTS));
	if (deletion == NULL) {
		perror("Struct fail");
		exit(EXIT_FAILURE);
	}

	switch (rem_By) {
	case 1: {
		int dlt_Seas, found = 0, helping = 0, count_Del = 0;
		printf("\nEnter season to delete: ");
		scanf("%d", &dlt_Seas);

		helping = num;
		fwrite(&helping, sizeof(int), 1, tmp_Pntr);

		for (int i = 0; i < num; i++) {
			fread(deletion, sizeof(OBJECTS), 1, read_Objs);
			if (deletion->season == dlt_Seas) {
				found = 1;
				count_Del++;
			}
			else {
				fwrite(deletion, sizeof(OBJECTS), 1, tmp_Pntr);
			}
		}

		helping = num - count_Del;
		rewind(tmp_Pntr);
		fwrite(&helping, sizeof(int), 1, tmp_Pntr);

		if (found != 1) {
			system("cls");
			printf("\n\tSeason [%d] was not found.\n", dlt_Seas);
			fclose(read_Objs);
			fclose(tmp_Pntr);
			free(deletion);
			_getch();
		}
		else {
			system("cls");
			printf("\n\tWhole season [%d] was "YLW"removed"ESC".\n", dlt_Seas);
			_getch();
			fclose(read_Objs);
			fclose(tmp_Pntr);
			free(deletion);
			if (helping == 0) {
				remove("objects.bin");
				remove("tmp.bin");
				printf("\n\tThere are no "YLW"objects"ESC" left.\n");
				_getch();
				return;
			}
			else {
				remove("objects.bin");
				rename("tmp.bin", "objects.bin");
			}
		}
		return;
	}
	case 2: {
		char* dlt_By_Name;
		int found = 0, helping = 0, count_Del = 0;
		dlt_By_Name = (char*)calloc(100, sizeof(char));
		if (dlt_By_Name == NULL) {
			perror("Memory error");
			exit(EXIT_FAILURE);
		}
		getchar();
		printf("\nEnter name of object to delete: ");
		fgets(dlt_By_Name, 99, stdin);

		helping = num;
		fwrite(&helping, sizeof(int), 1, tmp_Pntr);

		for (int i = 0; i < num; i++) {
			fread(deletion, sizeof(OBJECTS), 1, read_Objs);
			if (strstr(deletion->name, dlt_By_Name)) {
				found = 1;
				count_Del++;
			}
			else {
				fwrite(deletion, sizeof(OBJECTS), 1, tmp_Pntr);
			}
		}

		helping = num - count_Del;
		rewind(tmp_Pntr);
		fwrite(&helping, sizeof(int), 1, tmp_Pntr);

		if (found != 1) {
			system("cls");
			*(dlt_By_Name + (strlen(dlt_By_Name) - 1)) = 0;
			printf("\n\tObject [%s] was not found.\n", dlt_By_Name);
			fclose(read_Objs);
			fclose(tmp_Pntr);
			free(deletion);
			free(dlt_By_Name);
			_getch();
		}
		else {
			system("cls");
			*(dlt_By_Name + (strlen(dlt_By_Name) - 1)) = 0;
			printf("\n\tObject [%s] was "YLW"removed"ESC".\n", dlt_By_Name);
			_getch();
			fclose(read_Objs);
			fclose(tmp_Pntr);
			free(dlt_By_Name);
			free(deletion);

			if (helping == 0) {
				remove("objects.bin");
				remove("tmp.bin");
				printf("\n\tThere are no "YLW"objects"ESC" left.\n");
				_getch();
				return;
			}
			else {
				remove("objects.bin");
				rename("tmp.bin", "objects.bin");
			}
		}
		return;
	}
	case 3: {
		char* dlt_By_Manuf;
		int found = 0, helping = 0, count_Del = 0;
		dlt_By_Manuf = (char*)calloc(40, sizeof(char));
		if (dlt_By_Manuf == NULL) {
			perror("Memory error");
			exit(EXIT_FAILURE);
		}
		getchar();
		printf("\nEnter manufacturer name to delete by: ");
		fgets(dlt_By_Manuf, 39, stdin);

		helping = num;
		fwrite(&helping, sizeof(int), 1, tmp_Pntr);

		for (int i = 0; i < num; i++) {
			fread(deletion, sizeof(OBJECTS), 1, read_Objs);
			if (strstr(deletion->manufacturer, dlt_By_Manuf)) {
				found = 1;
				count_Del++;
			}
			else {
				fwrite(deletion, sizeof(OBJECTS), 1, tmp_Pntr);
			}
		}

		helping = num - count_Del;
		rewind(tmp_Pntr);
		fwrite(&helping, sizeof(int), 1, tmp_Pntr);

		if (found != 1) {
			system("cls");
			*(dlt_By_Manuf + (strlen(dlt_By_Manuf) - 1)) = 0;
			printf("\n\tObject made by [%s] was not found.\n", dlt_By_Manuf);
			fclose(read_Objs);
			fclose(tmp_Pntr);
			free(deletion);
			free(dlt_By_Manuf);
			_getch();
		}
		else {
			system("cls");
			*(dlt_By_Manuf + (strlen(dlt_By_Manuf) - 1)) = 0;
			printf("\n\tObject made by [%s] was "YLW"removed"ESC".\n", dlt_By_Manuf);
			_getch();
			fclose(read_Objs);
			fclose(tmp_Pntr);
			free(deletion);
			free(dlt_By_Manuf);

			if (helping == 0) {
				remove("objects.bin");
				remove("tmp.bin");
				printf("\n\tThere are no "YLW"objects by manufacturer"ESC" left.\n");
				_getch();
				return;
			}
			else {
				remove("objects.bin");
				rename("tmp.bin", "objects.bin");
			}
		}
		return;
	}
	case 4: {
		fclose(read_Objs);
		fclose(tmp_Pntr);
		free(deletion);
		return;
	}
	}
}

void objects_List(void) {

	//enter from music_Edit_Menu
	int list_Choice, obj_Num;
	do {
		system("cls");
		printf("\t  Logged in as: "RED"[%s]"ESC"\n\n\t"CYN"List objects by:\n\n"ESC"[1] Season\n[2] Manufacturer\n[3] Use\n[4] Return to edit panel\n\nChoice: ", logged_As);
		scanf("%d", &list_Choice);
	} while (list_Choice < 1 || list_Choice > 4);

	FILE* read = NULL;
	read = fopen("objects.bin", "rb");
	if (read == NULL) {
		perror("File error");
		exit(EXIT_FAILURE);
	}

	OBJECTS* read_St = NULL;
	fread(&obj_Num, sizeof(int), 1, read);
	read_St = (OBJECTS*)calloc(obj_Num, sizeof(OBJECTS));
	if (read_St == NULL) {
		perror("Struct error");
		exit(EXIT_FAILURE);
	}

	switch (list_Choice) {
	case 1: {
		int asc_Desc, i;
		do {
			system("cls");
			printf("\n\t"YLW"Sort objects by seasons:\n\n"ESC"[1] Ascending\n[2] Descending\n\nChoice: ");
			scanf("%d", &asc_Desc);
		} while (asc_Desc < 1 || asc_Desc > 2);

		fseek(read, sizeof(int), SEEK_SET);
		fread(read_St, sizeof(OBJECTS), obj_Num, read);
		if (asc_Desc == 1)
			qsort(read_St, obj_Num, sizeof(OBJECTS), compare_Season_Asc_Objects);
		else
			qsort(read_St, obj_Num, sizeof(OBJECTS), compare_Season_Desc_Objects);
		system("cls");
		printf("\n\tNumber of "BMNG"music tracks"ESC": [%d]\n\n", obj_Num);
		for (i = 0; i < obj_Num; i++) {
			fprintf(stdout, BMNG"\n[%d] Season:"ESC" %d\n", i + 1, (read_St + i)->season);
			fprintf(stdout, BMNG"[%d] Name:"ESC" %s", i + 1, (read_St + i)->name);
			fprintf(stdout, BMNG"[%d] Manufacturer:"ESC" %s", i + 1, (read_St + i)->manufacturer);
			fprintf(stdout, BMNG"[%d] Use:"ESC" %s", i + 1, (read_St + i)->use);
			fprintf(stdout, BMNG"[%d] Powers:"ESC" %s", i + 1, (read_St + i)->powers);
			fprintf(stdout, BMNG"[%d] Location / status:"ESC" %s\n", i + 1, (read_St + i)->location_Status);
		}
		_getch();
		fclose(read);
		free(read_St);
		return;
	}
	case 2: {
		int asc_Desc, i;
		do {
			system("cls");
			printf("\n\t"YLW"Sort objects by manufacturer:\n\n"ESC"[1] Ascending\n[2] Descending\n\nChoice: ");
			scanf("%d", &asc_Desc);
		} while (asc_Desc < 1 || asc_Desc > 2);

		fseek(read, sizeof(int), SEEK_SET);
		fread(read_St, sizeof(OBJECTS), obj_Num, read);
		if (asc_Desc == 1)
			qsort(read_St, obj_Num, sizeof(OBJECTS), comp_Manufacturer_Asc_Objects);
		else
			qsort(read_St, obj_Num, sizeof(OBJECTS), comp_Manufacturer_Desc_Objects);
		system("cls");
		printf("\n\tNumber of "BMNG"music tracks"ESC": [%d]\n\n", obj_Num);
		for (i = 0; i < obj_Num; i++) {
			fprintf(stdout, BMNG"\n[%d] Season:"ESC" %d\n", i + 1, (read_St + i)->season);
			fprintf(stdout, BMNG"[%d] Name:"ESC" %s", i + 1, (read_St + i)->name);
			fprintf(stdout, BMNG"[%d] Manufacturer:"ESC" %s", i + 1, (read_St + i)->manufacturer);
			fprintf(stdout, BMNG"[%d] Use:"ESC" %s", i + 1, (read_St + i)->use);
			fprintf(stdout, BMNG"[%d] Powers:"ESC" %s", i + 1, (read_St + i)->powers);
			fprintf(stdout, BMNG"[%d] Location / status:"ESC" %s\n", i + 1, (read_St + i)->location_Status);
		}
		_getch();
		fclose(read);
		free(read_St);
		return;
	}
	case 3: {
		int asc_Desc, i;
		do {
			system("cls");
			printf("\n\t"YLW"Sort objects by use:\n\n"ESC"[1] Ascending\n[2] Descending\n\nChoice: ");
			scanf("%d", &asc_Desc);
		} while (asc_Desc < 1 || asc_Desc > 2);

		fseek(read, sizeof(int), SEEK_SET);
		fread(read_St, sizeof(OBJECTS), obj_Num, read);
		if (asc_Desc == 1)
			qsort(read_St, obj_Num, sizeof(OBJECTS), comp_Use_Asc_Objects);
		else
			qsort(read_St, obj_Num, sizeof(OBJECTS), comp_Use_Desc_Objects);
		system("cls");
		printf("\n\tNumber of "BMNG"music tracks"ESC": [%d]\n\n", obj_Num);
		for (i = 0; i < obj_Num; i++) {
			fprintf(stdout, BMNG"\n[%d] Season:"ESC" %d\n", i + 1, (read_St + i)->season);
			fprintf(stdout, BMNG"[%d] Name:"ESC" %s", i + 1, (read_St + i)->name);
			fprintf(stdout, BMNG"[%d] Manufacturer:"ESC" %s", i + 1, (read_St + i)->manufacturer);
			fprintf(stdout, BMNG"[%d] Use:"ESC" %s", i + 1, (read_St + i)->use);
			fprintf(stdout, BMNG"[%d] Powers:"ESC" %s", i + 1, (read_St + i)->powers);
			fprintf(stdout, BMNG"[%d] Location / status:"ESC" %s\n", i + 1, (read_St + i)->location_Status);
		}
		_getch();
		fclose(read);
		free(read_St);
		return;
	}
	case 4: {
		fclose(read);
		free(read_St);
		return;
	}
	}

}

void search_Objects(void) {

	//enter from music_Edit_Menu
	int search_Choice, i, obj_Num;
	do {
		system("cls");
		printf("\t  Logged in as: "RED"[%s]"ESC"\n\n\t"YLW"Search objects by:\n\n"ESC"[1] Season\n[2] Name\n[3] Manufacturer\n[4] Return to edit panel\n\nChoice: ", logged_As);
		scanf("%d", &search_Choice);
	} while (search_Choice < 1 || search_Choice > 4);

	FILE* search = NULL;
	search = fopen("objects.bin", "rb");
	if (search == NULL) {
		perror("File error");
		exit(EXIT_FAILURE);
	}

	OBJECTS* read_St = NULL;
	fread(&obj_Num, sizeof(int), 1, search);
	read_St = (OBJECTS*)calloc(obj_Num, sizeof(OBJECTS));
	if (read_St == NULL) {
		perror("Struct error");
		exit(EXIT_FAILURE);
	}

	switch (search_Choice) {
	case 1: {
		int id_Srch, flag = 0;
		system("cls");
		printf("\nEnter season: ");
		scanf("%d", &id_Srch);
		for (i = 0; i < obj_Num; i++) {
			fread(read_St, sizeof(OBJECTS), 1, search);
			if (read_St->season == id_Srch) {
				fprintf(stdout, BMNG"\n[%d] Season:"ESC" %d\n", i + 1, read_St->season);
				fprintf(stdout, BMNG"[%d] Name:"ESC" %s", i + 1, read_St->name);
				fprintf(stdout, BMNG"[%d] Manufacturer:"ESC" %s", i + 1, read_St->manufacturer);
				fprintf(stdout, BMNG"[%d] Use:"ESC" %s", i + 1, read_St->use);
				fprintf(stdout, BMNG"[%d] Powers:"ESC" %s", i + 1, read_St->powers);
				fprintf(stdout, BMNG"[%d] Location / status:"ESC" %s\n", i + 1, read_St->location_Status);
				flag = 1;
				_getch();
			}
		}
		printf("End of list.");
		_getch();
		if (flag == 0) {
			printf("\nNo objects on season: [%d].\n", id_Srch);
			_getch();
		}
		free(read_St);
		fclose(search);
		return;
	}
	case 2: {
		int flag = 0;
		char* srch_Obj_Nm;
		srch_Obj_Nm = (char*)calloc(100, sizeof(char));
		if (srch_Obj_Nm == NULL) {
			perror("Memory error");
			exit(EXIT_FAILURE);
		}
		system("cls");
		getchar();
		printf("\nEnter object name: ");
		fgets(srch_Obj_Nm, 99, stdin);
		for (i = 0; i < obj_Num; i++) {
			fread(read_St, sizeof(OBJECTS), 1, search);
			if (strcmp(read_St->name, srch_Obj_Nm) == 0) {
				fprintf(stdout, BMNG"\n[%d] Season:"ESC" %d\n", i + 1, read_St->season);
				fprintf(stdout, BMNG"[%d] Name:"ESC" %s", i + 1, read_St->name);
				fprintf(stdout, BMNG"[%d] Manufacturer:"ESC" %s", i + 1, read_St->manufacturer);
				fprintf(stdout, BMNG"[%d] Use:"ESC" %s", i + 1, read_St->use);
				fprintf(stdout, BMNG"[%d] Powers:"ESC" %s", i + 1, read_St->powers);
				fprintf(stdout, BMNG"[%d] Location / status:"ESC" %s\n", i + 1, read_St->location_Status);
				flag = 1;
				_getch();
				break;
			}
		}
		printf("End of list.");
		_getch();
		if (flag == 0) {
			*(srch_Obj_Nm + (strlen(srch_Obj_Nm) - 1)) = 0;
			printf("\nNo object with name: [%s].\n", srch_Obj_Nm);
			_getch();
		}
		free(read_St);
		free(srch_Obj_Nm);
		fclose(search);
		return;
	}
	case 3: {
		int flag = 0;
		char* srch_Manuf;
		srch_Manuf = (char*)calloc(40, sizeof(char));
		if (srch_Manuf == NULL) {
			perror("Memory error");
			exit(EXIT_FAILURE);
		}
		system("cls");
		getchar();
		printf("\nEnter manufacturer: ");
		fgets(srch_Manuf, 39, stdin);
		for (i = 0; i < obj_Num; i++) {
			fread(read_St, sizeof(OBJECTS), 1, search);
			if (strcmp(read_St->manufacturer, srch_Manuf) == 0) {
				fprintf(stdout, BMNG"\n[%d] Season:"ESC" %d\n", i + 1, read_St->season);
				fprintf(stdout, BMNG"[%d] Name:"ESC" %s", i + 1, read_St->name);
				fprintf(stdout, BMNG"[%d] Manufacturer:"ESC" %s", i + 1, read_St->manufacturer);
				fprintf(stdout, BMNG"[%d] Use:"ESC" %s", i + 1, read_St->use);
				fprintf(stdout, BMNG"[%d] Powers:"ESC" %s", i + 1, read_St->powers);
				fprintf(stdout, BMNG"[%d] Location / status:"ESC" %s\n", i + 1, read_St->location_Status);
				flag = 1;
				_getch();
			}
		}
		printf("End of list.");
		_getch();
		if (flag == 0) {
			*(srch_Manuf + (strlen(srch_Manuf) - 1)) = 0;
			printf("\nNo manufacturer(s) named: [%s].\n", srch_Manuf);
			_getch();
		}

		free(read_St);
		free(srch_Manuf);
		fclose(search);
		return;
	}
	case 4: {
		free(read_St);
		fclose(search);
		return;
	}
	}
}

//rituals and spells functions
void rit_Spell_Edit_Menu(void) {

	//enter from library_Edit_Board
	int choice;
	while (1) {
		system("cls");
		printf("\t  Logged in as: "RED"[%s]"ESC"\n\n\t"RED"Rituals and Spells editing\n\n"ESC"[1] Add ritual / spell\n[2] Remove ritual / spell\n[3] List rituals / spells\n[4] Search rituals / spells\n[5] Return\n\nChoice: ", logged_As);
		scanf("%d", &choice);

		switch (choice) {
		case 1: {
			rit_Spell_Add();
			break;
		}
		case 2: {
			del_Rit_Spell();
			break;
		}
		case 3: {
			rit_Spell_List();
			break;
		}
		case 4: {
			search_Rit_Spell();
			break;
		}
		case 5: {
			return;
		}
		}
	}
}

void rit_Spell_Add(void) {

	RITSSPELLS* rsp_Struc = NULL;
	rsp_Struc = (RITSSPELLS*)calloc(1, sizeof(RITSSPELLS));
	if (rsp_Struc == NULL) {
		perror("Struct error");
		exit(EXIT_FAILURE);
	}
	int sprb;
	FILE* rsp_File = NULL;
	rsp_File = fopen("rits_spells.bin", "r+b");
	if (rsp_File == NULL) {
		rsp_File = fopen("rits_spells.bin", "wb");
		if (rsp_File == NULL) {
			perror("File error");
			exit(EXIT_FAILURE);
		}
		system("cls");
		printf("\n\tEntering 1. "RED"object"ESC".\n\nEnter name: "); getchar();		
		fgets(rsp_Struc->name, 99, stdin);
		do{
			printf("Is it a ritual [1], a spell [2] or both [3]: ");
			scanf("%d", &sprb);
		} while (sprb < 1 || sprb > 3);
		if (sprb == 1) {
			rsp_Struc->ritual = 1;
			rsp_Struc->spell = 0;
		}
		else if (sprb == 2) {
			rsp_Struc->spell = 1;
			rsp_Struc->ritual = 0;
		}
		else {
			rsp_Struc->ritual = 1;
			rsp_Struc->spell = 1;
		}
		printf("Enter manufacturer / caster: "); getchar();
		fgets(rsp_Struc->manuf_caster, 99, stdin);
		printf("Enter use: ");
		fgets(rsp_Struc->used, 299, stdin);
		printf("Enter details: ");
		fgets(rsp_Struc->details, 499, stdin);		
		int rsp_Num = 1;
		fwrite(&rsp_Num, sizeof(int), 1, rsp_File);
		fwrite(rsp_Struc, sizeof(RITSSPELLS), 1, rsp_File);
		fclose(rsp_File);
		free(rsp_Struc);
		return;
	}
	else {
		int rsp_Num;
		fread(&rsp_Num, sizeof(int), 1, rsp_File);
		rsp_Num++;
		system("cls");
		printf("\n\tEntering %d. "RED"object"ESC".\n\nEnter name: ", rsp_Num); getchar();
		fgets(rsp_Struc->name, 99, stdin);
		do {
			printf("Is it a ritual [1], a spell [2] or both [3]: ");
			scanf("%d", &sprb);
		} while (sprb < 1 || sprb > 3);
		if (sprb == 1) {
			rsp_Struc->ritual = 1;
		}
		else if (sprb == 2) {
			rsp_Struc->spell = 1;
		}
		else {
			rsp_Struc->ritual = 1;
			rsp_Struc->spell = 1;
		}
		printf("Enter manufacturer / caster: "); getchar();
		fgets(rsp_Struc->manuf_caster, 99, stdin);
		printf("Enter use: ");
		fgets(rsp_Struc->used, 299, stdin);
		printf("Enter details: ");
		fgets(rsp_Struc->details, 499, stdin);
		rewind(rsp_File);
		fwrite(&rsp_Num, sizeof(int), 1, rsp_File);
		fseek(rsp_File, sizeof(int) + ((rsp_Num - 1) * sizeof(RITSSPELLS)), SEEK_SET);
		fwrite(rsp_Struc, sizeof(RITSSPELLS), 1, rsp_File);
		fclose(rsp_File);
		free(rsp_Struc);
		return;
	}
}

void del_Rit_Spell(void) {

	//enter from music_Edit_Menu
	int rem_By, num;
	do {
		system("cls");
		printf("\t  Logged in as: "RED"[%s]"ESC"\n\n\tRemoving rituals and spells "RED"[BE CAREFUL!]\n\n"ESC"[1] Remove by name\n[2] Remove all rituals\n[3] Remove all spells\n[4] Remove both rituals and spells\n[5] Return\n\nChoice: ", logged_As);
		scanf("%d", &rem_By);
	} while (rem_By < 1 || rem_By > 5);

	FILE* rsp_File = NULL;
	rsp_File = fopen("rits_spells.bin", "rb");
	if (rsp_File == NULL) {
		perror("File error");
		exit(EXIT_FAILURE);
	}

	FILE* tmp_Pntr = NULL;
	tmp_Pntr = fopen("tmp.bin", "wb");
	if (tmp_Pntr == NULL) {
		printf("File error");
		exit(EXIT_FAILURE);
	}

	fread(&num, sizeof(int), 1, rsp_File);
	RITSSPELLS* deletion = NULL;
	deletion = (RITSSPELLS*)calloc(num, sizeof(RITSSPELLS));
	if (deletion == NULL) {
		perror("Struct error");
		exit(EXIT_FAILURE);
	}

	switch (rem_By) {
	case 1: {
		int found = 0, helping = 0, count_Del = 0;
		char* name_Dlt = NULL;
		name_Dlt = (char*)calloc(100, sizeof(char));
		if (name_Dlt == NULL) {
			perror("Memory error");
			exit(EXIT_FAILURE);
		}
		printf("\nEnter name to delete: "); getchar();
		fgets(name_Dlt, 99, stdin);

		helping = num;
		fwrite(&helping, sizeof(int), 1, tmp_Pntr);

		for (int i = 0; i < num; i++) {
			fread(deletion, sizeof(RITSSPELLS), 1, rsp_File);
			if (strcmp(deletion->name, name_Dlt) == 0) {
				found = 1;
				count_Del++;
			}
			else {
				fwrite(deletion, sizeof(RITSSPELLS), 1, tmp_Pntr);
			}
		}

		helping = num - count_Del;
		rewind(tmp_Pntr);
		fwrite(&helping, sizeof(int), 1, tmp_Pntr);

		if (found != 1) {
			system("cls");
			*(name_Dlt + (strlen(name_Dlt) - 1)) = 0;
			printf("\n\tSpell / ritual [%s] was not found.\n", name_Dlt);
			fclose(rsp_File);
			fclose(tmp_Pntr);
			free(deletion);
			_getch();
		}
		else {
			system("cls");
			*(name_Dlt + (strlen(name_Dlt) - 1)) = 0;
			printf("\n\tSpell / riutal [%s] was "RED"removed"ESC".\n", name_Dlt);
			_getch();
			fclose(rsp_File);
			fclose(tmp_Pntr);
			free(deletion);
			if (helping == 0) {
				remove("rits_spells.bin");
				remove("tmp.bin");
				printf("\n\tThere are no "RED"spells and / or rituals"ESC" left.\n");
				_getch();
				return;
			}
			else {
				remove("rits_spells.bin");
				rename("tmp.bin", "rits_spells.bin");
			}
		}
		return;
	}
	case 2: {
		int found = 0, helping = 0, count_Del = 0;
		char* y_Or_N;
		y_Or_N = (char*)calloc(5, sizeof(char));
		if (y_Or_N == NULL) {
			perror("Memory error");
			exit(EXIT_FAILURE);
		}
		getchar();
		printf("\nAre you sure you want to remove all rituals? [YES / NO] ");
		fgets(y_Or_N, 4, stdin);
		if(strcmp(y_Or_N, "YES") == 0){
			helping = num;
			fwrite(&helping, sizeof(int), 1, tmp_Pntr);

			for (int i = 0; i < num; i++) {
				fread(deletion, sizeof(RITSSPELLS), 1, rsp_File);
				if (deletion->ritual == 1 && deletion->spell == 0) {
					found = 1;
					count_Del++;
				}
				else {
					fwrite(deletion, sizeof(RITSSPELLS), 1, tmp_Pntr);
				}
			}

			helping = num - count_Del;
			rewind(tmp_Pntr);
			fwrite(&helping, sizeof(int), 1, tmp_Pntr);

			if (found != 1) {
				system("cls");
				printf("\n\tThere are no rituals on the list.\n");
				fclose(rsp_File);
				fclose(tmp_Pntr);
				free(deletion);
				free(y_Or_N);
				_getch();
			}
			else {
				system("cls");
				printf("\n\tAll riutals were "RED"removed"ESC".\n");
				_getch();
				fclose(rsp_File);
				fclose(tmp_Pntr);
				free(y_Or_N);
				free(deletion);

				if (helping == 0) {
					remove("rits_spells.bin");
					remove("tmp.bin");
					printf("\n\tThere are no "RED"rituals"ESC" left.\n");
					_getch();
					return;
				}
				else {
					remove("rits_spells.bin");
					rename("tmp.bin", "rits_spells.bin");
				}
			}
			return;
		}
		else{
			system("cls");
			printf("\nNot an option!");
			_getch();
			fclose(rsp_File);
			fclose(tmp_Pntr);
			free(y_Or_N);
			free(deletion);
			return;
		}
	}
	case 3: {
		int found = 0, helping = 0, count_Del = 0;
		char* y_Or_N;
		y_Or_N = (char*)calloc(5, sizeof(char));
		if (y_Or_N == NULL) {
			perror("Memory error");
			exit(EXIT_FAILURE);
		}
		getchar();
		printf("\nAre you sure you want to remove all spells? [YES / NO] ");
		fgets(y_Or_N, 4, stdin);
		if (strcmp(y_Or_N, "YES") == 0) {
			helping = num;
			fwrite(&helping, sizeof(int), 1, tmp_Pntr);

			for (int i = 0; i < num; i++) {
				fread(deletion, sizeof(RITSSPELLS), 1, rsp_File);
				if (deletion->ritual == 0 && deletion->spell == 1) {
					found = 1;
					count_Del++;
				}
				else {
					fwrite(deletion, sizeof(RITSSPELLS), 1, tmp_Pntr);
				}
			}

			helping = num - count_Del;
			rewind(tmp_Pntr);
			fwrite(&helping, sizeof(int), 1, tmp_Pntr);

			if (found != 1) {
				system("cls");
				printf("\n\tThere are no spells on the list.\n");
				fclose(rsp_File);
				fclose(tmp_Pntr);
				free(deletion);
				free(y_Or_N);
				_getch();
			}
			else {
				system("cls");
				printf("\n\tAll spells were "RED"removed"ESC".\n");
				_getch();
				fclose(rsp_File);
				fclose(tmp_Pntr);
				free(y_Or_N);
				free(deletion);

				if (helping == 0) {
					remove("rits_spells.bin");
					remove("tmp.bin");
					printf("\n\tThere are no "RED"spells"ESC" left.\n");
					_getch();
					return;
				}
				else {
					remove("rits_spells.bin");
					rename("tmp.bin", "rits_spells.bin");
				}
			}
			return;
		}
		else {
			system("cls");
			printf("\nNot an option!");
			_getch();
			fclose(rsp_File);
			fclose(tmp_Pntr);
			free(y_Or_N);
			free(deletion);
			return;
		}
	}
	case 4: {
		int found = 0, helping = 0, count_Del = 0;
		char* y_Or_N;
		y_Or_N = (char*)calloc(5, sizeof(char));
		if (y_Or_N == NULL) {
			perror("Memory error");
			exit(EXIT_FAILURE);
		}
		getchar();
		printf("\nAre you sure you want to remove all rituals and all spells? [YES / NO] ");
		fgets(y_Or_N, 4, stdin);
		if (strcmp(y_Or_N, "YES") == 0) {
			helping = num;
			fwrite(&helping, sizeof(int), 1, tmp_Pntr);

			for (int i = 0; i < num; i++) {
				fread(deletion, sizeof(RITSSPELLS), 1, rsp_File);
				if (deletion->ritual == 1 && deletion->spell == 1) {
					found = 1;
					count_Del++;
				}
				else {
					fwrite(deletion, sizeof(RITSSPELLS), 1, tmp_Pntr);
				}
			}

			helping = num - count_Del;
			rewind(tmp_Pntr);
			fwrite(&helping, sizeof(int), 1, tmp_Pntr);

			if (found != 1) {
				system("cls");
				printf("\n\tThere are no rituals nor spells on the list.\n");
				fclose(rsp_File);
				fclose(tmp_Pntr);
				free(deletion);
				free(y_Or_N);
				_getch();
			}
			else {
				system("cls");
				printf("\n\tAll riutals and spells were "RED"removed"ESC".\n");
				_getch();
				fclose(rsp_File);
				fclose(tmp_Pntr);
				free(y_Or_N);
				free(deletion);

				if (helping == 0) {
					remove("rits_spells.bin");
					remove("tmp.bin");
					printf("\n\tThere are no "RED"rituals"ESC"nor "RED"spells"ESC" left.\n");
					_getch();
					return;
				}
				else {
					remove("rits_spells.bin");
					rename("tmp.bin", "rits_spells.bin");
				}
			}
			return;
		}
		else {
			system("cls");
			printf("\nNot an option!");
			_getch();
			fclose(rsp_File);
			fclose(tmp_Pntr);
			free(y_Or_N);
			free(deletion);
			return;
		}
	}
	case 5: {
		fclose(rsp_File);
		fclose(tmp_Pntr);
		free(deletion);
		return;
	}
	}
}

void rit_Spell_List(void) {

	int list_Choice, rsp_Num;
	do {
		system("cls");
		printf("\t  Logged in as: "RED"[%s]"ESC"\n\n\t"RED"List rituals / spells by:\n\n"ESC"[1] Name\n[2] Manufacturer / caster\n[3] Return to edit panel\n\nChoice: ", logged_As);
		scanf("%d", &list_Choice);
	} while (list_Choice < 1 || list_Choice > 4);

	FILE* read = NULL;
	read = fopen("rits_spells.bin", "rb");
	if (read == NULL) {
		perror("File error");
		exit(EXIT_FAILURE);
	}

	RITSSPELLS* read_St = NULL;
	fread(&rsp_Num, sizeof(int), 1, read);
	read_St = (RITSSPELLS*)calloc(rsp_Num, sizeof(RITSSPELLS));
	if (read_St == NULL) {
		perror("Struct error");
		exit(EXIT_FAILURE);
	}

	switch (list_Choice) {
	case 1: {
		int asc_Desc, i;
		do {
			system("cls");
			printf("\n\t"RED"Sort rituals / spells by name:\n\n"ESC"[1] Ascending\n[2] Descending\n\nChoice: ");
			scanf("%d", &asc_Desc);
		} while (asc_Desc < 1 || asc_Desc > 2);

		fseek(read, sizeof(int), SEEK_SET);
		fread(read_St, sizeof(RITSSPELLS), rsp_Num, read);
		if (asc_Desc == 1)
			qsort(read_St, rsp_Num, sizeof(RITSSPELLS), comp_Name_Asc_Rsp);
		else
			qsort(read_St, rsp_Num, sizeof(RITSSPELLS), comp_Name_Desc_Rsp);
		system("cls");
		printf("\n\tNumber of "BMNG"rituals & spells"ESC": [%d]\n\n", rsp_Num);
		for (i = 0; i < rsp_Num; i++) {
			fprintf(stdout, BMNG"\n[%d] Name:"ESC" %s", i + 1, (read_St + i)->name);
			if((read_St + i)->ritual == 0 && (read_St + i)->spell == 1){
				fprintf(stdout, RED"[Spell]\n"ESC);
			}
			else if ((read_St + i)->ritual == 1 && (read_St + i)->spell == 0) {
				fprintf(stdout, RED"[Ritual]\n"ESC);
			}
			else {
				fprintf(stdout, RED"[Spell & ritual]\n"ESC);
			}
			fprintf(stdout, BMNG"[%d] Manufacturer / caster:"ESC" %s", i + 1, (read_St + i)->manuf_caster);
			fprintf(stdout, BMNG"[%d] Used:"ESC" %s", i + 1, (read_St + i)->used);
			fprintf(stdout, BMNG"[%d] Details:"ESC" %s\n", i + 1, (read_St + i)->details);			
		}
		_getch();
		fclose(read);
		free(read_St);
		return;
	}
	case 2: {
		int asc_Desc, i;
		do {
			system("cls");
			printf("\n\t"RED"Sort rituals / spells by manufacturer / caster:\n\n"ESC"[1] Ascending\n[2] Descending\n\nChoice: ");
			scanf("%d", &asc_Desc);
		} while (asc_Desc < 1 || asc_Desc > 2);

		fseek(read, sizeof(int), SEEK_SET);
		fread(read_St, sizeof(RITSSPELLS), rsp_Num, read);
		if (asc_Desc == 1)
			qsort(read_St, rsp_Num, sizeof(RITSSPELLS), comp_ManuCas_Asc_Rsp);
		else
			qsort(read_St, rsp_Num, sizeof(RITSSPELLS), comp_ManuCas_Desc_Rsp);
		system("cls");
		printf("\n\tNumber of "BMNG"rituals & spells"ESC": [%d]\n\n", rsp_Num);
		for (i = 0; i < rsp_Num; i++) {
			fprintf(stdout, BMNG"\n[%d] Name:"ESC" %s", i + 1, (read_St + i)->name);
			if ((read_St + i)->ritual == 0 && (read_St + i)->spell == 1) {
				fprintf(stdout, RED"[Spell]\n"ESC);
			}
			else if ((read_St + i)->ritual == 1 && (read_St + i)->spell == 0) {
				fprintf(stdout, RED"[Ritual]\n"ESC);
			}
			else {
				fprintf(stdout, RED"[Spell & ritual]\n"ESC);
			}
			fprintf(stdout, BMNG"[%d] Manufacturer / caster:"ESC" %s", i + 1, (read_St + i)->manuf_caster);
			fprintf(stdout, BMNG"[%d] Used:"ESC" %s", i + 1, (read_St + i)->used);
			fprintf(stdout, BMNG"[%d] Details:"ESC" %s\n", i + 1, (read_St + i)->details);
		}
		_getch();
		fclose(read);
		free(read_St);
		return;
	}
	case 3: {
		fclose(read);
		free(read_St);
		return;
	}
	}
}

void search_Rit_Spell(void) {

	//enter from music_Edit_Menu
	int search_Choice, i, obj_Num;
	do {
		system("cls");
		printf("\t  Logged in as: "RED"[%s]"ESC"\n\n\t"RED"Search rituals and spells by:\n\n"ESC"[1] Name\n[2] Manufacturer / caster\n[3] Spells\n[4] Rituals\n[5] Return to edit panel\n\nChoice: ", logged_As);
		scanf("%d", &search_Choice);
	} while (search_Choice < 1 || search_Choice > 5);

	FILE* search = NULL;
	search = fopen("rits_spells.bin", "rb");
	if (search == NULL) {
		perror("File error");
		exit(EXIT_FAILURE);
	}

	RITSSPELLS* read_St = NULL;
	fread(&obj_Num, sizeof(int), 1, search);
	read_St = (RITSSPELLS*)calloc(obj_Num, sizeof(RITSSPELLS));
	if (read_St == NULL) {
		perror("Struct error");
		exit(EXIT_FAILURE);
	}

	switch (search_Choice) {
	case 1: {
		int flag = 0;
		char* srch_Obj_Nm;
		srch_Obj_Nm = (char*)calloc(100, sizeof(char));
		if (srch_Obj_Nm == NULL) {
			perror("Memory error");
			exit(EXIT_FAILURE);
		}
		system("cls");
		getchar();
		printf("\nEnter object name: ");
		fgets(srch_Obj_Nm, 99, stdin);
		for (i = 0; i < obj_Num; i++) {
			fread(read_St, sizeof(RITSSPELLS), 1, search);
			if (strcmp(read_St->name, srch_Obj_Nm) == 0) {
				fprintf(stdout, BMNG"\n[%d] Name:"ESC" %s", i + 1, (read_St + i)->name);
				if ((read_St + i)->ritual == 0 && (read_St + i)->spell == 1) {
					fprintf(stdout, RED"[Spell]\n"ESC);
				}
				else if ((read_St + i)->ritual == 1 && (read_St + i)->spell == 0) {
					fprintf(stdout, RED"[Ritual]\n"ESC);
				}
				else {
					fprintf(stdout, RED"[Spell & ritual]\n"ESC);
				}
				fprintf(stdout, BMNG"[%d] Manufacturer / caster:"ESC" %s", i + 1, (read_St + i)->manuf_caster);
				fprintf(stdout, BMNG"[%d] Used:"ESC" %s", i + 1, (read_St + i)->used);
				fprintf(stdout, BMNG"[%d] Details:"ESC" %s\n", i + 1, (read_St + i)->details);
				flag = 1;
				_getch();
				break;
			}
		}
		printf("End of list.");
		_getch();
		if (flag == 0) {
			*(srch_Obj_Nm + (strlen(srch_Obj_Nm) - 1)) = 0;
			printf("\nNo riutal or spell with name: [%s].\n", srch_Obj_Nm);
			_getch();
		}
		free(read_St);
		free(srch_Obj_Nm);
		fclose(search);
		return;
	}
	case 2: {
		int flag = 0;
		char* srch_Manuf;
		srch_Manuf = (char*)calloc(100, sizeof(char));
		if (srch_Manuf == NULL) {
			perror("Memory error");
			exit(EXIT_FAILURE);
		}
		system("cls");
		printf("\nEnter manufacturer / caster: ");
		getchar();
		fgets(srch_Manuf, 99, stdin);
		for (i = 0; i < obj_Num; i++) {
			fread(read_St, sizeof(RITSSPELLS), 1, search);
			if (strcmp(read_St->manuf_caster, srch_Manuf) == 0) {
				fprintf(stdout, BMNG"\n[%d] Name:"ESC" %s", i + 1, read_St->name);
				if ((read_St + i)->ritual == 0 && (read_St + i)->spell == 1) {
					fprintf(stdout, RED"[Spell]\n"ESC);
				}
				else if ((read_St + i)->ritual == 1 && (read_St + i)->spell == 0) {
					fprintf(stdout, RED"[Ritual]\n"ESC);
				}
				else {
					fprintf(stdout, RED"[Spell & ritual]\n"ESC);
				}
				fprintf(stdout, BMNG"[%d] Manufacturer / caster:"ESC" %s", i + 1, read_St->manuf_caster);
				fprintf(stdout, BMNG"[%d] Used:"ESC" %s", i + 1, read_St->used);
				fprintf(stdout, BMNG"[%d] Details:"ESC" %s\n", i + 1, read_St->details);
				flag = 1;
				_getch();
			}
		}
		printf("End of list.");
		_getch();
		if (flag == 0) {
			*(srch_Manuf + (strlen(srch_Manuf) - 1)) = 0;
			printf("\nNo manufacturer(s) / caster(s) named: [%s].\n", srch_Manuf);
			_getch();
		}

		free(read_St);
		free(srch_Manuf);
		fclose(search);
		return;
	}
	case 3: {
		int flag = 0;
		system("cls");
		printf("\nListing all "RED"spells"ESC":\n");
		for (i = 0; i < obj_Num; i++) {
			fread(read_St, sizeof(RITSSPELLS), 1, search);
			if (read_St->spell == 1) {
				fprintf(stdout, BMNG"\n[%d] Name:"ESC" %s", i + 1, read_St->name);
				if (read_St->ritual == 0 && read_St->spell == 1) {
					fprintf(stdout, RED"[Spell]\n"ESC);
				}
				else if (read_St->ritual == 1 && read_St->spell == 0) {
					fprintf(stdout, RED"[Ritual]\n"ESC);
				}
				else {
					fprintf(stdout, RED"[Spell & ritual]\n"ESC);
				}
				fprintf(stdout, BMNG"[%d] Manufacturer / caster:"ESC" %s", i + 1, read_St->manuf_caster);
				fprintf(stdout, BMNG"[%d] Used:"ESC" %s", i + 1, read_St->used);
				fprintf(stdout, BMNG"[%d] Details:"ESC" %s\n", i + 1, read_St->details);
				flag = 1;
				_getch();
			}
		}
		printf("End of list.");
		_getch();
		if (flag == 0) {
			printf("\nNo spell(s) on the list.\n");
			_getch();
		}

		free(read_St);
		fclose(search);
		return;
	}
	case 4: {
		int flag = 0;
		system("cls");
		printf("\nListing all "RED"rituals"ESC" :");
		for (i = 0; i < obj_Num; i++) {
			fread(read_St, sizeof(RITSSPELLS), 1, search);
			if (read_St->ritual == 1) {
				fprintf(stdout, BMNG"\n[%d] Name:"ESC" %s", i + 1, (read_St + i)->name);
				if ((read_St + i)->ritual == 0 && (read_St + i)->spell == 1) {
					fprintf(stdout, RED"[Spell]\n"ESC);
				}
				else if ((read_St + i)->ritual == 1 && (read_St + i)->spell == 0) {
					fprintf(stdout, RED"[Ritual]\n"ESC);
				}
				else {
					fprintf(stdout, RED"[Spell & ritual]\n"ESC);
				}
				fprintf(stdout, BMNG"[%d] Manufacturer / caster:"ESC" %s", i + 1, (read_St + i)->manuf_caster);
				fprintf(stdout, BMNG"[%d] Used:"ESC" %s", i + 1, (read_St + i)->used);
				fprintf(stdout, BMNG"[%d] Details:"ESC" %s\n", i + 1, (read_St + i)->details);
				flag = 1;
				_getch();
			}
		}
		printf("End of list.");
		_getch();
		if (flag == 0) {
			printf("\nNo ritual(s) on the list.\n");
			_getch();
		}

		free(read_St);
		fclose(search);
		return;
	}
	case 5: {
		free(read_St);
		fclose(search);
		return;
	}
	}
}