Assign 1.01
Started 8/30/22

Struct for doors, represents an x, y location

struct for pokeloci, could be used for clearings, pokecenter, pokemart, and longgrass

struct for map, holds all data to ensure everything is accessible from a single location, doors, locations, char field itself, number of clearings, long grass, and a boulder-tree ratio

buildBorders function- creates the outside border of '%' from given struct.

print function - outputs the char map from given struct.

initField - set given char array to  empty spaces  - ' '.

createExit - randomly generates x,y to place '#' in given char array

buildPokeStructs - creates either pokemart, or pokecenter based on switch

validateLocation - checks to see if there is enough room for either pokemart or pokecenter based on struct

buildLongGrass - creates fields of long grass based on the input of given struct

isThereSpace - return 1 if there's enough space to place pokeloci

isEnoughSpace - redundant function that returns 1 if there's enough space to place pokeloci

buildClearings - place the clearings if there is space.

buildTerrain - finish placing items on the map, randomly generated as a ratio of trees to boulders.

generatePaths - generates paths to north/south exits & west/east exits, a switch designates direction 1, being N/S, 0 being W/E

additionalPaths - generates paths to pokeloci, starts in upper left space of pokeloci
