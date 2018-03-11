#pragma once
#include "TElement.h"

int hash(int k, int m);

class IteratorMM;

class MultiMap
{
	TElement** elements;
	int firstFree, m;
	int* next;
	int(*h)(int k, int m);

public:
	MultiMap();
	MultiMap(int l, int(*hash)(int k, int m));
	~MultiMap();

	TElement** getAll() { return this->elements; }
	int getFirstFree() { return this->firstFree; }
	int getLength() { return this->m; }
	int* getNext() { return this->next; }
	int size();

	void search(int k, TValue result[], int& l);

	void add(int& k, TValue& v);

	void changeFirstFree();

	IteratorMM* iterator();

	void remove(int k, TValue v);

	MultiMap* rehash(int l);
};

class IteratorMM
{
public:
	MultiMap* mm;
	int currentKey, currentValue;

	IteratorMM(MultiMap* m);
	~IteratorMM() {}

	void next();
	void element(int& k, TValue& v);
	bool valid();
};

