#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <float.h>
#include <math.h>
#include <iso646.h>
#include <ncurses.h>
#include "functions.h"
#include <string>
#include <iostream>
#include <fstream>
int main(int argc, char* argv[]){
	time_t t; 
	srand((unsigned) time(&t));
	int trainers = 0;
	
	std::string vals[9] = {"pokemon", "moves", "pokemon_moves",
	"pokemon_species", "experience", "type_names", "pokemon_stats", "stats", "pokemon_types"}; 

	struct worldMap* wm = (struct worldMap*) malloc(sizeof(struct worldMap)); 
	struct map* m = (struct map*) malloc(sizeof(struct map));
	generateWorldMap(wm,m);
	//play(wm,m);
	struct pokedata* d = (struct pokedata*) malloc(sizeof(struct pokedata));

	trainers = (rand() % (13 - 7 + 1)) + 7;
		
	if(argc == 3){
		if(strcmp(argv[1],"--numtrainers") == 0){
			trainers = atoi(argv[2]);
			if(trainers > 13 || trainers <= 0){
				trainers = (rand() % (13 - 7  + 1)) + 7;
			}
		}
	}
	
	//for(const string &val:vals)
	//	csvParser(val,d);
	//callOut(d);
	csvParser("pokemon",d);
	//csvParser("pokemon_moves",d);
	//csvParser("pokemon_stats",d);
	//csvParser("stats",d);

	grantMap(&wm,m,1,1,1,1);
	placePC(m);
	createTrainers(m,trainers);
	pcControl(wm,m);
	
	return 0;
}
