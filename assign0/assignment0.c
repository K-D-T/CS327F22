#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SIZE 23
//shows the numbers, -1 never gets changed; REMEMBER THAT
//middle is roughly floor(size/2)-1 = (11,11)
int field[SIZE][SIZE];

//standard display function called after every turn
void display(int a[][SIZE]);
//as long as there is zero found, not an issue, -1 found, can't update
int isSink(int x, int y, int a[][SIZE]);
//make sure we don't cause seg fault, keep it between 0-22;
int isBorder(int x, int y);
//if point in field is 8, return 1, lead to topple
int isTooHigh(int x, int y, int a[][SIZE]);
//take the location cause a 8-direction topple, pass sand to each neighbor
void topple(int a[][SIZE], int x, int y);
//place one grain in the middle
void start();
// take the given input and create the field
void salt(char* x, char* y, char* h, int a[][SIZE]);

void start(int time){
	while(1){
		field[11][11]++;
		topple(field,11,11);
		display(field);
		usleep(1000000/time);
		printf("\n");
	}
}

void topple(int a[][SIZE], int x, int y){
	if(isTooHigh(x, y, a) == 1){
		a[x][y]-=8;
		if(isBorder(x-1, y-1) == 0){
			if(isSink(x-1, y-1, field) == 0){
				a[x-1][y-1]++;
				topple(a, x-1, y-1);
			}
		}
		if(isBorder(x-1, y) == 0){
			if(isSink(x-1, y, field) == 0){
				a[x-1][y]++;
				topple(a, x-1, y);
			}
		}
		if(isBorder(x-1, y+1) == 0){
			if(isSink(x-1, y+1, field) == 0){
				a[x-1][y+1]++;
				topple(a, x-1, y+1);
			}
		}
		if(isBorder(x, y-1) == 0){
			if(isSink(x, y-1, field) == 0){
				a[x][y-1]++;
				topple(a, x, y-1);
			}
		}
		if(isBorder(x, y+1) == 0){
			if(isSink(x, y+1, field) == 0){
				a[x][y+1]++;
				topple(a, x, y+1);
			}
		}
		if(isBorder(x+1, y-1) == 0){
			if(isSink(x+1, y-1, field) == 0){
				a[x+1][y-1]++;
				topple(a, x+1, y-1);
			}
		}
		if(isBorder(x+1, y) == 0){
			if(isSink(x+1, y, field) == 0){
				a[x+1][y]++;
				topple(a, x+1, y);
			}
		}
		if(isBorder(x+1, y+1) == 0){
			if(isSink(x+1, y+1, field) == 0){
				a[x+1][y+1]++;
				topple(a, x+1, y+1);
			}
		}
	}
}

int isSink(int x, int y, int a[][SIZE]){
	if(a[x][y] == -1)
		return 1;
	else
		return 0;
}

//1 if too high, 0 if not.
int isTooHigh(int x, int y, int a[][SIZE]){
	if(a[x][y] > 8)
		return 1;
	return 0;
}

//offset by one, first is the call to start program
void salt(char* x, char* y, char* h, int a[][SIZE]){
	int xNum = atoi(x);
	int yNum = atoi(y);
	int hNum = atoi(h);
		
	if(!isBorder(xNum,yNum))
		a[xNum][yNum] = hNum;

	if(a[11][11] == -1){
		printf("Sink entered at the center, program aborted.\n");
		exit(1);
	}
}

int isBorder(int x, int y){
	if(x < 0 || x > SIZE-1 || y < 0 || y > SIZE-1)
		return 1;
	else
		return 0;
}

void display(int a[SIZE][SIZE]){
	for(int i = 0; i < SIZE; i++){
		for(int j = 0; j < SIZE; j++){
			if(a[i][j] != -1){	
				printf("%2d" ,a[i][j]);
			}
			else{
				printf("%2c", '#');
			}
		}
		printf("\n");
	}
}

int main(int c, const char * argv[]){
	int i = 1;
	int j = 0;
	char x[5];
	char y[5];
	char h[5];
	int framerate = 0;

	if(c < 4){
		printf("That's not going to work for me. Bye!\n");
		exit(1);
	}

	if(strcmp(argv[1],"--fps") == 0){
		framerate = atoi(argv[2]);
		i = 3;
	}else{
		framerate = 1;
	}
	while(i < c){
		while(j < 3){
			if(j == 0)
				strcpy(x,argv[i+j]);
			if(j == 1)
				strcpy(y,argv[i+j]);
			if(j == 2)
				strcpy(h,argv[i+j]);
			j++;
		}
		salt(x,y,h, field);
		j = 0;
		i+=3;
	}
	start(framerate);
}

