#include "header.h"
#include "structs.h"
#include "colors.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

void object_Edit_Menu(void) {

	//enter from library_Edit_Board
	int choice;
	while (1) {
		if (admin_Logged == 1) {
			do {
				system("cls");
				printf("\t  Logged in as: "RED"[%s]"ESC"\n\n\t"YLW"Objects editing\n\n"ESC"[1] Add objects\n[2] Remove objects\n[3] Edit objects\n[4] List objects\n[5] Search objects\n[6] Return\n\nChoice: ", logged_As);
				scanf("%d", &choice);
			} while (choice < 1 || choice > 6);
			switch (choice) {
			case 1: {
				add_Objects();
				break;
			}
			case 2: {
				del_Objects();
				break;
			}
			case 3: {
				edit_Objects();
				break;
			}
			case 4: {
				list_Objects();
				break;
			}
			case 5: {
				search_Objects();
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
				printf("\t  Logged in as: "BLUE"[%s]"ESC"\n\n\t"YLW"Objects\n\n"ESC"[1] List objects\n[2] Search objects\n[3] Edit objects\n[4] Return\n\nChoice: ", logged_As);
				scanf("%d", &choice);
			} while (choice < 1 || choice > 4);
			switch (choice) {
			case 1: {
				list_Objects();
				break;
			}
			case 2: {
				search_Objects();
				break;
			}
			case 3: {
				edit_Objects();
				break;
			}
			case 4: {
				return;
			}
			}
		}
	}
}

void add_Objects(void) {

	//enter from object_Edit_Menu
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
		printf("\n\tEntering 1. "YLW"object"ESC".\n\nEnter ID: ");
		scanf("%d", &obj_Struc->ID);
		printf("Enter seasons: ");
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
		printf("\n\tEntering %d. "YLW"object"ESC".\n\nEnter ID: ", obj_Num);
		scanf("%d", &obj_Struc->ID);
		printf("Enter season: ");
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

	//enter from object_Edit_Menu
	int rem_By, num;

	FILE* read_Objs = NULL;
	read_Objs = fopen("objects.bin", "rb");
	if (read_Objs == NULL) {
		system("cls");
		printf("\n\t\t"RED"Error!"ESC"\nThere are no objects, for now...\n");
		_getch();
		return;
	}

	do {
		system("cls");
		printf("\t  Logged in as: "RED"[%s]"ESC"\n\n\tRemoving objects "RED"[BE CAREFUL!]\n\n"ESC"[1] Remove by ID\n[2] Remove by name\n[3] Remove by manufacturer\n[4] Return\n\nChoice: ", logged_As);
		scanf("%d", &rem_By);
	} while (rem_By < 1 || rem_By > 4);

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
		int dlt_ID, found = 0, helping = 0, count_Del = 0;
		printf("\nEnter ID to delete: ");
		scanf("%d", &dlt_ID);

		helping = num;
		fwrite(&helping, sizeof(int), 1, tmp_Pntr);

		for (int i = 0; i < num; i++) {
			fread(deletion, sizeof(OBJECTS), 1, read_Objs);
			if (deletion->ID == dlt_ID) {
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
			printf("\n\tObject with ID [%d] was not found.\n", dlt_ID);
			fclose(read_Objs);
			fclose(tmp_Pntr);
			free(deletion);
			_getch();
		}
		else {
			system("cls");
			printf("\n\tObject with ID [%d] was "YLW"removed"ESC".\n", dlt_ID);
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
	case 4: {
		fclose(read_Objs);
		fclose(tmp_Pntr);
		free(deletion);
		return;
	}
	}
}

void edit_Objects(void) {

	//enter from object_Edit_Menu
	int edit_Obj, obj_Num, obj_ID_Choice, i, flag = 0;

	FILE* read = NULL;
	read = fopen("objects.bin", "r+b");
	if (read == NULL) {
		system("cls");
		printf("\n\t\t"RED"Error!"ESC"\nThere are no objects, for now...\n");
		_getch();
		return;
	}

	OBJECTS* read_St = NULL;
	fread(&obj_Num, sizeof(int), 1, read);
	read_St = (OBJECTS*)calloc(obj_Num, sizeof(OBJECTS));
	if (read_St == NULL) {
		perror("Struct error");
		exit(EXIT_FAILURE);
	}

	fseek(read, sizeof(int), SEEK_SET);
	fread(read_St, sizeof(OBJECTS), obj_Num, read);

	do {
		system("cls");
		if (admin_Logged == 1) {
			printf("\t  Logged in as: "RED"[%s]"ESC"\n\n\tEditing objects "RED"[BE CAREFUL!]\n\n"ESC"[1] Edit by ID\n[2] Return\n\nChoice: ", logged_As);
		}
		else {
			printf("\t  Logged in as: "BLUE"[%s]"ESC"\n\n\tEditing objects "RED"[BE CAREFUL!]\n\n"ESC"[1] Edit by ID\n[2] Return\n\nChoice: ", logged_As);
		}
		scanf("%d", &edit_Obj);
	} while (edit_Obj < 1 || edit_Obj > 2);
	switch (edit_Obj) {
	case 1: {
		system("cls");
		printf("\n\t"YLW"Edit objects by ID:\n\n"ESC"Enter ID: ");
		scanf("%d", &obj_ID_Choice);

		for (i = 0; i < obj_Num; i++) {
			if (obj_ID_Choice == (read_St + i)->ID) {
				flag = 1;
				break;
			}
		}

		if (flag == 0) {
			printf("\nNo object with ID [%d].\n", obj_ID_Choice);
			_getch();
			return;
		}
		else {
			OBJECTS* temp = NULL;
			temp = (OBJECTS*)calloc(1, sizeof(OBJECTS));
			if (temp == NULL) {
				perror("Struct error");
				exit(EXIT_FAILURE);
			}

			system("cls");
			printf("\n\tEditing ID [%d] of "YLW"object"ESC".\n\nEnter object ID: ", obj_ID_Choice);
			scanf("%d", &temp->ID);
			printf("Enter season: ");
			scanf("%d", &temp->season); getchar();
			printf("Enter name: ");
			fgets(temp->name, 99, stdin);
			printf("Enter manufacturer: ");
			fgets(temp->manufacturer, 39, stdin);
			printf("Enter use: ");
			fgets(temp->use, 99, stdin);
			printf("Enter powers: ");
			fgets(temp->powers, 99, stdin);
			printf("Enter location / stauts: ");
			fgets(temp->location_Status, 99, stdin);
			for (i = 0; i < obj_Num; i++) {
				if (obj_ID_Choice == (read_St + i)->ID) {
					fseek(read, ftell(read) - sizeof(OBJECTS), SEEK_SET);
					fwrite(temp, sizeof(OBJECTS), 1, read);
					fclose(read);
					free(temp);
					free(read_St);
					break;
				}
			}
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

void list_Objects(void) {

	//enter from object_Edit_Menu
	int list_Choice, obj_Num;

	FILE* read = NULL;
	read = fopen("objects.bin", "r+b");
	if (read == NULL) {
		system("cls");
		printf("\n\t\t"RED"Error!"ESC"\nThere are no objects, for now...\n");
		_getch();
		return;
	}

	do {
		system("cls");
		if (admin_Logged == 1) {
			printf("\t  Logged in as: "RED"[%s]"ESC"\n\n\t"YLW"List objects by:\n\n"ESC"[1] ID\n[2] Season\n[3] Manufacturer\n[4] Use\n[5] Return\n\nChoice: ", logged_As);
		}
		else {
			printf("\t  Logged in as: "BLUE"[%s]"ESC"\n\n\t"YLW"List objects by:\n\n"ESC"[1] ID\n[2] Season\n[3] Manufacturer\n[4] Use\n[5] Return\n\nChoice: ", logged_As);
		}
		scanf("%d", &list_Choice);
	} while (list_Choice < 1 || list_Choice > 5);

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
			printf("\n\t"YLW"Sort objects by ID:\n\n"ESC"[1] Ascending\n[2] Descending\n\nChoice: ");
			scanf("%d", &asc_Desc);
		} while (asc_Desc < 1 || asc_Desc > 2);

		fseek(read, sizeof(int), SEEK_SET);
		fread(read_St, sizeof(OBJECTS), obj_Num, read);
		if (asc_Desc == 1)
			qsort(read_St, obj_Num, sizeof(OBJECTS), compare_ID_Asc_Objects);
		else
			qsort(read_St, obj_Num, sizeof(OBJECTS), compare_ID_Desc_Objects);
		system("cls");
		printf("\n\tNumber of "YLW"objects"ESC": [%d]\n\n", obj_Num);
		for (i = 0; i < obj_Num; i++) {
			fprintf(stdout, BMNG"\n[%d] ID:"ESC" %d\n", i + 1, (read_St + i)->ID);
			fprintf(stdout, BMNG"[%d] Season:"ESC" %d\n", i + 1, (read_St + i)->season);
			fprintf(stdout, BMNG"[%d] Name:"ESC" %s", i + 1, (read_St + i)->name);
			fprintf(stdout, BMNG"[%d] Manufacturer:"ESC" %s", i + 1, (read_St + i)->manufacturer);
			fprintf(stdout, BMNG"[%d] Use:"ESC" %s", i + 1, (read_St + i)->use);
			fprintf(stdout, BMNG"[%d] Powers:"ESC" %s", i + 1, (read_St + i)->powers);
			fprintf(stdout, BMNG"[%d] Location / status:"ESC" %s\n", i + 1, (read_St + i)->location_Status);
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
		printf("\n\tNumber of "YLW"objects"ESC": [%d]\n\n", obj_Num);
		for (i = 0; i < obj_Num; i++) {
			fprintf(stdout, BMNG"\n[%d] ID:"ESC" %d\n", i + 1, (read_St + i)->ID);
			fprintf(stdout, BMNG"[%d] Season:"ESC" %d\n", i + 1, (read_St + i)->season);
			fprintf(stdout, BMNG"[%d] Name:"ESC" %s", i + 1, (read_St + i)->name);
			fprintf(stdout, BMNG"[%d] Manufacturer:"ESC" %s", i + 1, (read_St + i)->manufacturer);
			fprintf(stdout, BMNG"[%d] Use:"ESC" %s", i + 1, (read_St + i)->use);
			fprintf(stdout, BMNG"[%d] Powers:"ESC" %s", i + 1, (read_St + i)->powers);
			fprintf(stdout, BMNG"[%d] Location / status:"ESC" %s\n", i + 1, (read_St + i)->location_Status);
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
		printf("\n\tNumber of "YLW"objects"ESC": [%d]\n\n", obj_Num);
		for (i = 0; i < obj_Num; i++) {
			fprintf(stdout, BMNG"\n[%d] ID:"ESC" %d\n", i + 1, (read_St + i)->ID);
			fprintf(stdout, BMNG"[%d] Season:"ESC" %d\n", i + 1, (read_St + i)->season);
			fprintf(stdout, BMNG"[%d] Name:"ESC" %s", i + 1, (read_St + i)->name);
			fprintf(stdout, BMNG"[%d] Manufacturer:"ESC" %s", i + 1, (read_St + i)->manufacturer);
			fprintf(stdout, BMNG"[%d] Use:"ESC" %s", i + 1, (read_St + i)->use);
			fprintf(stdout, BMNG"[%d] Powers:"ESC" %s", i + 1, (read_St + i)->powers);
			fprintf(stdout, BMNG"[%d] Location / status:"ESC" %s\n", i + 1, (read_St + i)->location_Status);
		}
		fprintf(stdout, "\nEnd of list! Continue...\n");
		_getch();
		fclose(read);
		free(read_St);
		return;
	}
	case 4: {
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
		printf("\n\tNumber of "YLW"objects"ESC": [%d]\n\n", obj_Num);
		for (i = 0; i < obj_Num; i++) {
			fprintf(stdout, BMNG"\n[%d] ID:"ESC" %d\n", i + 1, (read_St + i)->ID);
			fprintf(stdout, BMNG"[%d] Season:"ESC" %d\n", i + 1, (read_St + i)->season);
			fprintf(stdout, BMNG"[%d] Name:"ESC" %s", i + 1, (read_St + i)->name);
			fprintf(stdout, BMNG"[%d] Manufacturer:"ESC" %s", i + 1, (read_St + i)->manufacturer);
			fprintf(stdout, BMNG"[%d] Use:"ESC" %s", i + 1, (read_St + i)->use);
			fprintf(stdout, BMNG"[%d] Powers:"ESC" %s", i + 1, (read_St + i)->powers);
			fprintf(stdout, BMNG"[%d] Location / status:"ESC" %s\n", i + 1, (read_St + i)->location_Status);
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
		return;
	}
	}

}

void search_Objects(void) {

	//enter from object_Edit_Menu
	int search_Choice, i, obj_Num;

	FILE* search = NULL;
	search = fopen("objects.bin", "rb");
	if (search == NULL) {
		system("cls");
		printf("\n\t\t"RED"Error!"ESC"\nThere are no objects, for now...\n");
		_getch();
		return;
	}

	do {
		system("cls");
		if(admin_Logged == 1) {
			printf("\t  Logged in as: "RED"[%s]"ESC"\n\n\t"YLW"Search objects by:\n\n"ESC"[1] ID\n[2] Season\n[3] Name\n[4] Manufacturer\n[5] Return to edit panel\n\nChoice: ", logged_As);
		}
		else {
			printf("\t  Logged in as: "BLUE"[%s]"ESC"\n\n\t"YLW"Search objects by:\n\n"ESC"[1] ID\n[2] Season\n[3] Name\n[4] Manufacturer\n[5] Return to edit panel\n\nChoice: ", logged_As);
		}
		scanf("%d", &search_Choice);
	} while (search_Choice < 1 || search_Choice > 5);

	OBJECTS* read_St = NULL;
	fread(&obj_Num, sizeof(int), 1, search);
	read_St = (OBJECTS*)calloc(obj_Num, sizeof(OBJECTS));
	if (read_St == NULL) {
		perror("Struct error");
		exit(EXIT_FAILURE);
	}

	switch (search_Choice) {
	case 1: {
		int ID_Srch, flag = 0;
		system("cls");
		printf("\nEnter ID: ");
		scanf("%d", &ID_Srch);
		for (i = 0; i < obj_Num; i++) {
			fread(read_St, sizeof(OBJECTS), 1, search);
			if (read_St->ID == ID_Srch) {
				fprintf(stdout, BMNG"\n[%d] ID:"ESC" %d\n", i + 1, (read_St + i)->ID);
				fprintf(stdout, BMNG"[%d] Season:"ESC" %d\n", i + 1, (read_St + i)->season);
				fprintf(stdout, BMNG"[%d] Name:"ESC" %s", i + 1, read_St->name);
				fprintf(stdout, BMNG"[%d] Manufacturer:"ESC" %s", i + 1, read_St->manufacturer);
				fprintf(stdout, BMNG"[%d] Use:"ESC" %s", i + 1, read_St->use);
				fprintf(stdout, BMNG"[%d] Powers:"ESC" %s", i + 1, read_St->powers);
				fprintf(stdout, BMNG"[%d] Location / status:"ESC" %s\n", i + 1, read_St->location_Status);
				flag = 1;
				_getch();
			}
		}
		if (flag == 0) {
			printf("\nNo objects with ID: [%d].\n", ID_Srch);
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
		int seas_Srch, flag = 0;
		system("cls");
		printf("\nEnter season: ");
		scanf("%d", &seas_Srch);
		for (i = 0; i < obj_Num; i++) {
			fread(read_St, sizeof(OBJECTS), 1, search);
			if (read_St->season == seas_Srch) {
				fprintf(stdout, BMNG"\n[%d] ID:"ESC" %d\n", i + 1, (read_St + i)->ID);
				fprintf(stdout, BMNG"[%d] Season:"ESC" %d\n", i + 1, (read_St + i)->season);
				fprintf(stdout, BMNG"[%d] Name:"ESC" %s", i + 1, read_St->name);
				fprintf(stdout, BMNG"[%d] Manufacturer:"ESC" %s", i + 1, read_St->manufacturer);
				fprintf(stdout, BMNG"[%d] Use:"ESC" %s", i + 1, read_St->use);
				fprintf(stdout, BMNG"[%d] Powers:"ESC" %s", i + 1, read_St->powers);
				fprintf(stdout, BMNG"[%d] Location / status:"ESC" %s\n", i + 1, read_St->location_Status);
				flag = 1;
				_getch();
			}
		}
		if (flag == 0) {
			printf("\nNo objects on season: [%d].\n", seas_Srch);
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
	case 3: {
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
				fprintf(stdout, BMNG"\n[%d] ID:"ESC" %d\n", i + 1, (read_St + i)->ID);
				fprintf(stdout, BMNG"[%d] Season:"ESC" %d\n", i + 1, (read_St + i)->season);
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
		if (flag == 0) {
			*(srch_Obj_Nm + (strlen(srch_Obj_Nm) - 1)) = 0;
			printf("\nNo object with name: [%s].\n", srch_Obj_Nm);
			_getch();
		}
		else {
			printf("End of list.");
			_getch();
		}
		free(read_St);
		free(srch_Obj_Nm);
		fclose(search);
		return;
	}
	case 4: {
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
				fprintf(stdout, BMNG"\n[%d] ID:"ESC" %d\n", i + 1, (read_St + i)->ID);
				fprintf(stdout, BMNG"[%d] Season:"ESC" %d\n", i + 1, (read_St + i)->season);
				fprintf(stdout, BMNG"[%d] Name:"ESC" %s", i + 1, read_St->name);
				fprintf(stdout, BMNG"[%d] Manufacturer:"ESC" %s", i + 1, read_St->manufacturer);
				fprintf(stdout, BMNG"[%d] Use:"ESC" %s", i + 1, read_St->use);
				fprintf(stdout, BMNG"[%d] Powers:"ESC" %s", i + 1, read_St->powers);
				fprintf(stdout, BMNG"[%d] Location / status:"ESC" %s\n", i + 1, read_St->location_Status);
				flag = 1;
				_getch();
			}
		}
		if (flag == 0) {
			*(srch_Manuf + (strlen(srch_Manuf) - 1)) = 0;
			printf("\nNo manufacturer(s) named: [%s].\n", srch_Manuf);
			_getch();
		}
		else {
			printf("End of list.");
			_getch();
		}
		free(read_St);
		free(srch_Manuf);
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