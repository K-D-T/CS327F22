Assign 1.09
Started Whenever

KNOWN BUGS!! 

Project can't be completed, after parsing the data, there are possible memory leaks that leads to seg faults, most functionality has to be turned off until I can track unknown issue causing game to crash on movement.


There is still unstable behavior with loading pokemon data, so no battles can actually be completed, mostly placeholders

we use 'A' or 'a' to bring up bag stats, as 'b' is used to move!

built class to hold data for pokemon, moves, pokemon_moves, pokemon_species, experience, type_names, pokemon_stats, stats, and pokemon_types
Can't move into maps going north if we haven't visited/flown to them, we can visit the north map, but the pc is not playable
maybe a memory leak, because I notice a piece of the map disappears. Will need more time on that...
In fact, going north seems to display some, unstable behavior. 


can't fly to parallel maps without a seg fault, which is odd, because going south is fine; north,west,east, can't understand this issue, will need more time

collision, I've got a big issue with trainers running into pc/other trainers and leaving "dead bodies"



Known GLitches_________

Because of the functioning of the QUEUE, sometimes we get unintended collision, because we check the location of next move and stuff the info into Queue, there can be 2 characters running into the same location, thus causing unintentional override of the map, need to figure out a fix.

There are random buffers where no action takes place, harder to track still working on finding the issue
