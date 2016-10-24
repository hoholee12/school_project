/*20154078 ����ȣ
*
* ��ü���� �̷� ����
*/

#include<iostream>
#include<cstring> //memset
#include<cmath> //sqrt
#define pow(x) (x)*(x)

typedef struct {
	int x, y;
}dot; //��ǥ ����ü

class Shape {
private:
	dot side[4]; //�簢������ ����
	int radius;
	const double PI; //����� �����Ҷ� �� �ʱ�ȭ�� �Ǿ����

	//���⿡�� �����ϱ�(�ؿ� print�Լ��� ���ּ���)
	double resultArea;
	double resultCircum;

public:
	Shape();
	//������
	int getRadius();
	dot getSide(int n);
	double getPI();
	//������
	void setRadius(int r);
	void setSide(dot val, int n);
	//PI�� ���
	
	//��, �簢��
	double setCircum(int n);
	double setArea(int n);
	//��
	double setCircum();
	double setArea();

	double getCircum() {
		return resultCircum;
	}
	double getArea() {
		return resultArea;
	}
};

Shape::Shape():PI(3.14), radius(0) { //�ʱ�ȭ����Ʈ �̿�
	memset(side, 0, sizeof*side); //�迭�� �ʱ�ȭ����Ʈ �ȵ�
}
//������
int Shape::getRadius() {
	return radius;
}
double Shape::getPI() {
	return PI;
}
dot Shape::getSide(int n) {
	return side[n];
}
//������
void Shape::setRadius(int r) {
	radius = r;
}
void Shape::setSide(dot val, int n) {
	side[n] = val;
}

//��, �簢��
double Shape::setCircum(int n) { //��, �簢�� �ѷ� ���ϱ�
	int trigger = 0;
	double length = 0.0;
	for (int i = 0; i < n; i++) { //n���� ���� ���̸� ���ϸ鼭 length�� ����
		length += sqrt(pow(side[i % n].x - side[(i + 1) % n].x) + pow(side[i % n].y - side[(i + 1) % n].y)); //�ε����� n-1�� �Ѿ�� ó�� �ε����� ��Ÿ���Բ� %n ����
	}
	return resultCircum = length; //��ȯ ���ÿ� ����
}
double Shape::setArea(int n) { //�ﰢ���� ���̸� ���ϴ� ����, �簢���� n�������� �̿��� �������� �װ� ������ �ﰢ�� �ΰ��� ���� ��� ����.
	dot a = side[(0 + n) % 4];
	dot b = side[(1 + n) % 4];
	dot c = side[(2 + n) % 4];

	return resultArea = fabs(((a.x*b.y + b.x*c.y + c.x*a.y) - (a.x*c.y + c.x*b.y + b.x*a.y)) / 2); //���밪
}

//��
double Shape::setCircum() {
	return resultCircum = radius * 2 * PI; //��ȯ ���ÿ� ����
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
	//����ϴ� �޼ҵ� �ڵ� ȣ��
	setArea();
	setCircum();
}
void Triangle::set(dot *side) {
	for (int i = 0; i < 3; i++) {
		setSide(side[i], i);
	}
	//����ϴ� �޼ҵ� �ڵ� ȣ��
	setArea();
	setCircum();
}
double Triangle::setArea() {
	return Shape::setArea(0); //�Լ��̸��� ���Ƶ�, �θ�::�Լ��̸� �ڽ�::�Լ��̸� �̷��� ���� ��밡��
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
	//����ϴ� �޼ҵ� �ڵ� ȣ��
	setArea();
	setCircum();
}
void Rectangle::set(dot *side) {
	for (int i = 0; i < 4; i++) {
		setSide(side[i], i);
	}
	//����ϴ� �޼ҵ� �ڵ� ȣ��
	setArea();
	setCircum();
}

double Rectangle::setArea() {
	return Shape::setArea(0) + Shape::setArea(2); //0, 1, 2 ������ �ﰢ���� ���� + 2, 3, 0 ������ �ﰢ�� ����
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
	//����ϴ� �޼ҵ� �ڵ� ȣ��
	setArea();
	setCircum();
}
void Circle::set(int radius) {
	setRadius(radius);
	//����ϴ� �޼ҵ� �ڵ� ȣ��
	setArea();
	setCircum();
}

double Circle::setArea(){
	return Shape::setArea();
}
double Circle::setCircum(){
	return Shape::setCircum();
}

//����� ������ ���� double���̴�, �̷��� �ϸ� ���� �������� ������ �ʾƵ� ��
void print(char *str, Shape &obj) {
	using namespace std;
	cout << str<< "�� ����:" << obj.getArea() << " �ѷ�:" << obj.getCircum() << endl;
}

int main() {
	dot test[4] = { {1, 5}, {1, 1}, {4, 2}, {4, 5} };
	Triangle hello(test);
	print("�ﰢ��", hello);
	Rectangle hello2(test);
	print("�簢��", hello2);
	Circle hello3(5.0);
	print("��", hello3);

	return 0;
}