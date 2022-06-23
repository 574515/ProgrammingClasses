#include "header.h"
#include "colors.h"
#include <stdio.h>
#include <stdlib.h>

void members_Menu(void) {
	
	//enter from admins_Menu
	if(admin_Logged == 1){
		int choice;
		do {
			system("cls");
			printf("\t  Logged in as: "RED"[%s]"ESC"\n\n\t"BYLW"Welcome to the Supernatural Library!"ESC"\n\n", logged_As);
			printf("[1] "BRED"Characters"ESC"\n[2] "CYN"Locations"ESC"\n[3] "BMNG"Music"ESC"\n[4] "YLW"Objects"ESC"\n[5] "RED"Rituals & Spells"ESC"\n[6] "GRN"Seasons"ESC"\n[7] "MNG"Trivia"ESC"\n[8] "BGRN"Return to admin panel"ESC"\n[9] "BBLUE"Log out"ESC"\n[10] "BCYN"Exit"ESC"\n\nChoice: ");
			scanf("%d", &choice);
		} while (choice < 1 || choice > 10);
		switch (choice) {
			case 8: {
				return;
			}
			case 9: {
				free(logged_As);
				initial_Menu();
				break;
			}
			case 10: {
				free(logged_As);
				exit(EXIT_SUCCESS);
			}
		}
	}
	else {
		int choice;
		do {
			system("cls");
			printf("\t  Logged in as: "BLUE"[%s]"ESC"\n\n\t"BYLW"Welcome to the Supernatural Library!"ESC"\n\n", logged_As);
			printf("[1] "BRED"Characters"ESC"\n[2] "CYN"Locations"ESC"\n[3] "BMNG"Music"ESC"\n[4] "YLW"Objects"ESC"\n[5] "RED"Rituals & Spells"ESC"\n[6] "GRN"Seasons"ESC"\n[7] "MNG"Trivia"ESC"\n[8] "BCYN"Exit"ESC"\n\nChoice: ");
			scanf("%d", &choice);
		} while (choice < 1 || choice > 8);
	}
}