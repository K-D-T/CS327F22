$HOME/.poke327/pokedex
/share/cs327/pokedex

strcat(getenv(HOME), "/.poke327/pokedex....");

string base = getenv(HOME) + "/.poke327/...";

string file = base + "pokedex/data/csv/pokemon_types.csv";

ifstream f(file);

file = base + "pokedex/data/csv/pokemon.csv";

f.open(file);

/share/cs327/pokedex

