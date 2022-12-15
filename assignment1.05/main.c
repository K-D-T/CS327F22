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

int main(int argc, char* argv[]){
	time_t t; 
	srand((unsigned) time(&t));
	int trainers = 0;
	
	struct worldMap* wm = malloc(sizeof(struct worldMap)); 
	struct map* m = malloc(sizeof(struct map));
	generateWorldMap(wm, m);
	//play(wm,m);
	
	if(argc == 3){
		if(strcmp(argv[1],"--numtrainers") == 0){
			trainers = atoi(argv[2]);
			//if(trainers == 0){
				//printf("Whatever you input was invalid, so we're going to decide how many trainers for you.\n");
			//	trainers = (rand() % (13 - 7 + 1)) + 7;
				//printf("There are %d trainers.\n",trainers);
			//}
			//printf("Format correct, there are %d trainers.\n", trainers);
			if(trainers > 13 || trainers <= 0){
				//printf("Too many or too little trainers generated, we'll generate a reasonable number for you.\n");
				trainers = (rand() % (13 - 7  + 1)) + 7;
				//printf("There are %d trainers.\n", trainers);
			}
		}
	}else{
		trainers = (rand() % (13 - 7 + 1)) + 7;
		//printf("No errors, no value specified, %d trainers\n", trainers);
	
	}

	//printf("%d trainers\n",trainers);
	//printf("argc: %d\n",argc);
	//printf("argv2: %s\n",argv[2]);
	//printf("count: %d\n",atoi(argv[2]));
	grantMap(wm,m,1,1,1,1);
	placePC(m);
	createTrainers(m,trainers);
	//print(m);
	pcControl(m);
	//turnControl(m);
	//movePC(m);
	//usleep(60000);
	

	//}
	//printf("This is a hiker map.\n");
	//dijkstra(m, m->pc.x, m->pc.y, 0);
	//printf("This is a rival map.\n");
	//dijkstra(m, m->pc.x, m->pc.y, 1);

	return 0;
}
