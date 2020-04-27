#include "header.h"

int main() {
	cout << "Singleton class implementation" << endl;

	int *x{ nullptr }, *y{ nullptr }, *z{ nullptr };

	cout << "x address after definition = " << x << endl
		<< "y address after definition = " << y << endl
		<< "z address after definition = " << z << endl;

	x = singletonClass<int>::getInstance();
	y = singletonClass<int>::getInstance();
	z = singletonClass<int>::getInstance();

	cout << "x address after singleton assigment = " << x << endl
		<< "y address after singleton assigment = " << y << endl
		<< "z address after singleton assigment = " << z << endl;

	return 0;
}