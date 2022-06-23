#include "header.h"
#include <stdio.h>
#include <stdlib.h>

ADMIN* alocirajAdmin(ADMIN* adminS, int brojAdmin) {
	if (!(adminS = calloc(brojAdmin, sizeof(ADMIN)))) {
		exit(EXIT_FAILURE);
	}
	return adminS;
}

INV* alocirajInventar(INV* inventarS, int brojInventara) {
	if (!(inventarS = calloc(brojInventara, sizeof(INV)))) {
		exit(EXIT_FAILURE);
	}
	return inventarS;
}