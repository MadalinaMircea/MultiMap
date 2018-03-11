#pragma once
#include "MultiMap.h"

class Problem
{
	MultiMap* mm;
	int degree, values[10], n, set[10];

public:
	Problem(MultiMap* m);
	Problem() {}
	~Problem();

	MultiMap* getMultimap() { return this->mm; }
	int getDegree() { return this->degree; }
	int* getValues() { return this->values; }
	int getN() { return this->n; }
	int* getSet() { return this->set; }
	void setDegree(int d) { this->degree = d; }
	void setN(int x) { this->n = x; }
	void setValue(int x, int i) { this->values[i] = x; }
	void setSet(int x, int i) { this->set[i] = x; }
	void start();
	void readFunction();
	void showFunction();
	void readSet();
	void showSet();
	void compute();
	void showResult();
	int functionValue(int x);
};