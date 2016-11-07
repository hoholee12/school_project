#include<iostream>
#include<vector>
using namespace std;

class Set{
	vector<int> hello;
public:
	Set();
	template<size_t n>Set(int (&b)[n]);

	Set operator+(Set &b);
	Set operator-(Set &b);
	Set operator|(Set &b);
	Set operator&(Set &b);
	bool operator==(Set &b);
	Set& operator<<(const int &b);
	void operator>>(int &b);
	int operator[](int &b);

	int size();
};
Set::Set(){

}
template<size_t n>
Set::Set(int (&b)[n]){
	for (int i = 0; i < n; i++){
		hello.push_back(b[i]);
	}
}

Set Set::operator+(Set &b){
	Set temp;
	temp.hello.insert(temp.hello.end(), this->hello.begin(), this->hello.end());
	temp.hello.insert(temp.hello.end(), b.hello.begin(), b.hello.end());
	return temp;
}
Set Set::operator-(Set &b){
	Set temp;
	for (vector<int>::iterator j = this->hello.begin(); j < this->hello.end(); j++){
		bool check = false;
		for (vector<int>::iterator i = b.hello.begin(); i < b.hello.end(); i++){
			if (*i == *j){
				check = true;
				break;
			}
		}
		if (!check){
			temp.hello.push_back(*j);
		}
	}
	return temp;
}

Set Set::operator|(Set &b){ //합집합
	Set temp;
	Set otherb = b; //vector는 깊은복사 안해도 된다
	for (vector<int>::iterator j = this->hello.begin(); j < this->hello.end(); j++){
		bool check = false;
		for (vector<int>::iterator i = otherb.hello.begin(); i < otherb.hello.end(); i++){
			if (*i == *j){
				otherb.hello.erase(i);
				break;
			}
		}
		temp.hello.push_back(*j);
	}
	for (vector<int>::iterator j = otherb.hello.begin(); j < otherb.hello.end(); j++){
		temp.hello.push_back(*j);
	}
	return temp;
}
Set Set::operator&(Set &b){ //교집합
	Set temp;
	for (vector<int>::iterator j = this->hello.begin(); j < this->hello.end(); j++){
		bool check = false;
		for (vector<int>::iterator i = b.hello.begin(); i < b.hello.end(); i++){
			if (*i == *j){
				temp.hello.push_back(*j);
			}
		}
	}
	return temp;
}
bool Set::operator==(Set &b){
	return (this->hello == b.hello) ? true : false;
}
Set& Set::operator<<(const int &b){
	this->hello.push_back(b);
	return *this;
}
void Set::operator>>(int &b){
	if (this->hello.size() == 0) return;
	b = this->hello.back();
	this->hello.pop_back();
}

int Set::operator[](int &b){
	return this->hello.at(b);
}

int Set::size(){
	return this->hello.size();
}

int main(){
	int a[] = { 1, 2, 3, 4 };
	Set test(a);
	for (int i = 0; i < test.size(); i++) //1234출력
		cout << test[i];
	cout << endl;
	Set test2;
	test2 << 2 << 3 << 4;
	for (int i = 0; i < test2.size(); i++) //234출력
		cout << test2[i];
	cout << endl;
	test << 1; //12341
	int t = 0;
	test = test2 + test; //23412341
	test >> t; //2341234 t=1
	for (int i = 0; i < test.size(); i++) //2341234 출력
		cout << test[i];
	cout << endl;
	cout << t << endl; //1 출력

	int b[] = { 4, 5, 6, 7 };
	Set test3(a);
	Set test4(b);
	test3 = test3 | test4;
	for (int i = 0; i < test3.size(); i++) //1234567 출력
		cout << test3[i];
	cout << endl;
	Set test5(a);
	test5 = test5 & test4;
	for (int i = 0; i < test5.size(); i++) //4 출력
		cout << test5[i];
	cout << endl;


	return 0;
}