
#include "holes.h"
typedef Process Item;

#define MAXLISTSIZE 4
typedef struct {
	Item items[MAXLISTSIZE];
	int size;
	int head;
} Queue;