#include<iostream>
using namespace std;

#include"Xml.h"
using namespace yazi::xml;

int main()
{
	Xml root;
	root.load("./test.xml");

	cout << root.str() << endl;

	system("pause");
	return 0;
}