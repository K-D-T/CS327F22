// these are reversed purposefully (y,x), will cause issues for me
#define X 21
#define Y 80

//struct to represent the four dours location
struct door{
	int doorX;
	int doorY;
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
};

//function to build the border around the map
void buildBorders(struct map* m);
//function to output the map
void print(struct map* m);
//create empty spaces in map
void initField(struct map* m);
//design each exit on the map
void createExit(struct map* m);

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
