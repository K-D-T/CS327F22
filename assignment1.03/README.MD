Assign 1.03
Started 9/14/22

Program runs on main.c, functions.c, and functions.h
Mostly the same information from README.MD 1.02, but there were some upgrades.


Important!! Sometimes there are clearings/longGrass that can't be accessed by roads, because of this there are sometimes fields of zero. 

I also choose to set my "Infinite" to 100,000,000, because of weird behavior with INT_MAX, it was causing the number to roll over(what happens with INT_MAX and addition) to negative.

placepc function used to pop the pc randomly on a path, only for the first run of the game.

dijkstra function, function to calculate distance for walkable paths, if it's connected to a path we  can get to it. Sometimes they're aren't fields that are connected, because everything is randomly generated.

Node create, builds a new node for Queue

push, puts node on the front of the list.

pop, removes from element from the linked list

isEmpty checks to see if linked list is empty

distUpgrade traverses the linked list and changes the dist

distCalc, utility function to find out new distance based on the char present.

mergeSort function to sort the linked list

frontBackSplit function to split 2 parts of the list

sortedMerge, push 2 pieces of list back together.
