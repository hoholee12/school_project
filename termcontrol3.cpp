#include<ncurses.h>
#include<string.h>

//rows==lines==y==row
//columns==x==col

int main(){
	char mesg[]="just a string";
	int row, col;

	initscr(); //enable stdscr mode ie clear everything

	getmaxyx(stdscr, row, col); //get the number of rows and columns
	mvprintw(row/2, (col-strlen(mesg))/2, "%s", mesg);

	mvprintw(row-2, 0, "this screen has %d rows and %d cols\n", row, col);

	move(row/2, col-strlen(mesg));
	refresh();
	getch();
	endwin(); //close stdscr mode bullshit happen on terminal if not called!

	return 0;
}
