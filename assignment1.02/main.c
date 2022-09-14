#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <float.h>
#include <math.h>
#include <iso646.h>
#include "functions.h"

int main(int argc, char* argv[]){
	time_t t; 
	srand((unsigned) time(&t));
	
	
	struct worldMap* wm = malloc(sizeof(struct worldMap)); 
	struct map* m = malloc(sizeof(struct map));
	generateWorldMap(wm, m);
	play(wm,m);
	
	return 0;
}
