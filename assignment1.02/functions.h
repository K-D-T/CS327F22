// these are reversed purposefully (y,x), will cause issues for me
#define X 21
#define Y 80

//struct to represent the four dours location
struct door{
	int doorX;
	int doorY;
};
//struct for location inside of 401 X 401 array of pointers
struct worldMapLoc{
	int mapX;
	int mapY;
};

//struct to represent various terrain information and pokemarts/centers
struct pokeloci{
	int x_loc;
	int y_loc;
	int width;
	int height;
};
//struct to represent map, various locations around the map
struct map{
	char field[X][Y];
	int density[X][Y];
	struct door north;
	struct door east;
	struct door south;
	struct door west;
	struct pokeloci pokemart;
	struct pokeloci pokecenter;
	struct pokeloci longGrass[10];
	struct pokeloci clearings[5];
	int longGrassPatches;
	int clearingCount;
	int boulderTree;
	struct worldMapLoc w;
	struct map* northMap;
	struct map* eastMap;
	struct map* southMap;
	struct map* westMap;

};

struct worldMap{
	struct map* wm[401][401];
};

//function to build the border around the map
void buildBorders(struct map* m);
//function to output the map
void print(struct map* m);
//create empty spaces in map
void initField(struct map* m);
//design each exit on the map
void createExit(struct map* m, int north, int east, int south, int west);

// second variable works as a switch and changes what's output, if s = 0 then it's a center
// if s = 1 then it's a mart
void buildPokeStructs(struct map* m, int s);

//0 if not valid, they're running into items, 1 if valid
int validateLocation(struct map* m, int x, int y, int s);
//create long grass on map
void buildLongGrass(struct map* m);

//return 1 if there is enough space, return 0 if there is not
int isThereSpace(struct map* m, int s, int c);
//another function to check if there's enough space
int isEnoughSpace(struct map* m, int s, int c);
//design the clearings
void buildClearings(struct map* m);
//build additional terrain
void buildTerrain(struct map* m);

//Function to build paths, S represents a switch that lets us know if we are looking for north/south or west/east
void generatePaths(struct map* m,struct door src, struct door dest, int s);
//function to connect p
void additionalPaths(struct map* m, struct pokeloci p);
//function to create a 400 x 400 array of pointers that can access the map
void generateWorldMap(struct worldMap* m, struct map* sm);
//function used to shift to a specific map, by taking a direction
void moveMap(struct worldMap* m, struct map* curr, struct map* next, char dir);
// function takes an x,y location to jump to specific map
void jumpToMap(struct worldMap* m, int x, int y);
//function with that takes user input and determines what's next
void play(struct worldMap* m, struct map* map);
//parse a string to see if it's valid input
int whichDirection(char buffer[]);
//function to hold functions to generate new maps, its tiresome rewriting it all over
void grantMap(struct worldMap* wm, struct map* m, int n, int s, int e, int w);
//function to determine if pokemart/pokecenter should be generated
int probPlacement(struct map* m);
