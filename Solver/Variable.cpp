#include "Variable.h"

Variable::Variable()
{
	indice =0;
	value = this;
	domaine.resize(0);
	marqueur = false;
	std::iota(std::begin(domaine), std::end(domaine), 0);
}

Variable::Variable(double INF, double SUP,int _indice, std::shared_ptr<std::queue<Variable*>> p1)
{
	indice = _indice;
	marqueur = false;
	value = this;
	domaine.resize(SUP - INF +1);
	std::iota(std::begin(domaine), std::end(domaine), INF );
	ptrQueue = p1;
}

void Variable::reduireDomaine(double val, int option)
{	
	if (option == 1) {
		domaine.erase(std::remove(domaine.begin(), domaine.end(), val), domaine.end());
		delta.insert(std::begin(delta), val);
		if (!marqueur) {
			ptrQueue.get()->push(this);
			marqueur = true;
		}
	}
	if (option == 2) {
		for (auto i : domaine)
			delta.insert(std::begin(delta), i);
		delta.erase(std::remove(delta.begin(), delta.end(), val), delta.end());
		domaine.clear();
		domaine.insert(domaine.begin(), val);
		/*if (!marqueur) {
			ptrQueue.get()->push(this);
			marqueur = true;
		}*/


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
int Variable::sizeDomaine()
{
	return domaine.size();
}
void Variable::setValue(double _value)
{
	value = value; 

}

int Variable::getIndice()
{
	return indice;
}

double Variable::getFirstEV()
{
	return domaine.at(0);
}

void Variable::resetMarqueur()
{
	if (marqueur)
		marqueur = false;
	else
		marqueur = true;
}

std::ostream & operator<<(std::ostream & os, const Variable & dt)
{
	os << dt.value << " ";
	return os;
}
