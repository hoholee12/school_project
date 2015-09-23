#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#ifdef _WIN32
#include<windows.h>
#endif

#define ROW 10
#define COL 10

#ifdef _WIN32
HWND hwnd;
HDC hdc;
#endif

void seed(){
	srand((unsigned)time(0));
}

typedef struct bug{
	int x;
	int y;
} bug;


int main(){
#ifdef _WIN32
	hwnd = GetForegroundWindow();
	hdc = GetWindowDC(hwnd);
#endif
	seed();
	int tile[ROW][COL] = { 0 };
	bug lonebug = { ROW / 2, COL / 2 };

	int back_y, back_x;
	for (int count = 1;; count++){
		back_y = lonebug.y;
		back_x = lonebug.x;
		switch (rand() % 8){
		case 0: lonebug.y--; break;
		case 1: lonebug.y--; lonebug.x++; break;
		case 2: lonebug.x++; break;
		case 3: lonebug.y++; lonebug.x++; break;
		case 4: lonebug.y++; break;
		case 5: lonebug.y++; lonebug.x--; break;
		case 6: lonebug.x--; break;
		case 7: lonebug.y--; lonebug.x--; break;
		}
		if (lonebug.x<0 || lonebug.x>COL - 1) lonebug.x = back_x;
		if (lonebug.y<0 || lonebug.y>ROW - 1) lonebug.y = back_y;
		tile[lonebug.y][lonebug.x]++;

		int empty = 0;
		for (int i = 0; i < ROW; i++){
			for (int j = 0; j < COL; j++){
#ifdef _WIN32
				if (tile[i][j]) Rectangle(hdc, j*30, i*30, j*30+20, i*30+20);
				else Ellipse(hdc, j * 30, i * 30, j * 30 + 20, i * 30 + 20);
#else
				if(tile[i][j]) printf("1 ");
				else printf("0 ");
#endif
				if (tile[i][j] == 0) empty++;
			}
			printf("\n");
		}
		if (empty == 0){
		//print info here
			printf("total move count: %d", count);
			break;
		}
		//Sleep(100); //100ms
		getchar();
		system("cls");
	}






	return 0;
}