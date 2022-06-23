#include "header.h"
#include "structs.h"
#include "colors.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

void initial_Menu(void) {

	int choice;

	logged_As = (char*)calloc(30, sizeof(char));
	if (logged_As == NULL) {
		perror("Memory error");
		exit(EXIT_FAILURE);
	}

	while (1) {
		do{
			system("cls");
			printf("\n\t"YLW"Welcome to the Supernatural!"ESC"\n\n[1] "RED"I am an admin"ESC"\n[2] "BLUE"I am a member"ESC"\n[3] "BBLUE"How to use the board"ESC"\n[4] "BCYN"Exit"ESC"\n\nChoice: ");
			if(scanf("%d", &choice) <= 0) exit(EXIT_FAILURE);
		} while (choice < 1 || choice > 4);

		switch (choice) {
			case 1:{
				admins_Login();
				break;
			}
			case 2:{
				members_Login();
				break;
			}
			case 3: {
				usage();
				break;
			}
			case 4: {
				free(logged_As);
				exit(EXIT_SUCCESS);
			}
		}
	}
}

void admins_Login(void) {

	//enter from initial_Menu
	FILE* check_F_Ad = NULL;
	check_F_Ad = fopen("admins.bin", "rb");
	if (check_F_Ad == NULL){
		system("cls");
		printf("\n\t   There are no "RED"admins"ESC".\n\tPress any key to create one.\n");
		c = _getch();
		admin_Input();
	}
	else {
		int adm_Num, i, flag = 0;
		fread(&adm_Num, sizeof(int), 1, check_F_Ad);
		ADMINS* admin_Struct = NULL;
		admin_Struct = (ADMINS*)calloc(adm_Num, sizeof(ADMINS));
		if (admin_Struct == NULL) {
			perror("Struct error");
			exit(EXIT_FAILURE);
		}
		char* username, * password;		
		username = (char*)calloc(30, sizeof(char));
		if (username == NULL) {
			perror("Memory error");
			exit(EXIT_FAILURE);
		}
		password = (char*)calloc(30, sizeof(char));
		if (password == NULL) {
			perror("Memory error");
			exit(EXIT_FAILURE);
		}

		system("cls");
		printf("\n\tWelcome to the "RED"admin"ESC" login!\n\nUsername: ");
		c = getchar();
		fgets(username, 29, stdin);
		printf("Password: ");
		for (i = 0; *(password + i - 1) != '\r'; i++) {
			*(password + i) = _getch();
			printf("*");
		}
		*(password + i - 1) = '\n';
		fread(admin_Struct, sizeof(ADMINS), adm_Num, check_F_Ad);
		for (i = 0; i < adm_Num; i++) {
			if (strcmp((admin_Struct + i)->username, username) == 0) {
				if (strcmp((admin_Struct + i)->password, password) == 0) {
					flag = 2;
					break;
				}
				else {
					flag = 1;
					break;
				}
			}
			else flag = 0;
		}
		if (flag == 2) {
			strcpy(logged_As, username);
			*(logged_As + (strlen(logged_As) - 1)) = 0;
			free(username);
			free(password);
			free(admin_Struct);
			fclose(check_F_Ad);
			admin_Logged = 1;
			admins_Menu();
		}
		else if (flag == 1) {
			free(username);
			free(password);
			free(admin_Struct);
			fclose(check_F_Ad);
			printf("\n\tWrong password!\n");
			c = _getch();
			return;
		}
		else if (flag == 0) {
			free(username);
			free(password);
			free(admin_Struct);
			fclose(check_F_Ad);
			printf("\n\t"RED"Admin "ESC"does not exist!\n");
			c = _getch();
			return;
		}
	}
}

void members_Login(void) {

	//enter from initial_Menu
	FILE* check_F_Mems = NULL;
	check_F_Mems = fopen("members.bin", "rb");
	if (check_F_Mems == NULL){
		system("cls");
		printf("\n\t"RED"Admins "ESC"haven't added any "BLUE"members "ESC"yet.\n");
		c = _getch();
		return;
	}
	else {
		int mem_Num, i, flag = 0;
		fread(&mem_Num, sizeof(int), 1, check_F_Mems);
		MEMBERS* member_Struct = NULL;
		member_Struct = (MEMBERS*)calloc(mem_Num, sizeof(MEMBERS));
		if (!member_Struct) exit(EXIT_FAILURE);
		char* username, * password;		
		username = (char*)calloc(30, sizeof(char));
		if (!username)exit(EXIT_FAILURE);
		password = (char*)calloc(30, sizeof(char));
		if (!password) exit(EXIT_FAILURE);

		system("cls");
		printf("\n\tWelcome to the "BLUE"member"ESC" login!\n\nUsername: ");
		c = getchar();
		fgets(username, 29, stdin);
		printf("Password: ");
		for (i = 0; *(password + i - 1) != '\r'; i++) {
			*(password + i) = _getch();
			printf("*");
		}
		*(password + i - 1) = '\n';
		fread(member_Struct, sizeof(MEMBERS), mem_Num, check_F_Mems);
		for (i = 0; i < mem_Num; i++) {
			if (strcmp((member_Struct + i)->username, username) == 0) {
				if (strcmp((member_Struct + i)->password, password) == 0) {
					flag = 2;
					break;
				}
				else {
					flag = 1;
					break;
				}
			}
			else flag = 0;
		}
		if (flag == 2) {
			strcpy(logged_As, username);
			*(logged_As + (strlen(logged_As) - 1)) = 0;
			admin_Logged = 0;
			free(username);
			free(password);
			free(member_Struct);
			fclose(check_F_Mems);
			members_Menu();
		}
		else if (flag == 1) {
			free(username);
			free(password);
			free(member_Struct);
			fclose(check_F_Mems);
			printf("\n\tWrong password!\n");
			c = _getch();
			return;
		}
		else if (flag == 0) {
			free(username);
			free(password);
			free(member_Struct);
			fclose(check_F_Mems);
			printf("\n\t"BLUE"Member "ESC"does not exist!\n");
			c = _getch();
			return;
		}
	}
}

void usage(void) {

	char c;
	system("cls");
	printf("\n\tWelcome, fellow traveler!\n\nFirst of all, You should login! You are either "RED"admin"ESC" or "BLUE"member"ESC". After logging You will be presented");
	printf("\nwith either "RED"edit board"ESC" or "BLUE"member board"ESC" in which You can choose between options.");
	printf("\n\nAs "RED"admin"ESC" You can add, remove, edit, list (sort) or sarch different aspects of the Supernatural.");
	printf("\nAs "BLUE"member"ESC" You can list (sort), search or edit different aspects of the Supernatural.");
	printf("\n\nAspects include and ARE limited to:\n\n");
	printf(BRED"[1] Characters"ESC"\n"CYN"[2] Locations"ESC"\n"BGRN"[3] Music"ESC"\n"YLW"[4] Objects"ESC"\n"RED"[5] Rituals & Spells"ESC"\n"MNG"[6] Seasons"ESC);
	printf("\n\nYou can press \""GRN"ESC"ESC"\" to return to login panel, or any other\nkey to read a brief introduction to Supernatural world!\n");

	c = _getch();

	if (c != 27) {
		system("cls");
		printf(BBLUE"\tDEATH"ESC" (talking to "RED"DEAN"ESC" in \"Brother's Keeper\"):\n\nBefore there was light, before there was God and the Archangels, there wasn't nothing.");
		c = _getch();
		printf(" There was the Darkness, a horribly destructive, amoral force that was beaten back by God and his Archangels in a terrible war.");
		c = _getch();
		printf(" God locked the Darkness away where it could do no harm, and he created a Mark that would serve as both lock and key, which he entrusted to his most valued lieutenant, Lucifer.");
		c = _getch();
		printf(" But the Mark began to exert its own will, revealed itself as a curse, and began to corrupt.");
		c = _getch();
		printf(" Lucifer became jealous of man. God banished Lucifer to Hell.");
		c = _getch();
		printf(" Lucifer passed the Mark to Cain, who passed the Mark to you, the proverbial finger in the dike.\n\n");
		c = _getch();
		printf("\t"YLW"Short dialogue between"ESC" "RED"Dean"ESC" "YLW"and"ESC" "BRED"Amara (The Darkness)"ESC" "YLW"explaning her destructiveness...\n\n"ESC);
		c = _getch();
		printf(RED"Dean"ESC": What is it exactly that you want? When you make the world at bliss and at peace, what's in it for you?\n");
		c = _getch();
		printf(BRED"Amara"ESC": What I deserve.");
		c = _getch();
		printf("\n"RED"Dean"ESC": Which is?\n");
		c = _getch();
		printf(BRED"Amara"ESC": Everything.\n");
		c = _getch();
		printf(RED"Dean"ESC": Everything?\n");
		c = _getch();
		printf(BRED"Amara"ESC": I was "GRN"the beginning"ESC", and I will be "CYN"the end"ESC". I will be all that there is.\n\n");
		c = _getch();
		printf("Concluding the short introduction, fans and those yet to be, are thrilled with the series so far...\n");
		c = _getch();
		return;
	}
	else {
		return;
	}
}