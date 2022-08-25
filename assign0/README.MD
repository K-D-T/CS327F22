Kenyon Thomas CS327 F22

field is a 2-D array to display the field

unnecessary constant SIZE represents the size of the array

void display is a function to show the table after sand has been added/toppled, parameter is main array

int isSink returns 1 if a sink is found, parameters are coordinates and array

int isBorder returns 1 if border/out of array; avoids seg faults, parameters are coordinates and array

int isTooHigh, returns 1 if location height is over 8, parameters are coordinates and array

void topple, meant to be a recursive call function, subtracts 8 if too high, adds 1 to each neighbor within bounds, callagain to ensure neighbors aren't over 8, parameters are array and coordinates.

void start, infinite loop adds grain to middle of board, calls topple, usleep to show and display field, parameter is framerate.

void salt, inputs characters into field, changes strings to numbers and places them in array, parameters are numbers and array.


Files are assignment0.c, README.MD, and changelog, MAKEFILE

