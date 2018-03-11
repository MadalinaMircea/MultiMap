#include <iostream>
#include "Problem.h"
#include <assert.h>
using namespace std;

void testMultiMap()
{
	MultiMap* test1 = new MultiMap{};
	
	int k;
	TValue v;

	assert(test1->getLength() == 15);
	assert(test1->size() == 0);
	assert(test1->getFirstFree() == 0);

	IteratorMM* it = test1->iterator();

	assert(it->currentValue == -1);

	int nr = 0;
	while (it->valid())
	{
		it->element(k, v);
		nr++;
		it->next();
	}

	assert(nr == 0);

	delete it;
	delete test1;

	MultiMap* test = new MultiMap{ 13 };
	
	assert(test->getLength() == 13);
	assert(test->size() == 0);
	assert(test->getFirstFree() == 0);
	
	int keys[] = { 5, 18, 16, 15, 13, 31, 26 };

	for (int i = 0; i < 7; i++)
	{
		v = TValue{ i, i };
		test->add(keys[i], v);
		assert(test->size() == i + 1);
	}

	assert(test->getAll()[5]->getKey() == 5);
	assert(test->getNext()[5] == 0);
	assert(test->getAll()[1]->getKey() == 13);
	assert(test->getNext()[1] == 4);

	assert(test->getAll()[2]->getSize() == 1);
	assert(test->getAll()[8]->getSize() == 0);
	assert(test->getNext()[10] == -1);

	assert(test->getAll()[0]->getAllValues()[0].getX() == 1);
	assert(test->getAll()[0]->getAllValues()[0].getY() == 1);

	assert(test->getAll()[4]->getAllValues()[0].getX() == 5);
	assert(test->getAll()[4]->getAllValues()[0].getY() == 5);

	k = 5;
	v = TValue{ 27, -93 };
	test->add(k, v);

	
	TValue result[10];
	int l = 0;
	test->search(5, result, l);
	assert(l == 2);
	assert(result[1] == v);

	l = 0;
	test->search(13, result, l);
	assert(l == 1);

	it = test->iterator();
	nr = 0;
	
	while (it->valid())
	{
		it->element(k, v);
		nr++;
		it->next();
	}
	
	assert(nr == test->size());
	delete it;

	assert(test->size() == 8);
	assert(test->getAll()[5]->getSize() == 2);
	assert(test->getAll()[5]->getAllValues()[1].getX() == 27);
	assert(test->getAll()[5]->getAllValues()[1].getY() == -93);

	v = TValue{ 0,0 };
	test->remove(5, v);
	assert(test->size() == 7);
	assert(test->getAll()[5]->getSize() == 1);

	try
	{
		k = 0;
		test->remove(k, v);
		assert(false);
	}
	catch (...)
	{
		assert(true);
	}

	try
	{
		k = 5;
		v = TValue{ 0, 0 };
		test->remove(k, v);
		assert(false);
	}
	catch (...)
	{
		assert(true);
	}

	k = 5;
	v = TValue{ 27, -93 };
	test->remove(k, v);
	assert(test->size() == 6);
	assert(test->getAll()[0]->getKey() == 13);
	assert(test->getNext()[0] == 4);

	it = test->iterator();
	
	assert(it->currentKey == 0);
	assert(it->currentValue == 0);

	nr = 0;
	while (it->valid())
	{
		it->element(k, v);
		nr++;
		it->next();
	}

	
	assert(nr = test->size());
	delete it;

	
	for (int i = 0; i < 15; i++)
	{
		v = TValue{ i, i };
		test->add(i, v);
	}

	k = 5;
	for (int i = 0; i < 15; i++)
	{
		v = TValue{ i, i };
		test->add(k, v);
	}

	assert(test->getLength() == 26);
	

	delete test;
}

int main()
{
	//testMultiMap();
	
	MultiMap* mm = new MultiMap{ 13 };

	Problem* pb = new Problem{ mm };

	pb->start();

	delete pb;
	
	return 0;
}