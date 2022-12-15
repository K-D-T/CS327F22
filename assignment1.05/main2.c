#include <ncurses.h>

int main(){
	int ch;
	initscr();
	raw();
	keypad(stdscr,TRUE);
	noecho();

	printw("Type to see bold\n");
	ch = getch();

	if(ch == KEY_F(1))
		printw("F1 key pressed");

	else{
		printw("The pressed key is ");
		attron(A_BOLD);
		printw("%c\n",ch);
		attroff(A_BOLD);
	}
	refresh();
	start_color();
	init_pair(1, COLOR_BLUE, COLOR_BLACK);
	attron(COLOR_PAIR(1));
	printw("HERE lIES WORDS\n");
	//attroff(COLOR_PAIR(1));
	printw(" And more words\n");
	ch = getch();
	init_color(COLOR_RED,360,250,200);
	init_color(COLOR_BLUE,203,596,858);
	init_color(COLOR_GREEN,98,435,240);
	init_pair(2,COLOR_RED, COLOR_BLUE);
	attron(COLOR_PAIR(2));
	printw("DID IT ADJUST\n");
	//init_color(COLOR_RED,700, 200, 1000);
	//attron(COLOR_PAIR(3));
	init_pair(3,COLOR_GREEN,COLOR_RED);
	attron(COLOR_PAIR(3));
	printw("Change red\n");
	init_pair(4,COLOR_GREEN,COLOR_BLUE);
	attron(COLOR_PAIR(4));
	printw("THESE ARE TREES\n");
	init_color(COLOR_MAGENTA,700,200,1000);
	init_pair(5,COLOR_MAGENTA,COLOR_RED);
	attron(COLOR_PAIR(5));
	printw("THE FIELDS ARE WHAT\n");
	init_color(COLOR_YELLOW,1000,976,200);
	init_pair(6,COLOR_YELLOW,COLOR_RED);
	attron(COLOR_PAIR(6));
	printw("ARE THERE FLOWERS\n");
	init_color(COLOR_CYAN,1000,200,600);
	init_pair(7,COLOR_CYAN,COLOR_BLACK);
	attron(COLOR_PAIR(7));
	printw("FARMS and stuff\n");
	ch = getch();
	//init_color(COLOR_WHITE,1000,318,0);
	//init_pair(8,COLOR_WHITE,COLOR_BLACK);
	//attron(COLOR_PAIR(8));
	printw("THE WORLD IS WHAT\n");
	//attroff(COLOR_PAIR(8));
	endwin();
	printf("Key name is: %s - %d\n", keyname(ch), ch);

	return 0;

}
