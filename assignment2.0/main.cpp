#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <float.h>
#include <math.h>
#include <iso646.h>
#include <ncurses.h>
#include "build.h"
#include <string>
#include <iostream>
#include <fstream>



int main(int argc, char* argv[]){
	

	Board b;
	b.initBoard();
	b.play();
	return 0;
}
