#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include<math.h>



typedef struct _shape {
	double *x;
	double *y;
} _shape;

/*사용할 것들*/
void input_xy(); /*도형 만들기*/
void move_xy(); /*도형 움직이기*/
void rotate_xy(); /*도형 회전하기*/
void size_xy(); /*도형 사이즈 변경하기*/
void print_xy(); /*도형 출력하기*/
void free_xy(); /*프로그램 끝나면 이거 꼭 써야함*/
void copy_xy(); /*도형 복사하기*/
void reset_xy(); /*도형을 원래 자리로*/
void camera_xy(_shape *shape, double userx, double usery, double zoom); /*bug in the vc++ compiler*/

				 /*쓰면 안되는 것들*/
void drawline_alt(); /*print_xy()에서 선 그릴때 쓰는거*/
void copy_temp(); /*print_xy()에서 삼각형 채울때 쓰는거*/
void input_temp(); /*rotate_xy()에서 도형 만들때 쓰는거*/


#define urand(x) (rand()%(2*(x)+1)-(x))

void seed() {
	srand((unsigned)time(0));

}

HWND hwnd;
HDC hdc;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define rotate_xy(x, y) rotate_xy((x), (double)(y) * M_PI / 180.0)

int main() {
	int i;
	double j;
	_shape shape[4] = { { 0 } };
	_shape instance[3] = { { 0 } }; /*나중에 쓸거임*/


	seed();

	/*도형 만들기*/
	input_xy(&shape[0], 0, 0);
	input_xy(&shape[0], 200, 0);
	input_xy(&shape[0], 400, 200);
	input_xy(&shape[0], 0, 200);


	/*도형 복사하기: 복사 당할곳, 복사 할곳*/
	copy_xy(&shape[1], &shape[0]);
	copy_xy(&shape[2], &shape[1]);

	copy_xy(&shape[3], &shape[2]);
	shape[3].x[0] = -1.0;

	/*도형 위치 움직이기*/
	move_xy(&shape[0], 500, 500);
	move_xy(&shape[1], 1000, 500);
	move_xy(&shape[2], 1500, 500);

	

	double fps = 1000;
	for (i = 0, j = 1.005;; i++) {
		/*system("cls");*/


		/*컬러링: 0xB;G;R*/

		rotate_xy(&shape[0], 1); /*도형 돌리기: 돌릴 도형, 각도*/
		print_xy(&shape[0], 0x0000ff, 1, 1); /*도형 출력하기: 출력할 도형, 색깔, 도형 채우기, 스크린 지우기*/
		rotate_xy(&shape[1], -1);
		print_xy(&shape[1], 0x00ff00, 1, 0); /*여기서 스크린 지우면 안됨*/
		rotate_xy(&shape[2], 1); /*urand(): -359~360 사이 임의의 각도*/
		print_xy(&shape[2], 0xff0000, 1, 0);

		if (i > 60) {
			if (j == 1.005) j = 0.995;
			else j = 1.005;
			i = 0;
		}

		//size_xy(&shape[0], j); /*여기서 j는 꼭 실수형이어야 한다*/
		//size_xy(&shape[1], j);
		//size_xy(&shape[2], j);

		camera_xy(shape, urand(50), urand(50), j);
		/*for (i = 0; shape[0].x[i] != -1; i++) {
		printf("%lf %lf\n", shape[0].x[i], shape[0].y[i]);
		}*/


		Sleep((DWORD)fps / 60); /*60fps*/
	}

	/*건들지 마시오*/
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
		shape->x[0] = (double)x;
		shape->y[0] = (double)y;
		shape->x[1] = -1.0;
		shape->y[1] = -1.0;
		return;

	}
	for (i = 0; shape->x[i] != -1; i++); /*x length = y length*/
	shape->x = realloc(shape->x, (i + 2)*sizeof*shape->x);
	shape->y = realloc(shape->y, (i + 2)*sizeof*shape->y);
	shape->x[i] = (double)x;
	shape->y[i] = (double)y;
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

void copy_temp(POINT *poly, _shape *shape, int *offset) {
	int i, j = 0;
	for (i = 0 + *offset; shape->x[i] != -1.0; i++, j++) {
		if (j > 2) {
			*offset = --i;
			return;
		}
		poly[j].x = (LONG)shape->x[i];
		poly[j].y = (LONG)shape->y[i];
	}
	if (j < 3) {
		poly[j].x = (LONG)shape->x[0];
		poly[j].y = (LONG)shape->y[0];
	}
	*offset = 0;
}


void move_xy(_shape *shape, int tempx, int tempy) {
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
	_shape temp = { 0 };
	double x = 0, y = 0; /*center*/

	for (i = 0; shape->x[i] != -1.0; i++) {
		input_temp(&temp, shape->x[i], shape->y[i]);
	}

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
	for (i = 0; shape->x[i] != -1.0; i++) {
		shape->x[i] += x;
		shape->y[i] += y;
	}
}

void size_xy(_shape *shape, double multi) {
	int i;
	double x = 0, y = 0; /*center*/

	for (i = 0; shape->x[i + 1] != -1.0; i++) {
		x += shape->x[i];
		y += shape->y[i];
	}
	x += shape->x[i];
	y += shape->y[i];
	x /= (double)++i;
	y /= (double)i;

	for (i = 0; shape->x[i] != -1.0; i++) {
		shape->x[i] -= x;
		shape->y[i] -= y;
	}

	/*multiply*/
	for (i = 0; shape->x[i] != -1.0; i++) {
		shape->x[i] *= multi;
		shape->y[i] *= multi;
	}

	/*add back*/
	for (i = 0; shape->x[i] != -1.0; i++) {
		shape->x[i] += x;
		shape->y[i] += y;
	}
}

void camera_xy(_shape *shape, double userx, double usery, double zoom) {
	int i, j, k;
	double x = 0, y = 0; /*center*/
	k = 0;
	for (i = 0; shape[i].x[0] != -1.0; i++) {
		for (j = 0; shape[i].x[j] != -1.0; j++, k++) {
			x += shape[i].x[j];
			y += shape[i].y[j];
		}
	}
	x /= (double)k;
	y /= (double)k;

	for (i = 0; shape[i].x[0] != -1.0; i++) {
		for (j = 0; shape[i].x[j] != -1.0; j++) {
			shape[i].x[j] -= x - userx;
			shape[i].y[j] -= y - usery;
		}
	}

	for (i = 0; shape[i].x[0] != -1.0; i++) {
		for (j = 0; shape[i].x[j] != -1.0; j++) {
			shape[i].x[j] *= zoom;
			shape[i].y[j] *= zoom;
		}
	}

	for (i = 0; shape[i].x[0] != -1.0; i++) {
		for (j = 0; shape[i].x[j] != -1.0; j++) {
			shape[i].x[j] += x;
			shape[i].y[j] += y;
		}
	}

}


void print_xy(_shape *shape, size_t color, size_t fill, size_t clear) {
	int i;
	int offset = 0;
	static HBRUSH brush;
	static size_t bcolor;
	POINT poly[3] = { 0 };
	if (!bcolor) bcolor = color;
	for (i = 0; shape->x[i + 1] != -1.0; i++) {
		drawline_alt((size_t)shape->x[i], (size_t)shape->y[i], (size_t)shape->x[i + 1], (size_t)shape->y[i + 1], color, clear);
		if (shape->x[i + 2] != -1.0)
			drawline_alt((size_t)shape->x[i], (size_t)shape->y[i], (size_t)shape->x[i + 2], (size_t)shape->y[i + 2], color, 0); /*hax*/
		if (clear) clear -= 1;
	}
	drawline_alt((size_t)shape->x[i], (size_t)shape->y[i], (size_t)shape->x[0], (size_t)shape->y[0], color, 0);
	if (!fill) return;
	if (bcolor != color) DeleteObject(brush);
	brush = CreateSolidBrush(color);
	SelectObject(hdc, brush);
	do {
		copy_temp(poly, shape, &offset);
		Polygon(hdc, poly, 3);
	} while (offset);

}


void drawline_alt(size_t x, size_t y, size_t dest_x, size_t dest_y, size_t color, size_t clear) {
	static HPEN pen;
	static HBRUSH brush;
	static size_t bcolor;
	if (!bcolor) bcolor = color;
	if (!hwnd)
		hwnd = GetForegroundWindow();
	if (!hdc)
		hdc = GetWindowDC(hwnd);

	if (clear) {
		if (!brush) brush = CreateSolidBrush(0xffffff);
		SelectObject(hdc, brush);
		Rectangle(hdc, 0, 0, GetSystemMetrics(SM_CXSCREEN) * 2, GetSystemMetrics(SM_CYSCREEN) * 2);
	}
	if (bcolor != color) DeleteObject(pen);
	pen = CreatePen(PS_SOLID, 1, color);
	SelectObject(hdc, pen);
	MoveToEx(hdc, x, y, 0);
	LineTo(hdc, dest_x, dest_y);
}
