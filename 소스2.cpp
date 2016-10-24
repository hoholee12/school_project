/*20154078 이정호
*
* 객체지향 이론 과제
*/

#include<iostream>
#include<cstring> //memset
#include<cmath> //sqrt
#define pow(x) (x)*(x)

typedef struct {
	int x, y;
}dot; //좌표 구조체

class Shape {
private:
	dot side[4]; //사각형까지 가능
	int radius;
	const double PI; //상수는 생성할때 꼭 초기화가 되어야함

	//여기에도 저장하기(밑에 print함수를 봐주세요)
	double resultArea;
	double resultCircum;

public:
	Shape();
	//접근자
	int getRadius();
	dot getSide(int n);
	double getPI();
	//설정자
	void setRadius(int r);
	void setSide(dot val, int n);
	//PI는 상수
	
	//삼, 사각형
	double setCircum(int n);
	double setArea(int n);
	//원
	double setCircum();
	double setArea();

	double getCircum() {
		return resultCircum;
	}
	double getArea() {
		return resultArea;
	}
};

Shape::Shape():PI(3.14), radius(0) { //초기화리스트 이용
	memset(side, 0, sizeof*side); //배열은 초기화리스트 안됨
}
//접근자
int Shape::getRadius() {
	return radius;
}
double Shape::getPI() {
	return PI;
}
dot Shape::getSide(int n) {
	return side[n];
}
//설정자
void Shape::setRadius(int r) {
	radius = r;
}
void Shape::setSide(dot val, int n) {
	side[n] = val;
}

//삼, 사각형
double Shape::setCircum(int n) { //삼, 사각형 둘레 구하기
	int trigger = 0;
	double length = 0.0;
	for (int i = 0; i < n; i++) { //n개의 변의 길이를 구하면서 length에 더함
		length += sqrt(pow(side[i % n].x - side[(i + 1) % n].x) + pow(side[i % n].y - side[(i + 1) % n].y)); //인덱스가 n-1을 넘어가면 처음 인덱스를 나타내게끔 %n 해줌
	}
	return resultCircum = length; //반환 동시에 저장
}
double Shape::setArea(int n) { //삼각형의 넓이를 구하는 공식, 사각형은 n오프셋을 이용해 꼭지점이 네개 있을때 삼각형 두개로 따로 묶어서 구함.
	dot a = side[(0 + n) % 4];
	dot b = side[(1 + n) % 4];
	dot c = side[(2 + n) % 4];

	return resultArea = fabs(((a.x*b.y + b.x*c.y + c.x*a.y) - (a.x*c.y + c.x*b.y + b.x*a.y)) / 2); //절대값
}

//원
double Shape::setCircum() {
	return resultCircum = radius * 2 * PI; //반환 동시에 저장
}
double Shape::setArea() {
	return resultArea = pow(radius) * PI;
}

class Triangle :public Shape{
public:
	Triangle(dot *side);
	void set(dot *side);
	double setArea();
	double setCircum();
};
Triangle::Triangle(dot *side) {
	for (int i = 0; i < 3; i++) {
		setSide(side[i], i);
	}
	//계산하는 메소드 자동 호출
	setArea();
	setCircum();
}
void Triangle::set(dot *side) {
	for (int i = 0; i < 3; i++) {
		setSide(side[i], i);
	}
	//계산하는 메소드 자동 호출
	setArea();
	setCircum();
}
double Triangle::setArea() {
	return Shape::setArea(0); //함수이름이 같아도, 부모::함수이름 자식::함수이름 이렇게 따로 사용가능
}
double Triangle::setCircum() {
	return Shape::setCircum(3);
}


class Rectangle : public Shape {
public:
	Rectangle(dot *side);
	void set(dot *side);
	double setArea();
	double setCircum();
};
Rectangle::Rectangle(dot *side) {
	for (int i = 0; i < 4; i++) {
		setSide(side[i], i);
	}
	//계산하는 메소드 자동 호출
	setArea();
	setCircum();
}
void Rectangle::set(dot *side) {
	for (int i = 0; i < 4; i++) {
		setSide(side[i], i);
	}
	//계산하는 메소드 자동 호출
	setArea();
	setCircum();
}

double Rectangle::setArea() {
	return Shape::setArea(0) + Shape::setArea(2); //0, 1, 2 꼭지점 삼각형의 넓이 + 2, 3, 0 꼭지점 삼각형 넓이
}
double Rectangle::setCircum() {
	return Shape::setCircum(4);
}


class Circle : public Shape {
public:
	Circle(int radius);
	void set(int radius);
	double setArea();
	double setCircum();
};
Circle::Circle(int radius) {
	setRadius(radius);
	//계산하는 메소드 자동 호출
	setArea();
	setCircum();
}
void Circle::set(int radius) {
	setRadius(radius);
	//계산하는 메소드 자동 호출
	setArea();
	setCircum();
}

double Circle::setArea(){
	return Shape::setArea();
}
double Circle::setCircum(){
	return Shape::setCircum();
}

//출력할 내용은 같은 double형이니, 이렇게 하면 각각 도형마다 만들지 않아도 됨
void print(char *str, Shape &obj) {
	using namespace std;
	cout << str<< "의 넓이:" << obj.getArea() << " 둘레:" << obj.getCircum() << endl;
}

int main() {
	dot test[4] = { {1, 5}, {1, 1}, {4, 2}, {4, 5} };
	Triangle hello(test);
	print("삼각형", hello);
	Rectangle hello2(test);
	print("사각형", hello2);
	Circle hello3(5.0);
	print("원", hello3);

	return 0;
}