#include "header.h"
#include "structs.h"
#include "colors.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

void rit_Spell_Edit_Menu(void) {

	//enter from library_Edit_Board
	int choice;
	while (1) {
		if (admin_Logged == 1) {
			do {
				system("cls");
				printf("\t  Logged in as: "RED"[%s]"ESC"\n\n\t"RED"Rituals and Spells editing\n\n"ESC"[1] Add ritual / spell\n[2] Remove ritual / spell\n[3] Edit rituals / spells\n[4] List rituals / spells\n[5] Search rituals / spells\n[6] Return\n\nChoice: ", logged_As);
				scanf("%d", &choice);
			} while (choice < 1 || choice > 6);
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
				edit_Rit_Spell();
				break;
			}
			case 4: {
				rit_Spell_List();
				break;
			}
			case 5: {
				search_Rit_Spell();
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
				printf("\t  Logged in as: "BLUE"[%s]"ESC"\n\n\t"RED"Rituals and Spells\n\n"ESC"[1] List rituals / spells\n[2] Search rituals / spells\n[3] Edit rituals / spells\n[4] Return\n\nChoice: ", logged_As);
				scanf("%d", &choice);
			} while (choice < 1 || choice > 4);
			switch (choice) {
			case 1: {
				rit_Spell_List();
				break;
			}
			case 2: {
				search_Rit_Spell();
				break;
			}
			case 3: {
				edit_Rit_Spell();
				break;
			}
			case 4: {
				return;
			}
			}
		}
	}
}

void rit_Spell_Add(void) {

	//enter from rit_Spell_Edit_Menu
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
		printf("\n\tEntering 1. "RED"ritual / spell"ESC".\n\nEnter ID: ");
		scanf("%d", &rsp_Struc->ID);
		getchar();
		printf("Enter name: ");
		fgets(rsp_Struc->name, 99, stdin);
		do {
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
		printf("\n\tEntering %d. "RED"ritual / spell"ESC".\n\nEnter ID: ", rsp_Num);
		scanf("%d", &rsp_Struc->ID);
		printf("Enter name: ");
		getchar();
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

	//enter from rit_Spell_Edit_Menu
	int rem_By, num;

	FILE* rsp_File = NULL;
	rsp_File = fopen("rits_spells.bin", "rb");
	if (rsp_File == NULL) {
		system("cls");
		printf("\n\t\t"RED"Error!"ESC"\nThere are no rituals or spells, for now...\n");
		_getch();
		return;
	}

	do {
		system("cls");
		printf("\t  Logged in as: "RED"[%s]"ESC"\n\n\tRemoving rituals and spells "RED"[BE CAREFUL!]\n\n"ESC"[1] Remove by ID\n[2] Remove all rituals\n[3] Remove all spells\n[4] Remove both rituals and spells\n[5] Return\n\nChoice: ", logged_As);
		scanf("%d", &rem_By);
	} while (rem_By < 1 || rem_By > 5);

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
		int found = 0, helping = 0, count_Del = 0, dlt_ID;
		printf("\nEnter ID to delete: ");
		scanf("%d", &dlt_ID);

		helping = num;
		fwrite(&helping, sizeof(int), 1, tmp_Pntr);

		for (int i = 0; i < num; i++) {
			fread(deletion, sizeof(RITSSPELLS), 1, rsp_File);
			if (deletion->ID == dlt_ID) {
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
			printf("\n\tSpell / ritual with ID [%d] was not found.\n", dlt_ID);
			fclose(rsp_File);
			fclose(tmp_Pntr);
			free(deletion);
			_getch();
		}
		else {
			system("cls");
			printf("\n\tSpell / riutal with ID [%d] was "RED"removed"ESC".\n", dlt_ID);
			_getch();
			fclose(rsp_File);
			fclose(tmp_Pntr);
			free(deletion);
			if (helping == 0) {
				remove("rits_spells.bin");
				remove("tmp.bin");
				printf("\n\tThere are no "RED"spells or rituals"ESC" left.\n");
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
		if (strcmp(y_Or_N, "YES") == 0) {
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
					printf("\n\tThere are no "RED"spells or rituals"ESC" left.\n");
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
		else if (strcmp(y_Or_N, "NO") == 0) {
			fclose(rsp_File);
			fclose(tmp_Pntr);
			free(y_Or_N);
			free(deletion);
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
					printf("\n\tThere are no "RED"spells or rituals"ESC" left.\n");
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
		else if (strcmp(y_Or_N, "NO") == 0) {
			fclose(rsp_File);
			fclose(tmp_Pntr);
			free(y_Or_N);
			free(deletion);
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
				if (deletion->ritual == 1 || deletion->spell == 1) {
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
					printf("\n\tThere are no "RED"rituals"ESC" or "RED"spells"ESC" left.\n");
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
		else if (strcmp(y_Or_N, "NO") == 0) {
			fclose(rsp_File);
			fclose(tmp_Pntr);
			free(y_Or_N);
			free(deletion);
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

void edit_Rit_Spell(void) {

	//enter from rit_Spell_Edit_Menu
	int edit_Rsp, rsp_Num, rsp_ID_Choice, i, flag = 0, sprb;

	FILE* read = NULL;
	read = fopen("rits_spells.bin", "r+b");
	if (read == NULL) {
		system("cls");
		printf("\n\t\t"RED"Error!"ESC"\nThere are no rituals or spells, for now...\n");
		_getch();
		return;
	}

	RITSSPELLS* read_St = NULL;
	fread(&rsp_Num, sizeof(int), 1, read);
	read_St = (RITSSPELLS*)calloc(rsp_Num, sizeof(RITSSPELLS));
	if (read_St == NULL) {
		perror("Struct error");
		exit(EXIT_FAILURE);
	}

	fseek(read, sizeof(int), SEEK_SET);
	fread(read_St, sizeof(RITSSPELLS), rsp_Num, read);

	do {
		system("cls");
		if (admin_Logged == 1) {
			printf("\t  Logged in as: "RED"[%s]"ESC"\n\n\tEditing rituals and spells "RED"[BE CAREFUL!]\n\n"ESC"[1] Edit by ID\n[2] Return\n\nChoice: ", logged_As);
		}
		else {
			printf("\t  Logged in as: "BLUE"[%s]"ESC"\n\n\tEditing rituals and spells "RED"[BE CAREFUL!]\n\n"ESC"[1] Edit by ID\n[2] Return\n\nChoice: ", logged_As);
		}
		scanf("%d", &edit_Rsp);
	} while (edit_Rsp < 1 || edit_Rsp > 2);
	switch (edit_Rsp) {
	case 1: {
		system("cls");
		printf("\n\t"RED"Edit rituals and spells by ID:\n\n"ESC"Enter ID: ");
		scanf("%d", &rsp_ID_Choice);

		for (i = 0; i < rsp_Num; i++) {
			if (rsp_ID_Choice == (read_St + i)->ID) {
				flag = 1;
				break;
			}
		}

		if (flag == 0) {
			printf("\nNo ritual or spell with ID [%d].\n", rsp_ID_Choice);
			_getch();
			return;
		}
		else {
			RITSSPELLS* temp = NULL;
			temp = (RITSSPELLS*)calloc(1, sizeof(RITSSPELLS));
			if (temp == NULL) {
				perror("Struct error");
				exit(EXIT_FAILURE);
			}

			system("cls");
			printf("\n\tEditing ID [%d] of "RED"ritual or spell"ESC".\n\nEnter ritual or spell ID: ", rsp_ID_Choice);
			scanf("%d", &temp->ID); getchar();
			printf("Enter name: ");
			fgets(temp->name, 99, stdin);
			do {
				printf("Is it a ritual [1], a spell [2] or both [3]: ");
				scanf("%d", &sprb);
			} while (sprb < 1 || sprb > 3);
			if (sprb == 1) {
				temp->ritual = 1;
				temp->spell = 0;
			}
			else if (sprb == 2) {
				temp->spell = 1;
				temp->ritual = 0;
			}
			else {
				temp->ritual = 1;
				temp->spell = 1;
			}
			printf("Enter manufacturer / caster: "); getchar();
			fgets(temp->manuf_caster, 99, stdin);
			printf("Enter use: ");
			fgets(temp->used, 299, stdin);
			printf("Enter details: ");
			fgets(temp->details, 499, stdin);
			for (i = 0; i < rsp_Num; i++) {
				if ((read_St + i)->ID == rsp_ID_Choice) {
					fseek(read, ftell(read) - sizeof(RITSSPELLS), SEEK_SET);
					fwrite(temp, sizeof(RITSSPELLS), 1, read);
					break;
				}
			}
			fclose(read);
			free(temp);
			free(read_St);
			return;
		}
	}
	case 2: {
		fclose(read);
		free(read_St);
		return;
	}
	}
}

void rit_Spell_List(void) {

	//enter from rit_Spell_Edit_Menu
	int list_Choice, rsp_Num;

	FILE* rsp_File = NULL;
	rsp_File = fopen("rits_spells.bin", "rb");
	if (rsp_File == NULL) {
		system("cls");
		printf("\n\t\t"RED"Error!"ESC"\nThere are no rituals or spells, for now...\n");
		_getch();
		return;
	}

	do {
		system("cls");
		if (admin_Logged == 1) {
			printf("\t  Logged in as: "RED"[%s]"ESC"\n\n\t"RED"List rituals / spells by:\n\n"ESC"[1] ID\n[2] Is ritual\n[3] Is spell\n[4] Is both ritual & spell\n[5] Return\n\nChoice: ", logged_As);
		}
		else {
			printf("\t  Logged in as: "BLUE"[%s]"ESC"\n\n\t"RED"List rituals / spells by:\n\n"ESC"[1] ID\n[2] Is ritual\n[3] Is spell\n[4] Is both ritual & spell\n[5] Return\n\nChoice: ", logged_As);
		}
		scanf("%d", &list_Choice);
	} while (list_Choice < 1 || list_Choice > 5);

	RITSSPELLS* rsp_Struc = NULL;
	fread(&rsp_Num, sizeof(int), 1, rsp_File);
	rsp_Struc = (RITSSPELLS*)calloc(rsp_Num, sizeof(RITSSPELLS));
	if (rsp_Struc == NULL) {
		perror("Struct error");
		exit(EXIT_FAILURE);
	}

	switch (list_Choice) {
	case 1: {
		int asc_Desc, i;
		do {
			system("cls");
			printf("\n\t"RED"Sort rituals / spells by ID:\n\n"ESC"[1] Ascending\n[2] Descending\n\nChoice: ");
			scanf("%d", &asc_Desc);
		} while (asc_Desc < 1 || asc_Desc > 2);

		fseek(rsp_File, sizeof(int), SEEK_SET);
		fread(rsp_Struc, sizeof(RITSSPELLS), rsp_Num, rsp_File);
		if (asc_Desc == 1)
			qsort(rsp_Struc, rsp_Num, sizeof(RITSSPELLS), comp_ID_Asc_Rsp);
		else
			qsort(rsp_Struc, rsp_Num, sizeof(RITSSPELLS), comp_ID_Desc_Rsp);
		system("cls");
		printf("\n\tNumber of "RED"rituals & spells"ESC": [%d]\n\n", rsp_Num);
		for (i = 0; i < rsp_Num; i++) {
			fprintf(stdout, BMNG"\n[%d] ID:"ESC" %d\n", i + 1, (rsp_Struc + i)->ID);
			fprintf(stdout, BMNG"[%d] Name:"ESC" %s", i + 1, (rsp_Struc + i)->name);
			if ((rsp_Struc + i)->ritual == 0 && (rsp_Struc + i)->spell == 1) {
				fprintf(stdout, RED"[Spell]\n"ESC);
			}
			else if ((rsp_Struc + i)->ritual == 1 && (rsp_Struc + i)->spell == 0) {
				fprintf(stdout, RED"[Ritual]\n"ESC);
			}
			else {
				fprintf(stdout, RED"[Spell & ritual]\n"ESC);
			}
			fprintf(stdout, BMNG"[%d] Manufacturer / caster:"ESC" %s", i + 1, (rsp_Struc + i)->manuf_caster);
			fprintf(stdout, BMNG"[%d] Used:"ESC" %s", i + 1, (rsp_Struc + i)->used);
			fprintf(stdout, BMNG"[%d] Details:"ESC" %s\n", i + 1, (rsp_Struc + i)->details);
		}
		fprintf(stdout, "\nEnd of list! Continue...\n");
		_getch();
		fclose(rsp_File);
		free(rsp_Struc);
		return;
	}
	case 2: {
		int asc_Desc, i;
		do {
			system("cls");
			printf("\n\t"RED"List all rituals:\n\n"ESC"[1] Ascending\n[2] Descending\n\nChoice: ");
			scanf("%d", &asc_Desc);
		} while (asc_Desc < 1 || asc_Desc > 2);

		fseek(rsp_File, sizeof(int), SEEK_SET);
		fread(rsp_Struc, sizeof(RITSSPELLS), rsp_Num, rsp_File);
		if (asc_Desc == 1)
			qsort(rsp_Struc, rsp_Num, sizeof(RITSSPELLS), comp_ID_Asc_Rsp);
		else
			qsort(rsp_Struc, rsp_Num, sizeof(RITSSPELLS), comp_ID_Desc_Rsp);
		system("cls");
		printf("\n\tNumber of "RED"rituals & spells"ESC": [%d]\n\n", rsp_Num);
		for (i = 0; i < rsp_Num; i++) {
			if ((rsp_Struc + i)->ritual == 1) {
				fprintf(stdout, BMNG"\n[%d] ID:"ESC" %d\n", i + 1, (rsp_Struc + i)->ID);
				fprintf(stdout, BMNG"[%d] Name:"ESC" %s", i + 1, (rsp_Struc + i)->name);
				if ((rsp_Struc + i)->ritual == 0 && (rsp_Struc + i)->spell == 1) {
					fprintf(stdout, RED"[Spell]\n"ESC);
				}
				else if ((rsp_Struc + i)->ritual == 1 && (rsp_Struc + i)->spell == 0) {
					fprintf(stdout, RED"[Ritual]\n"ESC);
				}
				else {
					fprintf(stdout, RED"[Spell & ritual]\n"ESC);
				}
				fprintf(stdout, BMNG"[%d] Manufacturer / caster:"ESC" %s", i + 1, (rsp_Struc + i)->manuf_caster);
				fprintf(stdout, BMNG"[%d] Used:"ESC" %s", i + 1, (rsp_Struc + i)->used);
				fprintf(stdout, BMNG"[%d] Details:"ESC" %s\n", i + 1, (rsp_Struc + i)->details);
			}
		}
		fprintf(stdout, "\nEnd of list! Continue...\n");
		_getch();
		fclose(rsp_File);
		free(rsp_Struc);
		return;
	}
	case 3: {
		int asc_Desc, i;
		do {
			system("cls");
			printf("\n\t"RED"List all spells:\n\n"ESC"[1] Ascending\n[2] Descending\n\nChoice: ");
			scanf("%d", &asc_Desc);
		} while (asc_Desc < 1 || asc_Desc > 2);

		fseek(rsp_File, sizeof(int), SEEK_SET);
		fread(rsp_Struc, sizeof(RITSSPELLS), rsp_Num, rsp_File);
		if (asc_Desc == 1)
			qsort(rsp_Struc, rsp_Num, sizeof(RITSSPELLS), comp_ID_Asc_Rsp);
		else
			qsort(rsp_Struc, rsp_Num, sizeof(RITSSPELLS), comp_ID_Desc_Rsp);
		system("cls");
		printf("\n\tNumber of "RED"rituals & spells"ESC": [%d]\n\n", rsp_Num);
		for (i = 0; i < rsp_Num; i++) {
			if ((rsp_Struc + i)->spell == 1) {
				fprintf(stdout, BMNG"\n[%d] ID:"ESC" %d\n", i + 1, (rsp_Struc + i)->ID);
				fprintf(stdout, BMNG"[%d] Name:"ESC" %s", i + 1, (rsp_Struc + i)->name);
				if ((rsp_Struc + i)->ritual == 0 && (rsp_Struc + i)->spell == 1) {
					fprintf(stdout, RED"[Spell]\n"ESC);
				}
				else if ((rsp_Struc + i)->ritual == 1 && (rsp_Struc + i)->spell == 0) {
					fprintf(stdout, RED"[Ritual]\n"ESC);
				}
				else {
					fprintf(stdout, RED"[Spell & ritual]\n"ESC);
				}
				fprintf(stdout, BMNG"[%d] Manufacturer / caster:"ESC" %s", i + 1, (rsp_Struc + i)->manuf_caster);
				fprintf(stdout, BMNG"[%d] Used:"ESC" %s", i + 1, (rsp_Struc + i)->used);
				fprintf(stdout, BMNG"[%d] Details:"ESC" %s\n", i + 1, (rsp_Struc + i)->details);
			}
		}
		fprintf(stdout, "\nEnd of list! Continue...\n");
		_getch();
		fclose(rsp_File);
		free(rsp_Struc);
		return;
	}
	case 4: {
		int asc_Desc, i, flag = 0;
		do {
			system("cls");
			printf("\n\t"RED"List all rituals & spells:\n\n"ESC"[1] Ascending\n[2] Descending\n\nChoice: ");
			scanf("%d", &asc_Desc);
		} while (asc_Desc < 1 || asc_Desc > 2);

		fseek(rsp_File, sizeof(int), SEEK_SET);
		fread(rsp_Struc, sizeof(RITSSPELLS), rsp_Num, rsp_File);
		if (asc_Desc == 1)
			qsort(rsp_Struc, rsp_Num, sizeof(RITSSPELLS), comp_ID_Asc_Rsp);
		else
			qsort(rsp_Struc, rsp_Num, sizeof(RITSSPELLS), comp_ID_Desc_Rsp);
		system("cls");
		printf("\n\tNumber of "RED"rituals & spells"ESC": [%d]\n\n", rsp_Num);
		for (i = 0; i < rsp_Num; i++) {
			if ((rsp_Struc + i)->spell == 1 && (rsp_Struc + i)->ritual == 1) {
				fprintf(stdout, BMNG"\n[%d] ID:"ESC" %d\n", i + 1, (rsp_Struc + i)->ID);
				fprintf(stdout, BMNG"[%d] Name:"ESC" %s", i + 1, (rsp_Struc + i)->name);
				if ((rsp_Struc + i)->ritual == 0 && (rsp_Struc + i)->spell == 1) {
					fprintf(stdout, RED"[Spell]\n"ESC);
				}
				else if ((rsp_Struc + i)->ritual == 1 && (rsp_Struc + i)->spell == 0) {
					fprintf(stdout, RED"[Ritual]\n"ESC);
				}
				else {
					fprintf(stdout, RED"[Spell & ritual]\n"ESC);
				}
				fprintf(stdout, BMNG"[%d] Manufacturer / caster:"ESC" %s", i + 1, (rsp_Struc + i)->manuf_caster);
				fprintf(stdout, BMNG"[%d] Used:"ESC" %s", i + 1, (rsp_Struc + i)->used);
				fprintf(stdout, BMNG"[%d] Details:"ESC" %s\n", i + 1, (rsp_Struc + i)->details);
				flag = 1;
			}
		}
		if (flag == 0) {
			fprintf(stdout, "\nNo rituals & spells on the list! Continue...\n");
			_getch();
		}
		else {
			fprintf(stdout, "\nEnd of list! Continue...\n");
			_getch();
		}
		fclose(rsp_File);
		free(rsp_Struc);
		return;
	}
	case 5: {
		fclose(rsp_File);
		free(rsp_Struc);
		return;
	}
	}
}

void search_Rit_Spell(void) {

	//enter from rit_Spell_Edit_Menu
	int search_Choice, i, rsp_Num;

	FILE* rsp_File = NULL;
	rsp_File = fopen("rits_spells.bin", "rb");
	if (rsp_File == NULL) {
		system("cls");
		printf("\n\t\t"RED"Error!"ESC"\nThere are no rituals or spells, for now...\n");
		_getch();
		return;
	}

	do {
		system("cls");
		if (admin_Logged == 1) {
			printf("\t  Logged in as: "RED"[%s]"ESC"\n\n\t"RED"Search rituals and spells by:\n\n"ESC"[1] Name\n[2] Manufacturer / caster\n[3] Spells\n[4] Rituals\n[5] Return\n\nChoice: ", logged_As);
		}
		else {
			printf("\t  Logged in as: "BLUE"[%s]"ESC"\n\n\t"RED"Search rituals and spells by:\n\n"ESC"[1] Name\n[2] Manufacturer / caster\n[3] Spells\n[4] Rituals\n[5] Return\n\nChoice: ", logged_As);
		}
		scanf("%d", &search_Choice);
	} while (search_Choice < 1 || search_Choice > 5);

	RITSSPELLS* rsp_Struc = NULL;
	fread(&rsp_Num, sizeof(int), 1, rsp_File);
	rsp_Struc = (RITSSPELLS*)calloc(rsp_Num, sizeof(RITSSPELLS));
	if (rsp_Struc == NULL) {
		perror("Struct error");
		exit(EXIT_FAILURE);
	}

	switch (search_Choice) {
	case 1: {
		int flag = 0;
		char* srch_Rsp_Nm;
		srch_Rsp_Nm = (char*)calloc(100, sizeof(char));
		if (srch_Rsp_Nm == NULL) {
			perror("Memory error");
			exit(EXIT_FAILURE);
		}
		system("cls");
		getchar();
		printf("\nEnter riutal / spell name: ");
		fgets(srch_Rsp_Nm, 99, stdin);
		for (i = 0; i < rsp_Num; i++) {
			fread(rsp_Struc, sizeof(RITSSPELLS), 1, rsp_File);
			if (strcmp(rsp_Struc->name, srch_Rsp_Nm) == 0) {
				fprintf(stdout, BMNG"\n[%d] ID:"ESC" %d\n", i + 1, (rsp_Struc + i)->ID);
				fprintf(stdout, BMNG"[%d] Name:"ESC" %s", i + 1, (rsp_Struc + i)->name);
				if ((rsp_Struc + i)->ritual == 0 && (rsp_Struc + i)->spell == 1) {
					fprintf(stdout, RED"[Spell]\n"ESC);
				}
				else if ((rsp_Struc + i)->ritual == 1 && (rsp_Struc + i)->spell == 0) {
					fprintf(stdout, RED"[Ritual]\n"ESC);
				}
				else {
					fprintf(stdout, RED"[Spell & ritual]\n"ESC);
				}
				fprintf(stdout, BMNG"[%d] Manufacturer / caster:"ESC" %s", i + 1, (rsp_Struc + i)->manuf_caster);
				fprintf(stdout, BMNG"[%d] Used:"ESC" %s", i + 1, (rsp_Struc + i)->used);
				fprintf(stdout, BMNG"[%d] Details:"ESC" %s\n", i + 1, (rsp_Struc + i)->details);
				flag = 1;
				_getch();
				break;
			}
		}
		if (flag == 0) {
			*(srch_Rsp_Nm + (strlen(srch_Rsp_Nm) - 1)) = 0;
			printf("\nNo riutal or spell with name: [%s].\n", srch_Rsp_Nm);
			_getch();
		}
		else {
			printf("End of list.");
			_getch();
		}
		free(rsp_Struc);
		free(srch_Rsp_Nm);
		fclose(rsp_File);
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
		for (i = 0; i < rsp_Num; i++) {
			fread(rsp_Struc, sizeof(RITSSPELLS), 1, rsp_File);
			if (strcmp(rsp_Struc->manuf_caster, srch_Manuf) == 0) {
				fprintf(stdout, BMNG"\n[%d] ID:"ESC" %d\n", i + 1, (rsp_Struc + i)->ID);
				fprintf(stdout, BMNG"[%d] Name:"ESC" %s", i + 1, (rsp_Struc + i)->name);
				if ((rsp_Struc + i)->ritual == 0 && (rsp_Struc + i)->spell == 1) {
					fprintf(stdout, RED"[Spell]\n"ESC);
				}
				else if ((rsp_Struc + i)->ritual == 1 && (rsp_Struc + i)->spell == 0) {
					fprintf(stdout, RED"[Ritual]\n"ESC);
				}
				else {
					fprintf(stdout, RED"[Spell & ritual]\n"ESC);
				}
				fprintf(stdout, BMNG"[%d] Manufacturer / caster:"ESC" %s", i + 1, rsp_Struc->manuf_caster);
				fprintf(stdout, BMNG"[%d] Used:"ESC" %s", i + 1, rsp_Struc->used);
				fprintf(stdout, BMNG"[%d] Details:"ESC" %s\n", i + 1, rsp_Struc->details);
				flag = 1;
				_getch();
			}
		}
		if (flag == 0) {
			*(srch_Manuf + (strlen(srch_Manuf) - 1)) = 0;
			printf("\nNo manufacturer(s) / caster(s) named: [%s].\n", srch_Manuf);
			_getch();
		}
		else {
			printf("End of list.");
			_getch();
		}
		free(rsp_Struc);
		free(srch_Manuf);
		fclose(rsp_File);
		return;
	}
	case 3: {
		int flag = 0;
		system("cls");
		printf("\nListing all "RED"spells"ESC":\n");
		for (i = 0; i < rsp_Num; i++) {
			fread(rsp_Struc, sizeof(RITSSPELLS), 1, rsp_File);
			if (rsp_Struc->spell == 1) {
				fprintf(stdout, BMNG"\n[%d] ID:"ESC" %d\n", i + 1, (rsp_Struc + i)->ID);
				fprintf(stdout, BMNG"[%d] Name:"ESC" %s", i + 1, (rsp_Struc + i)->name);
				if (rsp_Struc->ritual == 0 && rsp_Struc->spell == 1) {
					fprintf(stdout, RED"[Spell]\n"ESC);
				}
				else if (rsp_Struc->ritual == 1 && rsp_Struc->spell == 0) {
					fprintf(stdout, RED"[Ritual]\n"ESC);
				}
				else {
					fprintf(stdout, RED"[Spell & ritual]\n"ESC);
				}
				fprintf(stdout, BMNG"[%d] Manufacturer / caster:"ESC" %s", i + 1, rsp_Struc->manuf_caster);
				fprintf(stdout, BMNG"[%d] Used:"ESC" %s", i + 1, rsp_Struc->used);
				fprintf(stdout, BMNG"[%d] Details:"ESC" %s\n", i + 1, rsp_Struc->details);
				flag = 1;
				_getch();
			}
		}
		if (flag == 0) {
			printf("\nNo spell(s) on the list.\n");
			_getch();
		}
		else {
			printf("End of list.");
			_getch();
		}
		free(rsp_Struc);
		fclose(rsp_File);
		return;
	}
	case 4: {
		int flag = 0;
		system("cls");
		printf("\nListing all "RED"rituals"ESC" :");
		for (i = 0; i < rsp_Num; i++) {
			fread(rsp_Struc, sizeof(RITSSPELLS), 1, rsp_File);
			if (rsp_Struc->ritual == 1) {
				fprintf(stdout, BMNG"\n[%d] ID:"ESC" %d\n", i + 1, (rsp_Struc + i)->ID);
				fprintf(stdout, BMNG"[%d] Name:"ESC" %s", i + 1, (rsp_Struc + i)->name);
				if ((rsp_Struc + i)->ritual == 0 && (rsp_Struc + i)->spell == 1) {
					fprintf(stdout, RED"[Spell]\n"ESC);
				}
				else if ((rsp_Struc + i)->ritual == 1 && (rsp_Struc + i)->spell == 0) {
					fprintf(stdout, RED"[Ritual]\n"ESC);
				}
				else {
					fprintf(stdout, RED"[Spell & ritual]\n"ESC);
				}
				fprintf(stdout, BMNG"[%d] Manufacturer / caster:"ESC" %s", i + 1, (rsp_Struc + i)->manuf_caster);
				fprintf(stdout, BMNG"[%d] Used:"ESC" %s", i + 1, (rsp_Struc + i)->used);
				fprintf(stdout, BMNG"[%d] Details:"ESC" %s\n", i + 1, (rsp_Struc + i)->details);
				flag = 1;
				_getch();
			}
		}
		if (flag == 0) {
			printf("\nNo ritual(s) on the list.\n");
			_getch();
		}
		else {
			printf("End of list.");
			_getch();
		}
		free(rsp_Struc);
		fclose(rsp_File);
		return;
	}
	case 5: {
		free(rsp_Struc);
		fclose(rsp_File);
		return;
	}
	}
}