#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <float.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>

//rand() % MAX; which is 0 to max specified - 1
//time_t t; 
//srand((usigned)time(&t));
//for random numbers between a and b inclusive
//(rand() % b ) + a;
//(rand() % 10 ) + 1;

void generatePaths(struct map* m,struct door src, struct door dest, int s){
	
	int c = 0;
	//west to east
	if(s == 0){
		if(src.doorX < dest.doorX){
			c = (rand() % (78 - 2 + 1)) + 2;
			for(int j = src.doorY; j < c; j++){
				m->field[src.doorX][j] = '#';
			}
			for(int j = src.doorX; j < dest.doorX + 1; j++){
				m->field[j][c] = '#';
			}
			for(int j = c; j < dest.doorY; j++){
				m->field[dest.doorX][j] = '#';
			}
		}	
		if(src.doorX > dest.doorX){
			c = (rand() % (78 - 2 + 1)) + 2;
			for(int i = src.doorY; i < c; i++){
				m->field[src.doorX][i] = '#';
			}
			for(int i = src.doorX; i >= dest.doorX; i--){
				m->field[i][c] = '#';
			}
			for(int i = c; i < dest.doorY ; i++){
				m->field[dest.doorX][i] = '#';
			}
		}
		if(src.doorX == dest.doorX){
			for(int i = 0; i < 79; i++)
				m->field[src.doorX][i] = '#';
		}
	}
	//north to south
	if(s == 1){
		if(src.doorY > dest.doorY){
			c = (rand() % (19 - 2 + 1)) + 2;
			for(int i = src.doorX; i < c; i++){
				m->field[i][src.doorY] = '#';
			}
			for(int i = src.doorY; i > dest.doorY; i--){
				m->field[c][i] = '#'; 
			}
			for(int i = c ; i < dest.doorX; i++){
				m->field[i][dest.doorY] = '#';
			}
		}
		if(src.doorY < dest.doorY){
			c = (rand() % (19 - 2 + 1)) + 2;
			for(int i = src.doorX; i < c; i++){
				m->field[i][src.doorY] = '#';	
			}
			for(int i = src.doorY; i < dest.doorY ; i++){
				m->field[c][i] = '#';
			}
			for(int i = c; i < dest.doorX ; i++){
				m->field[i][dest.doorY] = '#';
			}
		}
		if(src.doorY == dest.doorY){
			for(int i = src.doorX; i < 20; i++)
				m->field[i][src.doorY] = '#';
		}
	}
}
void buildTerrain(struct map* m){
	m->boulderTree = (rand() % (20 - 5 + 1)) + 5;
	int c = 0;
	for(int i = 0; i < 20; i++)
		for(int j = 0; j < 79; j++){
			if(m->field[i][j] != '.' && m->field[i][j] != ':' && m->field[i][j] != 'M' &&
				      m->field[i][j] != 'C' && m->field[i][j] != '%' && m->field[i][j] != '#'){
				if(c <= m->boulderTree){
					m->field[i][j] = '^';
					c++;
				}
				else{
					if(c > m->boulderTree){
						m->field[i][j] = '%';
						c = 0;
					}
				}
			}
		}
}

int isEnoughSpace(struct map* m, int s, int c){
	for(int i = m->clearings[c].x_loc; i < m->clearings[c].x_loc + m->clearings[c].height; i++){
		for(int j = m->clearings[c].y_loc; j < m->clearings[c].y_loc + m->clearings[c].width; j++){
			if(i < 0 || i > 19 || j < 0 || j > 79)
				return 0;
			else{
				if(m->field[i][j] == '%')
					return 0;
				if(m->field[i][j] == ':')
					return 0;
				if(m->field[i][j] == 'C')
					return 0;
				if(m->field[i][j] == 'M')
					return 0;
				if(m->field[i][j] == '#')
					return 0;
				if(m->field[i][j] == '.')
					return 0;
			}
		}
	}
	return 1;
}

void buildClearings(struct map* m){
	int c = 0, v = 0;
	m->clearingCount = (rand() % (5 - 2 + 1)) + 2;
	while(c < m->clearingCount){
		while(v == 0){
			m->clearings[c].x_loc = (rand() % (19 - 2 + 1)) + 2;
			m->clearings[c].y_loc = (rand() % (78 - 2 + 1)) + 2;
			m->clearings[c].height = (rand() % (10 - 5 + 1)) + 5;
			m->clearings[c].width = (rand() % (10 - 5 + 1)) + 5;

			v = isEnoughSpace(m,v,c);
		}

		for(int i = m->clearings[c].x_loc; i < m->clearings[c].x_loc + m->clearings[c].height; i++)
			for(int j = m->clearings[c].y_loc; j < m->clearings[c].y_loc + m->clearings[c].width; j++){
				m->field[i][j] = '.';
			}

		v = 0;
		c++;
	}
}

int isThereSpace(struct map* m, int s, int c){
	for(int i = m->longGrass[c].x_loc; i < m->longGrass[c].x_loc + m->longGrass[c].height; i++)
		for(int j = m->longGrass[c].y_loc; j < m->longGrass[c].y_loc + m->longGrass[c].width; j++){
			if(i < 0 || i > 19 || j < 0 || j > 79)
				return 0;
			else{
				if(m->field[i][j] == '%')
					return 0;
				if(m->field[i][j] == 'M')
					return 0;
				if(m->field[i][j] == 'C')
					return 0;
				if(m->field[i][j] == '#')
					return 0;
				if(m->field[i][j] == ':')
					return 0;
				if(m->field[i][j] == '.')
					return 0;
			}
		}
	return 1;
}

void buildLongGrass(struct map* m){
	int v = 0, c = 0;
	m->longGrassPatches = (rand() % (7 - 2 + 1)) + 2;
	while(c < m->longGrassPatches){
		while(v == 0){

			m->longGrass[c].x_loc = (rand() % (19 - 2 + 1)) + 2;
			m->longGrass[c].y_loc = (rand() % (78 - 2 + 1)) + 2;
			m->longGrass[c].height = (rand() % (15 - 5 + 1)) + 2;
			m->longGrass[c].width = (rand() % (15 - 5 + 1)) + 2;
			
			v = isThereSpace(m,v,c);
		}
		for(int i = m->longGrass[c].x_loc; i < m->longGrass[c].x_loc + m->longGrass[c].height; i++)
			for(int j = m->longGrass[c].y_loc; j < m->longGrass[c].y_loc + m->longGrass[c].width; j++){
				m->field[i][j] = ':';
			}
		v = 0;
		c++;
	}
	
}

int validateLocation(struct map* m, int x, int y, int s){
	if(s == 0){
		for(int i = m->pokecenter.x_loc; i < m->pokecenter.x_loc + m->pokecenter.height; i++)
			for(int j = m->pokecenter.y_loc; j < m->pokecenter.y_loc + m->pokecenter.width; j++)
				if(i < 0 || i > 19 || j < 0 || j > 78){
					return 0;
				}else{
					if(m->field[i][j] == '%')
						return 0;
					if(m->field[i][j] == 'C')
						return 0;
					if(m->field[i][j] == 'M')
						return 0;
					if(m->field[i][j] == '#')
						return 0;
				}
		return 1;
	}else{
		for(int i = m->pokemart.x_loc; i < m->pokemart.x_loc + m->pokemart.height; i++)
			for(int j = m->pokemart.y_loc; j < m->pokemart.y_loc + m->pokemart.width; j++)
				if(i < 0 || i > 19 || j < 0 || j > 78){
					return 0;
				}else{
					if(m->field[i][j] == '%')
						return 0;
					if(m->field[i][j] == 'C')
						return 0;
					if(m->field[i][j] == 'M')
						return 0;
					if(m->field[i][j] == '#')
						return 0;
				}
		return 1;

	}
}

void buildPokeStructs(struct map* m, int s){
	int x = 0, y = 0, v = 0;

	if(s == 0){
		m->pokecenter.width = (rand() % 3) + 3;
		m->pokecenter.height = (rand() % 3) + 3;
		
		while(v == 0){
			m->pokecenter.x_loc = (rand() % 19) + 2;
			m->pokecenter.y_loc = (rand() % 78) + 2;
			v = validateLocation(m, m->pokecenter.x_loc, m->pokecenter.y_loc,0);
		}
		v = 0;
		for(int i = m->pokecenter.x_loc; i < m->pokecenter.x_loc + m->pokecenter.height; i++)
			for(int j = m->pokecenter.y_loc; j < m->pokecenter.y_loc + m->pokecenter.width; j++)
				m->field[i][j] = 'C';
	}else{
		m->pokemart.width = (rand() % 3) + 3;
		m->pokemart.height = (rand() % 3) + 3;

		while(v==0){
			m->pokemart.x_loc = (rand() % 19) + 2;
			m->pokemart.y_loc = (rand() % 78) + 2;
			v = validateLocation(m, m->pokemart.x_loc, m->pokemart.y_loc,1);
		}
		 		
		for(int i = m->pokemart.x_loc; i < m->pokemart.x_loc + m->pokemart.height; i++)
			for(int j = m->pokemart.y_loc; j < m->pokemart.y_loc + m->pokemart.width; j++)
				m->field[i][j] = 'M';
	}

}


void createExit(struct map* m, int north, int east, int south, int west){
	//we know they need to be on 0,R (0-79) / 20, R (0,79) / R(0,20), 0, R (0,20), 79
	//How does this work, well if I see a 0 in the directional switches, because we have pointers, we can grab the info using a pointer
	//if we get a north when searching the map, then south would have a zero, all other numbers were randomly generated, we'd take the north exit x location and set current south to 20,x, etc
	
	int x = 0, y = 0;

	//if zero, check if direction is null, if it is update,
	//if not, do nothing	
	if(west == 1){
		x = (rand() % 19 - 1 + 1) + 1;
		m->field[x][0] = '#';
		m->west.doorX = x;
		m->west.doorY = 0;
	} 
	if(west == 0){
		if(m->w.mapY == 0){
			x = (rand() % 19 - 1 + 1) + 1;
		}else{
			x = m->westMap->east.doorX;
		}
		m->field[x][0] = '#';
		m->west.doorX = x;
		m->west.doorY = 0;		
		
	}
	if (east == 1){
		x = (rand() % 19 - 1 + 1) + 1;
		m->field[x][79] = '#';
		m->east.doorX = x;
		m->east.doorY = 79;
	}
	if(east == 0){
		if(m->w.mapY == 400){
			x = (rand() % 19 - 1 + 1) + 1;
		}else{
			x = m->eastMap->west.doorX;
		}
		m->field[x][79] = '#';
		m->east.doorX = x;
		m->east.doorY = 79;
		
	}
	if(north == 1){
		y = (rand() % 78 - 1 + 1) + 1;
		m->field[0][y] = '#';
		m->north.doorX = 0;
		m->north.doorY = y;
	}
	if(north == 0){
		if(m->w.mapX == 0){
			y = (rand() % 78 - 1 + 1) + 1;
		}else{
			y = m->northMap->south.doorY;
		}
		m->field[0][y] = '#';
		m->north.doorX = 0;
		m->north.doorY = y;
	
	}
	if(south == 1){
		y = (rand() % 78 - 1 + 1) + 1;
		m->field[20][y] = '#';
		m->south.doorX = 20;
		m->south.doorY = y;
	}
	if(south == 0){
		if(m->w.mapX == 400){
			y = (rand() % 78 - 1 + 1) + 1;
		}else{
			y = m->southMap->north.doorY;
		}
		m->field[20][y] = '#';
		m->south.doorX = 20;
		m->south.doorY = y;
	}

}

void initField(struct map* m){
	m = malloc(sizeof(struct map));
	for(int i = 0; i < X; i++)
		for(int j = 0; j < Y; j++)
			m->field[i][j] = ' ';
}

void print(struct map* m){
	for(int i = 0; i < X; i++){
		for(int j = 0; j < Y; j++){
			printf("%c",m->field[i][j]);
		}
		printf("\n");
	}
	printf("Current map location: (%d , %d)\n", m->w.mapX-200, m->w.mapY-200);
}

void buildBorders(struct map* m){
	for(int i = 0; i < X; i++)
		for(int j = 0; j < Y; j++)
			if(j == 79 || i == 0 || i == 20 || j == 0)
				m->field[i][j] = '%';
}

void additionalPaths(struct map* m, struct pokeloci p){
	int c = 0, f = 0, q = 0, r = 0 , h = 0;
	int x = p.x_loc;
	int y = p.y_loc;

	for(int i = x; i > 0; i--,c++){
		if(m->field[i][y] == '#'){
			for(int j = x; q < c; j--, q++){
				if(m->field[j][y] != 'M' && m->field[j][y] != 'C')
					m->field[j][y] = '#';
			}
			break;
		}
	}
	
	c = 0;

	for(int i = y; i < 79 ; i++, c++){
		if(m->field[x][i] == '#'){
			for(int k = y;r < c; k++, r++){
				if(m->field[x][k] != 'M' && m->field[x][k] != 'C')
					m->field[x][k] = '#';
			}
			break;
		}
	}

	c = 0;

	for(int i = x; i < 20; i++,c++){
		if(m->field[i][y] == '#'){
			for(int j = x; h < c; j++, h++){
				if(m->field[j][y] != 'M'  && m->field[j][y] != 'C')
					m->field[j][y] = '#';
			}
			break;
		}
	}

	c = 0;

	for(int l = y; l > 0; l--,c++){
		if(m->field[x][l] == '#'){
			for(int d = y; f < c; y--,f++ ){
				if(m->field[x][d] != 'M' && m->field[x][d] != 'C')
					m->field[x][d] = '#';
			}
			break;
		}
	}
	c = 0;
}

void generateWorldMap(struct worldMap* m, struct map* sm){
	for(int i = 0; i < 401; i++)
		for(int j = 0; j < 401; j++)
			m->wm[i][j] == NULL;
	m->wm[200][200] = sm;
	sm->w.mapX = 200;
	sm->w.mapY = 200;
	sm->northMap = NULL;
	sm->eastMap = NULL;
	sm->southMap = NULL;
	sm->westMap = NULL;
};
void moveMap(struct worldMap* m, struct map* curr, struct map* next, char dir){
	//no matter the direction make sure we check that we are not at an edge,
	//moving towards the edge x = 0,20, y=0,79
	if(dir == 'n'){
		if(curr->w.mapX == 0){
			//display map again
			//print the coordinates under the map
			print(curr);
		}
		else if(curr->northMap != NULL){
			// update the current
			next = m->wm[curr->w.mapX-1][curr->w.mapY];
		       	print(next);	
			//display the map
			//print the coordinates under the map
		}else if(curr->northMap == NULL){
			next = malloc(sizeof(struct map));
			curr->northMap = next;
			next->southMap = curr;
			
			next->w.mapX = curr->w.mapX - 1;
			next->w.mapY = curr->w.mapY;
			m->wm[next->w.mapX][next->w.mapY] = next;

			grantMap(m,next,1,0,1,1);
			print(next);
			//create the map
			//make sure the south exit on new map is set to 0
			//input the xy in world map
			//create a pointer to the generated map in the xy location
			//use prior coordinates since we went north (y - 1)
			//display map, print the coordinates

		}
		//if mp is not null print
		//if mp is null create map and link to current and 2d array 
		//of pointers
	}else if(dir == 'e'){
		if(curr->w.mapY == 400){
			print(curr);
		}
		else if(curr->eastMap != NULL){
			next = m->wm[curr->w.mapX][curr->w.mapY+1];
			print(next);
		}
		else if(curr->eastMap == NULL){
			next = malloc(sizeof(struct map));
			curr->eastMap = next;
			next->westMap = curr;
			
			next->w.mapX = curr->w.mapX;
			next->w.mapY = curr->w.mapY + 1;
			m->wm[next->w.mapX][next->w.mapY] = next;

			grantMap(m,next,1,1,1,0);
			print(next);
		}
	
	}else if(dir == 's'){
		if(curr->w.mapX == 400){
			print(curr);
		}
		else if(curr->southMap != NULL){
			next = m->wm[curr->w.mapX+1][curr->w.mapY];
			print(next);
		}
		else if(curr->southMap == NULL){
			next = malloc(sizeof(struct map));
			curr->southMap = next;
			next->northMap = curr;
			
			next->w.mapX = curr->w.mapX + 1;
			next->w.mapY = curr->w.mapY;
			m->wm[next->w.mapX][next->w.mapY] = next;
			
			grantMap(m,next,0,1,1,1);
			print(next);
		}
	}else if(dir == 'w'){
		if(curr->w.mapY == 0){
			print(curr);
		}
		else if(curr->westMap != NULL){
			next = m->wm[curr->w.mapX][curr->w.mapY-1];
			print(next);
		}
		else if(curr->westMap == NULL){
			next = malloc(sizeof(struct map));
			curr->westMap = next;
			next->eastMap = curr;

			next->w.mapX = curr->w.mapX;
			next->w.mapY = curr->w.mapY - 1;
			m->wm[next->w.mapX][next->w.mapY] = next;

			grantMap(m,next,1,1,0,1);
			print(next);

		}
	}
}

void jumpToMap(struct worldMap* m, int x, int y){
	if(m->wm[x][y] == NULL){
		//generate a new map, check all directions, if present
		//that number is 1, if not it's zero and needs to be
		//place pointer in worldmap
		int n = -1, s = -1, w = -1, e = -1;
		struct map* curr = malloc(sizeof(struct map));
		//check north
	       	if(x != 0 && m->wm[x-1][y] == NULL){
			n = 1;
		}else{
			n = 0;
		}
		//check south
		if(x != 400 && m->wm[x+1][y] == NULL){
			s = 1;
		}else{
			s = 0;
		}
		//check east
		if(y != 400 && m->wm[x][y+1] == NULL){
			e = 1;
		}else{
			e = 0;
		}
		//check west
		if(y != 0 && m->wm[x][y-1] == NULL){
			w = 1;
		}
		else{
			w = 0;
		}

		curr->w.mapX = x;
		curr->w.mapY = y;

		grantMap(m,curr,n,s,e,w);
		m->wm[x][y] = curr;
		print(curr);


	}
	else if(m->wm[x][y] != NULL){
		struct map* curr = malloc(sizeof(struct map));
		curr = m->wm[x][y];
		print(curr);
		//print map, display coordinates
	}
}

void play(struct worldMap* m, struct map* go){
	// generate a new map
	// create an array as a buffer
	char buffer [1000];
	char bufferAlt[1000];
	int active = -1;
	int x = 0, y = 0;
	go = m->wm[200][200];

	grantMap(m,go,1,1,1,1);
	placePC(go);
	print(go);
	dijkstra(go, go->pc.x, go->pc.y, 0);

	// while loop to take user input
	// check if it exists as one of the commands
	// if correct, move/stay, display, quit,
	// if not tell them what the commands are and to stop that
	while(strcmp(buffer,"q") != 0){
		printf("Enter a direction, (n,s,e,w) to explore"
				" the maps.\nEnter f x y, where "
				"x and y are ints to jump to map."
				"\nEnter q to quit.\n");
		fgets(buffer,20,stdin);
		active = whichDirection(buffer);
		if(active == 0){
		}
		//North
		if(active == 1){
			if(go->w.mapX >= 1)
				moveMap(m,go,go->northMap,'n');
			else
				moveMap(m,go,go,'n');
			if(go->w.mapX >= 1)
				go = go->northMap;
		}
		//East
		if(active == 2){
			if(go->w.mapY <= 399)
				moveMap(m,go,go->eastMap,'e');
			else
				moveMap(m,go,go,'e');
			if(go->w.mapY <= 399)
				go = go->eastMap;
		}
		//South
		if(active == 3){
			if(go->w.mapX <= 399)
				moveMap(m,go,go->southMap,'s');
			else
				moveMap(m,go,go,'s');
			if(go->w.mapX <= 399)
				go = go->southMap;
		}
		//West
		if(active == 4){
			if(go->w.mapY >=1)
				moveMap(m,go,go->westMap,'w');
			else
				moveMap(m,go,go,'w');
			if(go->w.mapY >= 1)
				go = go->westMap;
		}
		// fly to
		if(active == 5){
			char* token;
			strcpy(bufferAlt,buffer);
			token = strtok(bufferAlt, " ");
			int i = 0, x = -1, y = -1;
			while(token != NULL){
				if(i == 1)
					x = atoi(token);
				if(i == 2)
					y = atoi(token);
				token = strtok(NULL, " ");
			i++;
			}
			jumpToMap(m,x+200,y+200);
			if(x >= -200 && x <= 200 && y >= -200 && y <= 200){
				go = m->wm[x+200][y+200];
			}
		}
		if(active == 6)
			break;
	}
}

int whichDirection(char buffer[]){
	char * token;
	char buffer2[1000];
	strcpy(buffer2,buffer);
	if(strcmp(buffer,"n\n") == 0)
		return 1;
	if(strcmp(buffer,"e\n") == 0)
		return 2;
	if(strcmp(buffer, "s\n") == 0)
		return 3;
	if(strcmp(buffer, "w\n") == 0)
		return 4;
	if((buffer[0] == 'f')){
		token = strtok(buffer2, " ");
		int i = 0, x = -1, y = -1;
		while(token != NULL){
			if(i == 1)
				x = atoi(token);
			if(i == 2)
				y = atoi(token);
			token = strtok(NULL, " ");
			i++;
		}
		if(i == 3 && x >= -200 && y >= -200 && x <= 200 && y <= 200)
			return 5;
	}
	if(strcmp(buffer,"q\n") == 0)
		return 6;
	return 0;

}

int probPlacement(struct map* m){
	double val = (double)rand()/ RAND_MAX;
	int md = abs(200 - m->w.mapX) + abs(200 - m->w.mapY);
	double c = (((-45 * md)/200.0) + 50) / (100);
	if(val < fabs(c))
		return 1;
	else
		return 0;
}

void grantMap(struct worldMap* wm, struct map* m, int n, int s, int e, int w){

		int pc = -1, pm = -1;

		initField(m);
		buildBorders(m);
		createExit(m,n,e,s,w);
		generatePaths(m,m->north,m->south,1);
		generatePaths(m,m->west,m->east,0);
		if(m->w.mapX == 200 && m->w.mapY == 200){
			buildPokeStructs(m,0);
			buildPokeStructs(m,1);
			additionalPaths(m,m->pokemart);
			additionalPaths(m,m->pokecenter);
		}else{
			pc = probPlacement(m);
			pm = probPlacement(m);
			if(pc == 1)
				buildPokeStructs(m, 0);//this is a pokecenter
			if(pm == 1)
				buildPokeStructs(m,1);//this is a pokemart
			if(pm == 1)
				additionalPaths(m,m->pokemart);
			if(pc == 1)
				additionalPaths(m,m->pokecenter);
		}
		buildLongGrass(m);
		buildClearings(m);
		buildTerrain(m);

		if(m->w.mapX == 0)
			m->field[0][m->north.doorY] = '%';
		if(m->w.mapX == 400)
			m->field[20][m->south.doorY] = '%';
		if(m->w.mapY == 0)
			m->field[m->west.doorX][0] = '%';
		if(m->w.mapY == 400)
			m->field[m->east.doorX][79] = '%';
}

void placePC(struct map* m){
	int x = 0, y = 0;
	
	while(m->field[x][y] != '#'){
		x = (rand() % 19 - 2 + 1) + 2;
		y = (rand() % 78 - 2 + 1) + 2;
	}
	m->field[x][y] = '@';
	m->pc.x = x;
	m->pc.y = y;
}
void dijkstra(struct map* m, int src_x, int src_y, int s){
	int visited[X][Y] = {0};
	int distance[X][Y] = {0}; // access m and use hikercost[][] if s = 0 for 
	//or acccess m and use rivalcost[][] if s = 1
	
	distance[src_x][src_y] = 0;
	visited[src_x][src_y] = 0;
	int alt = 0, distNew = 0;

	struct Node* pq = create(src_x, src_y,0);

	for(int i = 0; i < X; i++){
		for(int j = 0; j < Y; j++){
			if(i == src_x && j == src_y){
			}
			else if(m->field[i][j] != '%' && m->field[i][j] != '^'){
				distance[i][j] = INT_MAX;
				push(&pq,i,j,INT_MAX);
			}
			if(m->field[i][j] == '^' ||
					m->field[i][j] == '%')
				visited[i][j] = 1;
		}
	}

	while(!isEmpty(&pq)){// maybe its supposed to be while q isn't empty
		struct Node* temp = pop(&pq);

		//go up, left 1
		if(temp->x - 1 >= 0 && temp->y - 1 >= 0
				&& visited[temp->x - 1][temp->y - 1] == 0){

			distNew = distCalc(m, temp->x - 1, temp->y - 1, s);
			alt = temp->dist + distNew;

			if(alt < distance[temp->x - 1][temp->y - 1]){
				distance[temp->x - 1][temp->y - 1] = alt;
				distUpgrade(&pq, temp->x - 1, temp->y - 1, alt);
				mergesort(&pq);
			}
		}

		//go up, same column
		if(temp->x - 1 >= 0 && temp->y >= 0
				&& visited[temp->x - 1][temp->y] == 0){
			
			distNew = distCalc(m, temp->x - 1, temp->y, s);		
			alt = temp->dist + distNew;

			if(alt < distance[temp->x - 1][temp->y]){
				distance[temp->x - 1][temp->y] = alt;
				distUpgrade(&pq, temp->x - 1, temp->y, alt);
				mergesort(&pq);
			}
		}

		//go up, right 1
		if(temp->x - 1 >= 0 && temp->y + 1 <= 79 
				&& visited[temp->x - 1][temp->y + 1] == 0){
		
			distNew = distCalc(m, temp->x - 1, temp->y + 1, s);
			alt = temp->dist + distNew;

			if(alt < distance[temp->x - 1][temp->y + 1]){
				distance[temp->x - 1][temp->y + 1] = alt;
				distUpgrade(&pq, temp->x - 1, temp-> y + 1, alt);
				mergesort(&pq);
			}
		}

		//stay at x,go left 1, 
		if(temp->x >= 0 && temp->y - 1 >= 0
				&& visited[temp->x][temp->y - 1] == 0){
			
			distNew = distCalc(m, temp->x, temp->y - 1, s);
			alt = temp->dist + distNew;

			if(alt < distance[temp->x][temp->y - 1]){
				distance[temp->x][temp->y - 1] = alt;
				distUpgrade(&pq,temp->x, temp->y - 1, alt);
				mergesort(&pq);
			}
		}

		//stay at x, go right 1
		if(temp->x >= 0 && temp->y + 1 <= 79
				&& visited[temp->x][temp->y + 1] == 0){
						
			distNew = distCalc(m, temp->x, temp->y + 1, s);	
			alt = temp->dist + distNew; 

			if(alt < distance[temp->x][temp->y + 1]){
				distance[temp->x][temp->y + 1] = alt;
				distUpgrade(&pq,temp->x,temp->y + 1, alt);
				mergesort(&pq);
			}
		}

		//go down, go left 1
		if(temp->x + 1 <= 20 && temp->y - 1 >= 0
				&& visited[temp->x + 1][temp->y - 1] == 0){
			
			distNew = distCalc(m, temp->x + 1, temp->y - 1, s);
			alt = temp->dist + distNew;

			if(alt < distance[temp->x + 1][temp->y - 1]){
				distance[temp->x + 1][temp->y - 1] = alt;
				distUpgrade(&pq,temp->x + 1,temp->y - 1, alt);
				mergesort(&pq);
			}
		}
		
		//go down, same column
		if(temp->x + 1 <= 20 && temp->y >= 0
				&& visited[temp->x + 1][temp->y] == 0){
			
			distNew = distCalc(m, temp->x + 1, temp->y, s);
			alt = temp->dist + distNew;

			if(alt < distance[temp->x + 1][temp->y]){
				distance[temp->x + 1][temp->y] = alt;
				distUpgrade(&pq,temp->x + 1, temp->y,alt);
				mergesort(&pq);
			}
		}

		//go down, go right
		if(temp->x + 1 <= 20 && temp->y + 1 <= 79
				&& visited[temp->x + 1][temp->y + 1] == 0){
			
			distNew = distCalc(m, temp->x + 1, temp->y + 1, s);
			alt = temp->dist + distNew;

			if(alt < distance[temp->x + 1][temp->y + 1]){
				distance[temp->x + 1][temp->y + 1] = alt;
				distUpgrade(&pq,temp->x + 1, temp->y + 1, alt);
				mergesort(&pq);
			}
		}
		visited[temp->x][temp->y] = 1;
		free(temp);
	}
	for(int i = 0; i < X; i++){
		for(int j = 0; j < Y; j++){
			if(m->field[i][j] != '^' && m->field[i][j] != '%'
					&& distance[i][j] >= 0){
				printf("%d ",distance[i][j] % 100);
			}else{
				printf("  ");
			}
		}
		printf("\n");
	}
}


int distCalc(struct map* m, int x, int y, int s){
	int distNew = 0;
	if(m->field[x][y] == '.' || 
			m->field[x][y] == '#'){
		distNew = 10;
	}
	else if(m->field[x][y] == 'M'||
			m->field[x][y] == 'C'){
		distNew = 50;
	}
	else if(m->field[x][y] == ':'){
		if(s == 0){//hiker
			distNew = 15;
		}
		else{ //rival
			distNew = 20;
		}
	}
	return distNew;
}

struct Node* create(int x, int y, int dist){
	struct Node* temp = (struct Node*) malloc(sizeof(struct Node));
	temp->x = x;
	temp->y = y;
	temp->dist = dist;
	temp->visited = 0;
	temp->next = NULL;
	return temp;
}

void push(struct Node** head, int x, int y, int dist){
	struct Node* curr = (*head);

	struct Node* temp = create(x,y,dist);

	if((*head)->dist > dist){
		temp->next = *head;
		(*head) = temp;
	}else{
		while(curr->next != NULL && curr->next->dist < dist){
			curr = curr->next;
		}
		temp->next = curr->next;
		curr->next = temp;
	}	

}

struct Node* pop(struct Node** head){
	struct Node* temp = *head;
	(*head) = (*head)->next;
	return temp;
}

int isEmpty(struct Node** node){
	return (*node) == NULL;
}

void distUpgrade(struct Node** head, int x, int y, int dist){
	struct Node* curr = (*head);

	while(curr != NULL){
		if(curr->x == x && curr->y == y){
			curr->dist = dist;
		}
		curr = curr->next;
	}
}

struct Node* sortedMerge(struct Node* a, struct Node* b){
	if(a == NULL)
		return b;
	else if(b == NULL)
		return a;
	struct Node* result = NULL;

	if(a->dist <= b->dist){
		result = a;
		result->next = sortedMerge(a->next, b);
	}else{
		result = b;
		result->next = sortedMerge(a, b->next);
	}
	return result;
}

void frontBackSplit(struct Node* src, struct Node** fRef, struct Node** bRef){
	if(src == NULL || src->next == NULL){
		*fRef = src;
		*bRef = NULL;
		return;
	}

	struct Node* s = src;
	struct Node* f = src->next;

	while(f != NULL){
		f = f->next;
		if(f != NULL){
			s = s->next;
			f = f->next;
		}
	}
	*fRef = src;
	*bRef = s->next;
	s->next = NULL;
}

void mergesort(struct Node** head){
	if(*head == NULL || (*head)->next == NULL){
		return;
	}

	struct Node* a;
	struct Node* b;

	frontBackSplit(*head, &a, &b);
	mergesort(&a);
	mergesort(&b);

	*head = sortedMerge(a,b);
}

