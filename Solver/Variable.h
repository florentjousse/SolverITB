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
	Variable(int contante);
	Variable(int borneInf, int borneSup,int _indice, std::shared_ptr<std::queue<Variable*>> p1);
	void reduireDomaine(int val, int option);//option 1 = laisser que val dans domaine   ||| option 2 = enlever val du domaine 
	void printDomaine();
	void printDelta();
	void resetDelta();
	void addToDelta(int val);
	bool isEmptyDelta();
	int sizeDomaine();
	int getIndice();
	int getFirstEV();
	void resetMarqueur();
	bool getMarqueur();
	int getElemDomain(int indice);
private:
	void setValue(int _value);
	friend std::ostream& operator<<(std::ostream& os, const Variable& dt);
	 bool verifyDelta(int val);
	std::shared_ptr<std::queue<Variable*>> ptrQueue;
	std::vector<int> domaine;
	std::vector<int> delta;
	std::vector<int> deltaTemp;

	Variable * value; 
	bool marqueur;
	int indice;
};