#pragma once
#include "TValue.h"
#include <iostream>
using namespace std;

class TElement
{
	int key;
	TValue* values;
	int cap, len;

public:

	TElement();
	TElement(int& k, TValue& e);

	~TElement();

	int getKey();
	TValue* getAllValues();
	void add(TValue& e);
	void remove(int p);
	int getSize();
};