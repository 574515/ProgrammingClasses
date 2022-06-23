#ifndef HEADER_H
#define HEADER_H
#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

char* logged_Admin;
char c;

typedef struct ADMINISTRATOR {
	int ID;
	char username[15];
	char password[30];
	char first_Name[20];
	char last_Name[20];
	char contact[40];
} ADMIN;

typedef struct INVENTAR {
	int ID;
	char type[30];
	char name[30];
	char description[100];
	int quantity;
} INV;

// manage_Admins.c
void admin_Input(void);
void admin_Delete(void);
void admin_Search(void);
void admin_List(void);

// manage_Inventory.c
void inventory_Input(void);
void inventory_Delete(void);
void inventory_Search(void);
void inventory_List(void);

// manage_Memory.c
ADMIN* allocate_Admin(int);
INV* allocate_Inventory(int);
void prepare_Logged(char*, int);

// menus.c
void login_Menu(void);
void main_Menu(void);
void inventory_Menu(void);
void admin_Menu(void);

// qsort_Compare.c
int admin_ID_Asc(const void*, const void*);
int admin_ID_Desc(const void*, const void*);
int admin_Un_Asc(const void*, const void*);
int admin_Un_Desc(const void*, const void*);
int admin_Fn_Asc(const void*, const void*);
int admin_Fn_Desc(const void*, const void*);
int inventory_ID_Asc(const void*, const void*);
int inventory_ID_Desc(const void*, const void*);
int inventory_Type_Asc(const void*, const void*);
int inventory_Type_Desc(const void*, const void*);
int inventory_Name_Asc(const void*, const void*);
int inventory_Name_Desc(const void*, const void*);

#endif //HEADER_H