#include "header.h"
#include "structs.h"
#include "colors.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

void admins_Menu(void) {

	//enter from admins_Login & admin_Input
	int choice;
	while(1){
		do{
			system("cls");
			printf("\t  Logged in as: "RED"[%s]"ESC"\n\n\t"BYLW"Supernatural"ESC""RED" admins"ESC" panel.\n\n", logged_As);
			printf("[1] "RED"Edit admins\n"ESC"[2] "BLUE"Edit members\n"ESC"[3] "YLW"Edit library\n"ESC"[4] "BBLUE"Log out"ESC"\n[5] "BCYN"Exit program"ESC"\n\nChoice: ");
			scanf("%d", &choice);	 
		} while (choice < 1 || choice > 5);

		switch (choice) {
			case 1: {
				admin_Edit_Board();
				break;
			}
			case 2: {
				member_Edit_Board();
				break;
			}
			case 3: {
				library_Edit_Board();
				break;
			}
			case 4: {
				free(logged_As);
				return;				
			}
			case 5: {
				free(logged_As);
				exit(EXIT_SUCCESS);
			}
		}
	}
}

void members_Menu(void) {

	//enter from admins_Menu
	int choice;
	while (1) {
		do {
			system("cls");
			printf("\t  Logged in as: "BLUE"[%s]"ESC"\n\n\t"BYLW"Welcome to the Supernatural Library!"ESC"\n\n", logged_As);
			printf("[1] "BRED"Characters"ESC"\n[2] "CYN"Locations"ESC"\n[3] "BGRN"Music"ESC"\n[4] "YLW"Objects"ESC"\n[5] "RED"Rituals & Spells"ESC"\n[6] "MNG"Seasons"ESC"\n[7] "BCYN"Exit program"ESC"\n\nChoice: ");
			scanf("%d", &choice);
		} while (choice < 1 || choice > 8);
		switch (choice) {
		case 1: {
			chars_Edit_Menu();
			break;
		}
		case 2: {
			locs_Edit_Menu();
			break;
		}
		case 3: {
			music_Edit_Menu();
			break;
		}
		case 4: {
			object_Edit_Menu();
			break;
		}
		case 5: {
			rit_Spell_Edit_Menu();
			break;
		}
		case 6: {
			seas_Edit_Menu();
			break;
		}
		case 7: {
			free(logged_As);
			exit(EXIT_SUCCESS); }
		}
	}
}

void admin_Input(void) {

	//enter from admin_Edit_Board
	ADMINS* admins = NULL;
	admins = (ADMINS*)calloc(1, sizeof(ADMINS));
	if (admins == NULL) {
		perror("Struct error");
		exit(EXIT_FAILURE);
	}
	FILE* admin_File = NULL;
	admin_File = fopen("admins.bin", "r+b");
	if (admin_File == NULL) {
		admin_File = fopen("admins.bin", "wb");
		if (admin_File == NULL) {
			perror("File error");
			exit(EXIT_FAILURE);
		}
		system("cls");
		printf("\n\tEntering 1. "RED"admin"ESC".\n\nEnter admin ID: ");
		scanf("%d", &admins->ID);
		printf("Enter username: "); getchar();
		fgets(admins->username, 29, stdin);
		printf("Enter password: ");
		fgets(admins->password, 29, stdin);
		printf("Enter first name: ");
		fgets(admins->f_Name, 29, stdin);
		printf("Enter last name: ");
		fgets(admins->l_Name, 29, stdin);
		strcpy(logged_As, admins->username);
		*(logged_As + (strlen(logged_As) - 1)) = 0;
		int admin_Num = 1;
		fwrite(&admin_Num, sizeof(int), 1, admin_File);
		fwrite(admins, sizeof(ADMINS), 1, admin_File);
		free(admins);
		fclose(admin_File);
		return;
	}
	else {
		int admin_Num;
		fread(&admin_Num, sizeof(int), 1, admin_File);
		ADMINS* temp_Check = NULL;
		temp_Check = (ADMINS*)calloc(admin_Num, sizeof(ADMINS));
		if (temp_Check == NULL) {
			perror("Struct error");
			exit(EXIT_FAILURE);
		}
		fread(temp_Check, sizeof(ADMINS), admin_Num, admin_File);
		admin_Num++;
		system("cls");
		printf("\n\tEntering %d. "RED"admin"ESC".\n\nEnter ID: ", admin_Num);
		scanf("%d", &admins->ID);
		for (int i = 0; i < (admin_Num - 1); i++) {
			if ((temp_Check + i)->ID == admins->ID) {
				printf(RED"\n\tAdmin with that ID already exists!\n"ESC);
				_getch();
				return;
			}
		}
		printf("Enter username: "); getchar();
		fgets(admins->username, 29, stdin);		
		for (int i = 0; i < (admin_Num - 1); i++) {
			if (strcmp((temp_Check + i)->username, admins->username) == 0) {
				printf(RED"\n\tAdmin with that username already exists!\n"ESC);
				_getch();
				return;
			}
		}
		printf("Enter password: ");
		fgets(admins->password, 29, stdin);
		printf("Enter first name: ");
		fgets(admins->f_Name, 29, stdin);
		printf("Enter last name: ");
		fgets(admins->l_Name, 29, stdin);
		rewind(admin_File);
		fwrite(&admin_Num, sizeof(int), 1, admin_File);
		fseek(admin_File, sizeof(int) + ((admin_Num - 1) * sizeof(ADMINS)), SEEK_SET);
		fwrite(admins, sizeof(ADMINS), 1, admin_File);
		free(admins);
		fclose(admin_File);
		return;
	}
}

void del_Admins(void) {

	//enter from admin_Edit_Board
	FILE* read_Adms = NULL;
	read_Adms = fopen("admins.bin", "rb");
	if (read_Adms == NULL) {
		system("cls");
		printf("\n\t\t"RED"Error!"ESC"\nThere are no admins, for now...\n");
		_getch();
		return;
	}

	int rem_By, num;
	do {
		system("cls");
		printf("\t  Logged in as: "RED"[%s]"ESC"\n\n\tRemoving admins "RED"[BE CAREFUL!]\n\n"ESC"[1] Remove by ID\n[2] Remove by username\n[3] Return\n\nChoice: ", logged_As);
		scanf("%d", &rem_By);
	} while (rem_By < 1 || rem_By > 3);

	FILE* tmp_Pntr = NULL;
	tmp_Pntr = fopen("tmp.bin", "wb");
	if (tmp_Pntr == NULL) {
		printf("File error");
		exit(EXIT_FAILURE);
	}

	fread(&num, sizeof(int), 1, read_Adms);
	ADMINS* deletion = NULL;
	deletion = (ADMINS*)calloc(num, sizeof(ADMINS));
	if (deletion == NULL) {
		perror("Struct error");
		exit(EXIT_FAILURE);
	}

	switch (rem_By) {
		case 1: {
			int dlt_ID, found = 0, helping, i;
			printf("\nEnter ID to delete: ");
			scanf("%d", &dlt_ID);

			helping = num - 1;
			fwrite(&helping, sizeof(int), 1, tmp_Pntr);

			for (i = 0; i < num; i++) {
				fread(deletion, sizeof(ADMINS), 1, read_Adms);
				if (deletion->ID == dlt_ID) {
					found = 1;
				}
				else {
					fwrite(deletion, sizeof(ADMINS), 1, tmp_Pntr);
				}
			}

			if (found != 1) {
				system("cls");
				printf("\n\tAdmin with ID [%d] was not found.\n", dlt_ID);
				fclose(read_Adms);
				fclose(tmp_Pntr);
				free(deletion);
				_getch();
			}
			else {
				system("cls");
				printf("\n\tAdmin with ID [%d] was "BRED"removed"ESC".\n", dlt_ID);
				_getch();
				if (helping == 0) {
					fclose(read_Adms);
					fclose(tmp_Pntr);
					free(deletion);
					remove("admins.bin");
					remove("tmp.bin");
					printf("\n\tThere are no "RED"admins"ESC" left. Returning to login menu...\n");
					_getch();
					initial_Menu();
				}
				else {
					fclose(read_Adms);
					fclose(tmp_Pntr);
					free(deletion);
					remove("admins.bin");
					rename("tmp.bin", "admins.bin");
				}
			}
			return;
		}
		case 2: {
			char* dlt_Un;
			int found = 0, helping, i;
			dlt_Un = (char*)calloc(30, sizeof(char));
			if (dlt_Un == NULL) {
				perror("Memory error");
				exit(EXIT_FAILURE);
			}
			getchar();
			printf("\nEnter username to delete: ");
			fgets(dlt_Un, 29, stdin);

			helping = num - 1;
			fwrite(&helping, sizeof(int), 1, tmp_Pntr);

			for (i = 0; i < num; i++) {
				fread(deletion, sizeof(ADMINS), 1, read_Adms);
				if (strcmp(deletion->username, dlt_Un) == 0) {
					found = 1;
				}
				else {
					fwrite(deletion, sizeof(ADMINS), 1, tmp_Pntr);
				}
			}

			if (found != 1) {
				system("cls");
				*(dlt_Un + (strlen(dlt_Un) - 1)) = 0;
				printf("\n\tAdmin with username [%s] was not found.\n", dlt_Un);
				fclose(read_Adms);
				fclose(tmp_Pntr);
				free(deletion);
				free(dlt_Un);
				_getch();
			}
			else {
				system("cls");
				*(dlt_Un + (strlen(dlt_Un) - 1)) = 0;
				printf("\n\tAdmin with username [%s] was "BRED"removed"ESC".\n", dlt_Un);
				_getch();
				fclose(read_Adms);
				fclose(tmp_Pntr);
				free(deletion);
				free(dlt_Un);
				if (helping == 0) {
					remove("admins.bin");
					remove("tmp.bin");
					printf("\n\tThere are no "RED"admins"ESC" left. Returning to login menu...\n");
					_getch();
					initial_Menu();
				}
				else {
					remove("admins.bin");
					rename("tmp.bin", "admins.bin");
				}
			}
			return;
		}
		case 3: {
			fclose(read_Adms);
			fclose(tmp_Pntr);
			free(deletion);
			return;
		}
	}
}

void list_Admins(void) {

	//enter from admin_Edit_Board
	FILE* read = NULL;
	read = fopen("admins.bin", "rb");
	if (read == NULL) {
		system("cls");
		printf("\n\t\t"RED"Error!"ESC"\nThere are no admins, for now...\n");
		_getch();
		return;
	}

	int list_Choice, num_Admin;
	do {
		system("cls");
		printf("\n\t"RED"List admins by:\n\n"ESC"[1] ID\n[2] Username\n[3] First name\n[4] Return to edit panel\n\nChoice: ");
		scanf("%d", &list_Choice);
	} while (list_Choice < 1 || list_Choice > 4);


	ADMINS* read_St = NULL;
	fread(&num_Admin, sizeof(int), 1, read);
	read_St = (ADMINS*)calloc(num_Admin, sizeof(ADMINS));
	if (read_St == NULL) {
		perror("Struct error");
		exit(EXIT_FAILURE);
	}

	switch (list_Choice) {
		case 1: {
			int asc_Desc, i;
			do {
				system("cls");
				printf("\n\t"RED"Sort admins by ID:\n\n"ESC"[1] Ascending\n[2] Descending\n\nChoice: ");
				scanf("%d", &asc_Desc);
			} while (asc_Desc < 1 || asc_Desc > 2);

			fseek(read, sizeof(int), SEEK_SET);
			fread(read_St, sizeof(ADMINS), num_Admin, read);
			if (asc_Desc == 1){
				qsort(read_St, num_Admin, sizeof(ADMINS), comp_ID_Admin_Asc);
			}
			else{
				qsort(read_St, num_Admin, sizeof(ADMINS), comp_ID_Admin_Desc);
			}

			system("cls");
			printf("\n\tNumber of "RED"admins"ESC": %d\n\n", num_Admin);
			for (i = 0; i < num_Admin; i++) {
				fprintf(stdout, "[%d] ID: %d\n", i + 1, (read_St + i)->ID);
				fprintf(stdout, "[%d] Username: %s", i + 1, (read_St + i)->username);
				fprintf(stdout, "[%d] Password: %s", i + 1, (read_St + i)->password);
				fprintf(stdout, "[%d] First name: %s", i + 1, (read_St + i)->f_Name);
				fprintf(stdout, "[%d] Last name: %s\n", i + 1, (read_St + i)->l_Name);			
			}
			fprintf(stdout, "\nEnd of list! Continue...\n");
			_getch();
			fclose(read);
			free(read_St);
			return;
		}
		case 2: {
			int asc_Desc, i;
			do {
				system("cls");
				printf("\n\t"RED"Sort admins by username:\n\n"ESC"[1] Ascending\n[2] Descending\n\nChoice: ");
				scanf("%d", &asc_Desc);
			} while (asc_Desc < 1 || asc_Desc > 2);

			fseek(read, sizeof(int), SEEK_SET);
			fread(read_St, sizeof(ADMINS), num_Admin, read);
			if(asc_Desc == 1) {
				qsort(read_St, num_Admin, sizeof(ADMINS), comp_Un_Admin_Asc);
			}
			else {
				qsort(read_St, num_Admin, sizeof(ADMINS), comp_Un_Admin_Desc);
			}

			system("cls");
			printf("\n\tNumber of "RED"admins"ESC": %d\n\n", num_Admin);
			for (i = 0; i < num_Admin; i++) {
				fprintf(stdout, "[%d] ID: %d\n", i + 1, (read_St + i)->ID);
				fprintf(stdout, "[%d] Username: %s", i + 1, (read_St + i)->username);
				fprintf(stdout, "[%d] Password: %s", i + 1, (read_St + i)->password);
				fprintf(stdout, "[%d] First name: %s", i + 1, (read_St + i)->f_Name);
				fprintf(stdout, "[%d] Last name: %s\n", i + 1, (read_St + i)->l_Name);				
			}
			fprintf(stdout, "\nEnd of list! Continue...\n");
			_getch();
			fclose(read);
			free(read_St);
			return;
		}
		case 3: {
			int asc_Desc, i;
			do {
				system("cls");
				printf("\n\t"RED"Sort admins by first name:\n\n"ESC"[1] Ascending\n[2] Descending\n\nChoice: ");
				scanf("%d", &asc_Desc);
			} while (asc_Desc < 1 || asc_Desc > 2);

			fseek(read, sizeof(int), SEEK_SET);
			fread(read_St, sizeof(ADMINS), num_Admin, read);
			if (asc_Desc == 1) {
				qsort(read_St, num_Admin, sizeof(ADMINS), comp_Fn_Admin_Asc);
			}
			else {
				qsort(read_St, num_Admin, sizeof(ADMINS), comp_Fn_Admin_Desc);
			}

			system("cls");
			printf("\n\tNumber of "RED"admins"ESC": %d\n\n", num_Admin);
			for (i = 0; i < num_Admin; i++) {
				fprintf(stdout, "[%d] ID: %d\n", i + 1, (read_St + i)->ID);
				fprintf(stdout, "[%d] Username: %s", i + 1, (read_St + i)->username);
				fprintf(stdout, "[%d] Password: %s", i + 1, (read_St + i)->password);
				fprintf(stdout, "[%d] First name: %s", i + 1, (read_St + i)->f_Name);
				fprintf(stdout, "[%d] Last name: %s\n", i + 1, (read_St + i)->l_Name);
			}
			fprintf(stdout, "\nEnd of list! Continue...\n");
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

void search_Admins(void) {

	//enter from admin_Edit_Board
	FILE* search = NULL;
	search = fopen("admins.bin", "rb");
	if (search == NULL) {
		system("cls");
		printf("\n\t\t"RED"Error!"ESC"\nThere are no admins, for now...\n");
		_getch();
		return;
	}

	int search_Choice;
	do {
		system("cls");
		printf("\n\t"RED"Search admins by:\n\n"ESC"[1] ID\n[2] Username\n[3] First name\n[4] Last name\n[5] Return to edit panel\n\nChoice: ");
		scanf("%d", &search_Choice);
	} while (search_Choice < 1 || search_Choice > 5);

	ADMINS* read_St = NULL;
	int i, adm_Num, flag = 0;
	fread(&adm_Num, sizeof(int), 1, search);
	read_St = (ADMINS*)calloc(adm_Num, sizeof(ADMINS));
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
			for (i = 0; i < adm_Num; i++) {
				fread(read_St, sizeof(ADMINS), 1, search);
				if (read_St->ID == id_Srch) {
					fprintf(stdout, "\n[%d] ID: %d\n", i + 1, read_St->ID);
					fprintf(stdout, "[%d] Username: %s", i + 1, read_St->username);
					fprintf(stdout, "[%d] Password: %s", i + 1, read_St->password);
					fprintf(stdout, "[%d] First name: %s", i + 1, read_St->f_Name);
					fprintf(stdout, "[%d] Last name: %s", i + 1, read_St->l_Name);
					flag = 1;
					_getch();
					break;
				}
			}
			if (flag == 0) {
				printf("\nNo admin with ID: [%d].\n", id_Srch);
				_getch();
			}
			free(read_St);
			fclose(search);
			return;
		}
		case 2: {
			char* srch_Usrnm;
			srch_Usrnm = (char*)calloc(30, sizeof(char));
			if (srch_Usrnm == NULL) {
				perror("Memory error");
				exit(EXIT_FAILURE);
			}
			system("cls");
			getchar();
			printf("\nEnter username: ");
			fgets(srch_Usrnm, 29, stdin);
			for (i = 0; i < adm_Num; i++) {
				fread(read_St, sizeof(ADMINS), 1, search);
				if (strcmp(read_St->username, srch_Usrnm) == 0) {
					fprintf(stdout, "\n[%d] ID: %d\n", i + 1, read_St->ID);
					fprintf(stdout, "[%d] Username: %s", i + 1, read_St->username);
					fprintf(stdout, "[%d] Password: %s", i + 1, read_St->password);
					fprintf(stdout, "[%d] First name: %s", i + 1, read_St->f_Name);
					fprintf(stdout, "[%d] Last name: %s", i + 1, read_St->l_Name);
					flag = 1;
					_getch();
					break;
				}
			}
			if (flag == 0) {
				*(srch_Usrnm + (strlen(srch_Usrnm) - 1)) = 0;
				printf("\nNo admin with username: [%s].\n", srch_Usrnm);
				_getch();
			}
			free(read_St);
			free(srch_Usrnm);
			fclose(search);
			return;
		}
		case 3: {
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
			for (i = 0; i < adm_Num; i++) {
				fread(read_St, sizeof(ADMINS), 1, search);
				if (strcmp(read_St->f_Name, srch_Fnm) == 0) {
					fprintf(stdout, "\n[%d] ID: %d\n", i + 1, read_St->ID);
					fprintf(stdout, "[%d] Username: %s", i + 1, read_St->username);
					fprintf(stdout, "[%d] Password: %s", i + 1, read_St->password);
					fprintf(stdout, "[%d] First name: %s", i + 1, read_St->f_Name);
					fprintf(stdout, "[%d] Last name: %s", i + 1, read_St->l_Name);
					flag = 1;
					_getch();
				}
			}
			if (flag == 0) {
				*(srch_Fnm + (strlen(srch_Fnm) - 1)) = 0;
				printf("\nNo admin with first name: [%s].\n", srch_Fnm);
				_getch();
			}
			free(read_St);
			free(srch_Fnm);
			fclose(search);
			return;
		}
		case 4: {
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
			for (i = 0; i < adm_Num; i++) {
				fread(read_St, sizeof(ADMINS), 1, search);
				if (strcmp(read_St->l_Name, srch_Lnm) == 0) {
					fprintf(stdout, "\n[%d] ID: %d\n", i + 1, read_St->ID);
					fprintf(stdout, "[%d] Username: %s", i + 1, read_St->username);
					fprintf(stdout, "[%d] Password: %s", i + 1, read_St->password);
					fprintf(stdout, "[%d] First name: %s", i + 1, read_St->f_Name);
					fprintf(stdout, "[%d] Last name: %s", i + 1, read_St->l_Name);
					_getch();
					flag = 1;
				}
			}
			if (flag == 0) {
				*(srch_Lnm + (strlen(srch_Lnm) - 1)) = 0;
				printf("\nNo admin with last name: [%s].\n", srch_Lnm);
				_getch();
			}
			free(read_St);
			free(srch_Lnm);
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

void member_Input(void) {

	//enter from member_Edit_Board
	MEMBERS* member = NULL;
	member = (MEMBERS*)calloc(1, sizeof(MEMBERS));
	if (member == NULL) {
		perror("Struct error");
		exit(EXIT_FAILURE);
	}
	FILE* member_In = NULL;
	member_In = fopen("members.bin", "r+b");
	if (member_In == NULL) {
		member_In = fopen("members.bin", "wb");
		if (member_In == NULL) {
			perror("File error");
			exit(EXIT_FAILURE);
		}
		system("cls");
		printf("\n\tEntering 1. "BLUE"member"ESC".\n\nEnter ID: ");
		scanf("%d", &member->ID); getchar();
		printf("Enter username: ");
		fgets(member->username, 29, stdin);
		printf("Enter password: ");
		fgets(member->password, 29, stdin);
		printf("Enter first name: ");
		fgets(member->f_Name, 29, stdin);
		printf("Enter last name: ");
		fgets(member->l_Name, 29, stdin);
		printf("Enter contact: ");
		fgets(member->contact, 49, stdin);
		int mem_Num = 1;
		fwrite(&mem_Num, sizeof(int), 1, member_In);
		fwrite(member, sizeof(MEMBERS), 1, member_In);
		fclose(member_In);
		free(member);		
		return;
	}
	else {
		int mem_Num;
		fread(&mem_Num, sizeof(int), 1, member_In);
		mem_Num++;
		system("cls");
		printf("\n\tEntering %d. "BLUE"member"ESC".\n\nEnter ID: ", mem_Num);
		scanf("%d", &member->ID); getchar();
		printf("Enter username: ");
		fgets(member->username, 29, stdin);
		printf("Enter password: ");
		fgets(member->password, 29, stdin);
		printf("Enter first name: ");
		fgets(member->f_Name, 29, stdin);
		printf("Enter last name: ");
		fgets(member->l_Name, 29, stdin);
		printf("Enter contact: ");
		fgets(member->contact, 49, stdin);		
		rewind(member_In);
		fwrite(&mem_Num, sizeof(int), 1, member_In);
		fseek(member_In, sizeof(int) + ((mem_Num - 1) * sizeof(MEMBERS)), SEEK_SET);
		fwrite(member, sizeof(MEMBERS), 1, member_In);
		fclose(member_In);
		free(member);
		return;
	}
}

void del_Members(void) {
	
	//enter from member_Edit_Board
	FILE* read_Mems = NULL;
	read_Mems = fopen("members.bin", "rb");
	if (read_Mems == NULL) {
		system("cls");
		printf("\n\t\t"RED"Error!"ESC"\nThere are no members, for now...\n");
		_getch();
		return;
	}

	int rem_By, num;
	do {
		system("cls");
		printf("\n\tRemoving members "RED"[BE CAREFUL!]\n\n"ESC"[1] Remove by ID\n[2] Remove by username\n[3] Return\n\nChoice: ");
		scanf("%d", &rem_By);
	} while (rem_By < 1 || rem_By > 3);


	FILE* tmp_Pntr = NULL;
	tmp_Pntr = fopen("tmp.bin", "wb");
	if (tmp_Pntr == NULL) {
		printf("File error");
		exit(EXIT_FAILURE);
	}

	fread(&num, sizeof(int), 1, read_Mems);
	MEMBERS* deletion = NULL;
	deletion = (MEMBERS*)calloc(num, sizeof(MEMBERS));
	if (deletion == NULL) {
		perror("Struct error");
		exit(EXIT_FAILURE);
	}

	switch (rem_By) {
		case 1: {
			int dlt_ID, found = 0, helping;
			printf("Enter ID to delete: ");
			scanf("%d", &dlt_ID);

			helping = num - 1;
			fwrite(&helping, sizeof(int), 1, tmp_Pntr);

			for (int i = 0; i < num; i++) {
				fread(deletion, sizeof(MEMBERS), 1, read_Mems);
				if (deletion->ID == dlt_ID) {
					found = 1;
				}
				else {
					fwrite(deletion, sizeof(MEMBERS), 1, tmp_Pntr);
				}
			}

			if (found != 1) {
				system("cls");
				printf("\n\tMember with ID [%d] was not found.\n", dlt_ID);
				fclose(read_Mems);
				fclose(tmp_Pntr);
				free(deletion);
				_getch();
			}
			else {
				system("cls");
				printf("\n\tMember with ID [%d] was "BRED"removed"ESC".\n", dlt_ID);
				_getch();
				fclose(read_Mems);
				fclose(tmp_Pntr);
				free(deletion);
				if (helping == 0) {
					remove("members.bin");
					remove("tmp.bin");
					printf("\n\tThere are no "BLUE"members"ESC" left.\n");
					_getch();
				}
				else {
					remove("members.bin");
					rename("tmp.bin", "members.bin");
				}
			}
			return;
		}
		case 2: {
			char* dlt_Un;
			int found = 0, helping;
			dlt_Un = (char*)calloc(30, sizeof(char));
			if (dlt_Un == NULL) {
				perror("Memory error");
				exit(EXIT_FAILURE);
			}
			getchar();
			printf("Enter username to delete: ");
			fgets(dlt_Un, 29, stdin);

			helping = num - 1;
			fwrite(&helping, sizeof(int), 1, tmp_Pntr);

			for (int i = 0; i < num; i++) {
				fread(deletion, sizeof(MEMBERS), 1, read_Mems);
				if (strcmp(deletion->username, dlt_Un) == 0) {
					found = 1;
				}
				else {
					fwrite(deletion, sizeof(MEMBERS), 1, tmp_Pntr);
				}
			}

			if (found != 1) {
				system("cls");
				*(dlt_Un + (strlen(dlt_Un) - 1)) = 0;
				printf("\n\tMember with username [%s] was not found.\n", dlt_Un);
				fclose(read_Mems);
				fclose(tmp_Pntr);
				free(deletion);
				free(dlt_Un);
				_getch();
			}
			else {
				system("cls");
				*(dlt_Un + (strlen(dlt_Un) - 1)) = 0;
				printf("\n\tMember with username [%s] was "BRED"removed"ESC".\n", dlt_Un);
				_getch();
				fclose(read_Mems);
				fclose(tmp_Pntr);
				free(deletion);
				free(dlt_Un);
				if (helping == 0) {
					remove("members.bin");
					remove("tmp.bin");
					printf("\n\tThere are no "BLUE"members"ESC" left.\n");
					_getch();
				}
				else {
					remove("members.bin");
					rename("tmp.bin", "members.bin");
				}
			}
			return;
		}
		case 3: {
			free(deletion);
			fclose(read_Mems);
			fclose(tmp_Pntr);
			return;
		}
	}
}

void list_Members(void) {

	//enter from member_Edit_Board
	FILE* read = NULL;
	read = fopen("members.bin", "rb");
	if (read == NULL) {
		system("cls");
		printf("\n\t\t"RED"Error!"ESC"\nThere are no members, for now...\n");
		_getch();
		return;
	}

	int list_Choice, mem_Num;
	do {
		system("cls");
		printf("\n\t"BLUE"List members by:\n\n"ESC"[1] ID\n[2] Username\n[3] First name\n[4] Return to edit panel\n\nChoice: ");
		scanf("%d", &list_Choice);
	} while (list_Choice < 1 || list_Choice > 4);


	MEMBERS* read_St = NULL;
	fread(&mem_Num, sizeof(int), 1, read);
	read_St = (MEMBERS*)calloc(mem_Num, sizeof(MEMBERS));
	if (read_St == NULL) {
		perror("Struct error");
		exit(EXIT_FAILURE);
	}

	switch (list_Choice) {
		case 1: {
			int asc_Desc, i;
			do {
				system("cls");
				printf("\n\t"BLUE"Sort members by ID:\n\n"ESC"[1] Ascending\n[2] Descending\n\nChoice: ");
				scanf("%d", &asc_Desc);
			} while (asc_Desc < 1 || asc_Desc > 2);

			fseek(read, sizeof(int), SEEK_SET);
			fread(read_St, sizeof(MEMBERS), mem_Num, read);
			if (asc_Desc == 1) {
				qsort(read_St, mem_Num, sizeof(MEMBERS), comp_ID_Member_Asc);
			}
			else {
				qsort(read_St, mem_Num, sizeof(MEMBERS), comp_ID_Member_Desc);
			}

			system("cls");
			printf("\n\tNumber of "BLUE"members"ESC": %d\n\n", mem_Num);
			for (i = 0; i < mem_Num; i++) {
				fprintf(stdout, "[%d] ID: %d\n", i + 1, (read_St + i)->ID);
				fprintf(stdout, "[%d] Username: %s", i + 1, (read_St + i)->username);
				fprintf(stdout, "[%d] Password: %s", i + 1, (read_St + i)->password);
				fprintf(stdout, "[%d] First name: %s", i + 1, (read_St + i)->f_Name);
				fprintf(stdout, "[%d] Last name: %s", i + 1, (read_St + i)->l_Name);
				fprintf(stdout, "[%d] Contact: %s\n", i + 1, (read_St + i)->contact);
			}
			fprintf(stdout, "\nEnd of list! Continue...\n");
			_getch();
			fclose(read);
			free(read_St);
			return;
		}
		case 2: {
			int asc_Desc, i;
			do {
				system("cls");
				printf("\n\t"BLUE"Sort members by username:\n\n"ESC"[1] Ascending\n[2] Descending\n\nChoice: ");
				scanf("%d", &asc_Desc);
			} while (asc_Desc < 1 || asc_Desc > 2);

			fseek(read, sizeof(int), SEEK_SET);
			fread(read_St, sizeof(MEMBERS), mem_Num, read);
			if (asc_Desc == 1) {
				qsort(read_St, mem_Num, sizeof(MEMBERS), comp_Un_Member_Asc);
			}
			else {
				qsort(read_St, mem_Num, sizeof(MEMBERS), comp_Un_Member_Desc);
			}
			system("cls");
			printf("\n\tNumber of "BLUE"members"ESC": %d\n\n", mem_Num);
			for (i = 0; i < mem_Num; i++) {
				fprintf(stdout, "[%d] ID: %d\n", i + 1, (read_St + i)->ID);
				fprintf(stdout, "[%d] Username: %s", i + 1, (read_St + i)->username);
				fprintf(stdout, "[%d] Password: %s", i + 1, (read_St + i)->password);
				fprintf(stdout, "[%d] First name: %s", i + 1, (read_St + i)->f_Name);
				fprintf(stdout, "[%d] Last name: %s\n", i + 1, (read_St + i)->l_Name);
			}
			fprintf(stdout, "\nEnd of list! Continue...\n");
			_getch();
			fclose(read);
			free(read_St);
			return;
		}
		case 3: {
			int asc_Desc, i;
			do {
				system("cls");
				printf("\n\t"BLUE"Sort members by first name:\n\n"ESC"[1] Ascending\n[2] Descending\n\nChoice: ");
				scanf("%d", &asc_Desc);
			} while (asc_Desc < 1 || asc_Desc > 2);
						
			fseek(read, sizeof(int), SEEK_SET);
			fread(read_St, sizeof(MEMBERS), mem_Num, read);
			if (asc_Desc == 1) {
				qsort(read_St, mem_Num, sizeof(MEMBERS), comp_Fn_Member_Asc);
			}
			else {
				qsort(read_St, mem_Num, sizeof(MEMBERS), comp_Fn_Member_Desc);
			}
			system("cls");
			printf("\n\tNumber of "BLUE"members"ESC": %d\n\n", mem_Num);
			for (i = 0; i < mem_Num; i++) {
				fprintf(stdout, "[%d] ID: %d\n", i + 1, (read_St + i)->ID);
				fprintf(stdout, "[%d] Username: %s", i + 1, (read_St + i)->username);
				fprintf(stdout, "[%d] Password: %s", i + 1, (read_St + i)->password);
				fprintf(stdout, "[%d] First name: %s", i + 1, (read_St + i)->f_Name);
				fprintf(stdout, "[%d] Last name: %s\n", i + 1, (read_St + i)->l_Name);
			}
			fprintf(stdout, "\nEnd of list! Continue...\n");
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

void search_Members(void) {

	//enter from member_Edit_Board
	FILE* search = NULL;
	search = fopen("members.bin", "rb");
	if (search == NULL) {
		system("cls");
		printf("\n\t\t"RED"Error!"ESC"\nThere are no members, for now...\n");
		_getch();
		return;
	}

	int search_Choice;
	do {
		system("cls");
		printf("\n\t"BLUE"Search members by:\n\n"ESC"[1] ID\n[2] Username\n[3] First name\n[4] Last name\n[5] Return to edit panel\n\nChoice: ");
		scanf("%d", &search_Choice);
	} while (search_Choice < 1 || search_Choice > 5);


	MEMBERS* read_St = NULL;
	int i, mem_Num;
	fread(&mem_Num, sizeof(int), 1, search);
	read_St = (MEMBERS*)calloc(mem_Num, sizeof(MEMBERS));
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
			for (i = 0; i < mem_Num; i++) {
				fread(read_St, sizeof(MEMBERS), 1, search);
				if (read_St->ID == id_Srch) {
					fprintf(stdout, "\n[%d] ID: %d\n", i + 1, read_St->ID);
					fprintf(stdout, "[%d] Username: %s", i + 1, read_St->username);
					fprintf(stdout, "[%d] Password: %s", i + 1, read_St->password);
					fprintf(stdout, "[%d] First name: %s", i + 1, read_St->f_Name);
					fprintf(stdout, "[%d] Last name: %s", i + 1, read_St->l_Name);
					flag = 1;
					_getch();
					break;
				}
			}
			if (flag == 0) {
				printf("\nNo member with ID: [%d].\n", id_Srch);
				_getch();
			}
			free(read_St);
			fclose(search);
			return;
		}
		case 2: {
			int flag = 0;
			char* srch_Usrnm;
			srch_Usrnm = (char*)calloc(30, sizeof(char));
			if (srch_Usrnm == NULL) {
				perror("Memory error");
				exit(EXIT_FAILURE);
			}
			system("cls");
			getchar();
			printf("\nEnter username: ");
			fgets(srch_Usrnm, 29, stdin);
			for (i = 0; i < mem_Num; i++) {
				fread(read_St, sizeof(MEMBERS), 1, search);
				if (strcmp(read_St->username, srch_Usrnm) == 0) {
					fprintf(stdout, "\n[%d] ID: %d\n", i + 1, read_St->ID);
					fprintf(stdout, "[%d] Username: %s", i + 1, read_St->username);
					fprintf(stdout, "[%d] Password: %s", i + 1, read_St->password);
					fprintf(stdout, "[%d] First name: %s", i + 1, read_St->f_Name);
					fprintf(stdout, "[%d] Last name: %s", i + 1, read_St->l_Name);
					flag = 1;
					_getch();
					break;
				}
			}
			if (flag == 0) {
				*(srch_Usrnm + (strlen(srch_Usrnm) - 1)) = 0;
				printf("\nNo member with username: [%s].\n", srch_Usrnm);
				_getch();
			}
			free(read_St);
			free(srch_Usrnm);
			fclose(search);
			return;
		}
		case 3: {
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
			for (i = 0; i < mem_Num; i++) {
				fread(read_St, sizeof(MEMBERS), 1, search);
				if (strcmp(read_St->f_Name, srch_Fnm) == 0) {
					fprintf(stdout, "\n[%d] ID: %d\n", i + 1, read_St->ID);
					fprintf(stdout, "[%d] Username: %s", i + 1, read_St->username);
					fprintf(stdout, "[%d] Password: %s", i + 1, read_St->password);
					fprintf(stdout, "[%d] First name: %s", i + 1, read_St->f_Name);
					fprintf(stdout, "[%d] Last name: %s", i + 1, read_St->l_Name);
					flag = 1;
					_getch();
				}
			}
			if (flag == 0) {
				*(srch_Fnm + (strlen(srch_Fnm) - 1)) = 0;
				printf("\nNo member with first name: [%s].\n", srch_Fnm);
				_getch();
			}
			free(read_St);
			free(srch_Fnm);
			fclose(search);
			return;
		}
		case 4: {
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
			for (i = 0; i < mem_Num; i++) {
				fread(read_St, sizeof(MEMBERS), 1, search);
				if (strcmp(read_St->l_Name, srch_Lnm) == 0) {
					fprintf(stdout, "\n[%d] ID: %d\n", i + 1, read_St->ID);
					fprintf(stdout, "[%d] Username: %s", i + 1, read_St->username);
					fprintf(stdout, "[%d] Password: %s", i + 1, read_St->password);
					fprintf(stdout, "[%d] First name: %s", i + 1, read_St->f_Name);
					fprintf(stdout, "[%d] Last name: %s", i + 1, read_St->l_Name);
					_getch();
					flag = 1;
				}
			}
			if (flag == 0) {
				*(srch_Lnm + (strlen(srch_Lnm) - 1)) = 0;
				printf("\nNo member with last name: [%s].\n", srch_Lnm);
				_getch();
			}
			free(read_St);
			free(srch_Lnm);
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

void admin_Edit_Board(void) {

	//enter from admins_Menu
	int admin_Edit;
	while (1) {
		do {
			system("cls");
			printf("\t  Logged in as: "RED"[%s]"ESC"\n\n\t"RED"Admin editing\n\n"ESC"[1] Add an admin\n[2] Remove an admin\n[3] List admins\n[4] Search admins\n[5] Return\n\nChoice: ", logged_As);
			scanf("%d", &admin_Edit);
		} while (admin_Edit < 1 || admin_Edit > 5);

		switch (admin_Edit) {
		case 1: {
			admin_Input();
			break;
		}
		case 2: {
			del_Admins();
			break;
		}
		case 3: {
			list_Admins();
			break;
		}
		case 4: {
			search_Admins();
			break;
		}
		case 5: {
			return;
		}
		}
	}
}

void member_Edit_Board(void) {

	//enter from admins_Menu
	int mem_Edit;
	while (1) {
		do {
			system("cls");
			printf("\t  Logged in as: "RED"[% s]"ESC"\n\n\t"BLUE"Member editing\n\n"ESC"[1] Add a member\n[2] Remove a member\n[3] List members\n[4] Search members\n[5] Return\n\nChoice: ", logged_As);
			scanf("%d", &mem_Edit);
		} while (mem_Edit < 1 || mem_Edit > 5);
		switch (mem_Edit) {
		case 1: {
			member_Input();
			break;
		}
		case 2: {
			del_Members();
			break;
		}
		case 3: {
			list_Members();
			break;
		}
		case 4: {
			search_Members();
			break;
		}
		case 5: {
			return;
		}
		}
	}
}

void library_Edit_Board(void) {

	//enter from admins_Menu
	int lib_Ed;
	while (1) {
		do {
			system("cls");
			printf("\t  Logged in as: "RED"[%s]"ESC"\n\n\t"BYLW"Library editing\n\n"ESC"[1] "BRED"Characters"ESC"\n[2] "CYN"Locations"ESC"\n[3] "BGRN"Music"ESC"\n[4] "YLW"Objects"ESC"\n[5] "RED"Rituals & Spells"ESC"\n[6] "MNG"Seasons"ESC"\n[7] Return\n\nChoice: ", logged_As);
			scanf("%d", &lib_Ed);
		} while (lib_Ed < 1 || lib_Ed > 7);
		switch (lib_Ed) {
		case 1: {
			chars_Edit_Menu();
			break;
		}
		case 2: {
			locs_Edit_Menu();
			break;
		}
		case 3: {
			music_Edit_Menu();
			break;
		}
		case 4: {
			object_Edit_Menu();
			break;
		}
		case 5: {
			rit_Spell_Edit_Menu();
			break;
		}
		case 6: {
			seas_Edit_Menu();
			break;
		}
		case 7: {
			return;
		}
		}
	}
}