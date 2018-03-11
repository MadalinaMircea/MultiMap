#pragma once
#include <iostream>
using namespace std;

class TValue
{
	int x, y;

public:
	TValue();
	TValue(int f, int s);
	~TValue();

	int getX();
	int getY();

	bool operator==(TValue& t);
};