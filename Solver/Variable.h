#pragma once

#include <vector>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <memory>
#include <queue>
#include <string>
class Variable {
public :
	Variable();
	int getLabel();
	void setLabel(int _label);

	void setDomaine(std::vector<int> _domaine);

	Variable(int contante);
	Variable(int borneInf, int borneSup,int _indice, std::shared_ptr<std::queue<Variable*>> p1);
	void reduireDomaine(int val, int option);//option 1 = laisser que val dans domaine   ||| option 2 = enlever val du domaine 
	void printDomaine();
	void printDelta();
	void pushBackn();
	void popBackn();
	void resetDelta();
	void addToDomaine(int val);
	bool isEmptyDelta();
	int sizeDomaine();
	int getIndice();
	int getFirstEV();
	void resetMarqueur();
	bool getMarqueur();
	std::vector<int> getDomaine();
	std::vector<int> getDelta();
	int getElemDomain(int indice);
private:
	void setValue(int _value);
	friend std::ostream& operator<<(std::ostream& os, const Variable& dt);
	std::shared_ptr<std::queue<Variable*>> ptrQueue;
	std::vector<int> domaine;

	std::vector<int> deltaStr;
	Variable * value; 
	bool marqueur;
	int indice;
	int ind;
	int label;
};