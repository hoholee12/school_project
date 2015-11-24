#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include<math.h>
#include<stdarg.h>
#define va_copy(dest, src) ((dest) = (src))

typedef struct _shape {
	double *x;
	double *y;
	size_t color;
	size_t endmark;
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

/*도형 집합체*/
#define endmark_def 1 /*use teh most practical number*/
/*카메라 효과: 스크린에 있는 도형 전체를 움직이기*/
void camera_xy(_shape *shape, double userx, double usery, double zoom, double rad); /*found a bug in the vc++ compiler*/
void free_arr(); /*도형 집합체 없애기*/
void copy_arr(); /*도형 집합체 복사*/
void select_arr(double userx, double usery, double zoom, double rad, const int count, ...); /*원하는 도형을 직접 고르기*/

/*low level*/
void drawline_alt(); /*print_xy()에서 선 그릴때 쓰는거; print_xy()에 이니셜 코드가 있으니, 그전에 쓰면 안된다!!*/
void copy_temp(); /*print_xy()에서 삼각형 채울때 쓰는거*/
void input_temp(); /*rotate_xy()에서 도형 만들때 쓰는거*/

#define urand(x) (2*x*(double)rand()/RAND_MAX-x)


void seed() {
	srand((unsigned)time(0));

}

/*나중에 버리고 opengl로 갈아탈 계획중*/
HWND hwnd;
HDC hdc;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define rotate_xy(x, y) rotate_xy((x), (double)(y) * M_PI / 180.0)
#define camera_xy(a, b, c, x, y) camera_xy((a), (b), (c), (x), (double)(y) * M_PI / 180.0)
#define select_arr(b, c, x, y, count, ...) select_arr((b), (c), (x), (double)(y) * M_PI / 180.0, (count), __VA_ARGS__)

/*main() 놀이터*/
int main() {
	int i;
	double j;
	_shape shape[3] = { { 0 } }; /*건드리지 않기, 리셋할때 씀*/
	_shape instance[3] = { { 0 } }; /*디스플레이 - 대신 이거 맘대로 건드리기*/


	seed();

	/*도형 만들기*/
	input_xy(&shape[0], 0, 0);
	input_xy(&shape[0], 200, 0);
	input_xy(&shape[0], 400, 200);
	input_xy(&shape[0], 0, 200);


	/*도형 복사하기: 복사 당할곳, 복사 할곳*/
	copy_xy(&shape[1], &shape[0]);
	copy_xy(&shape[2], &shape[1]);

	/*도형 위치 움직이기*/
	move_xy(&shape[0], 500, 500);
	move_xy(&shape[1], 1000, 500);
	move_xy(&shape[2], 1500, 500);


	/*기본값 색깔 지정: print_xy()에서 int color부분을 -1으로 지정하면 이 색깔을 씀*/
	shape[0].color = 0x0000ff;
	shape[1].color = 0x00ff00;
	shape[2].color = 0xff0000;


	/*인스턴스로 복사*/
	copy_arr(instance, shape);

	double fps = 1000;
	for (;;) {
		/*print_xy(&instance[0], -1, 1, 1); /*도형 출력하기: 출력할 도형, 색깔, 도형 채우기, 스크린 지우기*/
		for (i = 0, j = 1.01;; i++) {
			/*system("cls");*/


			/*컬러링: 0xB;G;R*/

			rotate_xy(&instance[0], 1); /*도형 돌리기: 돌릴 도형, 각도*/
			print_xy(&instance[0], -1, 1, 1); /*도형 출력하기: 출력할 도형, 색깔, 도형 채우기, 스크린 지우기*/
			rotate_xy(&instance[1], -1);
			print_xy(&instance[1], -1, 1, 0); /*여기서 스크린 지우면 안됨*/
			rotate_xy(&instance[2], 1); /*urand(): -359~360 사이 임의의 각도*/
			print_xy(&instance[2], -1, 1, 0);

			rotate_xy(&shape[0], 1);
			rotate_xy(&shape[1], -1);
			rotate_xy(&shape[2], 1);


			if (i > 60) {
				if (j == 1.01) j = 0.99;
				else j = 1.01;
				i = 0;
			}

			/*size_xy(&shape[0], j); /*여기서 j는 꼭 실수형이어야 한다*/
			/*size_xy(&shape[1], j);
			size_xy(&shape[2], j);*/

			select_arr(urand(50), urand(50), j, 1.0, 2, &shape[0], &shape[1]);
			//camera_xy(instance, urand(50), urand(50), j, 1.0); /*도형 집합체, 확대/축소중심 x축, y축, 배율, 돌리기*/



			/*for (i = 0; shape[0].x[i] != -1; i++) {
				printf("%lf %lf\n", shape[0].x[i], shape[0].y[i])
			}*/


			Sleep((DWORD)fps / 60); /*60fps*/
		}
		/*도형 집함체를 리셋 할때*/
		/*copy_arr(instance, shape);*/

	}

	/*건들지 마시오*/
	free_arr(instance);
	free_arr(shape);
	return 0;
}
#undef rotate_xy
#undef camera_xy
#undef select_arr

void free_xy(_shape *shape) {
	free(shape->x);
	free(shape->y);

}

void free_arr(_shape *temp) {
	int i;
	for (i = 0; temp[i].endmark == endmark_def; i++) free_xy(&temp[i]);
	free(temp);
}

void copy_arr(_shape *dest, _shape *source) {
	int i;
	for (i = 0; source[i].endmark == endmark_def; i++) copy_xy(&dest[i], &source[i]);
}

void camera_xy(_shape *shape, double userx, double usery, double zoom, double rad) {
	int i, j, k;
	_shape *temp = NULL;
	double x = 0, y = 0; /*center*/

	k = 0;
	for (i = 0; shape[i].endmark == endmark_def; i++) {
		for (j = 0; shape[i].x[j] != -1.0; j++, k++) {
			x += shape[i].x[j];
			y += shape[i].y[j];
		}
	}
	x /= (double)k;
	y /= (double)k;

	temp = calloc(i, sizeof*temp); /*0~2 == 3 blocks*/

	for (i = 0; shape[i].endmark == endmark_def; i++) {
		for (j = 0; shape[i].x[j] != -1.0; j++) {
			input_temp(&temp[i], shape[i].x[j], shape[i].y[j]);
		}
	}


	for (i = 0; shape[i].endmark == endmark_def; i++) {
		for (j = 0; shape[i].x[j] != -1.0; j++) {
			temp[i].x[j] -= x - userx;
			temp[i].y[j] -= y - usery;
		}
	}

	for (i = 0; shape[i].endmark == endmark_def; i++) {
		for (j = 0; shape[i].x[j] != -1.0; j++) {
			shape[i].x[j] = cos(rad)*temp[i].x[j] - sin(rad)*temp[i].y[j];
			shape[i].y[j] = sin(rad)*temp[i].x[j] + cos(rad)*temp[i].y[j];
		}
	}

	for (i = 0; shape[i].endmark == endmark_def; i++) {
		for (j = 0; shape[i].x[j] != -1.0; j++) {
			shape[i].x[j] *= zoom;
			shape[i].y[j] *= zoom;
		}
	}

	for (i = 0; shape[i].endmark == endmark_def; i++) {
		for (j = 0; shape[i].x[j] != -1.0; j++) {
			shape[i].x[j] += x;
			shape[i].y[j] += y;
		}
	}
	free_arr(temp);
}

void select_arr(double userx, double usery, double zoom, double rad, const int count, ...) {
	va_list va[6] = { {0} };
	int i, j, k;
	double x = 0, y = 0;
	_shape *temp = NULL;
	_shape *vatemp = NULL;
	va_start(va[0], count);
	for (i = 0; i < 5; i++) va_copy(va[i+1], va[i]);

	k = 0;
	for (i = 0; i < count; i++) {
		vatemp = va_arg(va[0], _shape *);
		for (j = 0; vatemp->x[j] != -1.0; j++, k++) {
			x += vatemp->x[j];
			y += vatemp->y[j];
		}
	}
	x /= (double)k;
	y /= (double)k;
	va_end(va[0]);
	
	temp = calloc(i, sizeof*temp);

	for (i = 0; i < count; i++) {
		vatemp = va_arg(va[1], _shape *);
		for (j = 0; vatemp->x[j] != -1.0; j++) {
			input_temp(&temp[i], vatemp->x[j], vatemp->y[j]);
		}
	}
	va_end(va[1]);

	for (i = 0; i < count; i++) {
		vatemp = va_arg(va[2], _shape *);
		for (j = 0; vatemp->x[j] != -1.0; j++) {
			temp[i].x[j] -= x - userx;
			temp[i].y[j] -= y - usery;
		}
	}
	va_end(va[2]);

	for (i = 0; i < count; i++) {
		vatemp = va_arg(va[3], _shape *);
		for (j = 0; vatemp->x[j] != -1.0; j++) {
			vatemp->x[j] = cos(rad)*temp[i].x[j] - sin(rad)*temp[i].y[j];
			vatemp->y[j] = sin(rad)*temp[i].x[j] + cos(rad)*temp[i].y[j];
		}
	}
	va_end(va[3]);

	for (i = 0; i < count; i++) {
		vatemp = va_arg(va[4], _shape *);
		for (j = 0; vatemp->x[j] != -1.0; j++) {
			vatemp->x[j] *= zoom;
			vatemp->y[j] *= zoom;
		}
	}
	va_end(va[4]);

	for (i = 0; i < count; i++) {
		vatemp = va_arg(va[5], _shape *);
		for (j = 0; vatemp->x[j] != -1.0; j++) {
			vatemp->x[j] += x;
			vatemp->y[j] += y;
		}
	}
	va_end(va[5]);
	free_arr(temp);
}

/*memcpy is a shallow copy in this case*/
void copy_xy(_shape *dest, _shape *source) {
	int i;
	dest->color = source->color;
	dest->endmark = source->endmark;

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
	shape->endmark = endmark_def;
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

	for (i = 0; temp.x[i] != -1.0; i++) {
		x += temp.x[i];
		y += temp.y[i];
	}
	x /= (double)i;
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
	free_xy(&temp);
}

void size_xy(_shape *shape, double multi) {
	int i;
	double x = 0, y = 0; /*center*/

	for (i = 0; shape->x[i] != -1.0; i++) {
		x += shape->x[i];
		y += shape->y[i];
	}
	x /= (double)i;
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


/*나중에 버리고 opengl로 갈아탈 계획중*/
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

void print_xy(_shape *shape, int color, size_t fill, size_t clear) {
	int i;
	int offset = 0;
	HBRUSH brush;
	POINT poly[3] = { 0 };
	if (!hwnd)
		hwnd = GetForegroundWindow();
	if (!hdc)
		hdc = GetWindowDC(hwnd);
	if (color == -1) color = shape->color;
	for (i = 0; shape->x[i + 1] != -1.0; i++) {
		drawline_alt((size_t)shape->x[i], (size_t)shape->y[i], (size_t)shape->x[i + 1], (size_t)shape->y[i + 1], color, clear);
		if (shape->x[i + 2] != -1.0)
			drawline_alt((size_t)shape->x[i], (size_t)shape->y[i], (size_t)shape->x[i + 2], (size_t)shape->y[i + 2], color, 0); /*hax*/
		if (clear) clear -= 1;
	}
	drawline_alt((size_t)shape->x[i], (size_t)shape->y[i], (size_t)shape->x[0], (size_t)shape->y[0], color, 0);
	if (!fill) return;
	brush = CreateSolidBrush(color);
	SelectObject(hdc, brush);
	do {
		copy_temp(poly, shape, &offset);
		Polygon(hdc, poly, 3);
	} while (offset);
	DeleteObject(brush);
}


void drawline_alt(size_t x, size_t y, size_t dest_x, size_t dest_y, size_t color, size_t clear) {
	HPEN pen;
	HBRUSH brush;
	if (clear) {
		brush = CreateSolidBrush(0xffffff);
		SelectObject(hdc, brush);
		Rectangle(hdc, 0, 0, GetSystemMetrics(SM_CXSCREEN) * 2, GetSystemMetrics(SM_CYSCREEN) * 2);
		DeleteObject(brush);
	}
	pen = CreatePen(PS_SOLID, 1, color);
	SelectObject(hdc, pen);
	MoveToEx(hdc, x, y, 0);
	LineTo(hdc, dest_x, dest_y);
	DeleteObject(pen);
}
