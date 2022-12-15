Assign 1.07
Started Whenever

KNOWN BUGS!! 

I'm having trouble locating a bug, it seems there is duplicate information being placed in the vectors, possibly during a resize, we can see when we print, that the values are being duplicated.. Looking to figure out what's happening

built class to hold data for pokemon, moves, pokemon_moves, pokemon_species, experience, type_names, pokemon_stats, stats, and pokemon_types

built functions 
csvParse where the file is checked to see if its valid
csvParseAux, then takes the valid file and opens it up, this handles the parsing of the file and the placement into a vector, creation of a vector, printing of the data in the vector, basically an all purpose function
isNumber, goes through the string to ensure its a number, so it can be conveted with stoi
print functions for all 9 files 

Can't move into maps going north if we haven't visited/flown to them, we can visit the north map, but the pc is not playable
maybe a memory leak, because I notice a piece of the map disappears. Will need more time on that...
In fact, going north seems to display some, unstable behavior. 


can't fly to parallel maps without a seg fault, which is odd, because going south is fine; north,west,east, can't understand this issue, will need more time

collision, I've got a big issue with trainers running into pc/other trainers and leaving "dead bodies"



Known GLitches_________

Because of the functioning of the QUEUE, sometimes we get unintended collision, because we check the location of next move and stuff the info into Queue, there can be 2 characters running into the same location, thus causing unintentional override of the map, need to figure out a fix.

There are random buffers where no action takes place, harder to track still working on finding the issue
