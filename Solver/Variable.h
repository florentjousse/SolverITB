#pragma once

#include <vector>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <memory>
#include <queue>

class Variable {
public :
	Variable();
	Variable(double borneInf, double borneSup,int _indice, std::shared_ptr<std::queue<Variable*>> p1);
	void reduireDomaine(double val, int option);//option 1 = laisser que val dans domaine   ||| option 2 = enlever val du domaine 
	void printDomaine();
	void printDelta();
	void resetDelta();
	void addToDelta(double val);
	bool isEmptyDelta();
	int sizeDomaine();
	int getIndice();
	double getFirstEV();
	void resetMarqueur();
	bool getMarqueur();
	double getElemDomain(int indice);
private:
	void setValue(double _value);
	friend std::ostream& operator<<(std::ostream& os, const Variable& dt);
	 bool verifyDelta(double val);
	std::shared_ptr<std::queue<Variable*>> ptrQueue;
	std::vector<double> domaine;
	std::vector<double> delta;
	std::vector<double> deltaTemp;

	Variable * value; 
	bool marqueur;
	int indice;
};