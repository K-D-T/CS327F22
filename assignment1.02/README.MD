Assign 1.02
Started 9/07/22

Program runs on main.c, functions.c, and functions.h
Mostly the same information from README.MD 1.01, but there were some upgrades.

Struct for worldMapLoc, helps to track where the pointers for a location go.
Added in a struct data element for worldMapLoc in map struct, which contains data for specific map

struct for worldMap, a 2-d 401 X 401 array of pointers 

createExit needed to be updated to stop seg fault, based on edge cases where there wasno more data to pull from.

generateWorldMap, allocates enough memory for 401 x 401 pointers to maps, also initializes the first map and sets all border maps to NULL

moveMap, single movement function, takes direction as input and moves in the corresponding location, can build new maps, find old ones

jumpToMap, takes the input that a player would input(both x and y must be between -200 - 200) 

play, takes the worldmap *, and current map, starts at (0,0) -> (200,200) lets player, choose a direction, jump to x,y, or quit. BE AWARE!!!***!!!! 
 (I'm using standard x,y)

"f -200 -200" , I should be in the uppermost left corner (0,0)

"f -200 200", I should be in the uppermost right corner (0,400)

"f 200 -200", I should be in the lowest left corner (400,0)

"f 200 200", I should be in the lowest right corner (400, 400)

I'f a player wants to go to 200,200 (400,400) they would have to enter that.

if we start at
(0,0) (Internally (200,200)). go north, we should be at (-1,0) (Internally (199,200))

if we start at

(0,0) (Internally (200,200)) go south, we should be at (1,0) (Internally (201,200))

if we start at

(0,0) (Internally (200,200)) go west, we should be at (0,-1) (Internally (200,199))

if we start at

(0,0) (Internally (200,200)) go east, we should be at (0,1) (Internally (200,201))


whichDirection, takes a string as input, parses and figures out if the information is incorrect, a direction, a place to jump to, or to quit.

grantMap, a function to hold all functions, I got tired of writing the same thing down over and over, so we take directions to create exits

probPlacement, used to determine if a pokemart/center should be placed in the map, used a random float, instead of random int to determine. 
