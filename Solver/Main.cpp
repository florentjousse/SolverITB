#include <iostream>
#include "Variable.h"
#include "ContrainteV2.h"
#include "Propagation.h"
#include "Graphe.h"
#include <memory>
#include "ContrainteBinaire.h"
#include "ContrainteTernaire.h"
#include <regex>
#include <ctime>
int main() {

	std::queue<Variable*> *qV= new std::queue<Variable*>();
	std::shared_ptr<std::queue<Variable*>> sharedQv(qV);

	//=================================VARIABLES=======================
	// les variables ont un domaine entre -10 et 10 
	// 
	//================================================================


	int nbQueens = 6;
	std::vector<Variable*> ptrVariables;
	std::vector<Variable> *listeVariables = new std::vector<Variable>();
	for (int i = 0; i < nbQueens; i++) {
		Variable v(1, nbQueens, i, sharedQv);
		ptrVariables.insert(ptrVariables.begin(), &v);
		listeVariables->insert(listeVariables->begin(), v);

	}

	int nombreVars = ptrVariables.size();

	std::shared_ptr<std::vector<Variable>> sharedListVariable(listeVariables);	
	
	
	//=======================CONTRAINTES====================
	
	//Ici on a nos variables sur le heap, car gérés par un vector pas performant mais on verra plus tard TODO

	std::vector<ContrainteV2*> *listeContraintes =  new std::vector<ContrainteV2*>();
	
	for (int i = 0; i < nombreVars - 1; i++) {
		for (int j = i + 1; j < nombreVars; j++) {
		ContrainteBinaire *cb= new ContrainteBinaire(&listeVariables->at(i), "!=", &listeVariables->at(j));
		Variable *vconst= new Variable(j-i);
		ContrainteTernaire *ct1 = new ContrainteTernaire(&listeVariables->at(i), "!=", &listeVariables->at(j),"-",  *vconst);
		ContrainteTernaire *ct2 = new ContrainteTernaire(&listeVariables->at(i), "!=", &listeVariables->at(j), "+", *vconst);
		listeContraintes->insert(listeContraintes->begin(), cb);
		listeContraintes->insert(listeContraintes->begin(), ct1);
		listeContraintes->insert(listeContraintes->begin(), ct2);
			
		}
	}/*
	for (auto i : *listeVariables) {
		i.printDomaine();
		std::cout << "\n";
	}*/
	std::shared_ptr<std::vector<ContrainteV2*>> sharedListContraintes(listeContraintes);
	Graphe graphe(sharedListVariable, sharedListContraintes,nombreVars);
	
//	bool oooo = Propagation::reviser(listeVariables->at(0), listeVariables->at(1),"<");

	std::vector<Variable> listeVariables2 = *listeVariables;
	std::vector<Variable> *ptListeVariables2 = &listeVariables2;
	clock_t begin = clock();
	//Propagation::backtrack(*listeVariables, std::vector<Variable>(),ptListeVariables2, *listeContraintes, graphe, sharedQv, ptrVariables, nombreVars);
	clock_t end = clock();
	clock_t begin1 = clock();
	Propagation::backtrackAC3(*listeVariables, std::vector<Variable>(), ptListeVariables2, *listeContraintes, graphe,  ptrVariables, nombreVars);
	clock_t end1 = clock();

	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

	double elapsed_secs2 = double(end1 - begin1) / CLOCKS_PER_SEC;

	std::cout << "\n temps backtrack sans AC :" << elapsed_secs<<"\n temps backtrack avec AC3:"<<elapsed_secs2 << std::endl;
	system("pause");


}