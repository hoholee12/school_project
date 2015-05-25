#include<iostream>
using namespace std;

class RectManager;

class Rect{
	int width, height;
public:
	Rect(int width, int height){
		this->width=width;this->height=height;
	}
	friend class RectManager;
};

class RectManager{
public:
	bool equals(Rect &a, Rect &b){
		if(a.width==b.width&&a.height==b.height) return true;
		else return false;
	}
};

int main(int argc, char **argv){
	Rect a(3,4), b(3,4);
	RectManager man;
	if(man.equals(a,b)) cout<<"equal"<<endl;
	else cout<<"not equal"<<endl;
	return 0;
}