#include "header.h"
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>

//file pointer
FILE* stuff_For_Files(FILE* pointer, char* location, char* mode) {

	pointer = fopen(location, mode);
	if (pointer == NULL) {
		return NULL;
	}
	else {
		return pointer;
	}
}

//structs
ADMINS* admin_Allocs(ADMINS* adms, int n) {

	adms = (ADMINS*)calloc(n, sizeof(ADMINS));
	if (adms == NULL) {
		return NULL;
	}
	else {
		return adms;
	}
}

MEMBERS* member_Allocs(MEMBERS* mems, int n) {

	mems = (MEMBERS*)calloc(n, sizeof(MEMBERS));
	if (mems == NULL) {
		return NULL;
	}
	else {
		return mems;
	}
}

CHARACTERS* char_Allocs(CHARACTERS* chars, int n) {

	chars = (CHARACTERS*)calloc(n, sizeof(CHARACTERS));
	if (chars == NULL) {
		return NULL;
	}
	else {
		return chars;
	}
}

LOCATIONS* locs_Allocs(LOCATIONS* locs, int n) {

	locs = (LOCATIONS*)calloc(n, sizeof(LOCATIONS));
	if(locs == NULL) {
		return NULL;
	}
	else {
		return locs;
	}
}

MUSIC* music_Allocs(MUSIC* music, int n) {

	music = (MUSIC*)calloc(n, sizeof(MUSIC));
	if (music == NULL) {
		return NULL;
	}
	else {
		return music;
	}
}

OBJECTS* obj_Allocs(OBJECTS* objs, int n) {

	objs = (OBJECTS*)calloc(n, sizeof(OBJECTS));
	if (objs == NULL) {
		return NULL;
	}
	else {
		return objs;
	}
}

RITSSPELLS* ras_Allocs(RITSSPELLS* ras, int n) {

	ras = (RITSSPELLS*)calloc(n, sizeof(RITSSPELLS));
	if (ras == NULL) {
		return NULL;
	}
	else {
		return ras;
	}
}

SEASONS* sea_Allocs(SEASONS* seas, int n) {

	seas = (SEASONS*)calloc(n, sizeof(SEASONS));
	if (seas == NULL) {
		return NULL;
	}
	else {
		return seas;
	}
}