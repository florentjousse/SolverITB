#include <vector>
#include <algorithm>
#pragma once

class Variable {
public :
	Variable();
	Variable(double borneInf, double borneSup,int _indice);
	void reduireDomaine(double val, int option);//option 1 = laisser que val dans domaine   ||| option 2 = enlever val du domaine 
	void printDomaine();
	void printDelta();
	void resetDelta();
	bool isEmptyDelta();
	int getIndice();

private:
	void setValue(double _value);
	friend std::ostream& operator<<(std::ostream& os, const Variable& dt);
	std::vector<double> domaine;
	std::vector<double> delta;
	Variable * value; 
	int indice;
};