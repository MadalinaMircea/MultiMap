#include "TValue.h"

TValue::TValue() : x(0), y(0) {}
TValue::TValue(int f, int s) : x(f), y(s) {}
TValue::~TValue() {}

int TValue::getX()
{
	return this->x;
}

int TValue::getY()
{
	return this->y;
}

bool TValue::operator==(TValue& t)
{
	if (this->x == t.x && this->y == t.y)
		return true;
	return false;
}