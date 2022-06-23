#ifndef HEADER_H
#define HEADER_H
#define _CRT_SECURE_NO_WARNINGS

//global_Variables
int admin_Logged;
char* logged_As;
char c;
//admins_Panel.c
void admins_Menu(void);
void members_Menu(void);
void admin_Input(void);
void del_Admins(void);
void list_Admins(void);
void search_Admins(void);
void member_Input(void);
void del_Members(void);
void list_Members(void);
void search_Members(void);
void admin_Edit_Board(void);
void member_Edit_Board(void);
void library_Edit_Board(void);
//characters.c
void chars_Edit_Menu(void);
void add_Chars(void);
void del_Chars(void);
void edit_Chars(void);
void list_Chars(void);
void search_Chars(void);
//default_Funcs.c
void initial_Menu(void);
void admins_Login(void);
void members_Login(void);
void usage(void);
//locations.c
void locs_Edit_Menu(void);
void add_Locations(void);
void del_Locations(void);
void edit_Locations(void);
void list_Locations(void);
void search_Locations(void);
/*main.c
empty -> function call*/
//music.c
void music_Edit_Menu(void);
void add_Music(void);
void del_Music(void);
void edit_Music(void);
void list_Music(void);
void search_Music(void);
//objects.c
void object_Edit_Menu(void);
void add_Objects(void);
void del_Objects(void);
void edit_Objects(void);
void list_Objects(void);
void search_Objects(void);
//rituals_And_Spells.c
void rit_Spell_Edit_Menu(void);
void rit_Spell_Add(void);
void del_Rit_Spell(void);
void edit_Rit_Spell(void);
void rit_Spell_List(void);
void search_Rit_Spell(void);
//seasons.c
void seas_Edit_Menu(void);
void seas_Add(void);
void del_Seas(void);
void edit_Seas(void);
void seas_List(void);
void search_Seas(void);
//sorting_Funcs.c
int comp_ID_Admin_Asc(const void*, const void*);
int comp_ID_Admin_Desc(const void*, const void*);
int comp_Un_Admin_Asc(const void*, const void*);
int comp_Un_Admin_Desc(const void*, const void*);
int comp_Fn_Admin_Asc(const void*, const void*);
int comp_Fn_Admin_Desc(const void*, const void*);
int comp_ID_Member_Asc(const void*, const void*);
int comp_ID_Member_Desc(const void*, const void*);
int comp_Un_Member_Asc(const void*, const void*);
int comp_Un_Member_Desc(const void*, const void*);
int comp_Fn_Member_Asc(const void*, const void*);
int comp_Fn_Member_Desc(const void*, const void*);
int compare_ID_Asc_Locs(const void*, const void*);
int compare_ID_Desc_Locs(const void*, const void*);
int compare_ID_Asc_Chars(const void*, const void*);
int compare_ID_Desc_Chars(const void*, const void*);
int comp_Fn_Chars_Asc(const void*, const void*);
int comp_Fn_Chars_Desc(const void*, const void*);
int comp_Ln_Chars_Asc(const void*, const void*);
int comp_Ln_Chars_Desc(const void*, const void*);
int comp_Species_Chars_Asc(const void*, const void*);
int comp_Species_Chars_Desc(const void*, const void*);
int compare_Season_Asc_Locs(const void*, const void*);
int compare_Season_Desc_Locs(const void*, const void*);
int comp_Episode_Asc_Locs(const void*, const void*);
int comp_Episode_Desc_Locs(const void*, const void*);
int comp_Location_Asc_Locs(const void*, const void*);
int comp_Location_Desc_Locs(const void*, const void*);
int compare_Season_Asc_Music(const void*, const void*);
int compare_Season_Desc_Music(const void*, const void*);
int comp_Song_Name_Asc_Music(const void*, const void*);
int comp_Song_Name_Desc_Music(const void*, const void*);
int comp_Author_Asc_Music(const void*, const void*);
int comp_Author_Desc_Music(const void*, const void*);
int compare_ID_Asc_Objects(const void*, const void*);
int compare_ID_Desc_Objects(const void*, const void*);
int compare_Season_Asc_Objects(const void*, const void*);
int compare_Season_Desc_Objects(const void*, const void*);
int comp_Manufacturer_Asc_Objects(const void*, const void*);
int comp_Manufacturer_Desc_Objects(const void*, const void*);
int comp_Use_Asc_Objects(const void*, const void*);
int comp_Use_Desc_Objects(const void*, const void*);
int comp_ID_Asc_Rsp(const void*, const void*);
int comp_ID_Desc_Rsp(const void*, const void*);
int compare_Season_Asc(const void*, const void*);
int compare_Season_Desc(const void*, const void*);
int compare_Season_No_Ep_Asc(const void*, const void*);
int compare_Season_No_Ep_Desc(const void*, const void*);

#endif //HEADER_H