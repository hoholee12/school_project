#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include<math.h>



typedef struct _shape {
	double *x;
	double *y;
} _shape;



void input_xy();
void move_xy();
void rotate_xy();
void print_xy();
void drawline();
void free_xy();
void copy_xy();
void reset_xy();
void drawline_alt();

#define urand(x) (rand()%(2*(x)+1)-(x))

void seed() {
	srand((unsigned)time(0));

}

void clearscreen(HWND *hwnd, HDC *hdc) {
	InvalidateRect(hwnd, NULL, FALSE);
}

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define rotate_xy(x, y) rotate_xy((x), (double)(y) * M_PI / 180.0)

int main() {
	int i;
	_shape shape[3] = { { 0 } };
	_shape instance = { 0 };
	

	seed();

	input_xy(&shape[0], 0, 0);
	input_xy(&shape[0], 500, 0);
	input_xy(&shape[0], 500, 500);
	input_xy(&shape[0], 0, 500);

	move_xy(&shape[0], 500, 500);
	/*rotate_xy(&shape[0], 360);
	print_xy(&shape[0], 0xffffff, 1);
	exit(0);*/
	for (;;) {
		rotate_xy(&shape[0], 1); /*test here*/
		print_xy(&shape[0], 0xffffff, 1, 1);
		/*for (i = 0; shape[0].x[i] != -1; i++) {
			printf("%g %g\n", shape[0].x[i], shape[0].y[i]);
		}*/
		Sleep(16); /*60fps*/
	}
	exit(0);

	copy_xy(&shape[1], &shape[0]);
	copy_xy(&shape[2], &shape[1]);

	move_xy(&shape[0], 700, 500);
	move_xy(&shape[1], 700, 500);
	move_xy(&shape[2], 700, 500);
	for (i = 0; i < 10000; i++) {
		print_xy(&shape[0], 0x00bfff, 1, 1);
		move_xy(&shape[0], urand(20), urand(20));
		print_xy(&shape[1], 0xffbfff, 1, 1);
		move_xy(&shape[1], urand(20), urand(20));
		print_xy(&shape[2], 0x00bf00, 1, 1);
		move_xy(&shape[2], urand(20), urand(20));
	}


	free_xy(&shape[0]);
	free_xy(&shape[1]);
	free_xy(&shape[2]);
	return 0;
}
#undef rotate_xy(x, y)

void free_xy(_shape *shape) {
	free(shape->x);
	free(shape->y);

}

/*memcpy is a shallow copy in this case*/
void copy_xy(_shape *dest, _shape *source) {
	int i;
	if (!dest->x || !dest->y) {
		dest->x = malloc(2 * sizeof*dest->x);
		dest->y = malloc(2 * sizeof*dest->y);
	}
	for (i = 0; source->x[i] != -1.0; i++);
	dest->x = realloc(dest->x, (i + 1)*sizeof*dest->x);
	dest->y = realloc(dest->y, (i + 1)*sizeof*dest->y);
	for (i = 0; source->x[i] != -1.0; i++) {
		dest->x[i] = source->x[i];
		dest->y[i] = source->y[i];
	}
	dest->x[i] = -1;
	dest->y[i] = -1;

}


void reset_xy(_shape *shape) {
	double smallest_x = shape->x[0], smallest_y = shape->y[0];
	int i;
	for (i = 1; shape->x[i] != -1.0; i++) {
		if (shape->x[i] < smallest_x) smallest_x = shape->x[i];
		if (shape->y[i] < smallest_y) smallest_y = shape->y[i];

	}
	for (i = 0; shape->x[i] != -1.0; i++) {
		shape->x[i] -= smallest_x;
		shape->y[i] -= smallest_y;
	}

}

void input_xy(_shape *shape, size_t x, size_t y) {
	int i;
	if (!shape->x || !shape->y) {
		shape->x = malloc(2 * sizeof*shape->x);
		shape->y = malloc(2 * sizeof*shape->y);
		shape->x[0] = x;
		shape->y[0] = y;
		shape->x[1] = -1.0;
		shape->y[1] = -1.0;
		return;

	}
	for (i = 0; shape->x[i] != -1; i++); /*x length = y length*/
	shape->x = realloc(shape->x, (i + 2)*sizeof*shape->x);
	shape->y = realloc(shape->y, (i + 2)*sizeof*shape->y);
	shape->x[i] = x;
	shape->y[i] = y;
	shape->x[++i] = -1.0;
	shape->y[i] = -1.0;


}

void input_temp(_shape *temp, double x, double y) {
	int i;
	if (!temp->x || !temp->y) {
		temp->x = malloc(2 * sizeof*temp->x);
		temp->y = malloc(2 * sizeof*temp->y);
		temp->x[0] = x;
		temp->y[0] = y;
		temp->x[1] = -1.0;
		temp->y[1] = -1.0;
		return;

	}
	for (i = 0; temp->x[i] != -1.0; i++); /*x length = y length*/
	temp->x = realloc(temp->x, (i + 2)*sizeof*temp->x);
	temp->y = realloc(temp->y, (i + 2)*sizeof*temp->y);
	temp->x[i] = x;
	temp->y[i] = y;
	temp->x[++i] = -1.0;
	temp->y[i] = -1.0;


}

void move_xy(_shape *shape, size_t tempx, size_t tempy) {
	int i;
	double x = (double)tempx;
	double y = (double)tempy;
	for (i = 0; shape->x[i] != -1.0; i++) {
		shape->x[i] += x;
		shape->y[i] += y;
	}
}



void rotate_xy(_shape *shape, double rad) {
	int i;
	_shape temp = {0};
	for (i = 0; shape->x[i] != -1; i++) {
		input_temp(&temp, shape->x[i], shape->y[i]);
	}

	double x = 0, y = 0; /*center*/
	for (i = 0; temp.x[i + 1] != -1.0; i++) {
		x += temp.x[i];
		y += temp.y[i];
	}
	x += temp.x[i];
	y += temp.y[i];
	x /= (double)++i;
	y /= (double)i;

	for (i = 0; temp.x[i] != -1.0; i++) {
		temp.x[i] -= x;
		temp.y[i] -= y;
	}

	/*rotate*/
	for (i = 0; temp.x[i] != -1.0; i++) {
		shape->x[i] = cos(rad)*temp.x[i] - sin(rad)*temp.y[i];
		shape->y[i] = sin(rad)*temp.x[i] + cos(rad)*temp.y[i];
	}

	/*add back*/
	for (i = 0; shape->x[i] != -1; i++) {
		shape->x[i] += x;
		shape->y[i] += y;
	}
}

void print_xy(_shape *shape, size_t color, size_t fill, size_t clear) {
	int i;
	for (i = 0; shape->x[i + 1] != -1.0; i++) {
		drawline_alt((size_t)shape->x[i], (size_t)shape->y[i], (size_t)shape->x[i + 1], (size_t)shape->y[i + 1], color, clear);
		if (clear) clear -= 1;
	}
	drawline_alt((size_t)shape->x[i], (size_t)shape->y[i], (size_t)shape->x[0], (size_t)shape->y[0], color, clear);
	if (!fill) return;

}

/*this needs to be fixed!!*/
void drawline(size_t x, size_t y, size_t dest_x, size_t dest_y, size_t color) {
	HWND hwnd;
	HDC hdc;

	int i;
	int xlen = dest_x - x;
	int ylen = dest_y - y;
	double ixlen, iylen;
	int biglen;
	double ibiglen;
	double setx = 0, sety = 0;
	hwnd = GetForegroundWindow();
	hdc = GetWindowDC(hwnd);

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

void drawline_alt(size_t x, size_t y, size_t dest_x, size_t dest_y, size_t color, size_t clear) {
	HWND hwnd;
	HDC hdc;
	PAINTSTRUCT ps;
	HPEN pen;
	HPEN oldpen;
	hwnd = GetForegroundWindow();
	hdc = GetWindowDC(hwnd);
	if (clear) clearscreen(&hwnd, &hdc);
	pen = CreatePen(PS_SOLID, 1, color);
	oldpen = SelectObject(hdc, pen);
	MoveToEx(hdc, x, y, 0);
	LineTo(hdc, dest_x, dest_y);
	SelectObject(hdc, oldpen);
	DeleteObject(pen);
	EndPaint(hwnd, &ps);
}