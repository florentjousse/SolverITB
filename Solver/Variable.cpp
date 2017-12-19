#include "Variable.h"
#include <stdlib.h>
Variable::Variable()
{
	indice =0;
	value = this;
	domaine.resize(0);
	marqueur = false;
	std::iota(std::begin(domaine), std::end(domaine), 0);
}
void Variable::setLabel(int _label) {
	label = _label;
}
void Variable::setDomaine(std::vector<int> _domaine) {
	domaine = _domaine;
}
int Variable::getLabel() {
	return label;

}
Variable::Variable(int contante)
{
	indice = NULL;
	marqueur = false;
	value = this;
	domaine.resize(1);
	domaine.insert(domaine.begin(), contante);
}

Variable::Variable(int INF, int SUP,int _indice, std::shared_ptr<std::queue<Variable*>> p1)
{
	indice = _indice;
	marqueur = false;
	value = this;
	domaine.resize(SUP - INF +1);
	std::iota(std::begin(domaine), std::end(domaine), INF );
	int ind = 0;
	ptrQueue = p1;
}
std::vector<int> Variable::getDelta() {
	return deltaStr;
}
void Variable::reduireDomaine(int val, int option)
{	
	if (option == 1) {
		for (auto i : domaine) {
			if (i == val) {
				if (deltaStr.size() == 0 ) {
					//std::vector<int> temp;
					//temp.push_back(val);
					deltaStr.push_back(val);
				}
				else {
					deltaStr.push_back(val);
				}
				domaine.erase(std::remove(domaine.begin(), domaine.end(), val), domaine.end());
				break;
			}
		}
	}
	if (option == 2) {
		
		//deltaTemp.clear();
		//std::vector<int> temp;
		for (auto i : domaine) {
			deltaStr.push_back(i);
		}
	//	deltaStr.push_back(temp);
		//int size = deltaStr.size() - 1;
		deltaStr.erase(std::remove(deltaStr.begin(), deltaStr.end(), val), deltaStr.end());
		//ind++;
		domaine.clear();
		domaine.insert(domaine.begin(), val);
	
	}

}

void Variable::printDomaine()
{
std::cout << "Domaine var[" << this->indice +1 << "]:";

	for (auto i : domaine)
		std::cout << i << " ";
	std::cout << "\n";
}

void Variable::printDelta()
{
	std::cout << "Delta var["<<this->indice +1<< "] :";

	for (auto i : deltaStr) {
		std::cout << " i ";
	}
		
	std::cout << "\n";
}

void Variable::pushBackn()
{
	//deltaStr.push_back(std::vector<int>());
}
void Variable::popBackn()
{
	deltaStr.pop_back();

}
void Variable::resetDelta()
{
	if (deltaStr.size() != 0) {
		for (auto i : deltaStr)
			domaine.push_back(i);
		deltaStr.pop_back();
	}
}
void Variable::addToDomaine(int val) {
	//deltaStr.back().erase(std::remove(deltaStr.back().begin(), deltaStr.back().end(), val), deltaStr.back().end());

		domaine.insert(domaine.begin(), val);
	
}
bool Variable::isEmptyDelta()
{
	return deltaStr.size();
}
int Variable::sizeDomaine()
{
	return domaine.size();
}
void Variable::setValue(int _value)
{
	value = value; 

}

int Variable::getIndice()
{
	return indice;
}

int Variable::getFirstEV()
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

std::vector<int> Variable::getDomaine()
{
	return domaine;
}

int Variable::getElemDomain(int indice)
{
	return domaine.at(indice);
}

std::ostream & operator<<(std::ostream & os, const Variable & dt)
{
	os << dt.value << " ";
	return os;
}



//UNUSED
