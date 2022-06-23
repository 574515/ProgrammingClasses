#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//admins
int comp_ID_Admin_Asc(const void* x, const void* y) {

	ADMINS* ID_x = (ADMINS*)x;
	ADMINS* ID_y = (ADMINS*)y;

	return (ID_x->ID - ID_y->ID);
}

int comp_ID_Admin_Desc(const void* x, const void* y) {

	ADMINS* ID_x = (ADMINS*)x;
	ADMINS* ID_y = (ADMINS*)y;

	return (ID_y->ID - ID_x->ID);
}

int comp_Un_Admin_Asc(const void* a, const void* b) {

	ADMINS* un_A = (ADMINS*)a;
	ADMINS* un_B = (ADMINS*)b;

	return -(strcmp(un_B->username, un_A->username));
}

int comp_Un_Admin_Desc(const void* a, const void* b) {

	ADMINS* un_A = (ADMINS*)a;
	ADMINS* un_B = (ADMINS*)b;

	return strcmp(un_B->username, un_A->username);
}

int comp_Fn_Admin_Asc(const void* a, const void* b) {

	ADMINS* fn_A = (ADMINS*)a;
	ADMINS* fn_B = (ADMINS*)b;

	return -(strcmp(fn_B->f_Name, fn_A->f_Name));
}

int comp_Fn_Admin_Desc(const void* a, const void* b) {

	ADMINS* fn_A = (ADMINS*)a;
	ADMINS* fn_B = (ADMINS*)b;

	return strcmp(fn_B->f_Name, fn_A->f_Name);
}

//members
int comp_ID_Member_Asc(const void* x, const void* y) {

	MEMBERS* ID_x = (MEMBERS*)x;
	MEMBERS* ID_y = (MEMBERS*)y;

	return (ID_x->ID - ID_y->ID);
}

int comp_ID_Member_Desc(const void* x, const void* y) {

	MEMBERS* ID_x = (MEMBERS*)x;
	MEMBERS* ID_y = (MEMBERS*)y;

	return (ID_y->ID - ID_x->ID);
}

int comp_Un_Member_Asc(const void* a, const void* b) {

	MEMBERS* un_A = (MEMBERS*)a;
	MEMBERS* un_B = (MEMBERS*)b;

	return -(strcmp(un_B->username, un_A->username));
}

int comp_Un_Member_Desc(const void* a, const void* b) {

	MEMBERS* un_A = (MEMBERS*)a;
	MEMBERS* un_B = (MEMBERS*)b;

	return strcmp(un_B->username, un_A->username);
}

int comp_Fn_Member_Asc(const void* a, const void* b) {

	MEMBERS* fn_A = (MEMBERS*)a;
	MEMBERS* fn_B = (MEMBERS*)b;

	return -(strcmp(fn_B->f_Name, fn_A->f_Name));
}

int comp_Fn_Member_Desc(const void* a, const void* b) {

	MEMBERS* fn_A = (MEMBERS*)a;
	MEMBERS* fn_B = (MEMBERS*)b;

	return strcmp(fn_B->f_Name, fn_A->f_Name);
}

//chars
int compare_ID_Asc_Chars(const void* x, const void* y) {

	CHARACTERS* ID_x = (CHARACTERS*)x;
	CHARACTERS* ID_y = (CHARACTERS*)y;

	return (ID_x->ID - ID_y->ID);
}

int compare_ID_Desc_Chars(const void* x, const void* y) {

	CHARACTERS* ID_x = (CHARACTERS*)x;
	CHARACTERS* ID_y = (CHARACTERS*)y;

	return (ID_y->ID - ID_x->ID);
}

int comp_Fn_Chars_Asc(const void* a, const void* b) {

	CHARACTERS* fn_A = (CHARACTERS*)a;
	CHARACTERS* fn_B = (CHARACTERS*)b;

	return -(strcmp(fn_B->first_N, fn_A->first_N));
}

int comp_Fn_Chars_Desc(const void* a, const void* b) {
	
	CHARACTERS* fn_A = (CHARACTERS*)a;
	CHARACTERS* fn_B = (CHARACTERS*)b;

	return strcmp(fn_B->first_N, fn_A->first_N);
}

int comp_Ln_Chars_Asc(const void* a, const void* b) {

	CHARACTERS* ln_A = (CHARACTERS*)a;
	CHARACTERS* ln_B = (CHARACTERS*)b;

	return -(strcmp(ln_B->last_N, ln_A->last_N));
}

int comp_Ln_Chars_Desc(const void* a, const void* b) {

	CHARACTERS* ln_A = (CHARACTERS*)a;
	CHARACTERS* ln_B = (CHARACTERS*)b;

	return strcmp(ln_B->last_N, ln_A->last_N);
}

int comp_Species_Chars_Asc(const void* a, const void* b) {

	CHARACTERS* spec_A = (CHARACTERS*)a;
	CHARACTERS* spec_B = (CHARACTERS*)b;

	return -(strcmp(spec_B->species, spec_A->species));
}

int comp_Species_Chars_Desc(const void* a, const void* b) {

	CHARACTERS* spec_A = (CHARACTERS*)a;
	CHARACTERS* spec_B = (CHARACTERS*)b;

	return strcmp(spec_B->species, spec_A->species);
}

//locations
int compare_ID_Asc_Locs(const void* x, const void* y) {

	LOCATIONS* ID_x = (LOCATIONS*)x;
	LOCATIONS* ID_y = (LOCATIONS*)y;

	return (ID_x->ID - ID_y->ID);
}

int compare_ID_Desc_Locs(const void* x, const void* y) {

	LOCATIONS* ID_x = (LOCATIONS*)x;
	LOCATIONS* ID_y = (LOCATIONS*)y;

	return (ID_y->ID - ID_x->ID);
}

int compare_Season_Asc_Locs(const void* x, const void* y) {

	LOCATIONS* seas_x = (LOCATIONS*)x;
	LOCATIONS* seas_y = (LOCATIONS*)y;

	return (seas_x->season - seas_y->season);
}

int compare_Season_Desc_Locs(const void* x, const void* y) {

	LOCATIONS* seas_x = (LOCATIONS*)x;
	LOCATIONS* seas_y = (LOCATIONS*)y;

	return (seas_y->season - seas_x->season);
}

int comp_Episode_Asc_Locs(const void* a, const void* b) {

	LOCATIONS* epn_A = (LOCATIONS*)a;
	LOCATIONS* epn_B = (LOCATIONS*)b;

	return -(strcmp(epn_B->episode_Name, epn_A->episode_Name));
}

int comp_Episode_Desc_Locs(const void* a, const void* b) {

	LOCATIONS* epn_A = (LOCATIONS*)a;
	LOCATIONS* epn_B = (LOCATIONS*)b;

	return strcmp(epn_B->episode_Name, epn_A->episode_Name);
}

int comp_Location_Asc_Locs(const void* a, const void* b) {

	LOCATIONS* loc_A = (LOCATIONS*)a;
	LOCATIONS* loc_B = (LOCATIONS*)b;

	return -(strcmp(loc_B->location, loc_A->location));
}

int comp_Location_Desc_Locs(const void* a, const void* b) {

	LOCATIONS* loc_A = (LOCATIONS*)a;
	LOCATIONS* loc_B = (LOCATIONS*)b;

	return strcmp(loc_B->location, loc_A->location);
}

//music
int compare_Season_Asc_Music(const void* x, const void* y) {

	MUSIC* seas_x = (MUSIC*)x;
	MUSIC* seas_y = (MUSIC*)y;

	return (seas_x->season - seas_y->season);
}

int compare_Season_Desc_Music(const void* x, const void* y) {

	MUSIC* seas_x = (MUSIC*)x;
	MUSIC* seas_y = (MUSIC*)y;

	return (seas_y->season - seas_x->season);
}

int comp_Song_Name_Asc_Music(const void* a, const void* b) {

	MUSIC* snm_A = (MUSIC*)a;
	MUSIC* snm_B = (MUSIC*)b;

	return -(strcmp(snm_B->song_Name, snm_A->song_Name));
}

int comp_Song_Name_Desc_Music(const void* a, const void* b) {

	MUSIC* snm_A = (MUSIC*)a;
	MUSIC* snm_B = (MUSIC*)b;

	return strcmp(snm_B->song_Name, snm_A->song_Name);
}

int comp_Author_Asc_Music(const void* a, const void* b) {

	MUSIC* ath_A = (MUSIC*)a;
	MUSIC* ath_B = (MUSIC*)b;

	return -(strcmp(ath_B->author, ath_A->author));
}

int comp_Author_Desc_Music(const void* a, const void* b) {

	MUSIC* ath_A = (MUSIC*)a;
	MUSIC* ath_B = (MUSIC*)b;

	return strcmp(ath_B->author, ath_A->author);
}

//objects
int compare_ID_Asc_Objects(const void* x, const void* y) {

	OBJECTS* ID_X = (OBJECTS*)x;
	OBJECTS* ID_Y = (OBJECTS*)y;

	return (ID_X->ID - ID_Y->ID);
}

int compare_ID_Desc_Objects(const void* x, const void* y) {

	OBJECTS* ID_X = (OBJECTS*)x;
	OBJECTS* ID_Y = (OBJECTS*)y;

	return (ID_Y->ID - ID_X->ID);
}

int compare_Season_Asc_Objects(const void* x, const void* y) {

	OBJECTS* seas_x = (OBJECTS*)x;
	OBJECTS* seas_y = (OBJECTS*)y;

	return (seas_x->season - seas_y->season);
}

int compare_Season_Desc_Objects(const void* x, const void* y) {

	OBJECTS* seas_x = (OBJECTS*)x;
	OBJECTS* seas_y = (OBJECTS*)y;

	return (seas_y->season - seas_x->season);
}

int comp_Manufacturer_Asc_Objects(const void* a, const void* b) {

	OBJECTS* manf_A = (OBJECTS*)a;
	OBJECTS* manf_B = (OBJECTS*)b;

	return -(strcmp(manf_B->manufacturer, manf_A->manufacturer));
}

int comp_Manufacturer_Desc_Objects(const void* a, const void* b) {

	OBJECTS* manf_A = (OBJECTS*)a;
	OBJECTS* manf_B = (OBJECTS*)b;

	return strcmp(manf_B->manufacturer, manf_A->manufacturer);
}

int comp_Use_Asc_Objects(const void* a, const void* b) {

	OBJECTS* use_A = (OBJECTS*)a;
	OBJECTS* use_B = (OBJECTS*)b;

	return -(strcmp(use_B->use, use_A->use));
}

int comp_Use_Desc_Objects(const void* a, const void* b) {

	OBJECTS* use_A = (OBJECTS*)a;
	OBJECTS* use_B = (OBJECTS*)b;

	return strcmp(use_B->use, use_A->use);
}

//spells and rituals
int comp_ID_Asc_Rsp(const void* x, const void* y) {

	RITSSPELLS* ID_x = (RITSSPELLS*)x;
	RITSSPELLS* ID_y = (RITSSPELLS*)y;

	return (ID_x->ID - ID_y->ID);
}

int comp_ID_Desc_Rsp(const void* x, const void* y) {

	RITSSPELLS* ID_x = (RITSSPELLS*)x;
	RITSSPELLS* ID_y = (RITSSPELLS*)y;

	return (ID_y->ID - ID_x->ID);
}

//seasons
int compare_Season_Asc(const void* x, const void* y) {

	SEASONS* ID_x = (SEASONS*)x;
	SEASONS* ID_y = (SEASONS*)y;

	return (ID_x->ID - ID_y->ID);
}

int compare_Season_Desc(const void* x, const void* y) {

	SEASONS* ID_x = (SEASONS*)x;
	SEASONS* ID_y = (SEASONS*)y;

	return (ID_y->ID - ID_x->ID);
}

int compare_Season_No_Ep_Asc(const void* x, const void* y) {

	SEASONS* nuep_X = (SEASONS*)x;
	SEASONS* nuep_Y = (SEASONS*)y;

	return (nuep_X->num_Eps - nuep_Y->num_Eps);
}

int compare_Season_No_Ep_Desc(const void* x, const void* y) {

	SEASONS* nuep_X = (SEASONS*)x;
	SEASONS* nuep_Y = (SEASONS*)y;

	return (nuep_Y->num_Eps - nuep_X->num_Eps);
}