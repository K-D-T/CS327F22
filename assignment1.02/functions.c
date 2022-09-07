#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <float.h>
#include <math.h>
#include <iso646.h>
#
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


void createExit(struct map* m){
	//we know they need to be on 0,R (0-79) / 20, R (0,79) / R(0,20), 0, R (0,20), 79
	int i = 0, j_x = 0, j_y = 0, x = 0, y = 0;
	while(i < 4){
		if(i % 2 == 0){
			x = (rand() % 19 - 1 + 1) + 1;
			if(j_x % 2 == 0){
				m->field[x][0] = '#';
				m->west.doorX = x;
				m->west.doorY = 0;
			}else{
				m->field[x][79] = '#';
				m->east.doorX = x;
				m->east.doorY = 79;
			}
			j_x++;
		}else{
			y = (rand() % 78 - 1 + 1) + 1;
			if(j_y % 2 == 0){
				m->field[0][y] = '#';
				m->north.doorX = 0;
				m->north.doorY = y;
			}else{
				m->field[20][y] = '#';
				m->south.doorX = 20;
				m->south.doorY = y;
			}
			j_y++;
		}
		i++;
	}

}

void initField(struct map* m){
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
}

void buildBorders(struct map* m){
	for(int i = 0; i < X; i++)
		for(int j = 0; j < Y; j++)
			if(j == 79 || i == 0 || i == 20 || j == 0)
				m->field[i][j] = '%';
}

void additionalPaths(struct map* m, struct pokeloci p){
	int c = 0, f = 0, q = 0, r = 0 , h = 0;
	//int flag = 1;
	int x = p.x_loc;
	int y = p.y_loc;

	//while(flag == 1){
		for(int i = x; i > 0; i--,c++){
			//if(m->field[i][y] == '%')
			//	break;
			if(m->field[i][y] == '#'){
				for(int j = x; q < c; j--, q++){
					if(m->field[j][y] != 'M' && m->field[j][y] != 'C')
						m->field[j][y] = '#';
				}
				break;
			}
		}
		//flag = 2;
		c = 0;
	//}while(flag == 2){
		for(int i = y; i < 79 ; i++, c++){
			if(m->field[x][i] == '#'){
				for(int k = y;r < c; k++, r++){
					if(m->field[x][k] != 'M' && m->field[x][k] != 'C')
						m->field[x][k] = '#';
				}
				break;
			}
		}
		//flag = 3;
		c = 0;
	//}
	//while(flag == 3){
		for(int i = x; i < 20; i++,c++){
			if(m->field[i][y] == '#'){
				for(int j = x; h < c; j++, h++){
					if(m->field[j][y] != 'M'  && m->field[j][y] != 'C')
						m->field[j][y] = '#';
				}
				break;
			}
		}
		//flag = 4;
		c = 0;
	//}
	//while(flag == 4){
		for(int l = y; l > 0; l--,c++){
			if(m->field[x][l] == '#'){
				for(int d = y; f < c; y--,f++ ){
					if(m->field[x][d] != 'M' && m->field[x][d] != 'C')
						m->field[x][d] = '#';
				}
				break;
			}
		}
		//flag = 0;
		c = 0;
	//}
}

