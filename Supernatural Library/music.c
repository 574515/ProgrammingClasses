#include "header.h"
#include "structs.h"
#include "colors.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

void music_Edit_Menu(void) {

	//enter from library_Edit_Board
	int choice;
	while (1) {
		if (admin_Logged == 1) {
			do {
				system("cls");
				printf("\t  Logged in as: "RED"[%s]"ESC"\n\n\t"BMNG"Music editing\n\n"ESC"[1] Add music\n[2] Remove music\n[3] Edit music\n[4] List music\n[5] Search music\n[6] Return\n\nChoice: ", logged_As);
				scanf("%d", &choice);
			} while (choice < 1 || choice > 6);
			switch (choice) {
			case 1: {
				add_Music();
				break;
			}
			case 2: {
				del_Music();
				break;
			}
			case 3: {
				edit_Music();
				break;
			}
			case 4: {
				list_Music();
				break;
			}
			case 5: {
				search_Music();
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
				printf("\t  Logged in as: "BLUE"[%s]"ESC"\n\n\t"BMNG"Music\n\n"ESC"[1] List music\n[2] Search music\n[3] Edit music\n[4] Return\n\nChoice: ", logged_As);
				scanf("%d", &choice);
			} while (choice < 1 || choice > 4);
			switch (choice) {
			case 1: {
				list_Music();
				break;
			}
			case 2: {
				search_Music();
				break;
			}
			case 3: {
				edit_Music();
				break;
			}
			case 4: {
				return;
			}
			}
		}
	}
}

void add_Music(void) {

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
		printf("\n\tEntering 1. "BGRN"music track"ESC".\n\nEnter ID: ");
		scanf("%d", &mus_Struc->ID);
		printf("Enter season: ");
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
		printf("\n\tEntering %d. "BGRN"music track"ESC".\n\nEnter ID: ", music_Num);
		scanf("%d", &mus_Struc->ID);
		printf("Enter season: ");
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
	FILE* read_Music = NULL;
	read_Music = fopen("music.bin", "rb");
	if (read_Music == NULL) {
		system("cls");
		printf("\n\t\t"RED"Error!"ESC"\nThere is no music, for now...\n");
		_getch();
		return;
	}

	int rem_By, num;
	do {
		system("cls");
		printf("\t  Logged in as: "RED"[%s]"ESC"\n\n\tRemoving music "RED"[BE CAREFUL!]\n\n"ESC"[1] Remove by ID\n[2] Remove by episode name\n[3] Remove by song name\n[4] Remove by author\n[5] Return\n\nChoice: ", logged_As);
		scanf("%d", &rem_By);
	} while (rem_By < 1 || rem_By > 5);

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
		int dlt_ID, found = 0, helping = 0, count_Del = 0;
		printf("\nEnter season to delete: ");
		scanf("%d", &dlt_ID);

		helping = num;
		fwrite(&helping, sizeof(int), 1, tmp_Pntr);

		for (int i = 0; i < num; i++) {
			fread(deletion, sizeof(MUSIC), 1, read_Music);
			if (deletion->ID == dlt_ID) {
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
			printf("\n\tSeason [%d] was not found.\n", dlt_ID);
			fclose(read_Music);
			fclose(tmp_Pntr);
			free(deletion);
			_getch();
		}
		else {
			system("cls");
			printf("\n\tWhole season [%d] was "BGRN"removed"ESC".\n", dlt_ID);
			_getch();
			fclose(read_Music);
			fclose(tmp_Pntr);
			free(deletion);
			if (helping == 0) {
				remove("music.bin");
				remove("tmp.bin");
				printf("\n\tThere is no "BGRN"music"ESC" left.\n");
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
			printf("\n\tMusic from episode [%s] was "BGRN"removed"ESC".\n", dlt_By_Ep_Name);
			_getch();
			fclose(read_Music);
			fclose(tmp_Pntr);
			free(dlt_By_Ep_Name);
			free(deletion);

			if (helping == 0) {
				remove("music.bin");
				remove("tmp.bin");
				printf("\n\tThere is no "BGRN"music"ESC" left.\n");
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
			printf("\n\tSong [%s] was "BGRN"removed"ESC".\n", dlt_By_Sng_Nm);
			_getch();
			fclose(read_Music);
			fclose(tmp_Pntr);
			free(deletion);
			free(dlt_By_Sng_Nm);

			if (helping == 0) {
				remove("music.bin");
				remove("tmp.bin");
				printf("\n\tThere is no "BGRN"music"ESC" left.\n");
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
			printf("\n\tMusic by [%s] was not found.\n", dlt_By_Author);
			fclose(read_Music);
			fclose(tmp_Pntr);
			free(deletion);
			free(dlt_By_Author);
			_getch();
		}
		else {
			system("cls");
			*(dlt_By_Author + (strlen(dlt_By_Author) - 1)) = 0;
			printf("\n\tMusic by [%s] was "BGRN"removed"ESC".\n", dlt_By_Author);
			_getch();
			fclose(read_Music);
			fclose(tmp_Pntr);
			free(deletion);
			free(dlt_By_Author);

			if (helping == 0) {
				remove("music.bin");
				remove("tmp.bin");
				printf("\n\tThere is no "BGRN"music"ESC" left.\n");
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

void edit_Music(void) {

	//enter from music_Edit_Menu
	FILE* read_Music = NULL;
	read_Music = fopen("music.bin", "rb");
	if (read_Music == NULL) {
		system("cls");
		printf("\n\t\t"RED"Error!"ESC"\nThere is no music, for now...\n");
		_getch();
		return;
	}

	int edit_By, num;

	do {
		system("cls");
		if (admin_Logged == 1) {
			printf("\t  Logged in as: "RED"[%s]"ESC"\n\n\tEditing music "RED"[BE CAREFUL!]\n\n"ESC"[1] Edit by ID\n[2] Return\n\nChoice: ", logged_As);
		}
		else {
			printf("\t  Logged in as: "BLUE"[%s]"ESC"\n\n\tEditing music "RED"[BE CAREFUL!]\n\n"ESC"[1] Edit by ID\n[2] Return\n\nChoice: ", logged_As);
		}
		scanf("%d", &edit_By);
	} while (edit_By < 1 || edit_By > 2);

	FILE* tmp_Pntr = NULL;
	tmp_Pntr = fopen("tmp.bin", "wb");
	if (tmp_Pntr == NULL) {
		printf("File error");
		exit(EXIT_FAILURE);
	}

	fread(&num, sizeof(int), 1, read_Music);
	MUSIC* musc = NULL;
	musc = (MUSIC*)calloc(num, sizeof(MUSIC));
	if (musc == NULL) {
		perror("Struct error");
		exit(EXIT_FAILURE);
	}
	fread(musc, sizeof(MUSIC), num, read_Music);

	MUSIC* edit = NULL;
	edit = (MUSIC*)calloc(1, sizeof(MUSIC));
	if (edit == NULL) {
		perror("Struct error");
		exit(EXIT_FAILURE);
	}

	switch (edit_By) {
	case 1: {
		int i, edit_ID, flag = 0;
		system("cls");
		printf("\n\t"BGRN"Edit music by ID:\n\n"ESC"Enter ID: ");
		scanf("%d", &edit_ID);
		for (i = 0; i < num; i++) {
			if ((musc + i)->ID == edit_ID) {
				flag = 1;
				break;
			}
		}
		if (flag == 0) {
			system("cls");
			printf("\nNo music with ID [%d].\n", edit_ID);
			_getch();
			fclose(read_Music);
			fclose(tmp_Pntr);
			free(musc);
			free(edit);
			return;
		}
		else {
			printf("\nEnter new tracke ID: ");
			scanf("%d", &edit->ID);
			printf("Enter season: ");
			scanf("%d", &edit->season);
			printf("Enter episode name: "); getchar();
			fgets(edit->episode_Name, 99, stdin);
			printf("Enter song name: ");
			fgets(edit->song_Name, 99, stdin);
			printf("Enter author: ");
			fgets(edit->author, 99, stdin);
			fwrite(&num, sizeof(int), 1, tmp_Pntr);
			for (i = 0; i < num; i++) {
				if ((musc + i)->ID == edit_ID) {
					fwrite(edit, sizeof(MUSIC), 1, tmp_Pntr);
				}
				else {
					fwrite(musc, sizeof(MUSIC), 1, tmp_Pntr);
				}
			}

			system("cls");
			printf("\n\tMusic track with ID [%d] was "BGRN"edited"ESC".\n", edit_ID);
			_getch();
			fclose(read_Music);
			fclose(tmp_Pntr);
			free(musc);
			free(edit);
			remove("music.bin");
			rename("tmp.bin", "music.bin");
			return;
		}
	}
	case 2: {
		fclose(read_Music);
		fclose(tmp_Pntr);
		free(musc);
		free(edit);
		return;
	}
	}
}

void list_Music(void) {

	//enter from music_Edit_Menu
	FILE* read = NULL;
	read = fopen("music.bin", "rb");
	if (read == NULL) {
		system("cls");
		printf("\n\t\t"RED"Error!"ESC"\nThere is no music, for now...\n");
		_getch();
		return;
	}

	int list_Choice, music_Num, asc_Desc, i;
	do {
		system("cls");
		if (admin_Logged == 1) {
			printf("\t  Logged in as: "RED"[%s]"ESC"\n\n\t"BGRN"List music by:\n\n"ESC"[1] Season\n[2] Song name\n[3] Author\n[4] Default order\n[5] Return\n\nChoice: ", logged_As);
		}
		else {
			printf("\t  Logged in as: "BLUE"[%s]"ESC"\n\n\t"BGRN"List music by:\n\n"ESC"[1] Season\n[2] Song name\n[3] Author\n[4] Default order\n[5] Return\n\nChoice: ", logged_As);
		}
		scanf("%d", &list_Choice);
	} while (list_Choice < 1 || list_Choice > 5);


	MUSIC* read_St = NULL;
	fread(&music_Num, sizeof(int), 1, read);
	read_St = (MUSIC*)calloc(music_Num, sizeof(MUSIC));
	if (read_St == NULL) {
		perror("Struct error");
		exit(EXIT_FAILURE);
	}

	switch (list_Choice) {
	case 1: {
		do {
			system("cls");
			printf("\n\t"BGRN"Sort music by seasons:\n\n"ESC"[1] Ascending\n[2] Descending\n\nChoice: ");
			scanf("%d", &asc_Desc);
		} while (asc_Desc < 1 || asc_Desc > 2);

		fseek(read, sizeof(int), SEEK_SET);
		fread(read_St, sizeof(MUSIC), music_Num, read);
		if (asc_Desc == 1)
			qsort(read_St, music_Num, sizeof(MUSIC), compare_Season_Asc_Music);
		else
			qsort(read_St, music_Num, sizeof(MUSIC), compare_Season_Desc_Music);
		system("cls");
		printf("\n\tNumber of "BGRN"music tracks"ESC": [%d]\n\n", music_Num);
		for (i = 0; i < music_Num; i++) {
			fprintf(stdout, BMNG"\n[%d] Song ID:"ESC" %d\n", i + 1, (read_St + i)->ID);
			fprintf(stdout, BMNG"[%d] Season:"ESC" %d\n", i + 1, (read_St + i)->season);
			fprintf(stdout, BMNG"[%d] Episode name:"ESC" %s", i + 1, (read_St + i)->episode_Name);
			fprintf(stdout, BMNG"[%d] Song name:"ESC" %s", i + 1, (read_St + i)->song_Name);
			fprintf(stdout, BMNG"[%d] Author:"ESC" %s\n", i + 1, (read_St + i)->author);
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
			printf("\n\t"BGRN"Sort music by song name:\n\n"ESC"[1] Ascending\n[2] Descending\n\nChoice: ");
			scanf("%d", &asc_Desc);
		} while (asc_Desc < 1 || asc_Desc > 2);

		fseek(read, sizeof(int), SEEK_SET);
		fread(read_St, sizeof(MUSIC), music_Num, read);
		if (asc_Desc == 1)
			qsort(read_St, music_Num, sizeof(MUSIC), comp_Song_Name_Asc_Music);
		else
			qsort(read_St, music_Num, sizeof(MUSIC), comp_Song_Name_Desc_Music);
		system("cls");
		printf("\n\tNumber of "BGRN"music tracks"ESC": [%d]\n\n", music_Num);
		for (i = 0; i < music_Num; i++) {
			fprintf(stdout, BMNG"\n[%d] Song ID:"ESC" %d\n", i + 1, (read_St + i)->ID);
			fprintf(stdout, BMNG"[%d] Season:"ESC" %d\n", i + 1, (read_St + i)->season);
			fprintf(stdout, BMNG"[%d] Episode name:"ESC" %s", i + 1, (read_St + i)->episode_Name);
			fprintf(stdout, BMNG"[%d] Song name:"ESC" %s", i + 1, (read_St + i)->song_Name);
			fprintf(stdout, BMNG"[%d] Author:"ESC" %s\n", i + 1, (read_St + i)->author);
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
			printf("\n\t"BGRN"Sort music by author:\n\n"ESC"[1] Ascending\n[2] Descending\n\nChoice: ");
			scanf("%d", &asc_Desc);
		} while (asc_Desc < 1 || asc_Desc > 2);

		fseek(read, sizeof(int), SEEK_SET);
		fread(read_St, sizeof(MUSIC), music_Num, read);
		if (asc_Desc == 1)
			qsort(read_St, music_Num, sizeof(MUSIC), comp_Author_Asc_Music);
		else
			qsort(read_St, music_Num, sizeof(MUSIC), comp_Author_Desc_Music);
		system("cls");
		printf("\n\tNumber of "BGRN"music tracks"ESC": [%d]\n\n", music_Num);
		for (i = 0; i < music_Num; i++) {
			fprintf(stdout, BMNG"\n[%d] Song ID:"ESC" %d\n", i + 1, (read_St + i)->ID);
			fprintf(stdout, BMNG"[%d] Season:"ESC" %d\n", i + 1, (read_St + i)->season);
			fprintf(stdout, BMNG"[%d] Episode name:"ESC" %s", i + 1, (read_St + i)->episode_Name);
			fprintf(stdout, BMNG"[%d] Song name:"ESC" %s", i + 1, (read_St + i)->song_Name);
			fprintf(stdout, BMNG"[%d] Author:"ESC" %s\n", i + 1, (read_St + i)->author);
		}
		fprintf(stdout, "\nEnd of list! Continue...\n");
		_getch();
		fclose(read);
		free(read_St);
		return;
	}
	case 4: {
		fseek(read, sizeof(int), SEEK_SET);
		system("cls");
		fread(read_St, sizeof(MUSIC), music_Num, read);
		printf("\n\tNumber of "BGRN"music tracks"ESC": [%d]\n\n", music_Num);
		for (i = 0; i < music_Num; i++) {
			fprintf(stdout, BMNG"\n[%d] Song ID:"ESC" %d\n", i + 1, (read_St + i)->ID);
			fprintf(stdout, BMNG"[%d] Season:"ESC" %d\n", i + 1, (read_St + i)->season);
			fprintf(stdout, BMNG"[%d] Episode name:"ESC" %s", i + 1, (read_St + i)->episode_Name);
			fprintf(stdout, BMNG"[%d] Song name:"ESC" %s", i + 1, (read_St + i)->song_Name);
			fprintf(stdout, BMNG"[%d] Author:"ESC" %s\n", i + 1, (read_St + i)->author);
		}
		fprintf(stdout, "\nEnd of list! Continue...\n");
		_getch();
		fclose(read);
		free(read_St);
		return;
	}
	case 5: {
		fclose(read);
		free(read_St);
		return; }
	}
}

void search_Music(void) {

	//enter from music_Edit_Menu
	FILE* search = NULL;
	search = fopen("music.bin", "rb");
	if (search == NULL) {
		system("cls");
		printf("\n\t\t"RED"Error!"ESC"\nThere is no music, for now...\n");
		_getch();
		return;
	}

	int search_Choice, i, music_Num, id_Srch, flag = 0;
	do {
		system("cls");
		if (admin_Logged == 1) {
			printf("\t  Logged in as: "RED"[%s]"ESC"\n\n\t"BGRN"Search music by:\n\n"ESC"[1] Season\n[2] Song name\n[3] Author\n[4] Return\n\nChoice: ", logged_As);
		}
		else {
			printf("\t  Logged in as: "BLUE"[%s]"ESC"\n\n\t"BGRN"Search music by:\n\n"ESC"[1] Season\n[2] Song name\n[3] Author\n[4] Return\n\nChoice: ", logged_As);
		}
		scanf("%d", &search_Choice);
	} while (search_Choice < 1 || search_Choice > 4);

	MUSIC* read_St = NULL;
	fread(&music_Num, sizeof(int), 1, search);
	read_St = (MUSIC*)calloc(music_Num, sizeof(MUSIC));
	if (read_St == NULL) {
		perror("Struct error");
		exit(EXIT_FAILURE);
	}

	switch (search_Choice) {
	case 1: {
		system("cls");
		printf("\nEnter season: ");
		scanf("%d", &id_Srch);
		for (i = 0; i < music_Num; i++) {
			fread(read_St, sizeof(MUSIC), 1, search);
			if (read_St->season == id_Srch) {
				fprintf(stdout, BMNG"\n[%d] Song ID:"ESC" %d\n", i + 1, (read_St + i)->ID);
				fprintf(stdout, BMNG"[%d] Season:"ESC" %d\n", i + 1, (read_St + i)->season);
				fprintf(stdout, BMNG"[%d] Episode name:"ESC" %s", i + 1, (read_St + i)->episode_Name);
				fprintf(stdout, BMNG"[%d] Song name:"ESC" %s", i + 1, (read_St + i)->song_Name);
				fprintf(stdout, BMNG"[%d] Author:"ESC" %s\n", i + 1, (read_St + i)->author);
				flag = 1;
				_getch();
			}
		}
		if (flag == 0) {
			printf("\nNo music on season: [%d].\n", id_Srch);
			_getch();
		}
		else{
			printf("End of list.");
			_getch();
		}
		free(read_St);
		fclose(search);
		return;
	}
	case 2: {
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
				fprintf(stdout, BMNG"\n[%d] Song ID:"ESC" %d\n", i + 1, (read_St + i)->ID);
				fprintf(stdout, BMNG"[%d] Season:"ESC" %d\n", i + 1, (read_St + i)->season);
				fprintf(stdout, BMNG"[%d] Episode name:"ESC" %s", i + 1, (read_St + i)->episode_Name);
				fprintf(stdout, BMNG"[%d] Song name:"ESC" %s", i + 1, (read_St + i)->song_Name);
				fprintf(stdout, BMNG"[%d] Author:"ESC" %s\n", i + 1, (read_St + i)->author);
				flag = 1;
				_getch();
				break;
			}
		}
		if (flag == 0) {
			*(srch_Sng_Nm + (strlen(srch_Sng_Nm) - 1)) = 0;
			printf("\nNo song(s) named: [%s].\n", srch_Sng_Nm);
			_getch();
		}
		else{
			printf("End of list.");
			_getch();
		}
		free(read_St);
		free(srch_Sng_Nm);
		fclose(search);
		return;
	}
	case 3: {
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
				fprintf(stdout, BMNG"\n[%d] Song ID:"ESC" %d\n", i + 1, (read_St + i)->ID);
				fprintf(stdout, BMNG"[%d] Season:"ESC" %d\n", i + 1, (read_St + i)->season);
				fprintf(stdout, BMNG"[%d] Episode name:"ESC" %s", i + 1, (read_St + i)->episode_Name);
				fprintf(stdout, BMNG"[%d] Song name:"ESC" %s", i + 1, (read_St + i)->song_Name);
				fprintf(stdout, BMNG"[%d] Author:"ESC" %s\n", i + 1, (read_St + i)->author);
				flag = 1;
				_getch();
			}
		}
		if (flag == 0) {
			*(srch_Author + (strlen(srch_Author) - 1)) = 0;
			printf("\nNo author(s) named: [%s].\n", srch_Author);
			_getch();
		}
		else{
			printf("End of list.");
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