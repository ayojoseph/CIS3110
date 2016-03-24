#include "holes.h"
#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <string.h>

void InitProcess(char id, int size, Process *P) {
	P->id = id;
	P->size = size;
}

char idofProcess(Process P) {
	return P.id;
}

int sizeofProcess(Process P) {
	return P.size;
}

void FreeProcess (Process *P) {
}

// int main(int argc, char const *argv[])
// {
// 	/* code */
// 	return 0;
// }