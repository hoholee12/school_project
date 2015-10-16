#include<windows.h>
#include<stdio.h>
#include<math.h>

HWND hwnd;
HDC hdc;

void clear_screen() {
	Rectangle(hdc, 0, 0, 1000, 1000);


}

void car1(int dist){ //트럭
	//dist 는 x이다
	int y = 100;
	Rectangle(hdc, dist+70, y, dist + 100, y+50);
	Rectangle(hdc, dist + 73, y+3, dist + 97, y + 22);
	Rectangle(hdc, dist-40, y+25, dist + 70, y+50);

	Ellipse(hdc, dist+5, y+40, dist + 30, y+65);
	Ellipse(hdc, dist-20, y + 40, dist + 5, y + 65);
	Ellipse(hdc, dist + 75, y+40, dist + 100, y+65);
}

void car2(int dist) { //승용차
	//dist 는 x이다
	int y = 200;
	Rectangle(hdc, dist + 15, y, dist + 70, y + 25);
	Rectangle(hdc, dist + 28, y+3, dist + 37, y + 22);
	Rectangle(hdc, dist + 40, y + 3, dist + 70, y + 22);
	Rectangle(hdc, dist, y + 25, dist + 100, y + 50);

	Ellipse(hdc, dist + 10, y + 40, dist + 35, y + 65);
	Ellipse(hdc, dist + 75, y + 40, dist + 100, y + 65);
}

void print_car(int car_num, int dist) {
	switch (car_num) {
	case 1: car1(dist); break;
	case 2: car2(dist); break;
	}

}

void seed() {
	srand((unsigned)time(0));

}

int main() {
	int i, car1_dist = 0, car2_dist = 0;

	hwnd = GetForegroundWindow();
	hdc = GetWindowDC(hwnd);

	seed();

	for (i = 0; i < 20; i++) {
		clear_screen();
		car1_dist += rand() % 100;
		car2_dist += rand() % 100;
		print_car(1, car1_dist);
		print_car(2, car2_dist);
		getchar();
	}
	return 0;
}

