#include "header.h"
#include "colors.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

void admin_Edit_Board(void) {
	
	//enter from admins_Menu
	int admin_Edit;
	while(1) {
		system("cls");
		printf("\t  Logged in as: "RED"[%s]"ESC"\n\n\t"RED"Admin editing\n\n"ESC"[1] Add an admin\n[2] Remove an admin\n[3] List admins\n[4] Search admins\n[5] Return\n\nChoice: ", logged_As);
		scanf("%d", &admin_Edit);

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
	while(1) {
		system("cls");
		printf("\t  Logged in as: "RED"[% s]"ESC"\n\n\t"BLUE"Member editing\n\n"ESC"[1] Add a member\n[2] Remove a member\n[3] List members\n[4] Search members\n[5] Return\n\nChoice: ", logged_As);
		scanf("%d", &mem_Edit);

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
	while(1) {
		system("cls");
		printf("\t  Logged in as: "RED"[% s]"ESC"\n\n\t"BYLW"Library editing\n\n"ESC"[1] "BRED"Characters"ESC"\n[2] "CYN"Locations"ESC"\n[3] "BMNG"Music"ESC"\n[4] "YLW"Objects"ESC"\n[5] "RED"Rituals & Spells"ESC"\n[6] "GRN"Seasons"ESC"\n[7] "MNG"Trivia"ESC"\n[8] Return\n\nChoice: ", logged_As);
		scanf("%d", &lib_Ed);
	
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

			}
			case 7: {

			}
			case 8: {
				return;
			}
		}
	}
}