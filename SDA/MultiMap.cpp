#include "MultiMap.h"
#include <exception>

IteratorMM::IteratorMM(MultiMap* m) : mm(m)
{
	this->currentKey = 0;
	while (this->currentKey < this->mm->getLength() && \
		this->mm->getAll()[this->currentKey]->getSize() == 0)
		this->currentKey++;

	if (this->currentKey < this->mm->getLength())
		this->currentValue = 0;
	else
		this->currentValue = -1;
}

void IteratorMM::next()
{
	if (this->currentValue < this->mm->getAll()[this->currentKey]->getSize() - 1)
		this->currentValue++;
	else
	{
		this->currentKey++;

		while (this->currentKey < this->mm->getLength() &&\
			this->mm->getAll()[this->currentKey]->getSize() == 0)
			this->currentKey++;

		if (this->currentKey < this->mm->getLength())
			this->currentValue = 0;
		else
			this->currentValue = -1;
	}
}

void IteratorMM::element(int& k, TValue& v)
{
	k = this->mm->getAll()[this->currentKey]->getKey();
	v = this->mm->getAll()[this->currentKey]->getAllValues()[this->currentValue];
}
bool IteratorMM::valid()
{
	if (this->currentValue == -1)
		return false;

	return true;
}

MultiMap::MultiMap(int l, int(*hash)(int k, int m)) : m(l), firstFree(0)
{
	this->elements = new TElement*[m];
	next = new int[m];
	this->h = hash;
	for (int i = 0; i < m; i++)
	{
		next[i] = -1;
		this->elements[i] = new TElement;
	}
}

MultiMap::MultiMap() : m(15), firstFree(0)
{
	this->elements = new TElement*[m];
	next = new int[m];
	for (int i = 0; i < m; i++)
	{
		next[i] = -1;
		this->elements[i] = new TElement;
	}
}

MultiMap::~MultiMap()
{
	for (int i = 0; i < this->m; i++)
		delete this->elements[i];
}

int MultiMap::size()
{
	int total = 0;

	for (int i = 0; i < this->m; i++)
		total = total + this->elements[i]->getSize();

	return total;
}

void MultiMap::changeFirstFree()
{
	while (this->firstFree != this->m && this->elements[this->firstFree]->getSize() != 0)
		this->firstFree++;
}

void MultiMap::add(int& k, TValue& v)
{
	if (this->firstFree == this->m)
	{
		*this = *this->rehash(this->m * 2);
	}

	int pos = this->h(k, this->m);
	TElement* e = new TElement{ k, v };
	
	if (this->elements[pos]->getSize() == 0)
	{
		this->elements[pos] = e;
		this->next[pos] = -1;
	}
	else
	{
		int current = pos;
		while (this->next[current] != -1 && this->elements[current]->getKey() != k)
			current = this->next[current];

		if (this->elements[current]->getKey() == k)
		{
			this->elements[current]->add(v);
		}
		else
		{
			this->elements[this->firstFree] = e;
			this->next[current] = this->firstFree;
		}
	}

	this->changeFirstFree();
}

IteratorMM* MultiMap::iterator()
{
	IteratorMM* it = new IteratorMM{ this };
	return it;
}

void MultiMap::search(int k, TValue result[], int& l)
{
	int current = this->h(k, this->m);
	l = 0;

	while (this->elements[current]->getKey() != k && this->next[current] != -1)
		current = this->next[current];

	if (this->elements[current]->getKey() == k)
	{
		for (int i = 0; i < this->elements[current]->getSize(); i++)
			result[i] = this->elements[current]->getAllValues()[i];
		l = this->elements[current]->getSize();
	}
}

void MultiMap::remove(int key, TValue v)
{
	/*
	int i = this->hash(k);
	while (this->elements[i]->getKey() != k && this->next[i] != -1)
		i = this->next[i];

	if (this->elements[i]->getKey() != k)
		throw exception("Key not found.");
	else
	{
		int j = 0;
		for (j = 0; j < this->elements[i]->getSize(); j++)
			if (this->elements[i]->getAllValues()[j] == v)
				break;

		if (j == this->elements[i]->getSize())
			throw exception("Value not found.");
		else
		{
			this->elements[i]->remove(j);
			*this = *this->rehash(this->m);
		}
	}
	*/

	int i = this->h(key, this->m);
	int j = -1, k = 0;
	while (k < this->m && j == -1)
	{
		if (next[k] == i)
			j = k;
		k++;
	}

	while (i != -1 && this->elements[i]->getKey() != key)
	{
		j = i;
		i = this->next[i];
	}

	if (i == -1)
		throw exception("Key not found.");

	for (j = 0; j < this->elements[i]->getSize(); j++)
		if (this->elements[i]->getAllValues()[j] == v)
			break;

	if (j == this->elements[i]->getSize())
		throw exception("Value not found.");
	
	this->elements[i]->remove(j);

	if (this->elements[i]->getSize() == 0)
	{
		bool over = false;
		do
		{
			int p = next[i];
			int pp = i;
			while (p != -1 && this->h(this->elements[p]->getKey(), this->m) != i)
			{
				pp = p;
				p = this->next[p];
			}
			if (p == -1)
				over = true;
			else
			{
				this->elements[i] = this->elements[p];
				j = pp;
				i = p;
			}
		} while (!over);
		if (j != -1)
			this->next[j] = this->next[i];
		this->elements[i] = new TElement{};
		this->next[i] = -1;
		if (firstFree > i)
			firstFree = i;
	}
}

int hash(int k, int m) { return k % m; }

MultiMap* MultiMap::rehash(int l)
{
	MultiMap* newMap = new MultiMap{ l, &hash };

	for (int i = 0; i < this->m; i++)
	{
		int k = this->elements[i]->getKey();
		for (int j = 0; j < this->elements[i]->getSize(); j++)
		{
			TValue v = TValue{ this->elements[i]->getAllValues()[j].getX(), \
				this->elements[i]->getAllValues()[j].getY() };

			newMap->add(k, v);
		}
	}

	return newMap;
}