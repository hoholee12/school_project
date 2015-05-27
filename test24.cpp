#include<iostream>
#include<string>
using namespace std;

class point{
private:
	int x,y;
public:
	void set(int x, int y){this->x=x;this->y=y;}
	void showpoint(){
		cout<<"("<<x<<","<<y<<")"<<endl;
	}
};

class colorpoint : public point{
private:
	string color;
public:
	void setcolor(string color){this->color=color;}
	void showcolorpoint(){
		cout<<color<<":";
		showpoint();
	}
	/*bool equals(colorpoint &p){
		if(x==p.x&&y==p.y&&color==p.color) return true;
		else return false;
	}*/
};

int main(int argc, char **argv){
	colorpoint cp;
	point *pbase=&cp; //limit to point class upcasting.
	pbase->set(3,4);
	pbase->showpoint();
	
	colorpoint *pder;
	pder=(colorpoint *)pbase; //get all my stuff back downcasting.
	pder->set(4,5);
	pder->setcolor("red");
	pder->showcolorpoint();
	
	return 0;
}