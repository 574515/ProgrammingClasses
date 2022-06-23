#ifndef HEADER_H
#define HEADER_H
#define _CRT_SECURE_NO_WARNINGS

char c;
char* logiran;

typedef struct ADMIN {
	int ID;
	char korIme[20], lozinka[20], ime[20], prezime[20], kontakt[30];
} ADMIN;

typedef struct INVENTAR {
	int serijskiBroj, kolicina;
	char naziv[50], tip[30];
	float nabavnCijena, prodajnaCijena;
} INV;

// alokacija
ADMIN* alocirajAdmin(ADMIN*, int);
INV* alocirajInventar(INV*, int);

// izbornici
void pocetni(void);
void glavniIzbornik(void);
void inventarIzbornik(void);
void adminIzbornik(void);

// upravljanje
void kreirajAdmin(void);
void obrisiAdmin(void);
void listajAdmin(void);
void traziAdmin(void);
void kreirajInventar(void);
void obrisiInventar(void);
void listajInventar(void);
void traziInventar(void);

// usporediQsort
int adminPoIDUzlazno(const void*, const void*);
int adminPoIDSilazno(const void*, const void*);
int adminPoKorImeUzlazno(const void*, const void*);
int adminPoKorImeSilazno(const void*, const void*);
int adminPoImeUzlazno(const void*, const void*);
int adminPoImeSilazno(const void*, const void*);
int inventarPoSBUzlazno(const void* x, const void* y);
int inventarPoSBSilazno(const void* x, const void* y);
int inventarPoTipUzlazno(const void* a, const void* b);
int inventarPoTipSilazno(const void* a, const void* b);
int inventarPoNabCUzlazno(const void* x, const void* y);
int inventarPoNabCSilazno(const void* x, const void* y);
int inventarPoProdCUzlazno(const void* x, const void* y);
int inventarPoProdCSilazno(const void* x, const void* y);

#endif // HEADER_H