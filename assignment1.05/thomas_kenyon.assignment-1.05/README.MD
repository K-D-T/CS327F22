Assign 1.05
Started 10/10/22

displayTrainers, builds and shows the list of trainers, escape to close list

trainerCalc, builds a char * to display string of trainer

inStore, returns 1 if in store to activate interface

displayStore- placeholder interface for store, gt or lt sign to exit, i forget which one

battle- let's us know if battle takes place or the trainer has been defeated

displayBattle - interface to show battle, escape to exit

initBattle - lets us know if a battle should be started, this is if a npc touches PC

print, need a massive overhaul to color map

turnControl - minor tweaking to add in PcControl

Known GLitches_________

Because of the functioning of the QUEUE, sometimes we get unintended collision, because we check the location of next move and stuff the info into Queue, there can be 2 characters running into the same location, thus causing unintentional override of the map, need to figure out a fix.

There are random buffers where no action takes place, harder to track still working on finding the issue
