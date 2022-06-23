#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int adminPoIDUzlazno(const void* x, const void* y) {
	ADMIN* ID_x = (ADMIN*)x;
	ADMIN* ID_y = (ADMIN*)y;
	return (ID_x->ID - ID_y->ID);
}

int adminPoIDSilazno(const void* x, const void* y) {
	ADMIN* ID_x = (ADMIN*)x;
	ADMIN* ID_y = (ADMIN*)y;
	return (ID_y->ID - ID_x->ID);
}

int adminPoKorImeUzlazno(const void* a, const void* b) {
	ADMIN* userNA = (ADMIN*)a;
	ADMIN* userNB = (ADMIN*)b;
	return -(strcmp(userNB->korIme, userNA->korIme));
}

int adminPoKorImeSilazno(const void* a, const void* b) {
	ADMIN* userNA = (ADMIN*)a;
	ADMIN* userNB = (ADMIN*)b;
	return strcmp(userNB->korIme, userNA->korIme);
}

int adminPoImeUzlazno(const void* a, const void* b) {
	ADMIN* nameA = (ADMIN*)a;
	ADMIN* nameB = (ADMIN*)b;
	return -(strcmp(nameB->ime, nameA->ime));
}

int adminPoImeSilazno(const void* a, const void* b) {
	ADMIN* nameA = (ADMIN*)a;
	ADMIN* nameB = (ADMIN*)b;
	return strcmp(nameB->ime, nameA->ime);
}

int inventarPoSBUzlazno(const void* x, const void* y) {
	INV* ID_x = (INV*)x;
	INV* ID_y = (INV*)y;
	return (ID_x->serijskiBroj - ID_y->serijskiBroj);
}

int inventarPoSBSilazno(const void* x, const void* y) {
	INV* ID_x = (INV*)x;
	INV* ID_y = (INV*)y;
	return (ID_y->serijskiBroj - ID_x->serijskiBroj);
}

int inventarPoTipUzlazno(const void* a, const void* b) {
	INV* tipA = (INV*)a;
	INV* tipB = (INV*)b;
	return -(strcmp(tipB->tip, tipA->tip));
}

int inventarPoTipSilazno(const void* a, const void* b) {
	INV* tipA = (INV*)a;
	INV* tipB = (INV*)b;
	return strcmp(tipB->tip, tipA->tip);
}

int inventarPoNabCUzlazno(const void* x, const void* y) {
	INV* nabCX = (INV*)x;
	INV* nabCY = (INV*)y;
	return (nabCX->nabavnCijena - nabCY->nabavnCijena);
}

int inventarPoNabCSilazno(const void* x, const void* y) {
	INV* nabCX = (INV*)x;
	INV* nabCY = (INV*)y;
	return (nabCY->nabavnCijena - nabCX->nabavnCijena);
}

int inventarPoProdCUzlazno(const void* x, const void* y) {
	INV* prodCX = (INV*)x;
	INV* prodCY = (INV*)y;
	return (prodCX->prodajnaCijena - prodCY->prodajnaCijena);
}

int inventarPoProdCSilazno(const void* x, const void* y) {
	INV* prodCX = (INV*)x;
	INV* prodCY = (INV*)y;
	return (prodCY->prodajnaCijena - prodCX->prodajnaCijena);
}