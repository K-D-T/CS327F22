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
#include <ncurses.h>

//rand() % MAX; which is 0 to max specified - 1
//time_t t; 
//srand((usigned)time(&t));
//for random numbers between a and b inclusive
//(rand() % b ) + a;
//(rand() % 10 ) + 1;

void generatePaths(struct map** m,struct door src, struct door dest, int s){
	
	int c = 0;
	//west to east
	if(s == 0){
		if(src.doorX < dest.doorX){
			c = (rand() % (78 - 2 + 1)) + 2;
			for(int j = src.doorY; j < c; j++){
				(*m)->field[src.doorX][j] = '#';
			}
			for(int j = src.doorX; j < dest.doorX + 1; j++){
				(*m)->field[j][c] = '#';
			}
			for(int j = c; j < dest.doorY; j++){
				(*m)->field[dest.doorX][j] = '#';
			}
		}	
		if(src.doorX > dest.doorX){
			c = (rand() % (78 - 2 + 1)) + 2;
			for(int i = src.doorY; i < c; i++){
				(*m)->field[src.doorX][i] = '#';
			}
			for(int i = src.doorX; i >= dest.doorX; i--){
				(*m)->field[i][c] = '#';
			}
			for(int i = c; i < dest.doorY ; i++){
				(*m)->field[dest.doorX][i] = '#';
			}
		}
		if(src.doorX == dest.doorX){
			for(int i = 0; i < 79; i++)
				(*m)->field[src.doorX][i] = '#';
		}
	}
	//north to south
	if(s == 1){
		if(src.doorY > dest.doorY){
			c = (rand() % (19 - 2 + 1)) + 2;
			for(int i = src.doorX; i < c; i++){
				(*m)->field[i][src.doorY] = '#';
			}
			for(int i = src.doorY; i > dest.doorY; i--){
				(*m)->field[c][i] = '#'; 
			}
			for(int i = c ; i < dest.doorX; i++){
				(*m)->field[i][dest.doorY] = '#';
			}
		}
		if(src.doorY < dest.doorY){
			c = (rand() % (19 - 2 + 1)) + 2;
			for(int i = src.doorX; i < c; i++){
				(*m)->field[i][src.doorY] = '#';	
			}
			for(int i = src.doorY; i < dest.doorY ; i++){
				(*m)->field[c][i] = '#';
			}
			for(int i = c; i < dest.doorX ; i++){
				(*m)->field[i][dest.doorY] = '#';
			}
		}
		if(src.doorY == dest.doorY){
			for(int i = src.doorX; i < 20; i++)
				(*m)->field[i][src.doorY] = '#';
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


void createExit(struct map** m, int north, int east, int south, int west){
	//we know they need to be on 0,R (0-79) / 20, R (0,79) / R(0,20), 0, R (0,20), 79
	//How does this work, well if I see a 0 in the directional switches, because we have pointers, we can grab the info using a pointer
	//if we get a north when searching the map, then south would have a zero, all other numbers were randomly generated, we'd take the north exit x location and set current south to 20,x, etc
	
	int x = 0, y = 0;

	//if zero, check if direction is null, if it is update,
	//if not, do nothing	
	if(west == 1){
		x = (rand() % 19 - 1 + 1) + 1;
		(*m)->field[x][0] = '#';
		(*m)->west.doorX = x;
		(*m)->west.doorY = 0;
	} 
	if(west == 0){
		if((*m)->w.mapY == 0){
			x = (rand() % 19 - 1 + 1) + 1;
		}else{
			x = (*m)->westMap->east.doorX;
		}
		(*m)->field[x][0] = '#';
		(*m)->west.doorX = x;
		(*m)->west.doorY = 0;		
		
	}
	if (east == 1){
		x = (rand() % 19 - 1 + 1) + 1;
		(*m)->field[x][79] = '#';
		(*m)->east.doorX = x;
		(*m)->east.doorY = 79;
	}
	if(east == 0){
		if((*m)->w.mapY == 400){
			x = (rand() % 19 - 1 + 1) + 1;
		}else{
			x = (*m)->eastMap->west.doorX;
		}
		(*m)->field[x][79] = '#';
		(*m)->east.doorX = x;
		(*m)->east.doorY = 79;
		
	}
	if(north == 1){
		y = (rand() % 78 - 1 + 1) + 1;
		(*m)->field[0][y] = '#';
		(*m)->north.doorX = 0;
		(*m)->north.doorY = y;
	}
	if(north == 0){
		if((*m)->w.mapX == 0){
			y = (rand() % 78 - 1 + 1) + 1;
		}else{
			y = (*m)->northMap->south.doorY;
		}
		(*m)->field[0][y] = '#';
		(*m)->north.doorX = 0;
		(*m)->north.doorY = y;
	
	}
	if(south == 1){
		y = (rand() % 78 - 1 + 1) + 1;
		(*m)->field[20][y] = '#';
		(*m)->south.doorX = 20;
		(*m)->south.doorY = y;
	}
	if(south == 0){
		if((*m)->w.mapX == 400){
			y = (rand() % 78 - 1 + 1) + 1;
		}else{
			y = (*m)->southMap->north.doorY;
		}
		(*m)->field[20][y] = '#';
		(*m)->south.doorX = 20;
		(*m)->south.doorY = y;
	}

}

void initField(struct map* m){
	m = malloc(sizeof(struct map));
	for(int i = 0; i < X; i++)
		for(int j = 0; j < Y; j++)
			m->field[i][j] = ' ';
}

void print(struct map* m){
	start_color();
	//actually brown;
	init_color(COLOR_RED,360,250,200);
	//light blue
	init_color(COLOR_BLUE,203,596,858);
	//dark green
	init_color(COLOR_GREEN,98,435,240);
	//purple
	init_color(COLOR_MAGENTA,700,200,1000);
	//yellow
	init_color(COLOR_YELLOW,1000,976,200);
	//pink
	init_color(COLOR_CYAN,1000,200,600);
	//orange
	init_color(COLOR_WHITE,1000,318,0);
	
	init_pair(1,COLOR_RED,COLOR_BLUE);//border
	init_pair(2,COLOR_GREEN,COLOR_RED);//paths
	init_pair(3,COLOR_GREEN,COLOR_BLUE);//trees
	init_pair(4,COLOR_RED,COLOR_BLUE);//boulders
	init_pair(5,COLOR_MAGENTA,COLOR_RED);//colons
	init_pair(6,COLOR_YELLOW,COLOR_RED);//periods
	init_pair(7,COLOR_CYAN,COLOR_BLACK);//centers/marts
	init_pair(8,COLOR_WHITE,COLOR_BLACK);//players/npcs

	char c;
	for(int i = 0; i < X; i++){
		for(int j = 0; j < Y; j++){
			//printf("%c",m->field[i][j]);
			c = m->field[i][j];
			if(c == '%'){
				attron(COLOR_PAIR(1));
				mvaddch(i+1,j,m->field[i][j]);
				attroff(COLOR_PAIR(1));
			}
			else if(c == '#'){
				attron(COLOR_PAIR(2));
				mvaddch(i+1,j,m->field[i][j]);
				attroff(COLOR_PAIR(2));
			}
			else if(c == '^'){
				attron(COLOR_PAIR(3));
				mvaddch(i+1,j,m->field[i][j]);
				attroff(COLOR_PAIR(3));
			}
			else if(c == '.'){
				attron(COLOR_PAIR(6));
				mvaddch(i+1,j,m->field[i][j]);
				attroff(COLOR_PAIR(6));
			}
			else if(c == ':'){
				attron(COLOR_PAIR(5));
				mvaddch(i+1,j,m->field[i][j]);
				attroff(COLOR_PAIR(5));
			}
			else if(c == 'C'){
				attron(COLOR_PAIR(7));
				mvaddch(i+1,j,m->field[i][j]);
				attroff(COLOR_PAIR(7));
			}
			else if(c == 'M'){
				attron(COLOR_PAIR(7));
				mvaddch(i+1,j,m->field[i][j]);
				attroff(COLOR_PAIR(7));	
			}
			else if(c == '@' || c == 'r' || c == 'h' || c == 's'
					|| c == 'w' || c == 'p' || c == 'e'){
				attron(COLOR_PAIR(8));
				mvaddch(i+1,j,m->field[i][j]);
				attroff(COLOR_PAIR(8));		
			}
		}
	}
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
				if(m->field[j][y] != 'M' && m->field[j][y] != 'C'
					&& m->field[j][y] != '.'
					&& m->field[j][y] != ':')
					m->field[j][y] = '#';
			}
			break;
		}
	}
	
	c = 0;

	for(int i = y; i < 79 ; i++, c++){
		if(m->field[x][i] == '#'){
			for(int k = y;r < c; k++, r++){
				if(m->field[x][k] != 'M' && m->field[x][k] != 'C'
					&& m->field[x][k] != '.' 
					&& m->field[x][k] != ':')
					m->field[x][k] = '#';
			}
			break;
		}
	}

	c = 0;

	for(int i = x; i < 20; i++,c++){
		if(m->field[i][y] == '#'){
			for(int j = x; h < c; j++, h++){
				if(m->field[j][y] != 'M'  && m->field[j][y] != 'C'
					&& m->field[j][y] != '.' 
					&& m->field[j][y] != ':')
					m->field[j][y] = '#';
			}
			break;
		}
	}

	c = 0;

	for(int l = y; l > 0; l--,c++){
		if(m->field[x][l] == '#'){
			for(int d = y; f < c; y--,f++ ){
				if(m->field[x][d] != 'M' && m->field[x][d] != 'C'
					&& m->field[x][d] != '.' 
					&& m->field[x][d] != ':')
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
void moveMap(struct worldMap* m, struct map** curr, struct map** next, int dir){
	//no matter the direction make sure we check that we are not at an edge,
	//moving towards the edge x = 0,20, y=0,79
	//

	//We changed this function to an INT return
	//1 for curr that needs to be printed/2 for nextMap/map we move to to print
	if(dir == 1){
		if((*curr)->w.mapX == 0){
			//display map again
			//print the coordinates under the map	
			//print(curr);
			//return 1;
		}
		else if((*curr)->northMap != NULL){
			// update the current
			(*next) = m->wm[(*curr)->w.mapX-1][(*curr)->w.mapY];
		       	
			//print(next);	
			//return 2;
			//display the map
			//print the coordinates under the map
		}else if((*curr)->northMap == NULL){
			(*next) = malloc(sizeof(struct map));
			(*curr)->northMap = (*next);
			(*next)->southMap = (*curr);
			
			(*next)->w.mapX = (*curr)->w.mapX - 1;
			(*next)->w.mapY = (*curr)->w.mapY;
			m->wm[(*next)->w.mapX][(*next)->w.mapY] = (*next);

			grantMap(&m,(*next),1,0,1,1);
			//return 2;
			//print(next);
		}
	}else if(dir == 2){
		if((*curr)->w.mapY == 400){
			
			//print(curr);
			//return 1;
		}
		else if((*curr)->eastMap != NULL){
			(*next) = m->wm[(*curr)->w.mapX][(*curr)->w.mapY+1];
			
			//return 2;
			//print(next);
		}
		else if((*curr)->eastMap == NULL){
			(*next) = malloc(sizeof(struct map));
			(*curr)->eastMap = (*next);
			(*next)->westMap = (*curr);
			
			(*next)->w.mapX = (*curr)->w.mapX;
			(*next)->w.mapY = (*curr)->w.mapY + 1;
			m->wm[(*next)->w.mapX][(*next)->w.mapY] = (*next);

			grantMap(&m,(*next),1,1,1,0);
			
			//return 2; 
			//print(next);
		}
	
	}else if(dir == 3){
		if((*curr)->w.mapX == 400){
			
			//print(curr);
			//return 1;
		}
		else if((*curr)->southMap != NULL){
			(*next) = m->wm[(*curr)->w.mapX+1][(*curr)->w.mapY];
			
			//return 2;
			//print(next);
		}
		else if((*curr)->southMap == NULL){
			(*next) = malloc(sizeof(struct map));
			(*curr)->southMap = (*next);
			(*next)->northMap = (*curr);
			
			(*next)->w.mapX = (*curr)->w.mapX + 1;
			(*next)->w.mapY = (*curr)->w.mapY;
			m->wm[(*next)->w.mapX][(*next)->w.mapY] = (*next);
			
			grantMap(&m,(*next),0,1,1,1);
			
			//return 2;
			//print(next);
		}
	}else if(dir == 4){
		if((*curr)->w.mapY == 0){
			
			//return 1; 
			//print(curr);
		}
		else if((*curr)->westMap != NULL){
			(*next) = m->wm[(*curr)->w.mapX][(*curr)->w.mapY-1];
			
			//return 2;
			//print(next);
		}
		else if((*curr)->westMap == NULL){
			(*next) = malloc(sizeof(struct map));
			(*curr)->westMap = (*next);
			(*next)->eastMap = (*curr);

			(*next)->w.mapX = (*curr)->w.mapX;
			(*next)->w.mapY = (*curr)->w.mapY - 1;
			m->wm[(*next)->w.mapX][(*next)->w.mapY] = (*next);

			grantMap(&m,(*next),1,1,0,1);
			
			//return 2;
			//print(next);

		}
	}
	//return 0;
}

void jumpToMap(struct worldMap** m, int x, int y){
	if((*m)->wm[x][y] == NULL){
		//generate a new map, check all directions, if present
		//that number is 1, if not it's zero and needs to be
		//place pointer in worldmap
		int n = -1, s = -1, w = -1, e = -1;
		struct map* curr = malloc(sizeof(struct map));
		//check north
	       	if(x != 0 && (*m)->wm[x-1][y] == NULL){
			n = 1;
		}else{
			n = 0;
		}
		//check south
		if(x != 400 && (*m)->wm[x+1][y] == NULL){
			s = 1;
		}else{
			s = 0;
		}
		//check east
		if(y != 400 && (*m)->wm[x][y+1] == NULL){
			e = 1;
		}else{
			e = 0;
		}
		//check west
		if(y != 0 && (*m)->wm[x][y-1] == NULL){
			w = 1;
		}
		else{
			w = 0;
		}

		curr->w.mapX = x;
		curr->w.mapY = y;

		grantMap(m,curr,n,s,e,w);
		(*m)->wm[x][y] = curr;
		//print(curr);


	}
	else if((*m)->wm[x][y] != NULL){
		//struct map* curr = malloc(sizeof(struct map));
		//curr = m->wm[x][y];
		//print(curr);
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

	grantMap(&m,go,1,1,1,1);
	placePC(go);
	print(go);
	dijkstra(go, go->pc.x, go->pc.y, 0);

	// while loop to take user input
	// check if it exists as one of the commands
	// if correct, move/stay, display, quit,
	// if not tell them t the commands are and to stop that
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
			if(go->w.mapX >= 1){}
				//moveMap(m,go,go->northMap,'n');
			else{}
				//moveMap(m,go,go,'n');
			if(go->w.mapX >= 1)
				go = go->northMap;
		}
		//East
		if(active == 2){
			if(go->w.mapY <= 399){}
				//moveMap(m,go,go->eastMap,'e');
			else{}
				//moveMap(m,go,go,'e');
			if(go->w.mapY <= 399)
				go = go->eastMap;
		}
		//South
		if(active == 3){
			if(go->w.mapX <= 399){}
				//moveMap(m,go,go->southMap,'s');
			else{}
				//moveMap(m,go,go,'s');
			if(go->w.mapX <= 399)
				go = go->southMap;
		}
		//West
		if(active == 4){
			if(go->w.mapY >=1){}
				//moveMap(m,go,go->westMap,'w');
			else{}
				//moveMap(m,go,go,'w');
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
			jumpToMap(&m,x+200,y+200);
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

void grantMap(struct worldMap** wm, struct map* m, int n, int s, int e, int w){

		int pc = -1, pm = -1;

		initField(m);
		buildBorders(m);
		createExit(&m,n,e,s,w);
		generatePaths(&m,m->north,m->south,1);
		generatePaths(&m,m->west,m->east,0);
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
		for(int i = 0; i < m->longGrassPatches; i++)
			additionalPaths(m,m->longGrass[i]);

		for(int j = 0; j < m->clearingCount; j++)
			additionalPaths(m,m->clearings[j]);
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
	m->tempPC = m->field[x][y];
	m->field[x][y] = '@';
	m->pc.x = x;
	m->pc.y = y;
	m->pc.piece = '@';
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
			if(m->field[i][j] == '^' || m->field[i][j] == '%'
					|| m->field[i][j] == '@'
					|| m->field[i][j] == 'p'
					|| m->field[i][j] == 'w'
					|| m->field[i][j] == 'e'
					|| m->field[i][j] == 's'){
				visited[i][j] = 1;
				distance[i][j] = INT_MAX;
			}
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
			}else{
				
			}
			if(s == 0){//hiker
				m->hikerCost[i][j] = distance[i][j];
			}else if(s == 1){//rival
				m->rivalCost[i][j] = distance[i][j];
			}
		}
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

struct Element* eCreate(int n, char c, int f_x, int f_y,int x, int y, char p, int t_cost, int time ){
	struct Element* temp = (struct Element*)malloc(sizeof(struct Element));
	temp->c = c;
	temp->n = n;
	temp->f_x = f_x;
	temp->f_y = f_y;
	temp->t_x = x;
	temp->t_y = y;
	temp->t_cost = t_cost;
	temp->p = p;
	temp->time = time;
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

void ePush(struct Element** head, int n, char c, int f_x, int f_y, int x, int y, char p, int t_cost, int time){
	struct Element* curr = (*head);

	struct Element* temp = eCreate(n,c,f_x,f_y,x,y,p,t_cost,time);

	if((*head)->t_cost > t_cost){
		temp->next = *head;
		(*head) = temp;
	}else{
		while(curr->next != NULL && curr->next->t_cost <= t_cost){
			curr= curr->next;
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

struct Element* ePop(struct Element** head){
	struct Element* temp = *head;
	(*head) = (*head)->next;
	return temp;
}

int isEmpty(struct Node** node){
	return (*node) == NULL;
}

int isEEmpty(struct Element** e){
	return (*e) == NULL;
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

void decreaseTime(struct Element** head, int sub){
	struct Element* curr = (*head);

	while(curr != NULL){
		curr->t_cost = curr->t_cost - sub;

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

struct Element* eSortedMerge(struct Element* a, struct Element* b){
	if(a == NULL)
		return b;
	else if(b == NULL)
		return a;
	struct Element* result = NULL;

	if(a->time <= b->time){
		result = a;
		result->next = eSortedMerge(a->next,b);
	}else{
		result = b;
		result->next = eSortedMerge(a, b->next);
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

void eFrontBackSplit(struct Element* src, struct Element** fRef, struct Element** bRef){
	if(src == NULL || src->next == NULL){
		*fRef = src;
		*bRef = NULL;
		return;
	}
	struct Element* s = src;
	struct Element* f = src->next;

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

void eMergeSort(struct Element** head){
	if(*head == NULL || (*head)->next == NULL){
		return;
	}
	struct Element* a;
	struct Element* b;

	eFrontBackSplit(*head, &a, &b);
	eMergeSort(&a);
	eMergeSort(&b);

	*head = eSortedMerge(a,b);
}

int distMove(struct map* m, int x, int y, char c){
	int v = 0;
	if(c == '@' && (m->field[x][y] == '.' || m->field[x][y] == 'M'
		      || m->field[x][y] == 'C' || m->field[x][y] == '#'))
		v = 10;
	else if((c == 'r'|| c == 'h' || c == 'e' || c == 'w' || c == 'p')
			&& (m->field[x][y] == 'M' || m->field[x][y] == 'C'))
		v = 50;
	else if((c == 'r'|| c == 'h' || c == 'e' || c == 'w' || c == 'p')
			&& (m->field[x][y] == '.' || m->field[x][y] == '#'))
		v = 10;
	else if(c == 'h' && m->field[x][y] == ':')
		v = 15;
	else if((c == 'r' || c == 'w' || c =='e' || c == 'p' || c == '@')  
			&& m->field[x][y] == ':')
		v = 20;
	return v;

}

void turnControl(struct map* m){
	int start = 0;
	char t = ' ';
	//struct Element* pq = Ecreate();
	//pcMovement(map, pc x position, pc y position, )
	//struct Node* temp = pop(&pq);
	struct Element* temp;
	
	for(int i = 0; i < m->trainerCount; i++){
		if(m->trainers[i].piece == 'p')
			moveTrainers(m,'p',i);
		if(m->trainers[i].piece == 'w')
			moveTrainers(m,'w',i);
		if(m->trainers[i].piece == 'e')
			moveTrainers(m,'e',i);
		if(m->trainers[i].piece == 'r')
			moveTrainers(m,'r',i);
		if(m->trainers[i].piece == 'h')
			moveTrainers(m,'h',i);
	}
		while(!(isEEmpty(&m->pq))){
			temp = ePop(&m->pq);
			if(temp->c == '@'){
				if(freeLoc(m,temp->t_x,temp->t_y) == 1){
					m->tempPC = pcMovement(m,temp->t_x,temp->t_y,m->tempPC);		
				}
				dijkstra(m, m->pc.x, m->pc.y, 0);
				dijkstra(m, m->pc.x, m->pc.y, 1);		
			}
			else if(temp->c == 'p'){
				if(freeLoc(m,temp->t_x,temp->t_y) == 1)
					trainerMovement(m,temp->t_x,temp->t_y,temp->f_x,temp->f_y,temp->n,temp->p);
				
			}	
			else if(temp->c == 'w'){
				if(freeLoc(m,temp->t_x,temp->t_y) == 1)
					trainerMovement(m,temp->t_x,temp->t_y,temp->f_x,temp->f_y,temp->n,temp->p);
			}
			else if(temp->c == 'e'){
				if(freeLoc(m,temp->t_x,temp->t_y) == 1)
					trainerMovement(m,temp->t_x,temp->t_y,temp->f_x,temp->f_y,temp->n,temp->p);
			}
			else if(temp->c == 'r'){
				if(freeLoc(m,temp->t_x,temp->t_y) == 1)
					trainerMovement(m,temp->t_x,temp->t_y,temp->f_x,temp->f_y,temp->n,temp->p);
			}
			else if(temp->c == 'h'){
				if(freeLoc(m,temp->t_x,temp->t_y) == 1)
					trainerMovement(m,temp->t_x,temp->t_y,temp->f_x,temp->f_y,temp->n,temp->p);
			}
			start++;
		}
	free(temp);
}

void movePC(struct map* m){
	//we know the first move we need to place a '#' down from previous loc
	int start = 0;
	int direction = 0;
	int valid = 0, i = 0;
	char temp = ' ';
	char curr = ' ';
	while(direction == 0){
		direction = rand() % (8 - 1 + 1) + 1;
		valid = 0;
		while(valid == 0){
			//up 1, left 1
			if(direction == 1){
				valid = validPCMove(m, m->pc.x - 1, m->pc.y - 1);
				if(valid == 1){
					if(start == 0){	
						if(m->pq == NULL)
							m->pq = eCreate(0,'@',m->pc.x,m->pc.y,m->pc.x-1,m->pc.y-1,temp,distMove(m,m->pc.x-1,m->pc.y-1,'@'),0);
						else
							ePush(&m->pq,0,'@',m->pc.x,m->pc.y,m->pc.x-1,m->pc.y-1,m->tempPC,distMove(m,m->pc.x-1,m->pc.y-1,'@'),0);
					}
					start++;
				}
			}//up 1, same y
			else if(direction == 2){
				valid = validPCMove(m, m->pc.x - 1, m->pc.y);
				if(valid == 1){
					if(start == 0){
						if(m->pq == NULL)
							m->pq = eCreate(0,'@',m->pc.x,m->pc.y,m->pc.x-1,m->pc.y,temp,distMove(m,m->pc.x-1,m->pc.y,'@'),0);
						else
							ePush(&m->pq,0,'@',m->pc.x,m->pc.y,m->pc.x-1,m->pc.y,m->tempPC,distMove(m,m->pc.x-1,m->pc.y,'@'),0);
					}
					start++;
				}
			}//up 1, right 1
			else if(direction == 3){
				valid = validPCMove(m, m->pc.x - 1, m->pc.y + 1);
				if(valid == 1){
					if(start == 0){
						if(m->pq == NULL)
							m->pq = eCreate(0,'@',m->pc.x,m->pc.y,m->pc.x-1,m->pc.y+1,temp,distMove(m,m->pc.x-1,m->pc.y+1,'@'),0);
						else
							ePush(&m->pq,0,'@',m->pc.x,m->pc.y,m->pc.x-1,m->pc.y+1,m->tempPC,distMove(m,m->pc.x-1,m->pc.y+1,'@'),0);
					}
					start++;
				}
			}//same x, right 1
			else if(direction == 4){
				valid = validPCMove(m, m->pc.x, m->pc.y + 1);
				if(valid == 1){
					if(start == 0){
						if(m->pq == NULL)
							m->pq = eCreate(0,'@',m->pc.x,m->pc.y,m->pc.x,m->pc.y+1,temp,distMove(m,m->pc.x,m->pc.y+1,'@'),0);
						else
							ePush(&m->pq,0,'@',m->pc.x,m->pc.y,m->pc.x,m->pc.y+1,m->tempPC,distMove(m,m->pc.x,m->pc.y+1,'@'),0);
					}
					start++;
				}
			}// down 1, right 1
			else if(direction == 5){
				valid = validPCMove(m, m->pc.x + 1, m->pc.y + 1);
				if(valid == 1){
					if(start == 0){
						if(m->pq == NULL)
							m->pq = eCreate(0,'@',m->pc.x,m->pc.y,m->pc.x+1,m->pc.y+1,temp,distMove(m,m->pc.x+1,m->pc.y+1,'@'),0);
						else
							ePush(&m->pq,0,'@',m->pc.x,m->pc.y,m->pc.x+1,m->pc.y+1,m->tempPC,distMove(m,m->pc.x+1,m->pc.y+1,'@'),0);
					}
					start++;
				}
			}//down 1, same y
			else if(direction == 6){
				valid = validPCMove(m, m->pc.x + 1, m->pc.y);
				if(valid == 1){
					if(start == 0){
						if(m->pq == NULL)
							m->pq = eCreate(0,'@',m->pc.x,m->pc.y,m->pc.x+1,m->pc.y,temp,distMove(m,m->pc.x+1,m->pc.y,'@'),0);
						else
							ePush(&m->pq,0,'@',m->pc.x,m->pc.y,m->pc.x+1,m->pc.y,m->tempPC,distMove(m,m->pc.x+1,m->pc.y,'@'),0);
					}
					start++;
				}
			}//down 1, left 1
			else if(direction == 7){
				valid = validPCMove(m, m->pc.x + 1, m->pc.y - 1);
				if(valid == 1){
					if(start == 0){
						if(m->pq == NULL)
							m->pq = eCreate(0,'@',m->pc.x,m->pc.y,m->pc.x+1,m->pc.y-1,temp,distMove(m,m->pc.x+1,m->pc.y-1,'@'),0);
						else
							ePush(&m->pq,0,'@',m->pc.x,m->pc.y,m->pc.x+1,m->pc.y-1,m->tempPC,distMove(m,m->pc.x+1,m->pc.y-1,'@'),0);

					}
					start++;
				}
			}// same x, left 1
			else if(direction == 8){
				valid = validPCMove(m, m->pc.x, m->pc.y - 1);
				if(valid == 1){
					if(start == 0){
						if(m->pq == NULL)
							m->pq = eCreate(0,'@',m->pc.x,m->pc.y,m->pc.x,m->pc.y-1,temp,distMove(m,m->pc.x,m->pc.y-1,'@'),0);
						else
							ePush(&m->pq,0,'@',m->pc.x,m->pc.y,m->pc.x,m->pc.y-1,m->tempPC,distMove(m,m->pc.x,m->pc.y-1,'@'),0);

					}
					start++;
				}
			}
			if(valid == 1){
				dijkstra(m, m->pc.x, m->pc.y, 0);
				dijkstra(m, m->pc.x, m->pc.y, 1);
				for(i = 0; i < m->trainerCount; i++){
	
				}
			}
			direction = rand() % (8 - 1 + 1) + 1;
		
		}
	}
}

int validPCMove(struct map* m, int x, int y){
	if(x <= 0 || x >= 20 || y <= 0 || y >= 79)
		return 0;
	if(m->field[x][y] == '.' || m->field[x][y] == ':'
			|| m->field[x][y] == 'M' || m->field[x][y] == 'C'
			|| m->field[x][y] == '#')
		return 1;
	return 0;
}

char pcMovement(struct map* m, int x, int y, char p){
	char c; 
	int f_x = 0, f_y = 0;
	c = m->field[x][y];
	f_x = m->pc.x;
	f_y = m->pc.y;
	m->field[x][y] = '@';
	m->pc.x = x;
	m->pc.y = y;
	m->field[f_x][f_y] = p;
	return c;
}

void pcControl(struct worldMap* world, struct map* m){
	int ch;
	initscr();
	start_color();
	keypad(stdscr,TRUE);
	cbreak();
	noecho();
	curs_set(0);
	int s = 0;

	int f_x =-1000, f_y = -1000;
	int height = 10, width = 40;
        int x2 = (20-height) / 2 + 1, y2 = (80-width) / 2 + 1, pad_pos = 0;
	WINDOW *pad = newpad(20,width);
	char buffer[5];
	print(m);
	do{

		int x = m->pc.x;
		int y = m->pc.y;

		refresh();
		ch = getch();

		switch(ch){
			case 'y':
			case 'Y':
			case 7:
				if(ifExit(m,x-1,y-1) > 0){
					//clear();
					mapChange(world,&m,ifExit(m,x-1,y-1));
					print(m);
				}
				else if(validPCMove(m,x-1,y-1) == 1){
					if(m->pq == NULL)
						m->pq = eCreate(0,'@',m->pc.x,m->pc.y,m->pc.x-1,m->pc.y-1,m->tempPC,distMove(m,m->pc.x-1,m->pc.y-1,'@'),0);
					else
						ePush(&m->pq,0,'@',m->pc.x,m->pc.y,m->pc.x-1,m->pc.y-1,m->tempPC,distMove(m,m->pc.x-1,m->pc.y-1,'@'),0);

					turnControl(m);
					s++;
					x -= 1;
					y -= 1;
					print(m);

				}else if(validPCMove(m,x-1,y-1) != 1){
					if(battle(m,x-1,y-1) == 1){
						displayBattle(m);
					}
				}
				break;
			case 'k':
			case 'K':
			case 8:
				if(ifExit(m,x-1,y) > 0){
					clear();
					mapChange(world,&m,ifExit(m,x-1,y));
					//updatePC(m,78,
				//world->wm[m->w.mapX+1][m->w.mapY]->north.doorY);	
					print(m);
				}
				else if(validPCMove(m,x-1,y) == 1){
					if(m->pq == NULL)
						m->pq = eCreate(0,'@',m->pc.x,m->pc.y,m->pc.x-1,m->pc.y,m->tempPC,distMove(m,m->pc.x-1,m->pc.y,'@'),0);
					else
						ePush(&m->pq,0,'@',m->pc.x,m->pc.y,m->pc.x-1,m->pc.y,m->tempPC,distMove(m,m->pc.x-1,m->pc.y,'@'),0);

					turnControl(m);
					s++;
					x -= 1;
					print(m);
				}else if(validPCMove(m,x-1,y) != 1){
					if(battle(m,x-1,y) == 1){
						displayBattle(m);
					}
				}
				break;
			case 'u':
			case 'U':
			case 9:
				if(ifExit(m,x-1,y+1) > 0){
					//clear();
					mapChange(world,&m,ifExit(m,x-1,y+1));
					print(m);
				}
				else if(validPCMove(m,x-1,y+1) == 1){
					if(m->pq == NULL)
						m->pq = eCreate(0,'@',m->pc.x,m->pc.y,m->pc.x-1,m->pc.y+1,m->tempPC,distMove(m,m->pc.x-1,m->pc.y+1,'@'),0);
					else
						ePush(&m->pq,0,'@',m->pc.x,m->pc.y,m->pc.x-1,m->pc.y+1,m->tempPC,distMove(m,m->pc.x-1,m->pc.y+1,'@'),0);

					turnControl(m);
					s++;
					x -= 1;
					y += 1;
					print(m);
				}else if(validPCMove(m,x-1,y+1) != 1){
					if(battle(m,x-1,y+1) == 1){
						displayBattle(m);
					}
				}
				break;
			case 'l':
			case 'L':
			case 6:
				if(ifExit(m,x,y+1) > 0){
					//clear();
					mapChange(world,&m,ifExit(m,x,y+1));
					print(m);
				}
				else if(validPCMove(m,x,y+1) == 1){
					if(m->pq == NULL)
						m->pq = eCreate(0,'@',m->pc.x,m->pc.y,m->pc.x,m->pc.y+1,m->tempPC,distMove(m,m->pc.x,m->pc.y+1,'@'),0);
					else
						ePush(&m->pq,0,'@',m->pc.x,m->pc.y,m->pc.x,m->pc.y+1,m->tempPC,distMove(m,m->pc.x,m->pc.y+1,'@'),0);

					turnControl(m);
					s++;
					y += 1;
					print(m);
				}else if(validPCMove(m,x,y+1) != 1){
					if(battle(m,x,y+1) == 1){
						displayBattle(m);
					}
				}
				break;
			case 'n':
			case 'N':
			case 3:
				if(ifExit(m,x+1,y+1) > 0){
					//clear();
					mapChange(world,&m,ifExit(m,x+1,y+1));
					print(m);
				}
				else if(validPCMove(m,x+1,y+1) == 1){
					if(m->pq == NULL)
						m->pq = eCreate(0,'@',m->pc.x,m->pc.y,m->pc.x+1,m->pc.y+1,m->tempPC,distMove(m,m->pc.x+1,m->pc.y+1,'@'),0);
					else
						ePush(&m->pq,0,'@',m->pc.x,m->pc.y,m->pc.x+1,m->pc.y+1,m->tempPC,distMove(m,m->pc.x+1,m->pc.y+1,'@'),0);

					turnControl(m);
					s++;
					x += 1;
					y += 1;
					print(m);
				}else if(validPCMove(m,x+1,y+1) != 1){
					if(battle(m,x+1,y+1) == 1){
						displayBattle(m);
					}
				}
				break;
			case 'j':
			case 'J':
			case 2:
				if(ifExit(m,x+1,y) > 0){
					//clear();
					mapChange(world,&m,ifExit(m,x+1,y));
					print(m);
				}
				else if(validPCMove(m,x+1,y) == 1){
					if(m->pq == NULL)
						m->pq = eCreate(0,'@',m->pc.x,m->pc.y,m->pc.x+1,m->pc.y,m->tempPC,distMove(m,m->pc.x+1,m->pc.y,'@'),0);
					else
						ePush(&m->pq,0,'@',m->pc.x,m->pc.y,m->pc.x+1,m->pc.y,m->tempPC,distMove(m,m->pc.x+1,m->pc.y,'@'),0);

					turnControl(m);
					s++;
					x += 1;
					print(m);
				}else if(validPCMove(m,x+1,y) != 1){
					if(battle(m,x+1,y) == 1){
						displayBattle(m);
					}
				}
				break;
			case 'b':
			case 'B':
			case 1:
				if(ifExit(m,x+1,y-1) > 0){
					//clear();
					mapChange(world,&m,ifExit(m,x+1,y-1));
					print(m);
				}
				else if(validPCMove(m,x+1,y-1) == 1){
					if(m->pq == NULL)
						m->pq = eCreate(0,'@',m->pc.x,m->pc.y,m->pc.x+1,m->pc.y-1,m->tempPC,distMove(m,m->pc.x+1,m->pc.y-1,'@'),0);
					else
						ePush(&m->pq,0,'@',m->pc.x,m->pc.y,m->pc.x+1,m->pc.y-1,m->tempPC,distMove(m,m->pc.x+1,m->pc.y-1,'@'),0);
					
					turnControl(m);
					s++;
					x += 1;
					y -= 1;
					print(m);
				}else if(validPCMove(m,x+1,y-1) != 1){
					if(battle(m,x+1,y-1) == 1){
						displayBattle(m);
					}
				}
				break;
			case 'h':
			case 'H':
			case 4:
				if(ifExit(m,x,y-1) > 0){
					//clear();
					mapChange(world,&m,ifExit(m,x,y-1));
					print(m);
				}
				else if(validPCMove(m,x,y-1) == 1){
					if(m->pq == NULL)
						m->pq = eCreate(0,'@',m->pc.x,m->pc.y,m->pc.x,m->pc.y-1,m->tempPC,distMove(m,m->pc.x,m->pc.y-1,'@'),0);
					else
						ePush(&m->pq,0,'@',m->pc.x,m->pc.y,m->pc.x,m->pc.y-1,m->tempPC,distMove(m,m->pc.x,m->pc.y-1,'@'),0);
					
					turnControl(m);
					s++;
					y -= 1;
					print(m);
				}else if(validPCMove(m,x,y-1) != 1){
					if(battle(m,x,y-1) == 1){
						displayBattle(m);	
					}
				}
				break;
			case '.':
			case 5:
			case ' ':
				turnControl(m);
				print(m);
				break;
			case 't':
			case 'T':
				displayTrainers(m);
				refresh();
				break;
			case 62:
				if(inStore(m) == 1)
					displayStore(m);
				break;
			case 'f':
			case 'F':
				//handle fly to, error checking 
				// jumpToMap(struct worldMap* m, int x, int y)
				noecho();
				cbreak();
				prefresh(pad,0,0,x2,y2,15,50);
				wprintw(pad,"You're trying to jump" 
						" to a new map?\n"
						"Enter x and y.\n"
						"Values must be -200"
					        " to 200\n");
				while((f_x < -200 || f_x > 200) 
						|| (f_y < -200 || f_y > 200)){
					
					wprintw(pad,"Enter value for x to fly to:"
							"\n");
					prefresh(pad,0,0,x2,y2,15,50);
					getstr(buffer);
					if(stringInt(buffer) == 1)
						f_x = atoi(buffer);
					wprintw(pad,buffer);
					wprintw(pad,"\n");

					prefresh(pad,0,0,x2,y2,15,50);
					wprintw(pad,"Enter value for y to fly to:"
							"\n");
					prefresh(pad,0,0,x2,y2,15,50);
					getstr(buffer);
					if(stringInt(buffer) == 1)
						f_y = atoi(buffer);
					wprintw(pad,buffer);
					wprintw(pad,"\n");	
					
					werase(pad);
				}
				clear();
		
				f_x += 200;
				f_y += 200;
				updateMap(&m,world,f_x,f_y);
				jumpToMap(&world,f_x,f_y);
				m = world->wm[f_x][f_y];
				if(world->wm[m->w.mapX][m->w.mapY]->pc.piece == 0)
					placePC(m);
				if(m->trainers[0].piece == 0){
					int trainers = (rand() % (13 - 7 + 1)) + 7;
					createTrainers(m,trainers);
				}
				f_x = -1000,f_y = -1000;
				print(m);
				break;
		}
	
	}while((ch != 'Q' && ch != 'q'));

	endwin();
}

void updateMap(struct map** m, struct worldMap* world, int x, int y){
	(*m) = world->wm[x][y];
}

int ifExit(struct map* m, int x, int y){
	//doorX, doorY
	//we get right
	if(m->north.doorX == x && m->north.doorY == y)
		return 1;
	else if(m->east.doorX == x && m->east.doorY == y)
		return 2;
	else if(m->south.doorX == x && m->south.doorY == y)
		return 3; 
	else if(m->west.doorX == x && m->west.doorY == y)
		return 4;
	return 0;
}

int mapAux(struct worldMap* m, struct map* curr, int dir){
	int v = 0;
	if(dir == 1){//go north
		v = 1;
		moveMap(m,&curr,&curr->northMap,1);
	}
	else if(dir == 2){//go east
		v = 2;
       		moveMap(m,&curr,&curr->eastMap,2);
	}
	else if(dir == 3){
		//go south
		v = 3;
		moveMap(m,&curr,&curr->southMap,3);
	}
	else if(dir == 4){//go west
		v = 4;
		moveMap(m,&curr,&curr->westMap,4);
	}
	return v;
}

void updatePC(struct map* cur, int x, int y){
	char temp = cur->field[x][y];
	cur->field[cur->pc.x][cur->pc.y] = cur->tempPC;
	cur->pc.x = x;
	cur->pc.y = y;
	cur->tempPC = temp;
	cur->field[x][y] = '@';

}

void mapChange(struct worldMap* m, struct map** cur, int dir){
	int x = (*cur)->pc.x;
	int y = (*cur)->pc.y; 
	int n_x, n_y, v;//use these to update pc position; v is just a print cur/else
	if(dir == 1){
		n_x = 78;
		n_y = y;
		//updateMap(cur,m,(*cur)->w.mapX-1,(*cur)->w.mapY);
		//updatePC((*cur),n_x,n_y);
		if(mapAux(m,(*cur),dir) == 1){
			(*cur) = m->wm[(*cur)->w.mapX-1][(*cur)->w.mapY];
			if((*cur)->pc.x == 0 && (*cur)->pc.y == 0){
				updatePC((*cur),n_x,n_y);
			}else{//update the location of pc to n_x/n_y			
			}	
		}

		//updatePC((*cur),n_x,n_y);//change this to int, where it needs to be
		//one for curr, two for next map based on loc,1,2,3,4
		//print map , then update
	}
	else if(dir == 2){
		n_x = x;
		n_y = 1;
		if(mapAux(m,(*cur),dir) > 1){
			//updateMap(cur,m,(*cur)->w.mapX,(*cur)->w.mapY+1);
			//jumpToMap(m,cur->w.mapX,cur->w.mapY+1);
			(*cur) = m->wm[(*cur)->w.mapX][(*cur)->w.mapY+1];
			if((*cur)->pc.x == 0 && (*cur)->pc.y == 0){
				updatePC((*cur),n_x,n_y);
			}else{
		
			}	
		}
	}
	else if(dir == 3){
		n_x = 1;
		n_y = y;
		if(mapAux(m,(*cur),dir) > 1){
			//updateMap(cur,m,(*cur)->w.mapX+1,(*cur)->w.mapY);
			//jumpToMap(m,cur->w.mapX+1,cur->w.mapY);
			(*cur) = m->wm[(*cur)->w.mapX+1][(*cur)->w.mapY];
			if((*cur)->pc.x == 0 && (*cur)->pc.y == 0){
				updatePC((*cur),n_x,n_y);
			}else{
			
			}		
		}
	}
	else if(dir == 4){
		n_x = x;
		n_y = 78;
		if(mapAux(m,(*cur),dir) > 1){
			//updateMap(cur,m,(*cur)->w.mapX,(*cur)->w.mapY-1);
			//jumpToMap(m,cur->w.mapX,cur->w.mapY-1);
			(*cur) = m->wm[(*cur)->w.mapX][(*cur)->w.mapY-1];
			if((*cur)->pc.x == 0 && (*cur)->pc.y == 0){
				updatePC((*cur),n_x,n_y);
			}else{
			
			}	
		}
	}
}

int stringInt(char* a){
	//size_t n = sizeof(a) / sizeof(a[0]);
	//printf("n:%zu\n",n);
	//printf("string length: %zu\n",strlen(a));
	for(int i = 0; i < strlen(a); i++){
		if(a[0] == '-' && i == 0)
			i++;
		if(!isdigit(a[i]) && a[i] != '\n')
			return 0;
	}
	return 1;
}

void displayTrainers(struct map* m){
	int ch;
	initscr();
	int height = 10, width = 40;
	int x = (20 - height) / 2 + 1;
	int y = (80 - width) / 2 + 1;
	
	WINDOW *pad = newpad(m->trainerCount,width);
	keypad(stdscr,TRUE);
	cbreak();
	noecho();	

	prefresh(pad,0,0,x,y,10,50);
	char buffer[500];
	scrollok(pad, TRUE);
	int pad_pos = 0;
	
	for(int i = 0; i < m->trainerCount; i++){	
		strcpy(buffer,trainerCalc(m,i));
		wprintw(pad,"%s",buffer);
	}

	do{

		prefresh(pad,pad_pos,0,x,y,10,50);
		ch = getch();

		switch(ch){
			case KEY_UP:
				if(pad_pos > 0){
					prefresh(pad,pad_pos,0,x,y,10,50);
					pad_pos--;
				}
				break;

			case KEY_DOWN:
				if(pad_pos < m->trainerCount-6){
					prefresh(pad,pad_pos,0,x,y,10,50);
					pad_pos++;
				}
				break;
		}
			
	}while(ch != 27);

	clear();
	print(m);
}

char* trainerCalc(struct map* m, int n){
	char buffer[500];
	char *b_ptr = buffer;
	char* xtemp;
	char* ytemp;
	int relXPos = 0, relYPos = 0;
	relXPos = m->pc.x - m->trainers[n].x;
	relYPos = m->pc.y - m->trainers[n].y;
	if(relXPos > 0)
		xtemp = " north";
	else if(relXPos < 0)
		xtemp = " south";
	else if(relXPos == 0)
		xtemp = "";
	
	if(relYPos > 0)
		ytemp = " west";
	else if(relYPos < 0)
		ytemp = " east";
	else if(relYPos == 0)
		ytemp = "";

	if(abs(relXPos == 0)){
		snprintf(buffer, sizeof(buffer),
			       	"%c, %d %s.\n",
				m->trainers[n].piece, abs(relYPos), ytemp);

	}else if(abs(relYPos == 0)){
		snprintf(buffer, sizeof(buffer),
			       	"%c, %d %s.\n",
				m->trainers[n].piece, abs(relXPos), xtemp);

	}else
	snprintf(buffer, sizeof(buffer),
		       	"%c, %d %s, %d %s.\n",
			m->trainers[n].piece, abs(relXPos), xtemp,
		       	abs(relYPos), ytemp);
	return b_ptr;
			
}

int inStore(struct map* m){
	int pCenHeight = m->pokecenter.x_loc + m->pokecenter.height;
	int pCenWidth = m->pokecenter.y_loc + m->pokecenter.width;
	int pMarHeight = m->pokemart.x_loc + m->pokemart.height;
	int pMarWidth = m->pokemart.y_loc + m->pokemart.width; 
	//start with pokecenter
	for(int i = m->pokecenter.x_loc; i < pCenHeight; i++)
		for(int j = m->pokecenter.y_loc; j < pCenWidth; j++)
			if(m->pc.x == i && m->pc.y == j)
				return 1;
	//move onto pokemart
	for(int i = m->pokemart.x_loc; i < pMarHeight; i++)
		for(int j = m->pokemart.y_loc; j < pMarWidth; j++)
			if(m->pc.x == i && m->pc.y == j)
				return 1;
	return 0;

}

void displayStore(struct map* m){
	int ch;
	initscr();
	int height = 10, width = 40;
	int x = (20 - height) / 2 + 1;
	int y = (80 - width) / 2 + 1;
	WINDOW *pad = newpad(20,width);
	keypad(stdscr,TRUE);
	cbreak();
	noecho();	
	int pad_pos = 0;
	wprintw(pad,"Welcome to the store!\n");
	do{

		prefresh(pad,pad_pos,0,x,y,10,50);
		ch = getch();
	
		switch(ch){
		}

	}while(ch != 60);

	clear();
	print(m);
}

void displayBattle(struct map* m){
	int ch;
	initscr();
	int height = 10, width = 40;
	int x = (20 - height) / 2 + 1;
	int y = (80 - width) / 2 + 1;
	WINDOW *pad = newpad(20,width);
	keypad(stdscr,TRUE);
	cbreak();
	noecho();	
	int pad_pos = 0;
	wprintw(pad,"This is basically a fight...\n");
	wprintw(pad,"Press escape to leave.\n");
	do{

		prefresh(pad,pad_pos,0,x,y,10,50);
		ch = getch();
	
		switch(ch){
		}

	}while(ch != 27);

	clear();
	print(m);

}

int npcInitBattle(struct map* m, int n, int x, int y){
	char p = m->field[x][y];
	if(p == '@' && m->trainerStatus[n] == 0){
		m->trainerStatus[n] = 1;
		return 1;
	}
	return 0;
}

int battle(struct map* m, int x, int y){
	char p = m->field[x][y];
	if(p == 'r' || p == 'h' || p == 'w' || p == 's' || p == 'e' || p == 'p')
		for(int i = 0; i < m->trainerCount; i++)
			if(m->trainers[i].x == x && m->trainers[i].y == y)
				if(m->trainerStatus[i] == 0){
					m->trainerStatus[i] = 1;
					return 1;
				}
	
	return 0;
}

void trainerMovement(struct map* m, int x, int y, int f_x, int f_y, int n, char p){
	char c; 
	c = m->field[x][y];

	m->trainers[n].x = x;
	m->trainers[n].y = y;

	m->field[x][y] = m->trainers[n].piece;
	m->field[f_x][f_y] = p;
	m->trainerTemp[n] = c;
	return; 

}

void createTrainers(struct map* m, int n){
	int count = 0, p = 0;
	m->trainerCount = n;
	while(p < n){
		if(count == 0){
			struct character c;
			c.piece = 'h';
			m->trainers[p] = c;
			placeTrainers(m,c.piece,p);
		}else if(count == 1){
			struct character c;
			c.piece = 'r';
			m->trainers[p] = c;
			placeTrainers(m,c.piece,p);
		}else if(count == 2){
			struct character c;
			c.piece = 'p';
			m->trainers[p] = c;
			placeTrainers(m,c.piece,p);
		}else if(count == 3){
			struct character c;
			c.piece = 'w';
			m->trainers[p] = c;
			placeTrainers(m,c.piece,p);
		}else if(count == 4){
			struct character c;
			c.piece = 's';
			m->trainers[p] = c;
			placeTrainers(m,c.piece,p);
		}else if(count == 5){
			struct character c;
			c.piece = 'e';
			m->trainers[p] = c;
			placeTrainers(m,c.piece,p);
		}
	
		p++;
		count++;
		if(count == 6)
			count = 0;
	}

}

void placeTrainers(struct map* m, char c, int n){
	int x = 0, y = 0;
	if(c == 'h' || c == 'r' || c == 's'|| c == 'p' || c == 'e'){
		while((x == 0 && y == 0) || m->hikerCost[x][y] < 0 || 
				(m->field[x][y] != '.' && m->field[x][y] != ':'
				 && m->field[x][y] != '#' && m->field[x][y] != 'C'
				 && m->field[x][y] != 'M')){
			x = rand() % (19 - 1 + 1) + 1;
			y = rand() % (78 - 1 + 1) + 1;
		}
	}
	else if(c =='w'){
		while((x == 0 && y == 0) || (m->field[x][y] != '.' 
					&& m->field[x][y] != ':' 
					&& m->field[x][y] != 'C'
					&& m->field[x][y] != 'M')){
			x = rand() % (19 - 1 + 1) + 1;
			y = rand() % (78 - 1 + 1) + 1;
		}
	}

	m->trainerTemp[n] = m->field[x][y];
	m->field[x][y] = c;
	m->trainers[n].x = x;
	m->trainers[n].y = y;
	m->trainers[n].piece = c;
}
void moveTrainers(struct map* m, char c, int n){
	int p_d = 0, s_d = 0, e_d = 0, h_d = 0, r_d = 0, w_d = 0;
	int valid = 0;
	char temp = ' ';
	int i = -1, w_to = 100000, w_fo = 0,flag = 0;
	struct character ch = m->trainers[n];
	//pacers
	if(c == 'p'){
		//1 is north, 2 is east, 3 is south,4 is west
		if(m->trainerDirection[n] == 0){
			m->trainerDirection[n] = rand()%(4 - 1 + 1) + 1;
			while(valid == 0){
				if(m->trainerDirection[n] == 1){
					i = freeLoc(m,ch.x-1,ch.y);
					if (i == 0){
						m->trainerDirection[n] = rand() % (4-1+1) + 1;
					}else if(i == 1){
						valid = 1;
					}
				}
				if(m->trainerDirection[n] == 2){
					i = freeLoc(m,ch.x,ch.y+1);
					if(i == 0){
						m->trainerDirection[n] = rand() % (4-1+1) + 1;
					}else if(i == 1){
						valid = 1;
					}
				}
				if(m->trainerDirection[n] == 3){
					i = freeLoc(m,ch.x+1,ch.y);
					if(i == 0){
						m->trainerDirection[n] = rand() % (4-1+1) + 1;
					}else if(i == 1){
						valid = 1;
					}
				}
				if(m->trainerDirection[n] == 4){
					i = freeLoc(m,ch.x,ch.y-1);
					if(i == 0){
						m->trainerDirection[n] = rand() % (4-1+1) + 1;
					}else if(i == 1){
						valid = 1;
					}
				}
			}
		}
		if(m->trainerDirection[n] == 1){
			i = freeLoc(m,ch.x-1,ch.y);
			if(i == 1 && ch.x-1 > 1){
				temp = m->trainerTemp[n];
				if(m->pq == NULL)
					m->pq = eCreate(n,'p',ch.x,ch.y,ch.x-1,ch.y,temp,distMove(m,ch.x-1,ch.y,'p'),0);
				else
					ePush(&m->pq,n,'p',ch.x,ch.y,ch.x-1,ch.y,temp,distMove(m,ch.x-1,ch.y,'p'),0);//push
				
				m->trainerTemp[n] = temp;
				ch.x = ch.x-1;
				m->trainers[n].x = ch.x;

			}else if(npcInitBattle(m,n,ch.x-1,ch.y) == 1)
				displayBattle(m);
			else{
				m->trainerDirection[n] = 3;
				
			}	
		} if(m->trainerDirection[n] == 2){
			i = freeLoc(m,ch.x,ch.y+1);
			if(i == 1 && ch.y+1 < 79){
				temp = m->trainerTemp[n];
				if(m->pq == NULL)
					m->pq = eCreate(n,'p',ch.x,ch.y,ch.x,ch.y+1,temp,distMove(m,ch.x,ch.y+1,'p'),0);
				else
					ePush(&m->pq,n,'p',ch.x,ch.y,ch.x,ch.y+1,temp,distMove(m,ch.x,ch.y+1,'p'),0);
				
				m->trainerTemp[n] = temp;
				ch.y = ch.y+1;
				m->trainers[n].y = ch.y;

			}else if(npcInitBattle(m,n,ch.x,ch.y+1) == 1)
				displayBattle(m);	
			else{
				m->trainerDirection[n] = 4;
				
			}	
		} if(m->trainerDirection[n] == 3){
			i = freeLoc(m,ch.x+1,ch.y);
			if(i == 1 && ch.x+1 < 20){
				temp = m->trainerTemp[n];
				if(m->pq == NULL)
					m->pq = eCreate(n,'p',ch.x,ch.y,ch.x+1,ch.y,temp,distMove(m,ch.x+1,ch.y,'p'),0);
				else
					ePush(&m->pq,n,'p',ch.x,ch.y,ch.x+1,ch.y,temp,distMove(m,ch.x+1,ch.y,'p'),0);
				
				
				m->trainerTemp[n] = temp;
				ch.x = ch.x+1;
				m->trainers[n].x = ch.x;
			}else if(npcInitBattle(m,n,ch.x+1,ch.y) == 1)
				displayBattle(m);
			else{
				m->trainerDirection[n] = 1;
				
			}
		} if(m->trainerDirection[n] == 4){
			i = freeLoc(m,ch.x,ch.y-1);
			if(i == 1 && ch.y-1 > 0){
				temp = m->trainerTemp[n];
				if(m->pq == NULL)
					m->pq = eCreate(n,'p',ch.x,ch.y,ch.x,ch.y-1,temp,distMove(m,ch.x,ch.y-1,'p'),0);
				else
					ePush(&m->pq,n,'p',ch.x,ch.y,ch.x,ch.y-1,temp,distMove(m,ch.x,ch.y-1,'p'),0);
				
				m->trainerTemp[n] = temp;
				ch.y = ch.y-1;
				m->trainers[n].y = ch.y;
			}else if(npcInitBattle(m,n,ch.x,ch.y-1) == 1)
				displayBattle(m);
			else{
				m->trainerDirection[n] = 2;
	
			}
		}
	}
	else if(c == 'w'){
		valid = 0, i = 0;
		if(m->trainerDirection[n] == 0){
			m->trainerDirection[n] = rand() % (4 - 1 + 1) + 1;
		}
		while(valid == 0){
			if(m->trainerDirection[n] == 1){
				i = freeLoc(m,ch.x-1,ch.y);
				if(m->field[ch.x-1][ch.y] == m->trainerTemp[n]){
					temp = m->trainerTemp[n];
					if(m->pq == NULL)
						m->pq = eCreate(n,c,ch.x,ch.y,ch.x-1,ch.y,temp,distMove(m,ch.x-1,ch.y,c),0);
					else
						ePush(&m->pq,n,c,ch.x,ch.y,ch.x-1,ch.y,temp,distMove(m,ch.x-1,ch.y,c),0);

					ch.x = ch.x-1;
					m->trainers[n].x = ch.x;
					valid = 1;
				}else if(npcInitBattle(m,n,ch.x-1,ch.y) == 1)
					displayBattle(m);
				else{
					m->trainerDirection[n] = rand() % (4 - 1 + 1) + 1;
				}
			}
			else if(m->trainerDirection[n] == 2){
				i = freeLoc(m,ch.x,ch.y+1);
				if(m->field[ch.x][ch.y+1] == m->trainerTemp[n]){
					temp = m->trainerTemp[n];
					if(m->pq == NULL)
						m->pq = eCreate(n,'w',ch.x,ch.y,ch.x,ch.y+1,temp,distMove(m,ch.x,ch.y+1,'w'),0);
					else
						ePush(&m->pq,n,'w',ch.x,ch.y,ch.x,ch.y+1,temp,distMove(m,ch.x,ch.y+1,'w'),0);
					
					ch.y = ch.y+1;
					m->trainers[n].y = ch.y;
					valid = 1;
				}else if(npcInitBattle(m,n,ch.x,ch.y+1) == 1)
					displayBattle(m);
				else{
					m->trainerDirection[n] = rand() % (4 - 1 + 1) + 1;
					
				}
			}
			else if(m->trainerDirection[n] == 3){
				if(m->field[ch.x+1][ch.y] == m->trainerTemp[n]){
					temp = m->trainerTemp[n];
					if(m->pq == NULL)
						m->pq = eCreate(n,'w',ch.x,ch.y,ch.x+1,ch.y,temp,distMove(m,ch.x+1,ch.y,'w'),0);
					else
						ePush(&m->pq,n,'w',ch.x,ch.y,ch.x+1,ch.y,temp,distMove(m,ch.x+1,ch.y,'w'),0);
					
					ch.x = ch.x+1;
					m->trainers[n].x = ch.x;
					valid = 1;
				}else if(npcInitBattle(m,n,ch.x+1,ch.y) == 1)
					displayBattle(m);
				else{
					m->trainerDirection[n] = rand() % (4 - 1 + 1) + 1;
					
				}
			}
			else if(m->trainerDirection[n] == 4){
				if(m->field[ch.x][ch.y-1] == m->trainerTemp[n]){
					temp = m->trainerTemp[n];
					if(m->pq == NULL)
						m->pq = eCreate(n,'w',ch.x,ch.y,ch.x,ch.y-1,temp,distMove(m,ch.x,ch.y-1,'w'),0);
					else
						ePush(&m->pq,n,'w',ch.x,ch.y,ch.x,ch.y-1,temp,distMove(m,ch.x,ch.y-1,'w'),0);
					
					
					ch.y = ch.y-1;
					m->trainers[n].y = ch.y;
					valid = 1;
				}else if(npcInitBattle(m,n,ch.x,ch.y-1) == 1)
					displayBattle(m);
				else{
					m->trainerDirection[n] = rand() % (4 - 1 + 1) + 1;
				
				}
			}
		}	
	}
	else if(c == 'e'){
		valid = 0;
		if(m->trainerDirection[n] == 0){
			m->trainerDirection[n] = rand() % (4 - 1 + 1) + 1;
		}
		while(valid == 0){
			if(m->trainerDirection[n] == 1){
				i = freeLoc(m,ch.x-1,ch.y);
				if(i == 1){
					temp = m->trainerTemp[n];

					if(m->pq == NULL)
						m->pq = eCreate(n,'e',ch.x,ch.y,ch.x-1,ch.y,temp,distMove(m,ch.x-1,ch.y,'e'),0);
					else
						ePush(&m->pq,n,'e',ch.x,ch.y,ch.x-1,ch.y,temp,distMove(m,ch.x-1,ch.y,'e'),0);
					
					ch.x = ch.x-1;
					m->trainers[n].x = ch.x;
					valid = 1;
				}else if(npcInitBattle(m,n,ch.x-1,ch.y) == 1)
					displayBattle(m);
				else{
					
					m->trainerDirection[n] = rand() % (4-1+1)+1;
					
				}
			}
			else if(m->trainerDirection[n] == 2){
				i = freeLoc(m,ch.x,ch.y+1);
				if(i == 1){
					temp = m->trainerTemp[n];
					
					if(m->pq == NULL)
						m->pq = eCreate(n,'e',ch.x,ch.y,ch.x,ch.y+1,temp,distMove(m,ch.x,ch.y+1,'e'),0);
					else
						ePush(&m->pq,n,'e',ch.x,ch.y,ch.x,ch.y+1,temp,distMove(m,ch.x,ch.y+1,'e'),0);
					
					ch.y = ch.y+1;
					m->trainers[n].y = ch.y;
					valid = 1;
				}else if(npcInitBattle(m,n,ch.x,ch.y+1) == 1)
					displayBattle(m);
				else{
					m->trainerDirection[n] = rand() % (4-1+1)+1;
					
				}
			}
			else if(m->trainerDirection[n] == 3){
				i = freeLoc(m,ch.x+1,ch.y);
				if(i == 1){
					temp = m->trainerTemp[n];
					
					if(m->pq == NULL)
						m->pq = eCreate(n,'e',ch.x,ch.y,ch.x+1,ch.y,temp,distMove(m,ch.x+1,ch.y,'e'),0);
					else
						ePush(&m->pq,n,'e',ch.x,ch.y,ch.x+1,ch.y,temp,distMove(m,ch.x+1,ch.y,'e'),0);
					
					ch.x = ch.x+1;
					m->trainers[n].x = ch.x;
					valid = 1;
				}else if(npcInitBattle(m,n,ch.x+1,ch.y) == 1)
					displayBattle(m);
				else{
					m->trainerDirection[n] = rand() % (4-1+1)+1;
					
				}
			}
			else if(m->trainerDirection[n] == 4){
				i = freeLoc(m,ch.x,ch.y-1);
				if(i == 1){
					temp = m->trainerTemp[n];
					
					if(m->pq == NULL)
						m->pq = eCreate(n,'e',ch.x,ch.y,ch.x,ch.y-1,temp,distMove(m,ch.x,ch.y-1,'e'),0);
					else
						ePush(&m->pq,n,'e',ch.x,ch.y,ch.x,ch.y-1,temp,distMove(m,ch.x,ch.y-1,'e'),0);
					
					ch.y = ch.y-1;
					m->trainers[n].y = ch.y;
					valid = 1;
				}else if(npcInitBattle(m,n,ch.x,ch.y-1) == 1)
					displayBattle(m);
				else{
					m->trainerDirection[n] = rand() % (4-1+1)+1;
					
				}
			}
		}
	}
	else if(c == 'r' && m->trainerStatus[n] == 0){
		if(ch.x-1 > 0 && ch.y-1 > 0 && w_to > m->rivalCost[ch.x-1][ch.y-1]
				&& freeLoc(m,ch.x-1,ch.y-1) == 1){
			w_to = m->rivalCost[ch.x-1][ch.y-1];
			flag = 1;
		}
		if(npcInitBattle(m,n,ch.x-1,ch.y-1) == 1){
			displayBattle(m);
		}
		if(ch.x-1 > 0 && w_to > m->rivalCost[ch.x-1][ch.y]
				&& freeLoc(m,ch.x-1,ch.y) == 1){
			w_to = m->rivalCost[ch.x-1][ch.y];
			flag = 2;
		}
		if(npcInitBattle(m,n,ch.x-1,ch.y) == 1){
			displayBattle(m);
		}
		if(ch.x-1 > 0 && ch.y+1 < 79 && w_to > m->rivalCost[ch.x-1][ch.y+1]
				&& freeLoc(m,ch.x-1,ch.y+1) == 1){
			w_to = m->rivalCost[ch.x-1][ch.y+1];
			flag = 3;
		}
		if(npcInitBattle(m,n,ch.x-1,ch.y+1) == 1){
			displayBattle(m);
		}
		if(ch.y+1 < 79 && w_to > m->rivalCost[ch.x][ch.y+1]
				&& freeLoc(m,ch.x,ch.y+1) == 1){
			w_to = m->rivalCost[ch.x][ch.y+1];
			flag = 4;
		}
		if(npcInitBattle(m,n,ch.x,ch.y+1) == 1){
			displayBattle(m);
		}
		if(ch.x+1 < 20 && ch.y+1 < 79 && w_to > m->rivalCost[ch.x+1][ch.y+1]
				&& freeLoc(m,ch.x+1,ch.y+1) == 1){
			w_to = m->rivalCost[ch.x+1][ch.y+1];
			flag = 5;
		}
		if(npcInitBattle(m,n,ch.x+1,ch.y+1) == 1){
			displayBattle(m);
		}
		if(ch.x+1 < 20 && w_to > m->rivalCost[ch.x+1][ch.y]
				&& freeLoc(m,ch.x+1,ch.y) == 1){
			w_to = m->rivalCost[ch.x+1][ch.y];
			flag = 6;
		}
		if(npcInitBattle(m,n,ch.x+1,ch.y) == 1){
			displayBattle(m);
		}
		if(ch.x+1 < 20 && ch.y-1 > 0 && w_to > m->rivalCost[ch.x+1][ch.y-1]
				&& freeLoc(m,ch.x+1,ch.y-1) == 1){
			w_to = m->rivalCost[ch.x+1][ch.y-1];
			flag = 7;
		}
		if(npcInitBattle(m,n,ch.x+1,ch.y-1) == 1){
			displayBattle(m);
		}
		if(ch.y-1 > 0 && w_to > m->rivalCost[ch.x][ch.y-1]
				&& freeLoc(m,ch.x,ch.y-1) == 1){
			w_to = m->rivalCost[ch.x][ch.y-1];
			flag = 8;
		}
		if(npcInitBattle(m,n,ch.x,ch.y-1) == 1){
			displayBattle(m);
		}

		if(flag == 1){
			temp = m->trainerTemp[n];
			if(m->pq == NULL)
				m->pq = eCreate(n,c,ch.x,ch.y,ch.x-1,ch.y-1,temp,distMove(m,ch.x-1,ch.y-1,c),0);
			else
				ePush(&m->pq,n,c,ch.x,ch.y,ch.x-1,ch.y-1,temp,distMove(m,ch.x-1,ch.y-1,c),0);
		
		
			m->trainers[n].y = ch.y-1;
			m->trainers[n].x = ch.x-1;
		

		}else if(flag == 2){
			temp = m->trainerTemp[n];
			if(m->pq == NULL)
				m->pq = eCreate(n,c,ch.x,ch.y,ch.x-1,ch.y,temp,distMove(m,ch.x-1,ch.y,c),0);
			else 
				ePush(&m->pq,n,c,ch.x,ch.y,ch.x-1,ch.y,temp,distMove(m,ch.x-1,ch.y,c),0);

		
			m->trainers[n].x = ch.x-1;
			

		}else if(flag == 3){
			temp = m->trainerTemp[n];
			if(m->pq == NULL)
				m->pq = eCreate(n,c,ch.x,ch.y,ch.x-1,ch.y+1,temp,distMove(m,ch.x-1,ch.y+1,c),0); 
			else 
				ePush(&m->pq,n,c,ch.x,ch.y,ch.x-1,ch.y+1,temp,distMove(m,ch.x-1,ch.y+1,c),0);
			
	
			m->trainers[n].x = ch.x-1;
			m->trainers[n].y = ch.y+1;

		}else if(flag == 4){
			temp = m->trainerTemp[n];
			if(m->pq == NULL)
				m->pq = eCreate(n,c,ch.x,ch.y,ch.x,ch.y+1,temp,distMove(m,ch.x,ch.y+1,c),0);
			else
				ePush(&m->pq,n,c,ch.x,ch.y,ch.x,ch.y+1,temp,distMove(m,ch.x,ch.y+1,c),0);
			
			m->trainers[n].y = ch.y+1;

		}else if(flag == 5){
			temp = m->trainerTemp[n];
			if(m->pq == NULL)
				m->pq = eCreate(n,c,ch.x,ch.y,ch.x+1,ch.y+1,temp,distMove(m,ch.x+1,ch.y+1,c),0);
			else
				ePush(&m->pq,n,c,ch.x,ch.y,ch.x+1,ch.y+1,temp,distMove(m,ch.x+1,ch.y+1,c),0);
			
			m->trainers[n].x = ch.x+1;
			m->trainers[n].y = ch.y+1;

		}else if(flag == 6){
			temp = m->trainerTemp[n];
			if(m->pq == NULL)
				m->pq = eCreate(n,c,ch.x,ch.y,ch.x+1,ch.y,temp,distMove(m,ch.x+1,ch.y,c),0);
			else
				ePush(&m->pq,n,c,ch.x,ch.y,ch.x+1,ch.y,temp,distMove(m,ch.x+1,ch.y,c),0);
			
			m->trainers[n].x = ch.x+1;

		}else if(flag == 7){
			temp = m->trainerTemp[n];
			if(m->pq == NULL)
				m->pq = eCreate(n,c,ch.x,ch.y,ch.x+1,ch.y-1,temp,distMove(m,ch.x+1,ch.y-1,c),0);
			else
				ePush(&m->pq,n,c,ch.x,ch.y,ch.x+1,ch.y-1,temp,distMove(m,ch.x+1,ch.y-1,c),0);
			
			
			m->trainers[n].x = ch.x+1;
			m->trainers[n].y = ch.y-1;

		}else if(flag == 8){
			temp = m->trainerTemp[n];
			if(m->pq == NULL)
				m->pq = eCreate(n,c,ch.x,ch.y,ch.x,ch.y-1,temp,distMove(m,ch.x,ch.y-1,c),0);
			else
				ePush(&m->pq,n,c,ch.x,ch.y,ch.x,ch.y-1,temp,distMove(m,ch.x,ch.y-1,c),0);
			
			m->trainers[n].y = ch.y-1;
		}
	}

	else if(c == 'r' && m->trainerStatus[n] == 1){
		if(ch.x-1 > 0 && ch.y-1 > 0 && w_fo < m->rivalCost[ch.x-1][ch.y-1]
				&& freeLoc(m,ch.x-1,ch.y-1) == 1){
			w_fo = m->rivalCost[ch.x-1][ch.y-1];
			flag = 1;
		}
		if(ch.x-1 > 0 && w_fo < m->rivalCost[ch.x-1][ch.y]
				&& freeLoc(m,ch.x-1,ch.y) == 1){
			w_fo = m->rivalCost[ch.x-1][ch.y];
			flag = 2;
		}
		if(ch.x-1 > 0 && ch.y+1 < 79 && w_fo < m->rivalCost[ch.x-1][ch.y+1]
				&& freeLoc(m,ch.x-1,ch.y+1) == 1){
			w_fo = m->rivalCost[ch.x-1][ch.y+1];
			flag = 3;
		}
		if(ch.y+1 < 79 && w_fo < m->rivalCost[ch.x][ch.y+1]
				&& freeLoc(m,ch.x,ch.y+1) == 1){
			w_fo = m->rivalCost[ch.x][ch.y+1];
			flag = 4;
		}
		if(ch.x+1 < 20 && ch.y+1 < 79 && w_fo < m->rivalCost[ch.x+1][ch.y+1]
				&& freeLoc(m,ch.x+1,ch.y+1) == 1){
			w_fo = m->rivalCost[ch.x+1][ch.y+1];
			flag = 5;
		}
		if(ch.x+1 < 20 && w_fo < m->rivalCost[ch.x+1][ch.y]
				&& freeLoc(m,ch.x+1,ch.y) == 1){
			w_fo = m->rivalCost[ch.x+1][ch.y];
			flag = 6;
		}
		if(ch.x+1 < 20 && ch.y-1 > 0 && w_fo < m->rivalCost[ch.x+1][ch.y-1]
				&& freeLoc(m,ch.x+1,ch.y-1) == 1){
			w_fo = m->rivalCost[ch.x+1][ch.y-1];
			flag = 7;
		}
		if(ch.y-1 > 0 && w_fo < m->rivalCost[ch.x][ch.y-1]
				&& freeLoc(m,ch.x,ch.y-1) == 1){
			w_fo = m->rivalCost[ch.x][ch.y-1];
			flag = 8;
		}

		if(flag == 1){
			temp = m->trainerTemp[n];
			if(m->pq == NULL)
				m->pq = eCreate(n,c,ch.x,ch.y,ch.x-1,ch.y-1,temp,distMove(m,ch.x-1,ch.y-1,c),0);
			else
				ePush(&m->pq,n,c,ch.x,ch.y,ch.x-1,ch.y-1,temp,distMove(m,ch.x-1,ch.y-1,c),0);
		
			m->trainers[n].y = ch.y-1;
			m->trainers[n].x = ch.x-1;

		}else if(flag == 2){
			temp = m->trainerTemp[n];
			if(m->pq == NULL)
				m->pq = eCreate(n,c,ch.x,ch.y,ch.x-1,ch.y,temp,distMove(m,ch.x-1,ch.y,c),0);
			else 
				ePush(&m->pq,n,c,ch.x,ch.y,ch.x-1,ch.y,temp,distMove(m,ch.x-1,ch.y,c),0);
 
		
			m->trainers[n].x = ch.x-1;

		}else if(flag == 3){
			temp = m->trainerTemp[n];
			if(m->pq == NULL)
				m->pq = eCreate(n,c,ch.x,ch.y,ch.x-1,ch.y+1,temp,distMove(m,ch.x-1,ch.y+1,c),0); 
			else 
				ePush(&m->pq,n,c,ch.x,ch.y,ch.x-1,ch.y+1,temp,distMove(m,ch.x-1,ch.y+1,c),0);
			
	
			m->trainers[n].x = ch.x-1;
			m->trainers[n].y = ch.y+1;

		}else if(flag == 4){
			temp = m->trainerTemp[n];
			if(m->pq == NULL)
				m->pq = eCreate(n,c,ch.x,ch.y,ch.x,ch.y+1,temp,distMove(m,ch.x,ch.y+1,c),0);
			else
				ePush(&m->pq,n,c,ch.x,ch.y,ch.x,ch.y+1,temp,distMove(m,ch.x,ch.y+1,c),0);
			
			m->trainers[n].y = ch.y+1;

		}else if(flag == 5){
			temp = m->trainerTemp[n];
			if(m->pq == NULL)
				m->pq = eCreate(n,c,ch.x,ch.y,ch.x+1,ch.y+1,temp,distMove(m,ch.x+1,ch.y+1,c),0);
			else
				ePush(&m->pq,n,c,ch.x,ch.y,ch.x+1,ch.y+1,temp,distMove(m,ch.x+1,ch.y+1,c),0);
			
			m->trainers[n].x = ch.x+1;
			m->trainers[n].y = ch.y+1;

		}else if(flag == 6){
			temp = m->trainerTemp[n];
			if(m->pq == NULL)
				m->pq = eCreate(n,c,ch.x,ch.y,ch.x+1,ch.y,temp,distMove(m,ch.x+1,ch.y,c),0);
			else
				ePush(&m->pq,n,c,ch.x,ch.y,ch.x+1,ch.y,temp,distMove(m,ch.x+1,ch.y,c),0);
			
			m->trainers[n].x = ch.x+1;

		}else if(flag == 7){
			temp = m->trainerTemp[n];
			if(m->pq == NULL)
				m->pq = eCreate(n,c,ch.x,ch.y,ch.x+1,ch.y-1,temp,distMove(m,ch.x+1,ch.y-1,c),0);
			else
				ePush(&m->pq,n,c,ch.x,ch.y,ch.x+1,ch.y-1,temp,distMove(m,ch.x+1,ch.y-1,c),0);
			
			m->trainers[n].x = ch.x+1;
			m->trainers[n].y = ch.y-1;

		}else if(flag == 8){
			temp = m->trainerTemp[n];
			if(m->pq == NULL)
				m->pq = eCreate(n,c,ch.x,ch.y,ch.x,ch.y-1,temp,distMove(m,ch.x,ch.y-1,c),0);
			else
				ePush(&m->pq,n,c,ch.x,ch.y,ch.x,ch.y-1,temp,distMove(m,ch.x,ch.y-1,c),0);
			
			m->trainers[n].y = ch.y-1;
		}
	}



	else if(c == 'h' && m->trainerStatus[n] == 0){
		if(ch.x-1 > 0 && ch.y-1 > 0 && w_to > m->hikerCost[ch.x-1][ch.y-1]
				&& freeLoc(m,ch.x-1,ch.y-1) == 1){
			w_to = m->hikerCost[ch.x-1][ch.y-1];
			flag = 1;
		}
		if(npcInitBattle(m,n,ch.x-1,ch.y-1) == 1)
			displayBattle(m);

		if(ch.x-1 > 0 && w_to > m->hikerCost[ch.x-1][ch.y]
				&& freeLoc(m,ch.x-1,ch.y) == 1){
			w_to = m->hikerCost[ch.x-1][ch.y];
			flag = 2;
		}
		if(npcInitBattle(m,n,ch.x-1,ch.y) == 1)
			displayBattle(m);

		if(ch.x-1 > 0 && ch.y+1 < 79 && w_to > m->hikerCost[ch.x-1][ch.y+1]
				&& freeLoc(m,ch.x-1,ch.y+1) == 1){
			w_to = m->hikerCost[ch.x-1][ch.y+1];
			flag = 3;
		}
		if(npcInitBattle(m,n,ch.x,ch.y+1) == 1)
			displayBattle(m);

		if(ch.y+1 < 79 && w_to > m->hikerCost[ch.x][ch.y+1]
				&& freeLoc(m,ch.x,ch.y+1) == 1){
			w_to = m->hikerCost[ch.x][ch.y+1];
			flag = 4;
		}
		if(npcInitBattle(m,n,ch.x,ch.y+1) == 1)
			displayBattle(m);

		if(ch.x+1 < 20 && ch.y+1 < 79 && w_to > m->hikerCost[ch.x+1][ch.y+1]
				&& freeLoc(m,ch.x+1,ch.y+1) == 1){
			w_to = m->hikerCost[ch.x+1][ch.y+1];
			flag = 5;
		}
		if(npcInitBattle(m,n,ch.x+1,ch.y+1) == 1)
			displayBattle(m);

		if(ch.x+1 < 20 && w_to > m->hikerCost[ch.x+1][ch.y]
				&& freeLoc(m,ch.x+1,ch.y) == 1){
			w_to = m->hikerCost[ch.x+1][ch.y];
			flag = 6;
		}
		if(npcInitBattle(m,n,ch.x+1,ch.y) == 1)
			displayBattle(m);

		if(ch.x+1 < 20 && ch.y-1 > 0 && w_to > m->hikerCost[ch.x+1][ch.y-1]
				&& freeLoc(m,ch.x+1,ch.y-1) == 1){
			w_to = m->hikerCost[ch.x+1][ch.y-1];
			flag = 7;
		}
		if(npcInitBattle(m,n,ch.x+1,ch.y-1) == 1)
			displayBattle(m);

		if(ch.y-1 > 0 && w_to > m->hikerCost[ch.x][ch.y-1]
				&& freeLoc(m,ch.x,ch.y-1) == 1){
			w_to = m->hikerCost[ch.x][ch.y-1];
			flag = 8;
		}
		if(npcInitBattle(m,n,ch.x,ch.y-1) == 1)
			displayBattle(m);

		if(flag == 1){
			temp = m->trainerTemp[n];
			if(m->pq == NULL)
				m->pq = eCreate(n,c,ch.x,ch.y,ch.x-1,ch.y-1,temp,distMove(m,ch.x-1,ch.y-1,c),0);
			else
				ePush(&m->pq,n,c,ch.x,ch.y,ch.x-1,ch.y-1,temp,distMove(m,ch.x-1,ch.y-1,c),0);	
		
			m->trainers[n].y = ch.y-1;
			m->trainers[n].x = ch.x-1;

		}else if(flag == 2){
			temp = m->trainerTemp[n];
			if(m->pq == NULL)
				m->pq = eCreate(n,c,ch.x,ch.y,ch.x-1,ch.y,temp,distMove(m,ch.x-1,ch.y,c),0);
			else
				ePush(&m->pq,n,c,ch.x,ch.y,ch.x-1,ch.y,temp,distMove(m,ch.x-1,ch.y,c),0); 
		
			m->trainers[n].x = ch.x-1;

		}else if(flag == 3){
			temp = m->trainerTemp[n];
			if(m->pq == NULL)
				m->pq = eCreate(n,c,ch.x,ch.y,ch.x-1,ch.y+1,temp,distMove(m,ch.x-1,ch.y+1,c),0);
			else
				ePush(&m->pq,n,c,ch.x,ch.y,ch.x-1,ch.y+1,temp,distMove(m,ch.x-1,ch.y+1,c),0);
	
			m->trainers[n].x = ch.x-1;
			m->trainers[n].y = ch.y+1;

		}else if(flag == 4){
			temp = m->trainerTemp[n];
			if(m->pq == NULL)
				m->pq = eCreate(n,c,ch.x,ch.y,ch.x,ch.y+1,temp,distMove(m,ch.x,ch.y+1,c),0);
			else
				ePush(&m->pq,n,c,ch.x,ch.y,ch.x,ch.y+1,temp,distMove(m,ch.x,ch.y+1,c),0);	
			
			m->trainers[n].y = ch.y+1;

		}else if(flag == 5){
			temp = m->trainerTemp[n];
			if(m->pq == NULL)
				m->pq = eCreate(n,c,ch.x,ch.y,ch.x+1,ch.y+1,temp,distMove(m,ch.x+1,ch.y+1,c),0);
			else
				ePush(&m->pq,n,c,ch.x,ch.y,ch.x+1,ch.y+1,temp,distMove(m,ch.x+1,ch.y+1,c),0);
			
			m->trainers[n].x = ch.x+1;
			m->trainers[n].y = ch.y+1;

		}else if(flag == 6){
			temp = m->trainerTemp[n];
			if(m->pq == NULL)
				m->pq = eCreate(n,c,ch.x,ch.y,ch.x+1,ch.y,temp,distMove(m,ch.x+1,ch.y,c),0);
			else
				ePush(&m->pq,n,c,ch.x,ch.y,ch.x+1,ch.y,temp,distMove(m,ch.x+1,ch.y,c),0);
			
			m->trainers[n].x = ch.x+1;

		}else if(flag == 7){
			temp = m->trainerTemp[n];
			if(m->pq == NULL)
				m->pq = eCreate(n,c,ch.x,ch.y,ch.x+1,ch.y-1,temp,distMove(m,ch.x+1,ch.y-1,c),0);
			else
				ePush(&m->pq,n,c,ch.x,ch.y,ch.x+1,ch.y-1,temp,distMove(m,ch.x+1,ch.y,c),0);
			
			m->trainers[n].x = ch.x+1;
			m->trainers[n].y = ch.y-1;

		}else if(flag == 8){
			temp = m->trainerTemp[n];
			if(m->pq == NULL)
				m->pq = eCreate(n,c,ch.x,ch.y,ch.x,ch.y-1,temp,distMove(m,ch.x,ch.y-1,c),0);
			else
				ePush(&m->pq,n,c,ch.x,ch.y,ch.x,ch.y-1,temp,distMove(m,ch.x,ch.y-1,c),0);	
			
			m->trainers[n].y = ch.y-1;
		}
	}
	else if(c == 'h' && m->trainerStatus[n] == 1){
		if(ch.x-1 > 0 && ch.y-1 > 0 && w_fo < m->hikerCost[ch.x-1][ch.y-1]
				&& freeLoc(m,ch.x-1,ch.y-1) == 1){
			w_fo = m->hikerCost[ch.x-1][ch.y-1];
			flag = 1;
		}
		if(ch.x-1 > 0 && w_fo < m->hikerCost[ch.x-1][ch.y]
				&& freeLoc(m,ch.x-1,ch.y) == 1){
			w_fo = m->hikerCost[ch.x-1][ch.y];
			flag = 2;
		}
		if(ch.x-1 > 0 && ch.y+1 < 79 && w_fo < m->hikerCost[ch.x-1][ch.y+1]
				&& freeLoc(m,ch.x-1,ch.y+1) == 1){
			w_fo = m->hikerCost[ch.x-1][ch.y+1];
			flag = 3;
		}

		if(ch.y+1 < 79 && w_fo < m->hikerCost[ch.x][ch.y+1]
				&& freeLoc(m,ch.x,ch.y+1) == 1){
			w_fo = m->hikerCost[ch.x][ch.y+1];
			flag = 4;
		}
	
		if(ch.x+1 < 20 && ch.y+1 < 79 && w_fo < m->hikerCost[ch.x+1][ch.y+1]
				&& freeLoc(m,ch.x+1,ch.y+1) == 1){
			w_fo = m->hikerCost[ch.x+1][ch.y+1];
			flag = 5;
		}
		
		if(ch.x+1 < 20 && w_fo < m->hikerCost[ch.x+1][ch.y]
				&& freeLoc(m,ch.x+1,ch.y) == 1){
			w_fo = m->hikerCost[ch.x+1][ch.y];
			flag = 6;
		}
		if(ch.x+1 < 20 && ch.y-1 > 0 && w_fo < m->hikerCost[ch.x+1][ch.y-1]
				&& freeLoc(m,ch.x+1,ch.y-1) == 1){
			w_fo = m->hikerCost[ch.x+1][ch.y-1];
			flag = 7;
		}
		
		if(ch.y-1 > 0 && w_fo < m->hikerCost[ch.x][ch.y-1]
				&& freeLoc(m,ch.x,ch.y-1) == 1){
			w_fo = m->hikerCost[ch.x][ch.y-1];
			flag = 8;
		}

		if(flag == 1){
			temp = m->trainerTemp[n];
			if(m->pq == NULL)
				m->pq = eCreate(n,c,ch.x,ch.y,ch.x-1,ch.y-1,temp,distMove(m,ch.x-1,ch.y-1,c),0);
			else
				ePush(&m->pq,n,c,ch.x,ch.y,ch.x-1,ch.y-1,temp,distMove(m,ch.x-1,ch.y-1,c),0);
		
			m->trainers[n].y = ch.y-1;
			m->trainers[n].x = ch.x-1;

		}else if(flag == 2){
			temp = m->trainerTemp[n];
			if(m->pq == NULL)
				m->pq = eCreate(n,c,ch.x,ch.y,ch.x-1,ch.y,temp,distMove(m,ch.x-1,ch.y,c),0);
			else
				ePush(&m->pq,n,c,ch.x,ch.y,ch.x-1,ch.y,temp,distMove(m,ch.x-1,ch.y,c),0); 
		
			m->trainers[n].x = ch.x-1;

		}else if(flag == 3){
			temp = m->trainerTemp[n];
			if(m->pq == NULL)
				m->pq = eCreate(n,c,ch.x,ch.y,ch.x-1,ch.y+1,temp,distMove(m,ch.x-1,ch.y+1,c),0);
			else
				ePush(&m->pq,n,c,ch.x,ch.y,ch.x-1,ch.y+1,temp,distMove(m,ch.x-1,ch.y+1,c),0);	
	
			m->trainers[n].x = ch.x-1;
			m->trainers[n].y = ch.y+1;

		}else if(flag == 4){
			temp = m->trainerTemp[n];
			if(m->pq == NULL)
				m->pq = eCreate(n,c,ch.x,ch.y,ch.x,ch.y+1,temp,distMove(m,ch.x,ch.y+1,c),0);
			else
				ePush(&m->pq,n,c,ch.x,ch.y,ch.x,ch.y+1,temp,distMove(m,ch.x,ch.y+1,c),0);	
			
			m->trainers[n].y = ch.y+1;

		}else if(flag == 5){
			temp = m->trainerTemp[n];
			if(m->pq == NULL)
				m->pq = eCreate(n,c,ch.x,ch.y,ch.x+1,ch.y+1,temp,distMove(m,ch.x+1,ch.y+1,c),0);
			else
				ePush(&m->pq,n,c,ch.x,ch.y,ch.x+1,ch.y+1,temp,distMove(m,ch.x+1,ch.y+1,c),0);
			
			m->trainers[n].x = ch.x+1;
			m->trainers[n].y = ch.y+1;

		}else if(flag == 6){
			temp = m->trainerTemp[n];
			if(m->pq == NULL)
				m->pq = eCreate(n,c,ch.x,ch.y,ch.x+1,ch.y,temp,distMove(m,ch.x+1,ch.y,c),0);
			else
				ePush(&m->pq,n,c,ch.x,ch.y,ch.x+1,ch.y,temp,distMove(m,ch.x+1,ch.y,c),0);
			
			m->trainers[n].x = ch.x+1;

		}else if(flag == 7){
			temp = m->trainerTemp[n];
			if(m->pq == NULL)
				m->pq = eCreate(n,c,ch.x,ch.y,ch.x+1,ch.y-1,temp,distMove(m,ch.x+1,ch.y-1,c),0);
			else
				ePush(&m->pq,n,c,ch.x,ch.y,ch.x+1,ch.y-1,temp,distMove(m,ch.x+1,ch.y,c),0);
			
			m->trainers[n].x = ch.x+1;
			m->trainers[n].y = ch.y-1;

		}else if(flag == 8){
			temp = m->trainerTemp[n];
			if(m->pq == NULL)
				m->pq = eCreate(n,c,ch.x,ch.y,ch.x,ch.y-1,temp,distMove(m,ch.x,ch.y-1,c),0);
			else
				ePush(&m->pq,n,c,ch.x,ch.y,ch.x,ch.y-1,temp,distMove(m,ch.x,ch.y-1,c),0);
			
			m->trainers[n].y = ch.y-1;
		}
	}

}

int freeLoc(struct map* m, int x, int y){
	char c = m->field[x][y];
	if(c == '^' || c == '%' || c == 'p' || c == '@' || c == 'w' || c == 'e' ||
		       c == 's' || c == 'h' || c == 'r')
		return 0;
	if(x == 0 || x == 20 || y == 0 || y == 79)
		return 0;
	return 1;
}

void rivalCaught(struct map* m, int n){
	if(abs(m->pc.x - m->trainers[n].x) == 1 && m->pc.y == m->trainers[n].y){
		printf("Collision, match started!\n");
		exit(1);
	}
	if(abs(m->pc.y - m->trainers[n].y) == 1 && m->pc.x == m->trainers[n].x){
		printf("Collision, match started!\n");
		exit(1);
	}
	if(abs(m->pc.x - m->trainers[n].x) == 1 && abs(m->pc.y - m->trainers[n].y) == 1){
		printf("Collision, match started!\n");
		exit(1);
	}
} 
