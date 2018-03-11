#include "Problem.h"
#include <cstring>

Problem::Problem(MultiMap* m) : mm(m) {}

Problem::~Problem()
{
	delete this->mm;
}

void Problem::readFunction()
{
	char x[10];
	cout << "Give the degree of the function ( 0 < degree < 10 ): ";

	try
	{
		cin >> x;
		this->setDegree(atoi(x));
		if (this->getDegree() <= 0 || this->getDegree() >= 10)
			throw std::exception("Degree not valid.");
	}
	catch(...)
	{
		throw std::exception("Degree not valid.");
	}		

	for (int i = 0; i <= this->getDegree(); i++)
	{
		cout << "Give the coefficient of x^" << i << " (integer): ";

		cin >> x;
		this->setValue(atoi(x), i);
	}
}

void Problem::showFunction()
{
	cout << "Your function is: \n";
	cout << this->getValues()[this->getDegree()] << "*x^" << this->getDegree();
	for (int i = this->getDegree() - 1; i >= 0; i--)
	{
		if (this->getValues()[i] == 0)
			continue;

		if (this->getValues()[i] > 0)
			cout << " + ";
		else
			cout << " ";
		cout << this->getValues()[i] << "*x^" << i;
		
	}

	cout << "\n\n";
}

void Problem::readSet()
{
	char x[10];
	cout << "Give the number of elements of the set ( 1 < nr < 10 ): ";

	try
	{
		cin >> x;
		this->setN(atoi(x));
		if (this->getN() <= 1 || this->getN() >= 10)
			throw std::exception("Number not valid.");
	}
	catch (...)
	{
		throw std::exception("Number not valid.");
	}

	int i = 0, j = 0;
	while(i < this->getN())
	{
		cout << "Element number " << i << ": ";

		cin >> x;
		bool ok = true;
		this->setSet(atoi(x), i);
		for(j = 0; j < i; j++)
			if (this->getSet()[j] == this->getSet()[i])
			{
				ok = false;
				break;
			}
		if (ok == true)
			i++;
	}
}

void Problem::showSet()
{
	cout << "Your set is: ";

	for (int i = 0; i < this->getN(); i++)
		cout << this->getSet()[i] << " ";

	cout << "\n\n";
}

void Problem::start()
{
	try
	{
		this->readFunction();
	}
	catch (exception& e)
	{
		cout << e.what() << '\n';
		return;
	}
	this->showFunction();

	try
	{
		this->readSet();
	}
	catch (exception& e)
	{
		cout << e.what() << '\n';
		return;
	}
	this->showSet();

	this->compute();
	this->showResult();
}

int Problem::functionValue(int x)
{
	int p = 1, total = 0;
	for (int i = 0; i <= this->getDegree(); i++)
	{
		total = total + p * this->getValues()[i];
		p = p * x;
	}

	return total;
}

void Problem::compute()
{
	int i, j, s;
	TValue v;

	for (i = 0; i < this->getN() - 1; i++)
		for (j = i + 1; j < this->getN(); j++)
		{
			s = this->functionValue(this->getSet()[i]) + this->functionValue(this->getSet()[j]);
			v = TValue{ this->getSet()[i], this->getSet()[j] };
			this->mm->add(s, v);
		}
}

void Problem::showResult()
{
	bool ok = false;
	for(int i = 0; i < this->mm->getLength(); i++)
		if (this->mm->getAll()[i]->getSize() > 1)
		{
			if(ok == false)
				cout << "The quadruplets (x, y, z, t) that satisfy f(x) + f(y) = f(z) + f(t) are: \n";

			for (int j = 0; j < this->mm->getAll()[i]->getSize() - 1; j++)
				for (int k = j + 1; k < this->mm->getAll()[i]->getSize(); k++)
					cout << "f(" << this->mm->getAll()[i]->getAllValues()[j].getX() << ") + f(" << \
					this->mm->getAll()[i]->getAllValues()[j].getY() << ") = f(" << \
					this->mm->getAll()[i]->getAllValues()[k].getX() << ") + f(" << \
					this->mm->getAll()[i]->getAllValues()[k].getY() << ") = " << \
					this->mm->getAll()[i]->getKey() << "\n";

			ok = true;
		}

	if (ok == false)
		cout << "There are no quadruplets (x, y, z, t) that satisfy f(x) + f(y) = f(z) + f(t).\n";
}