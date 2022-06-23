#include "header.h"
#include "structs.h"
#include "colors.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

void seas_Edit_Menu(void) {

	//enter from library_Edit_Board
	int choice;
	while (1) {
		if(admin_Logged == 1){
			do {
				system("cls");
				printf("\t  Logged in as: "RED"[%s]"ESC"\n\n\t"MNG"Season editing\n\n"ESC"[1] Add seasons\n[2] Remove seasons\n[3] Edit seasons\n[4] List seasons\n[5] Search seasons\n[6] Return\n\nChoice: ", logged_As);
				scanf("%d", &choice);
			} while (choice < 1 || choice > 6);
			switch (choice) {
			case 1: {
				seas_Add();
				break;
			}
			case 2: {
				del_Seas();
				break;
			}
			case 3: {
				edit_Seas();
				break;
			}
			case 4: {
				seas_List();
				break;
			}
			case 5: {
				search_Seas();
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
				printf("\t  Logged in as: "RED"[%s]"ESC"\n\n\t"MNG"Seasons\n\n"ESC"[1] List seasons\n[2] Search seasons\n[3] Edit seasons\n[4] Return\n\nChoice: ", logged_As);
				scanf("%d", &choice);
			} while (choice < 1 || choice > 4);
			switch (choice) {
			case 1: {
				seas_List();
				break;
			}
			case 2: {
				search_Seas();
				break;
			}
			case 3: {
				edit_Seas();
				break;
			}
			case 4: {
			}
				return;
			}
		}
	}
}

void seas_Add(void) {

	//enter from seas_Edit_Menu
	SEASONS* seas_Struc = NULL;
	seas_Struc = (SEASONS*)calloc(1, sizeof(SEASONS));
	if (seas_Struc == NULL) {
		perror("Struct error");
		exit(EXIT_FAILURE);
	}
	FILE* seas_File = NULL;
	seas_File = fopen("seasons.bin", "r+b");
	if (seas_File == NULL) {
		seas_File = fopen("seasons.bin", "wb");
		if (seas_File == NULL) {
			perror("File error");
			exit(EXIT_FAILURE);
		}
		system("cls");
		printf("\n\tEntering 1. "MNG"season"ESC".\n\nEnter season: ");
		scanf("%d", &seas_Struc->ID);
		printf("Enter number of episodes: ");
		scanf("%d", &seas_Struc->num_Eps);
		printf("Enter premier episode name: "); getchar();
		fgets(seas_Struc->premier, 39, stdin);
		printf("Enter premier episode date: ");
		fgets(seas_Struc->prem_Dat, 14, stdin);
		printf("Enter finale episode date: ");
		fgets(seas_Struc->finale, 49, stdin);
		printf("Enter finale episode date: ");
		fgets(seas_Struc->fin_Date, 14, stdin);
		printf("Enter season summary: ");
		fgets(seas_Struc->summary, 699, stdin);
		int seas_Num = 1;
		fwrite(&seas_Num, sizeof(int), 1, seas_File);
		fwrite(seas_Struc, sizeof(SEASONS), 1, seas_File);
		fclose(seas_File);
		free(seas_Struc);
		return;
	}
	else {
		int seas_Num;
		fread(&seas_Num, sizeof(int), 1, seas_File);
		seas_Num++;
		system("cls");
		printf("\n\tEntering %d. "MNG"season"ESC".\n\nEnter season: ", seas_Num);
		scanf("%d", &seas_Struc->ID);
		printf("Enter number of episodes: ");
		scanf("%d", &seas_Struc->num_Eps);
		printf("Enter premier episode name: "); getchar();
		fgets(seas_Struc->premier, 39, stdin);
		printf("Enter premier episode date: ");
		fgets(seas_Struc->prem_Dat, 14, stdin);
		printf("Enter finale episode date: ");
		fgets(seas_Struc->finale, 49, stdin);
		printf("Enter finale episode date: ");
		fgets(seas_Struc->fin_Date, 14, stdin);
		printf("Enter season summary: ");
		fgets(seas_Struc->summary, 699, stdin);
		rewind(seas_File);
		fwrite(&seas_Num, sizeof(int), 1, seas_File);
		fseek(seas_File, sizeof(int) + ((seas_Num - 1) * sizeof(SEASONS)), SEEK_SET);
		fwrite(seas_Struc, sizeof(SEASONS), 1, seas_File);
		fclose(seas_File);
		free(seas_Struc);
		return;
	}
}

void del_Seas(void) {

	//enter from seas_Edit_Menu
	FILE* seas_File = NULL;
	seas_File = fopen("seasons.bin", "rb");
	if (seas_File == NULL) {
		system("cls");
		printf("\n\t\t"RED"Error!"ESC"\nThere are no seasons, for now...\n");
		_getch();
		return;
	}

	int rem_By, num;
	do {
		system("cls");
		printf("\t  Logged in as: "RED"[%s]"ESC"\n\n\tRemoving seasons "RED"[BE CAREFUL!]\n\n"ESC"[1] Remove by season\n[2] Remove by premier name\n[3] Remove by finale name\n[4] Return\n\nChoice: ", logged_As);
		scanf("%d", &rem_By);
	} while (rem_By < 1 || rem_By > 5);


	FILE* tmp_Pntr = NULL;
	tmp_Pntr = fopen("tmp.bin", "wb");
	if (tmp_Pntr == NULL) {
		printf("File error");
		exit(EXIT_FAILURE);
	}

	fread(&num, sizeof(int), 1, seas_File);
	SEASONS* deletion = NULL;
	deletion = (SEASONS*)calloc(num, sizeof(SEASONS));
	if (deletion == NULL) {
		perror("Struct error");
		exit(EXIT_FAILURE);
	}

	switch (rem_By) {
	case 1: {
		int found = 0, helping = 0, count_Del = 0, season_ID;
		printf("\nEnter season to delete: ");
		scanf("%d", &season_ID);

		helping = num;
		fwrite(&helping, sizeof(int), 1, tmp_Pntr);

		for (int i = 0; i < num; i++) {
			fread(deletion, sizeof(SEASONS), 1, seas_File);
			if (deletion->ID == season_ID) {
				found = 1;
				count_Del++;
			}
			else {
				fwrite(deletion, sizeof(SEASONS), 1, tmp_Pntr);
			}
		}

		helping = num - count_Del;
		rewind(tmp_Pntr);
		fwrite(&helping, sizeof(int), 1, tmp_Pntr);

		if (found != 1) {
			system("cls");
			printf("\n\tSeason [%d] was not found.\n", season_ID);
			fclose(seas_File);
			fclose(tmp_Pntr);
			free(deletion);
			_getch();
		}
		else {
			system("cls");
			printf("\n\tSeason [%d] was "MNG"removed"ESC".\n", season_ID);
			_getch();
			fclose(seas_File);
			fclose(tmp_Pntr);
			free(deletion);
			if (helping == 0) {
				remove("seasons.bin");
				remove("tmp.bin");
				printf("\n\tThere are no "MNG"seasons"ESC" left.\n");
				_getch();
				return;
			}
			else {
				remove("seasons.bin");
				rename("tmp.bin", "seasons.bin");
			}
		}
		return;
	}
	case 2: {
		char* dlt_By_Prem;
		int found = 0, helping = 0, count_Del = 0;
		dlt_By_Prem = (char*)calloc(40, sizeof(char));
		if (dlt_By_Prem == NULL) {
			perror("Memory error");
			exit(EXIT_FAILURE);
		}
		getchar();
		printf("\nEnter premier episode name to delete by: ");
		fgets(dlt_By_Prem, 39, stdin);

		helping = num;
		fwrite(&helping, sizeof(int), 1, tmp_Pntr);

		for (int i = 0; i < num; i++) {
			fread(deletion, sizeof(SEASONS), 1, seas_File);
			if (strstr(deletion->premier, dlt_By_Prem)) {
				found = 1;
				count_Del++;
			}
			else {
				fwrite(deletion, sizeof(SEASONS), 1, tmp_Pntr);
			}
		}

		helping = num - count_Del;
		rewind(tmp_Pntr);
		fwrite(&helping, sizeof(int), 1, tmp_Pntr);

		if (found != 1) {
			system("cls");
			*(dlt_By_Prem + (strlen(dlt_By_Prem) - 1)) = 0;
			printf("\n\tPremier episode named [%s] was not found.\n", dlt_By_Prem);
			fclose(seas_File);
			fclose(tmp_Pntr);
			free(deletion);
			free(dlt_By_Prem);
			_getch();
		}
		else {
			system("cls");
			*(dlt_By_Prem + (strlen(dlt_By_Prem) - 1)) = 0;
			printf("\n\tPremier episode [%s] was "MNG"removed"ESC".\n", dlt_By_Prem);
			_getch();
			fclose(seas_File);
			fclose(tmp_Pntr);
			free(dlt_By_Prem);
			free(deletion);

			if (helping == 0) {
				remove("seasons.bin");
				remove("tmp.bin");
				printf("\n\tThere are no "MNG"seasons"ESC" left.\n");
				_getch();
				return;
			}
			else {
				remove("seasons.bin");
				rename("tmp.bin", "seasons.bin");
			}
		}
		return;
	}
	case 3: {
		char* dlt_By_Fina;
		int found = 0, helping = 0, count_Del = 0;
		dlt_By_Fina = (char*)calloc(40, sizeof(char));
		if (dlt_By_Fina == NULL) {
			perror("Memory error");
			exit(EXIT_FAILURE);
		}
		getchar();
		printf("\nEnter final episode name to delete by: ");
		fgets(dlt_By_Fina, 39, stdin);

		helping = num;
		fwrite(&helping, sizeof(int), 1, tmp_Pntr);

		for (int i = 0; i < num; i++) {
			fread(deletion, sizeof(SEASONS), 1, seas_File);
			if (strstr(deletion->finale, dlt_By_Fina)) {
				found = 1;
				count_Del++;
			}
			else {
				fwrite(deletion, sizeof(SEASONS), 1, tmp_Pntr);
			}
		}

		helping = num - count_Del;
		rewind(tmp_Pntr);
		fwrite(&helping, sizeof(int), 1, tmp_Pntr);

		if (found != 1) {
			system("cls");
			*(dlt_By_Fina + (strlen(dlt_By_Fina) - 1)) = 0;
			printf("\n\tFinale episode named [%s] was not found.\n", dlt_By_Fina);
			fclose(seas_File);
			fclose(tmp_Pntr);
			free(deletion);
			free(dlt_By_Fina);
			_getch();
		}
		else {
			system("cls");
			*(dlt_By_Fina + (strlen(dlt_By_Fina) - 1)) = 0;
			printf("\n\tFinale episode [%s] was "MNG"removed"ESC".\n", dlt_By_Fina);
			_getch();
			fclose(seas_File);
			fclose(tmp_Pntr);
			free(dlt_By_Fina);
			free(deletion);

			if (helping == 0) {
				remove("seasons.bin");
				remove("tmp.bin");
				printf("\n\tThere are no "MNG"seasons"ESC" left.\n");
				_getch();
				return;
			}
			else {
				remove("seasons.bin");
				rename("tmp.bin", "seasons.bin");
			}
		}
		return;
	}
	case 4: {
		fclose(seas_File);
		fclose(tmp_Pntr);
		free(deletion);
		return;
	}
	}
}

void edit_Seas(void) {

	//enter from seas_Edit_Menu
	int edit_Seas, seas_Num, seas_ID_Choice, i, flag = 0;

	FILE* read = NULL;
	read = fopen("seasons.bin", "r+b");
	if (read == NULL) {
		system("cls");
		printf("\n\t\t"RED"Error!"ESC"\nThere are no seasons, for now...\n");
		_getch();
		return;
	}

	SEASONS* read_St = NULL;
	fread(&seas_Num, sizeof(int), 1, read);
	read_St = (SEASONS*)calloc(seas_Num, sizeof(SEASONS));
	if (read_St == NULL) {
		perror("Struct error");
		exit(EXIT_FAILURE);
	}

	fseek(read, sizeof(int), SEEK_SET);
	fread(read_St, sizeof(SEASONS), seas_Num, read);

	do {
		system("cls");
		if (admin_Logged == 1) {
			printf("\t  Logged in as: "RED"[%s]"ESC"\n\n\tEditing seasons "RED"[BE CAREFUL!]\n\n"ESC"[1] Edit by ID\n[2] Return\n\nChoice: ", logged_As);
		}
		else {
			printf("\t  Logged in as: "BLUE"[%s]"ESC"\n\n\tEditing seasons "RED"[BE CAREFUL!]\n\n"ESC"[1] Edit by ID\n[2] Return\n\nChoice: ", logged_As);
		}
		scanf("%d", &edit_Seas);
	} while (edit_Seas < 1 || edit_Seas > 2);
	switch (edit_Seas) {
	case 1: {
		system("cls");
		printf("\n\t"MNG"Edit seasons by ID:\n\n"ESC"Enter ID: ");
		scanf("%d", &seas_ID_Choice);

		for (i = 0; i < seas_Num; i++) {
			if (seas_ID_Choice == (read_St + i)->ID) {
				flag = 1;
				break;
			}
		}

		if (flag == 0) {
			printf("\nNo season with ID [%d].\n", seas_ID_Choice);
			_getch();
			return;
		}
		else {
			SEASONS* temp = NULL;
			temp = (SEASONS*)calloc(1, sizeof(SEASONS));
			if (temp == NULL) {
				perror("Struct error");
				exit(EXIT_FAILURE);
			}

			system("cls");
			printf("\n\tEditing ID [%d] of "MNG"seasons"ESC".\n\nEnter new ID: ", seas_ID_Choice);
			scanf("%d", &temp->ID);
			printf("Enter number of episodes: ");
			scanf("%d", &temp->num_Eps);
			printf("Enter premier episode name: "); getchar();
			fgets(temp->premier, 39, stdin);
			printf("Enter premier episode date: ");
			fgets(temp->prem_Dat, 14, stdin);
			printf("Enter finale episode date: ");
			fgets(temp->finale, 49, stdin);
			printf("Enter finale episode date: ");
			fgets(temp->fin_Date, 14, stdin);
			printf("Enter season summary: ");
			fgets(temp->summary, 699, stdin);
			for (i = 0; i < seas_Num; i++) {
				if ((read_St + i)->ID == seas_ID_Choice) {
					fseek(read, ftell(read) - sizeof(SEASONS), SEEK_SET);
					fwrite(temp, sizeof(SEASONS), 1, read);
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

void seas_List(void) {

	//enter from seas_Edit_Menu
	FILE* read = NULL;
	read = fopen("seasons.bin", "rb");
	if (read == NULL) {
		system("cls");
		printf("\n\t\t"RED"Error!"ESC"\nThere are no seasons, for now...\n");
		_getch();
		return;
	}

	int list_Choice, seas_Num;
	do {
		system("cls");
		printf("\t  Logged in as: "RED"[%s]"ESC"\n\n\t"MNG"List seasons by:\n\n"ESC"[1] ID\n[2] Number of episodes\n[4] Return\n\nChoice: ", logged_As);
		scanf("%d", &list_Choice);
	} while (list_Choice < 1 || list_Choice > 4);


	SEASONS* read_St = NULL;
	fread(&seas_Num, sizeof(int), 1, read);
	read_St = (SEASONS*)calloc(seas_Num, sizeof(SEASONS));
	if (read_St == NULL) {
		perror("Struct error");
		exit(EXIT_FAILURE);
	}

	switch (list_Choice) {
	case 1: {		
		int asc_Desc, i;
		do {
			system("cls");
			printf("\n\t"MNG"Sort seasons by season:\n\n"ESC"[1] Ascending\n[2] Descending\n\nChoice: ");
			scanf("%d", &asc_Desc);
		} while (asc_Desc < 1 || asc_Desc > 2);

		fseek(read, sizeof(int), SEEK_SET);
		fread(read_St, sizeof(SEASONS), seas_Num, read);
		if (asc_Desc == 1)
			qsort(read_St, seas_Num, sizeof(SEASONS), compare_Season_Asc);
		else
			qsort(read_St, seas_Num, sizeof(SEASONS), compare_Season_Desc);
		system("cls");
		printf("\n\tNumber of "MNG"seasons"ESC": [%d]\n\n", seas_Num);
		for (i = 0; i < seas_Num; i++) {
			fprintf(stdout, BMNG"\n[%d] Season: "ESC"%d\n", i + 1, (read_St + i)->ID);
			fprintf(stdout, BMNG"[%d] Number of episodes: "ESC"%d\n", i + 1, (read_St + i)->num_Eps);
			fprintf(stdout, BMNG"[%d] Pemier episode: "ESC"%s", i + 1, (read_St + i)->premier);
			fprintf(stdout, BMNG"[%d] Pemier episode date: "ESC"%s", i + 1, (read_St + i)->prem_Dat);
			fprintf(stdout, BMNG"[%d] Final episode: "ESC"%s", i + 1, (read_St + i)->finale);
			fprintf(stdout, BMNG"[%d] Final episode date: "ESC"%s", i + 1, (read_St + i)->fin_Date);
			fprintf(stdout, BMNG"[%d] Summary: "ESC"%s", i + 1, (read_St + i)->summary);
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
			printf("\n\t"MNG"Sort seasons by number of episodes:\n\n"ESC"[1] Ascending\n[2] Descending\n\nChoice: ");
			scanf("%d", &asc_Desc);
		} while (asc_Desc < 1 || asc_Desc > 2);

		fseek(read, sizeof(int), SEEK_SET);
		fread(read_St, sizeof(SEASONS), seas_Num, read);
		if (asc_Desc == 1)
			qsort(read_St, seas_Num, sizeof(SEASONS), compare_Season_No_Ep_Asc);
		else
			qsort(read_St, seas_Num, sizeof(SEASONS), compare_Season_No_Ep_Desc);
		system("cls");
		printf("\n\tNumber of "MNG"rituals & spells"ESC": [%d]\n\n", seas_Num);
		for (i = 0; i < seas_Num; i++) {
			fprintf(stdout, BMNG"\n[%d] Season: "ESC"%d\n", i + 1, (read_St + i)->ID);
			fprintf(stdout, BMNG"[%d] Number of episodes: "ESC"%d\n", i + 1, (read_St + i)->num_Eps);
			fprintf(stdout, BMNG"[%d] Pemier episode: "ESC"%s", i + 1, (read_St + i)->premier);
			fprintf(stdout, BMNG"[%d] Pemier episode date: "ESC"%s", i + 1, (read_St + i)->prem_Dat);
			fprintf(stdout, BMNG"[%d] Final episode: "ESC"%s", i + 1, (read_St + i)->finale);
			fprintf(stdout, BMNG"[%d] Final episode date: "ESC"%s", i + 1, (read_St + i)->fin_Date);
			fprintf(stdout, BMNG"[%d] Summary: "ESC"%s", i + 1, (read_St + i)->summary);
		}
		fprintf(stdout, "\nEnd of list! Continue...\n");
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

void search_Seas(void) {

	//enter from seas_Edit_Menu
	FILE* search = NULL;
	search = fopen("seasons.bin", "rb");
	if (search == NULL) {
		system("cls");
		printf("\n\t\t"RED"Error!"ESC"\nThere are no seasons, for now...\n");
		_getch();
		return;
	}

	int search_Choice, i, seas_Num;
	do {
		system("cls");
		printf("\t  Logged in as: "RED"[%s]"ESC"\n\n\t"MNG"Search seasons by:\n\n"ESC"[1] Season\n[2] Premier name\n[3] Premiare date\n[4] Finale name\n[5] Finale date\n[6] Return to edit panel\n\nChoice: ", logged_As);
		scanf("%d", &search_Choice);
	} while (search_Choice < 1 || search_Choice > 5);


	SEASONS* read_St = NULL;
	fread(&seas_Num, sizeof(int), 1, search);
	read_St = (SEASONS*)calloc(seas_Num, sizeof(SEASONS));
	if (read_St == NULL) {
		perror("Struct error");
		exit(EXIT_FAILURE);
	}

	switch (search_Choice) {
	case 1: {
		int flag = 0, season_ID;
		system("cls");
		printf("\nEnter season number: ");
		scanf("%d", &season_ID);
		for (i = 0; i < seas_Num; i++) {
			fread(read_St, sizeof(SEASONS), 1, search);
			if (season_ID == read_St->ID) {
				fprintf(stdout, BMNG"\n[%d] Season: "ESC"%d\n", i + 1, read_St->ID);
				fprintf(stdout, BMNG"[%d] Number of episodes: "ESC"%d\n", i + 1, read_St->num_Eps);
				fprintf(stdout, BMNG"[%d] Pemier episode: "ESC"%s", i + 1, read_St->premier);
				fprintf(stdout, BMNG"[%d] Pemier episode date: "ESC"%s", i + 1, read_St->prem_Dat);
				fprintf(stdout, BMNG"[%d] Final episode: "ESC"%s", i + 1, read_St->finale);
				fprintf(stdout, BMNG"[%d] Final episode date: "ESC"%s", i + 1, read_St->fin_Date);
				fprintf(stdout, BMNG"[%d] Summary: "ESC"%s", i + 1, read_St->summary);
				flag = 1;
				_getch();
				break;
			}
		}
		if (flag == 0) {
			printf("\nNo season: [%d].\n", season_ID);
			_getch();
		}
		else {
			printf("End of list.");
			_getch();
		}
		free(read_St);
		fclose(search);
		return;
	}
	case 2: {
		int flag = 0;
		char* prem_Name;
		prem_Name = (char*)calloc(40, sizeof(char));
		if (prem_Name == NULL) {
			perror("Memory error");
			exit(EXIT_FAILURE);
		}
		system("cls");
		printf("\nEnter premier episode name: ");
		getchar();
		fgets(prem_Name, 39, stdin);
		for (i = 0; i < seas_Num; i++) {
			fread(read_St, sizeof(SEASONS), 1, search);
			if (strcmp(read_St->premier, prem_Name) == 0) {
				fprintf(stdout, BMNG"\n[%d] Season: "ESC"%d\n", i + 1, read_St->ID);
				fprintf(stdout, BMNG"[%d] Number of episodes: "ESC"%d\n", i + 1, read_St->num_Eps);
				fprintf(stdout, BMNG"[%d] Pemier episode: "ESC"%s", i + 1, read_St->premier);
				fprintf(stdout, BMNG"[%d] Pemier episode date: "ESC"%s", i + 1, read_St->prem_Dat);
				fprintf(stdout, BMNG"[%d] Final episode: "ESC"%s", i + 1, read_St->finale);
				fprintf(stdout, BMNG"[%d] Final episode date: "ESC"%s", i + 1, read_St->fin_Date);
				fprintf(stdout, BMNG"[%d] Summary: "ESC"%s", i + 1, read_St->summary);
				flag = 1;
				_getch();
			}
		}
		if (flag == 0) {
			*(prem_Name + (strlen(prem_Name) - 1)) = 0;
			printf("\nNo premier episode named: [%s].\n", prem_Name);
			_getch();
		}
		else {
			printf("End of list.");
			_getch();
		}
		free(read_St);
		free(prem_Name);
		fclose(search);
		return;
	}
	case 3: {
		int flag = 0;
		char* prem_Date;
		prem_Date = (char*)calloc(15, sizeof(char));
		if (prem_Date == NULL) {
			perror("Memory error");
			exit(EXIT_FAILURE);
		}
		system("cls");
		printf("\nEnter premier episode date: ");
		getchar();
		fgets(prem_Date, 14, stdin);
		for (i = 0; i < seas_Num; i++) {
			fread(read_St, sizeof(SEASONS), 1, search);
			if (strcmp(read_St->prem_Dat, prem_Date) == 0) {
				fprintf(stdout, BMNG"\n[%d] Season: "ESC"%d\n", i + 1, read_St->ID);
				fprintf(stdout, BMNG"[%d] Number of episodes: "ESC"%d\n", i + 1, read_St->num_Eps);
				fprintf(stdout, BMNG"[%d] Pemier episode: "ESC"%s", i + 1, read_St->premier);
				fprintf(stdout, BMNG"[%d] Pemier episode date: "ESC"%s", i + 1, read_St->prem_Dat);
				fprintf(stdout, BMNG"[%d] Final episode: "ESC"%s", i + 1, read_St->finale);
				fprintf(stdout, BMNG"[%d] Final episode date: "ESC"%s", i + 1, read_St->fin_Date);
				fprintf(stdout, BMNG"[%d] Summary: "ESC"%s", i + 1, read_St->summary);
				flag = 1;
				_getch();
			}
		}
		if (flag == 0) {
			*(prem_Date + (strlen(prem_Date) - 1)) = 0;
			printf("\nNo premier episode dated: [%s].\n", prem_Date);
			_getch();
		}
		else {
			printf("End of list.");
			_getch();
		}
		free(read_St);
		free(prem_Date);
		fclose(search);
		return;
	}
	case 4: {
		int flag = 0;
		char* final_Name;
		final_Name = (char*)calloc(40, sizeof(char));
		if (final_Name == NULL) {
			perror("Memory error");
			exit(EXIT_FAILURE);
		}
		system("cls");
		printf("\nEnter final episode name: ");
		getchar();
		fgets(final_Name, 39, stdin);
		for (i = 0; i < seas_Num; i++) {
			fread(read_St, sizeof(SEASONS), 1, search);
			if (strcmp(read_St->finale, final_Name) == 0) {
				fprintf(stdout, BMNG"\n[%d] Season: "ESC"%d\n", i + 1, read_St->ID);
				fprintf(stdout, BMNG"[%d] Number of episodes: "ESC"%d\n", i + 1, read_St->num_Eps);
				fprintf(stdout, BMNG"[%d] Pemier episode: "ESC"%s", i + 1, read_St->premier);
				fprintf(stdout, BMNG"[%d] Pemier episode date: "ESC"%s", i + 1, read_St->prem_Dat);
				fprintf(stdout, BMNG"[%d] Final episode: "ESC"%s", i + 1, read_St->finale);
				fprintf(stdout, BMNG"[%d] Final episode date: "ESC"%s", i + 1, read_St->fin_Date);
				fprintf(stdout, BMNG"[%d] Summary: "ESC"%s", i + 1, read_St->summary);
				flag = 1;
				_getch();
			}
		}
		if (flag == 0) {
			*(final_Name + (strlen(final_Name) - 1)) = 0;
			printf("\nNo final episode named: [%s].\n", final_Name);
			_getch();
		}
		else {
			printf("End of list.");
			_getch();
		}
		free(read_St);
		free(final_Name);
		fclose(search);
		return;
	}
	case 5: {
		int flag = 0;
		char* final_Date;
		final_Date = (char*)calloc(15, sizeof(char));
		if (final_Date == NULL) {
			perror("Memory error");
			exit(EXIT_FAILURE);
		}
		system("cls");
		printf("\nEnter final episode date: ");
		getchar();
		fgets(final_Date, 14, stdin);
		for (i = 0; i < seas_Num; i++) {
			fread(read_St, sizeof(SEASONS), 1, search);
			if (strcmp(read_St->fin_Date, final_Date) == 0) {
				fprintf(stdout, BMNG"\n[%d] Season: "ESC"%d\n", i + 1, read_St->ID);
				fprintf(stdout, BMNG"[%d] Number of episodes: "ESC"%d\n", i + 1, read_St->num_Eps);
				fprintf(stdout, BMNG"[%d] Pemier episode: "ESC"%s", i + 1, read_St->premier);
				fprintf(stdout, BMNG"[%d] Pemier episode date: "ESC"%s", i + 1, read_St->prem_Dat);
				fprintf(stdout, BMNG"[%d] Final episode: "ESC"%s", i + 1, read_St->finale);
				fprintf(stdout, BMNG"[%d] Final episode date: "ESC"%s", i + 1, read_St->fin_Date);
				fprintf(stdout, BMNG"[%d] Summary: "ESC"%s", i + 1, read_St->summary);
				flag = 1;
				_getch();
			}
		}
		if (flag == 0) {
			*(final_Date + (strlen(final_Date) - 1)) = 0;
			printf("\nNo final episode dated: [%s].\n", final_Date);
			_getch();
		}
		else {
			printf("End of list.");
			_getch();
		}
		free(read_St);
		free(final_Date);
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