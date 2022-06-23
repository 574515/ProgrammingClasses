#ifndef STRUCTS_H
#define STRUCTS_H
#include <stdbool.h>

typedef struct admins {
	int ID;
	char username[30];
	char password[30];
	char f_Name[30];
	char l_Name[30];
}ADMINS;

typedef struct members {
	int ID;
	char username[30];
	char password[30];
	char f_Name[30];
	char l_Name[30];
	char contact[50];
}MEMBERS;

typedef struct characters {
	int ID;
	char first_N[100];
	char last_N[100];
	char species[500];
	bool alive;
	char titles[1000];
	char occupation[1000];
	char affiliation[1000];
	char family[1000];
	char portrayed[1000];
}CHARACTERS;

typedef struct locations {
	int ID;
	int season;
	char episode_Name[100];
	char location[250];
}LOCATIONS;

typedef struct music {
	int ID;
	int season;
	char episode_Name[100];
	char song_Name[100];
	char author[100];
}MUSIC;

typedef struct objects {
	int ID;
	int season;
	char name[100];
	char manufacturer[40];
	char use[100];
	char powers[100];
	char location_Status[100];
}OBJECTS;

typedef struct rits_Spells {
	int ID;
	char name[100];
	char manuf_caster[100];
	char used[300];
	char details[500];
	bool ritual;
	bool spell;
}RITSSPELLS;

typedef struct seasons {
	int ID;
	int num_Eps;
	char premier[40];
	char prem_Dat[15];
	char finale[40];
	char fin_Date[15];
	char summary[700];
}SEASONS;

#endif //STRUCTS_H