#include <stdio.h>
#include <ctype.h>


/* Right when you can, left when you must */
/* words is array of pointer to char */
char *words[] = {
  "Abrakadabra",
  "Blastoise",
  "Clefairy",
  "Dialga",
  "Eevee",
  "Flygon",
  "Graveler",
  "Ho-oh",
  "Igglybuff",
  "Jumpluff",
  "Kechlion",
  "Lugia",
  "Magnemite",
  "Nidoran",
  "Onyx",
  "Pikachu",
  "Quagsire",
  "Rapidash",
  "Squirtle",
  "Typhlosion",
  "Umbreon",
  "Venonat",
  "Wartortle",
  "Xernius",
  "Yveltal",
  "Zapdos",
};

int main(int argc, char *argv[])
{
  if (argc != 2) {
    fprintf(stderr, "Usage: char <letter>");

    return -1;
  }

  printf("%c is for %s\n", argv[1][0], words[tolower(argv[1][0]) - 'a']);

  return 0;

}
