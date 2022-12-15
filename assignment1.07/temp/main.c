#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <float.h>
#include <math.h>
#include <iso646.h>
#include <ncurses.h>
#include <bits/stdc++.h>
#include "functions.h"

int main(int argc, char* argv[]){
	time_t t; 
	srand((unsigned) time(&t));
	int trainers = 0;
	
	struct worldMap* wm = malloc(sizeof(struct worldMap)); 
	struct map* m = malloc(sizeof(struct map));
	//map* m;
	//worldMap* wm;
	generateWorldMap(wm,m);
	
	trainers = (rand() % (13 - 7  + 1)) + 7;

	if(argc == 3){
		if(strcmp(argv[1],"--numtrainers") == 0){
			trainers = atoi(argv[2]);
			if(trainers > 13 || trainers <= 0){
				trainers = (rand() % (13 - 7  + 1)) + 7;
			}
		}
	}



	grantMap(&wm,m,1,1,1,1);
	placePC(m);
	createTrainers(m,trainers);

	pcControl(wm,m);

	return 0;
}
