#ifndef HEADER_H
#define HEADER_H
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

short** arrayAllocation(int);
void fillArray(short**, int);
void arrayDeallocation(short**, int);
short biggestEvenNumber(short**, int);
void newArray(short**, int, short);
void printArray(short**, int);

#endif // HEADER_H