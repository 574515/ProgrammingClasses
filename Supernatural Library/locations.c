#include "header.h"
#include "structs.h"
#include "colors.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

void locs_Edit_Menu(void) {

	//enter from library_Edit_Board
	int choice = 0;
	while (1) {
		if (admin_Logged == 1) {
			do {
				system("cls");
				printf("\t  Logged in as: "RED"[%s]"ESC"\n\n\t"CYN"Locations editing\n\n"ESC"[1] Add a location\n[2] Remove a location\n[3] Edit locations\n[4] List locations\n[5] Search a location\n[6] Return\n\nChoice: ", logged_As);
				scanf(" %d", &choice);
			} while (choice < 1 || choice > 6);

			switch (choice) {
			case 1: {
				add_Locations();
				break;
			}
			case 2: {
				del_Locations();
				break;
			}
			case 3: {
				edit_Locations();
				break;
			}
			case 4: {
				list_Locations();
				break;
			}
			case 5: {
				search_Locations();
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
				printf("\t  Logged in as: "BLUE"[%s]"ESC"\n\n\t"CYN"Locations\n\n"ESC"[1] List locations\n[2] Search a location\n[3] Edit locations\n[4] Return\n\nChoice: ", logged_As);
				scanf(" %d", &choice);
			} while (choice < 1 || choice > 4);

			switch (choice) {
			case 1: {
				list_Locations();
				break;
			}
			case 2: {
				search_Locations();
				break;
			}
			case 3: {
				edit_Locations();
				break;
			}
			case 4: {
				return;
			}
			}
		}
	}
}

void add_Locations(void) {

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
		printf("\n\tEntering 1. "CYN"location"ESC".\n\nEnter location ID: ");
		scanf("%d", &locs->ID);
		printf("Enter season: ");
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
		printf("\n\tEntering %d. "CYN"location"ESC".\n\nEnter location ID: ", locs_Num);
		scanf("%d", &locs->ID);
		printf("Enter season: ");
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

void del_Locations(void) {

	//enter from locs_Edit_Menu
	FILE* read_Locs = NULL;
	read_Locs = fopen("locations.bin", "rb");
	if (read_Locs == NULL) {
		system("cls");
		printf("\n\t\t"RED"Error!"ESC"\nThere are no locations, for now...\n");
		_getch();
		return;
	}

	int rem_By, num, dlt_ID, found = 0, helping = 0, count_Del = 0;
	do {
		system("cls");
		printf("\t  Logged in as: "RED"[%s]"ESC"\n\n\tRemoving locations "RED"[BE CAREFUL!]\n\n"ESC"[1] Remove by ID\n[2] Remove by episode\n[3] Remove by location\n[4] Return\n\nChoice: ", logged_As);
		scanf("%d", &rem_By);
	} while (rem_By < 1 || rem_By > 4);


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
		printf("\nEnter ID to delete: ");
		scanf("%d", &dlt_ID);

		helping = num;
		fwrite(&helping, sizeof(int), 1, tmp_Pntr);

		for (int i = 0; i < num; i++) {
			fread(deletion, sizeof(LOCATIONS), 1, read_Locs);
			if (deletion->ID == dlt_ID) {
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
			printf("\n\tSeason [%d] was not found.\n", dlt_ID);
			fclose(read_Locs);
			fclose(tmp_Pntr);
			free(deletion);
			_getch();
		}
		else {
			system("cls");
			printf("\n\tWhole season [%d] was "CYN"removed"ESC".\n", dlt_ID);
			_getch();
			fclose(read_Locs);
			fclose(tmp_Pntr);
			free(deletion);
			if (helping == 0) {
				remove("locations.bin");
				remove("tmp.bin");
				printf("\n\tThere are no "CYN"locations"ESC" left.\n");
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
				printf("\n\tThere are no "CYN"locations"ESC" left.\n");
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
				printf("\n\tThere are no "CYN"locations"ESC" left.\n");
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

void edit_Locations(void) {

	FILE* locs_File = NULL;
	locs_File = fopen("locations.bin", "rb");
	if (locs_File == NULL) {
		system("cls");
		printf("\n\t\t"RED"Error!"ESC"\nThere are no locations, for now...\n");
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

	fread(&num, sizeof(int), 1, locs_File);
	LOCATIONS* locs = NULL;
	locs = (LOCATIONS*)calloc(num, sizeof(LOCATIONS));
	if (locs == NULL) {
		perror("Struct error");
		exit(EXIT_FAILURE);
	}
	fread(locs, sizeof(LOCATIONS), num, locs_File);

	LOCATIONS* edit = NULL;
	edit = (LOCATIONS*)calloc(1, sizeof(LOCATIONS));
	if (edit == NULL) {
		perror("Struct error");
		exit(EXIT_FAILURE);
	}

	switch (edit_By) {
	case 1: {
		int i, edit_ID, flag = 0;
		system("cls");
		printf("\n\t"CYN"Edit locations by ID:\n\n"ESC"Enter ID: ");
		scanf("%d", &edit_ID);
		for (i = 0; i < num; i++) {
			if ((locs + i)->ID == edit_ID) {
				flag = 1;
				break;
			}
		}
		if (flag == 0) {
			system("cls");
			printf("\nNo location with ID [%d].\n", edit_ID);
			_getch();
			fclose(locs_File);
			fclose(tmp_Pntr);
			free(locs);
			free(edit);
			return;
		}
		else {
			printf("\nEnter new location ID: ");
			scanf("%d", &edit->ID);
			printf("Enter season: ");
			scanf("%d", &edit->season);
			printf("Enter episode name: "); getchar();
			fgets(edit->episode_Name, 99, stdin);
			printf("Enter location: ");
			fgets(edit->location, 249, stdin);
			fwrite(&num, sizeof(int), 1, tmp_Pntr);
			for (i = 0; i < num; i++) {
				if ((locs + i)->ID == edit_ID) {
					fwrite(edit, sizeof(LOCATIONS), 1, tmp_Pntr);
				}
				else {
					fwrite(locs, sizeof(LOCATIONS), 1, tmp_Pntr);
				}
			}

			system("cls");
			printf("\n\tLocation with ID [%d] was "CYN"edited"ESC".\n", edit_ID);
			_getch();
			fclose(locs_File);
			fclose(tmp_Pntr);
			free(locs);
			free(edit);
			remove("locations.bin");
			rename("tmp.bin", "locations.bin");
			return;
		}
	}
	case 2: {
		fclose(locs_File);
		fclose(tmp_Pntr);
		free(locs);
		free(edit);
		return;
	}
	}
}

void list_Locations(void) {

	//enter from locs_Edit_Menu

	FILE* read = NULL;
	read = fopen("locations.bin", "rb");
	if (read == NULL) {
		system("cls");
		printf("\n\t\t"RED"Error!"ESC"\nThere are no locations, for now...\n");
		_getch();
		return;
	}

	int list_Choice, locs_Num, asc_Desc, i;
	do {
		system("cls");
		if (admin_Logged == 1) {
			printf("\t  Logged in as: "RED"[%s]"ESC"\n\n\t"CYN"List locations by:\n\n"ESC"[1] ID\n[2] Season\n[3] Episode\n[4] Location\n[5] Default order\n[6] Return\n\nChoice: ", logged_As);
		}
		else {
			printf("\t  Logged in as: "BLUE"[%s]"ESC"\n\n\t"CYN"List locations by:\n\n"ESC"[1] ID\n[2] Season\n[3] Episode\n[4] Location\n[5] Default order\n[6] Return\n\nChoice: ", logged_As);
		}
		scanf("%d", &list_Choice);
	} while (list_Choice < 1 || list_Choice > 5);


	LOCATIONS* read_St = NULL;
	fread(&locs_Num, sizeof(int), 1, read);
	read_St = (LOCATIONS*)calloc(locs_Num, sizeof(LOCATIONS));
	if (read_St == NULL) {
		perror("Struct error");
		exit(EXIT_FAILURE);
	}

	switch (list_Choice) {
	case 1: {
		do {
			system("cls");
			printf("\n\t"CYN"Sort locations by ID:\n\n"ESC"[1] Ascending\n[2] Descending\n\nChoice: ");
			scanf("%d", &asc_Desc);
		} while (asc_Desc < 1 || asc_Desc > 2);

		fseek(read, sizeof(int), SEEK_SET);
		fread(read_St, sizeof(LOCATIONS), locs_Num, read);
		if (asc_Desc == 1)
			qsort(read_St, locs_Num, sizeof(LOCATIONS), compare_ID_Asc_Locs);
		else
			qsort(read_St, locs_Num, sizeof(LOCATIONS), compare_ID_Desc_Locs);
		system("cls");
		printf("\n\tNumber of "CYN"locations"ESC": [%d]\n\n", locs_Num);
		for (i = 0; i < locs_Num; i++) {
			fprintf(stdout, BMNG"\n[%d] Location ID:"ESC" %d\n", i + 1, (read_St + i)->ID);
			fprintf(stdout, BMNG"[%d] Season:"ESC" %d\n", i + 1, (read_St + i)->season);
			fprintf(stdout, BMNG"[%d] Episode name:"ESC" %s", i + 1, (read_St + i)->episode_Name);
			fprintf(stdout, BMNG"[%d] Location:"ESC" %s\n", i + 1, (read_St + i)->location);
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
			fprintf(stdout, BMNG"\n[%d] Location ID:"ESC" %d\n", i + 1, (read_St + i)->ID);
			fprintf(stdout, BMNG"[%d] Season:"ESC" %d\n", i + 1, (read_St + i)->season);
			fprintf(stdout, BMNG"[%d] Episode name:"ESC" %s", i + 1, (read_St + i)->episode_Name);
			fprintf(stdout, BMNG"[%d] Location:"ESC" %s\n", i + 1, (read_St + i)->location);
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
			fprintf(stdout, BMNG"\n[%d] Location ID:"ESC" %d\n", i + 1, (read_St + i)->ID);
			fprintf(stdout, BMNG"[%d] Season:"ESC" %d\n", i + 1, (read_St + i)->season);
			fprintf(stdout, BMNG"[%d] Episode name:"ESC" %s", i + 1, (read_St + i)->episode_Name);
			fprintf(stdout, BMNG"[%d] Location:"ESC" %s\n", i + 1, (read_St + i)->location);
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
			fprintf(stdout, BMNG"\n[%d] Location ID:"ESC" %d\n", i + 1, (read_St + i)->ID);
			fprintf(stdout, BMNG"[%d] Season:"ESC" %d\n", i + 1, (read_St + i)->season);
			fprintf(stdout, BMNG"[%d] Episode name:"ESC" %s", i + 1, (read_St + i)->episode_Name);
			fprintf(stdout, BMNG"[%d] Location:"ESC" %s\n", i + 1, (read_St + i)->location);
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
		fread(read_St, sizeof(LOCATIONS), locs_Num, read);
		printf("\n\tNumber of "CYN"locations"ESC": [%d]\n\n", locs_Num);
		for (i = 0; i < locs_Num; i++) {
			fprintf(stdout, BMNG"\n[%d] Location ID:"ESC" %d\n", i + 1, (read_St + i)->ID);
			fprintf(stdout, BMNG"[%d] Season:"ESC" %d\n", i + 1, (read_St + i)->season);
			fprintf(stdout, BMNG"[%d] Episode name:"ESC" %s", i + 1, (read_St + i)->episode_Name);
			fprintf(stdout, BMNG"[%d] Location:"ESC" %s\n", i + 1, (read_St + i)->location);
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

void search_Locations(void) {

	//enter from locs_Edit_Menu

	FILE* search = NULL;
	search = fopen("locations.bin", "rb");
	if (search == NULL) {
		system("cls");
		printf("\n\t\t"RED"Error!"ESC"\nThere are no locations, for now...\n");
		_getch();
		return;
	}

	int search_Choice;
	do {
		system("cls");
		if (admin_Logged == 1) {
			printf("\t  Logged in as: "RED"[%s]"ESC"\n\n\t"CYN"Search locations by:\n\n"ESC"[1] Season\n[2] Episode name\n[3] Location\n[4] Return\n\nChoice: ", logged_As);
		}
		else {
			printf("\t  Logged in as: "BLUE"[%s]"ESC"\n\n\t"CYN"Search locations by:\n\n"ESC"[1] Season\n[2] Episode name\n[3] Location\n[4] Return\n\nChoice: ", logged_As);
		}
		scanf("%d", &search_Choice);
	} while (search_Choice < 1 || search_Choice > 4);

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
				fprintf(stdout, BMNG"\n[%d] Location ID:"ESC" %d\n", i + 1, (read_St + i)->ID);
				fprintf(stdout, BMNG"[%d] Season:"ESC" %d\n", i + 1, (read_St + i)->season);
				fprintf(stdout, BMNG"[%d] Episode name:"ESC" %s", i + 1, (read_St + i)->episode_Name);
				fprintf(stdout, BMNG"[%d] Location:"ESC" %s\n", i + 1, (read_St + i)->location);
				flag = 1;
				_getch();
				break;
			}
		}
		if (flag == 0) {
			printf("\nNo locations on season: [%d].\n", id_Srch);
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
				fprintf(stdout, BMNG"\n[%d] Location ID:"ESC" %d\n", i + 1, (read_St + i)->ID);
				fprintf(stdout, BMNG"[%d] Season:"ESC" %d\n", i + 1, (read_St + i)->season);
				fprintf(stdout, BMNG"[%d] Episode name:"ESC" %s", i + 1, (read_St + i)->episode_Name);
				fprintf(stdout, BMNG"[%d] Location:"ESC" %s\n", i + 1, (read_St + i)->location);
				flag = 1;
				_getch();
				break;
			}
		}
		if (flag == 0) {
			*(srch_Enm + (strlen(srch_Enm) - 1)) = 0;
			printf("\nNo location within episode name: [%s].\n", srch_Enm);
			_getch();
		}
		else {
			printf("\nEnd of list.\n");
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
				fprintf(stdout, BMNG"\n[%d] Location ID:"ESC" %d\n", i + 1, (read_St + i)->ID);
				fprintf(stdout, BMNG"[%d] Season:"ESC" %d\n", i + 1, (read_St + i)->season);
				fprintf(stdout, BMNG"[%d] Episode name:"ESC" %s", i + 1, (read_St + i)->episode_Name);
				fprintf(stdout, BMNG"[%d] Location:"ESC" %s\n", i + 1, (read_St + i)->location);
				flag = 1;
				_getch();
			}
		}
		if (flag == 0) {
			*(srch_Loc + (strlen(srch_Loc) - 1)) = 0;
			printf("\nNo location named: [%s].\n", srch_Loc);
			_getch();
		}
		else {
			printf("\nEnd of list.\n");
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