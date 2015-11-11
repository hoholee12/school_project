#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

HWND hwnd;
HDC hdc;

typedef struct _test {
	size_t *x;
	size_t *y;
} _test;

void input_xy();
void print_xy();
void drawline();
void free_xy();


int main() {
	_test test[3] = { 0 };
	
	hwnd = GetForegroundWindow();
	hdc = GetWindowDC(hwnd);

	input_xy(&test[0], 500, 500);
	input_xy(&test[0], 1000, 1000);
	input_xy(&test[0], 1500, 1000);
	input_xy(&test[0], 1000, 500);
	print_xy(&test[0], 0x00bfff, 1);

	free_xy(&test[0]);
	return 0;
}


void free_xy(_test *test) {
	free(test->x);
	free(test->y);

}

void input_xy(_test *test, size_t x, size_t y) {
	int i;
	if (!test->x || !test->y) {
		test->x = malloc(2 * sizeof*test->x);
		test->y = malloc(2 * sizeof*test->y);
		test->x[0] = x;
		test->y[0] = y;
		test->x[1] = -1;
		test->y[1] = -1;
		return;

	}
	for (i = 0; test->x[i] != -1; i++); /*x length = y length*/
	test->x = realloc(test->x, (i + 2)*sizeof*test->x);
	test->y = realloc(test->y, (i + 2)*sizeof*test->y);
	test->x[i] = x;
	test->y[i] = y;
	test->x[++i] = -1;
	test->y[i] = -1;


}

void print_xy(_test *test, size_t color, size_t fill) {
	int i;
	for (i = 0; test->x[i + 1] != -1; i++) {
		drawline(test->x[i], test->y[i], test->x[i + 1], test->y[i + 1], color);
	}
	drawline(test->x[i], test->y[i], test->x[0], test->y[0], color);
	if (!fill) return;

}

void drawline(size_t x, size_t y, size_t dest_x, size_t dest_y, size_t color) {
	int i;
	int xlen = dest_x - x;
	int ylen = dest_y - y;
	float ixlen, iylen;
	int biglen;
	float ibiglen;
	float setx = 0, sety = 0;

	if (xlen < 0) {
		xlen *= -1;
		setx = dest_x;
	}
	else setx = x;
	if (ylen < 0) {
		ylen *= -1;
		sety = dest_y;
	}
	else sety = y;
	biglen = xlen;
	if (ylen > xlen) biglen = ylen;
	ibiglen = biglen;
	ixlen = xlen;
	iylen = ylen;
	for (i = 0; i < biglen; i++) {
		setx += ixlen / ibiglen;
		sety += iylen / ibiglen;
		SetPixel(hdc, (int)setx, (int)sety, color);
	}
}