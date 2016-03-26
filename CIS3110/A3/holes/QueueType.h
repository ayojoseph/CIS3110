
#include "holes.h"
typedef Process Item;

#define MAXLISTSIZE 1000
typedef struct {
	Item items[MAXLISTSIZE];
	int size;
	int head;
} Queue;