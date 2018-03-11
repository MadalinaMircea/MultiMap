#include "TElement.h"

TElement::TElement() : cap(0), len(0), key(0)
{
	this->values = new TValue[cap];
}

TElement::TElement(int& k, TValue& e) : cap(10), len(0), key(k)
{
	this->values = new TValue[cap];
	this->add(e);
}

TElement::~TElement() {}


void TElement::add(TValue& e)
{
	if (this->len == this->cap)
		return;

	this->values[this->len] = e;
	this->len = this->len + 1;
}

void TElement::remove(int p)
{
	for (int i = p; i < this->len - 1; i++)
		this->values[i] = this->values[i + 1];

	this->len = this->len - 1;
}

int TElement::getSize()
{
	return this->len;
}

int TElement::getKey()
{ 
	return this->key;
}

TValue* TElement::getAllValues()
{
	return this->values;
}