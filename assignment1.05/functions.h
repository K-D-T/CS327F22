// these are reversed purposefully (y,x), will cause issues for me
#define X 21
#define Y 80

//struct to represent the four dours location
struct door{
	int doorX;
	int doorY;
};

//used to showcase PC
struct character{
	int x;
	int y;
	char piece;
};

//build a priority Q
struct Node{
	int x;
	int y;
	int visited;
	int dist; // <-priority 
	struct Node* next;
};

struct Element{
	char c;// value
	int time;// value to decrease every deque
	int n;// where it's located in trainer array
	int t_cost;//terrain cost
	int f_x; // from location x
	int f_y; /// from location y
	int t_x; // new location x
	int t_y; // new location y
	char p; // former char found in trainertemp[n]
	struct Element* next;
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
	int hikerCost[X][Y];
	int rivalCost[X][Y];
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
	struct character pc;
	struct character trainers[13];
	char trainerTemp[13];
	int trainerCount;
	int trainerDirection[13];
	int trainerStatus[13];
	struct Element* pq;
	char tempPC;

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
//function to place pc randomly on a road, only used at the start
void placePC(struct map* m);
//function to find distances to hiker/rival// s = 0 hiker, s = 1 rival
//different values so it helps keep track
void dijkstra(struct map* m, int src_x, int src_y, int s);
//function to create node
struct Node* create(int x, int y, int dist);
//function to push node into Q
void push(struct Node** head, int x, int y, int dist);
//function to grab node, and remove it from Q
struct Node* pop(struct Node** head);
//function to check if Q is empty
int isEmpty(struct Node** node);
//find the location in Q, upgrade values and leave
void distUpgrade(struct Node** head, int x, int y, int dist);
//Find the value based on what is there
int distCalc(struct map* m, int x, int y, int s);
//utility function for 3 part mergesort
void mergesort(struct Node** head);
//utility function for merge sort
void frontBackSplit(struct Node* src, struct Node** fRef, struct Node** bRef);
//function to move nodes around;
struct Node* sortedMerge(struct Node* a, struct Node* b);
//function to move PC to new position
void movePC(struct map* m);
//function to display a 1 if the move can be completed, 0 if not.
int validPCMove(struct map*m, int x, int y);
//function to move PC and replace tile with previous char
char pcMovement(struct map* m, int x, int y, char p);
//function to build trainers from given input
void createTrainers(struct map* m, int n);
//function to randomly place the trainers
void placeTrainers(struct map* m, char c, int n);
//function to move each type of trainer
void moveTrainers(struct map* m, char c, int n);
//function to move the trainer and grab the char of previous location
void trainerMovement(struct map* m, int x, int y, int f_x, int f_y, int n, char p);
//function to check for objects 0 means shouldn't move there
int freeLoc(struct map* m, int x, int y);
//function to check direction for dijkstra moving chars; return the direction
void rivalCaught(struct map* m, int n);
//function to create a new Queue for list of moves
struct Element* eCreate(int n, char c, int f_x, int f_y, int x, int y, char p, int t_cost, int time);
//function to push new element into Queue
void ePush(struct Element** head, int n, char c, int f_x, int f_y, int x, int y, char p, int t_cost, int time);
//pop an element from Queue
struct Element* ePop(struct Element** head);
//checks if Element Queue is empty
int isEEmpty(struct Element** e);
//goes through and remove time from dist
void decreaseTime(struct Element** head, int sub);
//sorted the element Queue
struct Element* eSortedMerge(struct Element* a, struct Element* b);
//aux for merged sort
void eFrontBackSplit(struct Element* src, struct Element** fRef, struct Element** bRef);
//mergesort for element queue
void eMergeSort(struct Element** head);
//calculates the distance based on location we're moving to
int distMove(struct map* m, int x, int y, char c);
//figures out who goes next
void turnControl(struct map* m);
//the input for our characters
void pcControl(struct map* m);
//provide a map of the trainers
void displayTrainers(struct map* m);
//aux function to display distance from pc
char* trainerCalc(struct map* m, int n);
//return 1 if in pokecenter/pokemart
int inStore(struct map* m);
//function that puts up a placeholder, when inside mart/center
void displayStore(struct map* m);
//return 1, if we should launch for battle, 0 of not
int battle(struct map* m, int x, int y);
//display a battle interface placeholder
void displayBattle(struct map* m);
//function if a battle should be started, if 1 true, 0 if already defeated
int npcInitBattle(struct map* m, int n, int x, int y);
