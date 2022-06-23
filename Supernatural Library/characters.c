#include "header.h"
#include "structs.h"
#include "colors.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

void chars_Edit_Menu(void) {

	//enter from library_Edit_Board
	int choice;
	while (1) {
		if(admin_Logged == 1){
			do {
				system("cls");
				printf("\t  Logged in as: "RED"[%s]"ESC"\n\n\t"BRED"Characters editing\n\n"ESC"[1] Add a character\n[2] Remove a character\n[3] Edit characters\n[4] List characters\n[5] Search a character\n[6] Return\n\nChoice: ", logged_As);
				scanf("%d", &choice);
			} while (choice < 1 || choice > 6);

			switch (choice) {
			case 1: {
				add_Chars();
				break;
			}
			case 2: {
				del_Chars();
				break;
			}
			case 3: {
				edit_Chars();
				break;
			}
			case 4: {
				list_Chars();
				break;
			}
			case 5: {
				search_Chars();
				break;
			}
			case 6: {
				return;
			}
			}
		}
		else {
			do {
				system("cls");
				printf("\t  Logged in as: "BLUE"[%s]"ESC"\n\n\t"BRED"Characters\n\n"ESC"[1] List characters\n[2] Search a character\n[3] Edit characters\n[4] Return\n\nChoice: ", logged_As);
				scanf("%d", &choice);
			} while (choice < 1 || choice > 4);

			switch (choice) {
			case 1: {
				list_Chars();
				break;
			}
			case 2: {
				search_Chars();
				break;
			}
			case 3: {
				edit_Chars();
				break;
			}
			case 4: {
				return;
			}
			}
		}
	}
}

void add_Chars(void) {

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
		printf("\n\tCurrently entering 1. "BRED"character"ESC".\n\nEnter character ID: ");
		scanf("%d", &chars->ID);
		printf("Enter first name: ");
		getchar();
		fgets(chars->first_N, 99, stdin);
		printf("Enter last name: ");
		fgets(chars->last_N, 99, stdin);
		printf("Enter species: ");
		fgets(chars->species, 499, stdin);
		do{
			printf("Is character alive [1 / 0]: ");
			scanf("%d", &alive);
		} while (alive < 0 || alive > 1);
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
		printf("\n\tCurrently entering %d. "BRED"character"ESC".\n\nEnter character ID: ", char_Num);
		scanf("%d", &chars->ID);
		printf("Enter first name: ");
		getchar();
		fgets(chars->first_N, 99, stdin);
		printf("Enter last name: ");
		fgets(chars->last_N, 99, stdin);
		printf("Enter species: ");
		fgets(chars->species, 499, stdin);
		do{
			printf("Is character alive [1 / 0]: ");
			scanf("%d", &alive);
		} while (alive < 0 || alive > 1);
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

	FILE* read_Chars = NULL;
	read_Chars = fopen("characters.bin", "rb");
	if (read_Chars == NULL) {
		system("cls");
		printf("\n\t\t"RED"Error!"ESC"\nThere are no characters, for now...\n");
		_getch();
		return;
	}

	int rem_By, num, i, dlt_ID, found = 0, helping = 0;
	do {
		system("cls");
		printf("\t  Logged in as: "RED"[%s]"ESC"\n\n\tRemoving characters "RED"[BE CAREFUL!]\n\n"ESC"[1] Remove by ID\n[2] Remove by first name\n[3] Remove by species\n[4] Return\n\nChoice: ", logged_As);
		scanf("%d", &rem_By);
	} while (rem_By < 1 || rem_By > 4);

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
		printf("\nEnter ID to delete: ");
		scanf("%d", &dlt_ID);

		helping = num - 1;
		fwrite(&helping, sizeof(int), 1, tmp_Pntr);

		for (i = 0; i < num; i++) {
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

		for (i = 0; i < num; i++) {
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
		int count_Del = 0;
		dlt_Spec = (char*)calloc(30, sizeof(char));
		if (dlt_Spec == NULL) {
			perror("Memory error");
			exit(EXIT_FAILURE);
		}
		getchar();
		printf("\nEnter species to delete: ");
		fgets(dlt_Spec, 29, stdin);

		helping = num;
		fwrite(&helping, sizeof(int), 1, tmp_Pntr);

		for (i = 0; i < num; i++) {
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

void edit_Chars(void) {

	FILE* read_Chars = NULL;
	read_Chars = fopen("characters.bin", "rb");
	if (read_Chars == NULL) {
		system("cls");
		printf("\n\t\t"RED"Error!"ESC"\nThere are no characters, for now...\n");
		_getch();
		return;
	}

	int edit_By, num;

	do {
		system("cls");
		if (admin_Logged == 1) {
			printf("\t  Logged in as: "RED"[%s]"ESC"\n\n\tEditing characters "RED"[BE CAREFUL!]\n\n"ESC"[1] Edit by ID\n[2] Return\n\nChoice: ", logged_As);
		}
		else {
			printf("\t  Logged in as: "BLUE"[%s]"ESC"\n\n\tEditing characters "RED"[BE CAREFUL!]\n\n"ESC"[1] Edit by ID\n[2] Return\n\nChoice: ", logged_As);
		}
		scanf("%d", &edit_By);
	} while (edit_By < 1 || edit_By > 2);

	FILE* tmp_Pntr = NULL;
	tmp_Pntr = fopen("tmp.bin", "wb");
	if (tmp_Pntr == NULL) {
		printf("File error");
		exit(EXIT_FAILURE);
	}

	fread(&num, sizeof(int), 1, read_Chars);
	CHARACTERS* chars = NULL;
	chars = (CHARACTERS*)calloc(num, sizeof(CHARACTERS));
	if (chars == NULL) {
		perror("Struct error");
		exit(EXIT_FAILURE);
	}
	fread(chars, sizeof(CHARACTERS), num, read_Chars);

	CHARACTERS* edit = NULL;
	edit = (CHARACTERS*)calloc(1, sizeof(CHARACTERS));
	if (edit == NULL) {
		perror("Struct error");
		exit(EXIT_FAILURE);
	}

	switch (edit_By) {
	case 1: {
		int i, edit_ID, alive, flag = 0;
		system("cls");
		printf("\n\t"BRED"Edit characters by ID:\n\n"ESC"Enter ID: ");
		scanf("%d", &edit_ID);
		for (i = 0; i < num; i++) {
			if ((chars + i)->ID == edit_ID) {
				flag = 1;
				break;
			}
		}
		if (flag == 0) {
			system("cls");
			printf("\nNo character with ID [%d].\n", edit_ID);
			_getch();
			fclose(read_Chars);
			fclose(tmp_Pntr);
			free(chars);
			free(edit);
			return;
		}
		else {
			printf("\nEnter new character ID: ");
			scanf("%d", &edit->ID);
			printf("Enter first name: ");
			getchar();
			fgets(edit->first_N, 99, stdin);
			printf("Enter last name: ");
			/*if (strcmp(edit->first_N, "\n") == 0) {
				strcpy(edit->first_N, chars->first_N);
			}*/
			fgets(edit->last_N, 99, stdin);
			printf("Enter species: ");
			fgets(edit->species, 499, stdin);
			printf("Is character alive [1 / 0]: ");
			scanf("%d", &alive);
			edit->alive = alive;
			getchar();
			printf("Titles: ");
			fgets(edit->titles, 999, stdin);
			printf("Occupation: ");
			fgets(edit->occupation, 999, stdin);
			printf("Affiliation: ");
			fgets(edit->affiliation, 999, stdin);
			printf("Family relations: ");
			fgets(edit->family, 999, stdin);
			printf("Portrayed by: ");
			fgets(edit->portrayed, 999, stdin);

			fwrite(&num, sizeof(int), 1, tmp_Pntr);
			for (i = 0; i < num; i++) {
				if ((chars + i)->ID == edit_ID) {
					fwrite(edit, sizeof(CHARACTERS), 1, tmp_Pntr);
				}
				else {
					fwrite(chars, sizeof(CHARACTERS), 1, tmp_Pntr);
				}
			}

			system("cls");
			printf("\n\tCharacter with ID [%d] was "BRED"edited"ESC".\n", edit_ID);
			_getch();
			fclose(read_Chars);
			fclose(tmp_Pntr);
			free(chars);
			free(edit);
			remove("characters.bin");
			rename("tmp.bin", "characters.bin");
			return;
		}
	}
	case 2: {
		fclose(read_Chars);
		fclose(tmp_Pntr);
		free(chars);
		free(edit);
		return;
	}
	}
}

void list_Chars(void) {

	//enter from chars_Edit_Menu

	FILE* read = NULL;
	read = fopen("characters.bin", "rb");
	if (read == NULL) {
		system("cls");
		printf("\n\t\t"RED"Error!"ESC"\nThere are no characters, for now...\n");
		_getch();
		return;
	}

	int list_Choice, char_Num, asc_Desc, i;
	do {
		system("cls");
		if(admin_Logged == 1) {
			printf("\t  Logged in as: "RED"[%s]"ESC"\n\n\t"BRED"List characters by:\n\n"ESC"[1] ID\n[2] First name\n[3] Last name\n[4] Species\n[5] Default order\n[6] Return\n\nChoice: ", logged_As);
		}
		else {
			printf("\t  Logged in as: "BLUE"[%s]"ESC"\n\n\t"BRED"List characters by:\n\n"ESC"[1] ID\n[2] First name\n[3] Last name\n[4] Species\n[5] Default order\n[6] Return\n\nChoice: ", logged_As);
		}
		scanf("%d", &list_Choice);
	} while (list_Choice < 1 || list_Choice > 6);


	CHARACTERS* read_St = NULL;
	fread(&char_Num, sizeof(int), 1, read);
	read_St = (CHARACTERS*)calloc(char_Num, sizeof(CHARACTERS));
	if (read_St == NULL) {
		perror("Struct error");
		exit(EXIT_FAILURE);
	}

	switch (list_Choice) {
	case 1: {
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
		printf("\n\tNumber of "BRED"characters"ESC": [%d]\n\n", char_Num);
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
		fprintf(stdout, "\nEnd of list! Continue...\n");
		_getch();
		fclose(read);
		free(read_St);
		return;
	}
	case 2: {
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
		printf("\n\tNumber of "BRED"characters"ESC": [%d]\n\n", char_Num);
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
		fprintf(stdout, "\nEnd of list! Continue...\n");
		_getch();
		fclose(read);
		free(read_St);
		return;
	}
	case 3: {
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
		printf("\n\tNumber of "BRED"characters"ESC": [%d]\n\n", char_Num);
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
		fprintf(stdout, "\nEnd of list! Continue...\n");
		_getch();
		fclose(read);
		free(read_St);
		return;
	}
	case 4: {
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
		printf("\n\tNumber of "BRED"characters"ESC": [%d]\n\n", char_Num);
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
		fprintf(stdout, "\nEnd of list! Continue...\n");
		_getch();
		fclose(read);
		free(read_St);
		return;
	}
	case 5: {
		fseek(read, sizeof(int), SEEK_SET);
		system("cls");
		printf("\n\tNumber of "BRED"characters"ESC": [%d]\n\n", char_Num);
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
		fprintf(stdout, "\nEnd of list! Continue...\n");
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

	FILE* search = NULL;
	search = fopen("characters.bin", "rb");
	if (search == NULL) {
		system("cls");
		printf("\n\t\t"RED"Error!"ESC"\nThere are no characters, for now...\n");
		_getch();
		return;
	}

	int search_Choice, chars_Num, i, flag = 0;
	do {
		system("cls");
		if (admin_Logged == 1) {
			printf("\t  Logged in as: "RED"[%s]"ESC"\n\n\t"BRED"Search characters by:\n\n"ESC"[1] ID\n[2] First name\n[3] Last name\n[4] Species\n[5] Status (alive / deceased)\n[6] Return\n\nChoice: ", logged_As);
		}
		else {
			printf("\t  Logged in as: "BLUE"[%s]"ESC"\n\n\t"BRED"Search characters by:\n\n"ESC"[1] ID\n[2] First name\n[3] Last name\n[4] Species\n[5] Status (alive / deceased)\n[6] Return\n\nChoice: ", logged_As);
		}
		scanf("%d", &search_Choice);
	} while (search_Choice < 1 || search_Choice > 6);


	CHARACTERS* read_St = NULL;
	fread(&chars_Num, sizeof(int), 1, search);
	read_St = (CHARACTERS*)calloc(chars_Num, sizeof(CHARACTERS));
	if (read_St == NULL) {
		perror("Struct error");
		exit(EXIT_FAILURE);
	}

	switch (search_Choice) {
	case 1: {
		int id_Srch;
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
		if (flag == 0) {
			printf("\nNo character with ID: [%d].\n", id_Srch);
			_getch();
		}
		else {
			printf("\nEnd of list.\n");
			_getch();
		}
		free(read_St);
		fclose(search);
		return;
	}
	case 2: {
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
		if (flag == 0) {
			*(srch_Fnm + (strlen(srch_Fnm) - 1)) = 0;
			printf("\nNo character with first name: [%s].\n", srch_Fnm);
			_getch();
		}
		else {
			printf("\nEnd of list.\n");
			_getch();
		}
		free(read_St);
		free(srch_Fnm);
		fclose(search);
		return;
	}
	case 3: {
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
		if (flag == 0) {
			*(srch_Lnm + (strlen(srch_Lnm) - 1)) = 0;
			printf("\nNo character with last name: [%s].\n", srch_Lnm);
			_getch();
		}
		else {
			printf("\nEnd of list.\n");
			_getch();
		}
		free(read_St);
		free(srch_Lnm);
		fclose(search);
		return;
	}
	case 4: {
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
		if (flag == 0) {
			*(srch_Spec + (strlen(srch_Spec) - 1)) = 0;
			printf("\nNo character of species: [%s].\n", srch_Spec);
			_getch();
		}
		else {
			printf("\nEnd of list.\n");
			_getch();
		}
		free(read_St);
		free(srch_Spec);
		fclose(search);
		return;
	}
	case 5: {
		int status;
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
		else {
			printf("\nEnd of list.\n");
			_getch();
		}
		free(read_St);
		fclose(search);
		return;
	}
	case 6: {
		free(read_St);
		fclose(search);
		return;
	}
	}
}