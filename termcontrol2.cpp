#include<ncurses.h>

int main(){
	int ch;

	initscr(); //enable stdscr mode ie clear everything
	raw(); //line buffer disabled for instant access
	keypad(stdscr, 1); //we get all the shit in keyboard such as fkeys and arrows and shit
	noecho(); //dont echo while on getch();
	printw("Hello, World!\n"); //write this to buffer coordinates and shit
	//refresh(); //dump the buffer to stdscr ie print everything
	//getch(); //end user input if no raw() we have to press enter to refresh
	ch=getch();
	if(ch==KEY_F(1)) printw("F1 key pressed\n");
	else{
		printw("The pressed key is ");
		attron(A_BOLD);
		printw("%c", ch);
		attroff(A_BOLD);
	}
	refresh();
	getch();
	endwin(); //close stdscr mode bullshit happen on terminal if not called!

	return 0;
}
