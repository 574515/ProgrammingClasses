#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

int igracScore = 0, racunaloScore = 0, izjednacenoScore = 0;

void intro(void) {
	system("cls");
	printf("\n\t"YLW"TIC TAC TOE\n\n-> KOLEGIJ:"ESC" Algoritmi i strukture podataka");
	printf(YLW"\n-> STUDENT:"ESC" Hrvoje Skrbina"YLW"\n-> ZADATAK:"ESC" Dodatni zadatak (\"Iks-Oks\")\n\n");
	printf(YLW"-> "ESC RED"Igrac [X]"ESC" igra protiv"BLU" racunala [O]"ESC".");
	printf(YLW"\n-> "ESC"Pobjednik je onaj koji ima 3 znaka ("RED"X"ESC" ili "BLU"O"ESC")");
	printf(" horizontalno, vodoravno ili dijagonalno.\n");
	printf(YLW"->"ESC" Pritisnite bilo koju tipku za pocetak.");
	if (_getch() <= 0) exit(EXIT_FAILURE);
	play();
}

void printBoard(void) {
	printf("\t"RED"IGRAC:"ESC" [%d]\t"BLU"RACUNALO:"ESC" [%d]\t"YLW"IZJEDNACENO:"ESC" [%d]\n\n", igracScore, racunaloScore, izjednacenoScore);	
	for (int i = 0; i < N; i++) {
		if (board[i] == 'X' && (i == 0 || i == 3 || i == 6)) printf(RED"\t\t\t%c"ESC, board[i]);
		else if (board[i] == 'X' && (i == 1 || i == 4 || i == 7 || i == 2 || i == 5 || i == 8))
			printf(RED"\t%c"ESC, board[i]);
		else if (board[i] == 'O' && (i == 0 || i == 3 || i == 6)) printf(BLU"\t\t\t%c"ESC, board[i]);
		else if (board[i] == 'O' && (i == 1 || i == 4 || i == 7 || i == 2 || i == 5 || i == 8))
			printf(BLU"\t%c"ESC, board[i]);
		else if (i == 0 || i == 3 || i == 6) printf("\t\t\t%c ", board[i]);
		else if (i == 1 || i == 4 || i == 7 || i == 2 || i == 5 || i == 8)
			printf("\t%c", board[i]);
		if (i == 2 || i == 5) printf("\n");
	}
	printf("\n\n");
	/* Funkcija za ispis polja sa brojevima koji se prepisuju sa znakovima (X ili O)
	kako igra traje, te crvena predstavlja igrača (X), a plava računalo (O).
	RED, BLU, YLW i ESC su makro definirani u headeru za bojanje ispsia na konzoli. */
}

void play(void) {

	for (int i = 0; i < N; i++) board[i] = (char)(i + 49);
	/* Popunjavanje ploče brojevima od 1 do 9, castamo i u char i dodajemo
	   49 kako bi dobili ASCII vrijednost brojeva koji nam trebaju. */

	while(true) {
		playerMove();
		computerMove();
	}
}

void playerMove(void) {
	int humanMove = (-1);
	do {
		system("cls");
		printBoard();
		printf("Unesite broj [1, 9]: ");
		if (scanf("%d", &humanMove) <= 0) exit(EXIT_FAILURE);
	} while ((humanMove < 1 || humanMove > N) || isTaken(humanMove - 1));
	/* Broj se ne prihvaća i unos se ponavlja ukoliko je izvan
	   granica ili već postoji X ili O na tom polju. */
	board[humanMove - 1] = 'X';
	checkWinner(); // provjera je li potez pobjednički
}

void computerMove(void) {
	int computerMove = (-1);
	do {
		computerMove = (rand() % (N - 1 + 1) + 1);
	} while ((computerMove < 1 || computerMove > N) || isTaken(computerMove - 1));
	board[computerMove - 1] = 'O';
	checkWinner();
}

bool isTaken(int move) {
	if (board[move] != 'X' && board[move] != 'O') return false;
	return true;
}

bool isFull(void) {
	int i, count = 0;
	for (i = 0; i < N; i++) if (board[i] == 'X' || board[i] == 'O') count++;
	if (count <= 8) return false;
	return true;
}

void printEnd(char winner) {

	char rematch = 'X';

	system("cls");
	switch (winner) {
	case 'H': {
		igracScore++;
		printBoard();
		printf(RED"Igrac"ESC" je pobijedio!\n");
		break;
	}
	case 'C': {
		racunaloScore++;
		printBoard();
		printf(BLU"Racunalo"ESC" je pobijedilo!\n");
		break;
	}
	case 'X': {
		izjednacenoScore++;
		printBoard();
		printf(YLW"Izjednaceno je!"ESC"\n");
		break;
	}
	}
	do {
		printf("Zelite li igrati ponovno [Y / N]: ");
		if (scanf(" %c", &rematch) <= 0) exit(EXIT_FAILURE);
	} while (rematch != 'Y' && rematch != 'y' && rematch != 'N' && rematch != 'n');
	if (rematch == 'Y' || rematch == 'y') play();
	exit(EXIT_SUCCESS);
}

void checkWinner(void) {
	if (xWin() && !oWin()) printEnd('H');
	else if (oWin() && !xWin()) printEnd('C');
	if (isFull()) printEnd('X');
}

bool xWin(void) { // Provjera svih vertikala, horizontala i dijagonala.
	if ((board[0] == 'X' && board[1] == 'X' && board[2] == 'X') ||
		(board[3] == 'X' && board[4] == 'X' && board[5] == 'X') ||
		(board[6] == 'X' && board[7] == 'X' && board[8] == 'X') ||
		(board[0] == 'X' && board[3] == 'X' && board[6] == 'X') ||
		(board[1] == 'X' && board[4] == 'X' && board[7] == 'X') ||
		(board[2] == 'X' && board[5] == 'X' && board[8] == 'X') ||
		(board[0] == 'X' && board[4] == 'X' && board[8] == 'X') ||
		(board[2] == 'X' && board[4] == 'X' && board[6] == 'X'))
		return true;
	return false;
}

bool oWin(void) {
	if ((board[0] == 'O' && board[1] == 'O' && board[2] == 'O') ||
		(board[3] == 'O' && board[4] == 'O' && board[5] == 'O') ||
		(board[6] == 'O' && board[7] == 'O' && board[8] == 'O') ||
		(board[0] == 'O' && board[3] == 'O' && board[6] == 'O') ||
		(board[1] == 'O' && board[4] == 'O' && board[7] == 'O') ||
		(board[2] == 'O' && board[5] == 'O' && board[8] == 'O') ||
		(board[0] == 'O' && board[4] == 'O' && board[8] == 'O') ||
		(board[2] == 'O' && board[4] == 'O' && board[6] == 'O'))
		return true;
	return false;
}