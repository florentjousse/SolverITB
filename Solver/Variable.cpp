#include "Variable.h"
#include <algorithm>
#include <iostream>
#include <numeric>

Variable::Variable()
{
	indice =0;
	value = this;
	domaine.resize(0);
	std::iota(std::begin(domaine), std::end(domaine), 0);
}

Variable::Variable(double INF, double SUP,int _indice)
{
	indice = _indice;
	value = this;
	domaine.resize(SUP - INF +1);
	std::iota(std::begin(domaine), std::end(domaine), INF );
}

void Variable::reduireDomaine(double val, int option)
{	
	if (option == 1) {
		domaine.erase(std::remove(domaine.begin(), domaine.end(), val), domaine.end());
		delta.insert(std::begin(delta), val);
	}
	if (option == 2) {
		for (auto i : domaine)
			delta.insert(std::begin(delta), i);
		delta.erase(std::remove(delta.begin(), delta.end(), val), delta.end());
		domaine.clear();
		domaine.insert(domaine.begin(), val);
	}

}

void Variable::printDomaine()
{
	std::cout << "Domaine " << this << " :";

	for (auto i : domaine)
		std::cout << i << " ";
	std::cout << "\n";
}

void Variable::printDelta()
{
	std::cout << "Delta "<<this<< " :";

	for (auto i : delta)
		std::cout << i << " ";
	std::cout << "\n";
}
void Variable::resetDelta()
{
	delta.clear();
}
bool Variable::isEmptyDelta()
{
	return delta.size();
}
void Variable::setValue(double _value)
{
	value = value; 

}

int Variable::getIndice()
{
	return indice;
}

std::ostream & operator<<(std::ostream & os, const Variable & dt)
{
	os << dt.value << " ";
	return os;
}
