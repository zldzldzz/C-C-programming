#include <iostream>
#include <string> 
using namespace std;

class Rectangle
	{
	public:
	int width;
	int height;
	double getArea(/* args */);
	};
	double Rectangle::getArea(){
		return width*height;
	}

int main() {

	Rectangle rect;
	rect.width = 3;
	rect.height = 5;
	cout << "�簢���� ������ " << rect.getArea() << endl;
}

