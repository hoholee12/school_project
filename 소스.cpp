#include<iostream>
#include<string>


using namespace std;

class Point {
private:
	int xpos, ypos;
public:
	Point(int x, int y);
	Point();
	~Point();
};

Point::~Point() {
	printf("outside Point\n"); 
}

Point::Point(int x, int y) :xpos(x), ypos(y) {
	printf("inside Point\n");
}
Point::Point() :xpos(0), ypos(0) {
	printf("inside Point\n");
}

class Circle : public Point{
private:
	double radius;
	const double PI; //const�� ����̴�, �ʱ�ȭ �Ҷ� ���� �� �������־����. ����Ʈ �����ڰ� �ڵ� �����Ǹ� �� �����Ѵٴ� ������ ����.
public:
	Circle(double radius);
	Circle();
	Circle(Circle &n);

	~Circle();

	double getRadius();
	void setRadius(double n);

	double getArea();
	double getPerimeter();
};

Circle::~Circle() {
	printf("outside Circle\n");
}

Circle::Circle(double radius) :Circle::Point(), PI(3.14){
	printf("inside Circle\n");
	this->radius = radius; //this�� ������
}

Circle::Circle(): radius(0.0), Circle::Point(), PI(3.14){
	printf("inside Circle\n");
}

Circle::Circle(Circle &n) : radius(n.radius), PI(3.14){ //����������� ����
	printf("inside Circle\n");
}


double Circle::getRadius() {
	return radius;
}
void Circle::setRadius(double n) {
	radius = n;
}
double Circle::getArea() {
	return radius * radius * PI;
}
double Circle::getPerimeter() {
	return radius * 2 * PI;
}

Circle c2() {
	return 0;
}

void print(Circle &c) {
	cout << "radius:" << c.getRadius() << " area:" << c.getArea() << " perimeter:" << c.getPerimeter() << endl;
}

int main() {
	Circle c1; print(c1);
	Circle c2(); //����
	Circle c3(5.0); print(c3);
	Circle c4(c1); print(c4); //��������� ȣ��
	Circle c5 = Circle(5.0); print(c5); //��������� ȣ��
	return 0;
}