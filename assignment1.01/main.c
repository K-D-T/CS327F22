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
	
	struct map go;
	//memset(ind, -1, sizeof(ind));
	initField(&go);
	buildBorders(&go);
	createExit(&go);
	generatePaths(&go, go.north, go.south,1);
	generatePaths(&go, go.west, go.east, 0);
	buildPokeStructs(&go,0);
	buildPokeStructs(&go,1);
	additionalPaths(&go, go.pokemart);
	additionalPaths(&go, go.pokecenter);
	buildLongGrass(&go);
	buildClearings(&go);
	buildTerrain(&go);
	//aStar(&go);
	print(&go);
	
	return 0;
}
