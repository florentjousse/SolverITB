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
		if (verifyDelta(val)) {
			delta.insert(std::begin(delta), val);
			domaine.erase(std::remove(domaine.begin(), domaine.end(), val), domaine.end());
		}
		deltaTemp.clear();
		deltaTemp.insert(std::begin(deltaTemp), val);
	//TODO verifier: pousser l'élément peut etre dans propagation
		if (!marqueur) {
			ptrQueue.get()->push(this);
			marqueur = true;
		}
	}
	if (option == 2) {
		for (auto i : domaine)
			if (verifyDelta(i)) {
				delta.insert(std::begin(delta), i);
			}
		delta.erase(std::remove(delta.begin(), delta.end(), val), delta.end());
		deltaTemp.clear();
		for (auto i : domaine)
				deltaTemp.insert(std::begin(deltaTemp), i);
		deltaTemp.erase(std::remove(deltaTemp.begin(), deltaTemp.end(), val), deltaTemp.end());
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
	for (auto i : domaine) {
		delta.insert(delta.begin(), i);
	}
	domaine.clear();
	for (auto i : delta) {
		domaine.insert(domaine.end(), i);
	}
	delta.clear();
}
void Variable::addToDelta(double val) {
	delta.erase(std::remove(delta.begin(), delta.end(), val), delta.end());
	for (auto i : deltaTemp) {
		domaine.insert(domaine.begin(), i);
	}
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

bool Variable::getMarqueur()
{
	return marqueur;
}

std::ostream & operator<<(std::ostream & os, const Variable & dt)
{
	os << dt.value << " ";
	return os;
}

bool  Variable::verifyDelta(double val) {
	for (auto i : delta) {
		if (i == val) {
			return  false;
		}
	}
	int flag = 0;
	for (auto i : domaine) {
		if (i == val) {
			flag++;
		}
		
	}
	if (flag==0) {
		return false;
	}
	return true;
}