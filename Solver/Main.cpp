#include <iostream>
#include "Variable.h"
#include "Contrainte.h"
#include "ContraintePlus.h"
#include "Propagation.h"
#include "Graphe.h"
#include <memory>
int main() {
	std::queue<Variable*> *qV= new std::queue<Variable*>();
	std::shared_ptr<std::queue<Variable*>> sharedQv(qV);

	//=================================VARIABLES=======================
	// les variables ont un domaine entre -10 et 10 
	// V1 = [-10,10]
	// V2 = [-10,10]
	// V3 = [-10,10]
	// V4 = [-10,10]
	//================================================================

	Variable v1(1, 5, 0, sharedQv);
	Variable v2(2, 4, 1, sharedQv);
	Variable v3(1, 4, 2, sharedQv);
	Variable v4(1, 5, 3, sharedQv);
	Variable v5(1, 3, 4, sharedQv);

	sharedQv.get()->push(&v1);
	v1.resetMarqueur();

	std::vector<Variable*> ptrVariables;

	ptrVariables.insert(ptrVariables.begin(), &v5);
	ptrVariables.insert(ptrVariables.begin(), &v4);
	ptrVariables.insert(ptrVariables.begin(), &v3);
	ptrVariables.insert(ptrVariables.begin(), &v2);
	ptrVariables.insert(ptrVariables.begin(), &v1);

	
	int nombreVars = ptrVariables.size();

	/*
	v1.printDomaine();
	v1.printDelta();
	v1.reduireDomaine(8, 2);
	v1.printDomaine();
	v1.printDelta();
	v1.resetDelta();
	v1.printDelta();
	}*/


	//Ici on a nos variables sur le heap, car gérés par un vector pas performant mais on verra plus tard TODO
	std::vector<Variable> *listeVariables = new std::vector<Variable>();
	listeVariables->insert(listeVariables->begin(), v1);
	listeVariables->insert(listeVariables->begin(),v2);
	listeVariables->insert(listeVariables->begin(), v3);
	listeVariables->insert(listeVariables->begin(), v4);
	listeVariables->insert(listeVariables->begin(), v5);
	std::shared_ptr<std::vector<Variable>> sharedListVariable(listeVariables);	
	
	
	//=======================CONTRAINTES====================
	// V1 != V2 
	// V1 != V4
	// v1 != V3 
	// V2 != V3 
	//======================================================
	//Ici on a nos variables sur le heap, car gérés par un vector pas performant mais on verra plus tard TODO

	std::vector<Contrainte> *listeContraintes = new std::vector<Contrainte>();
/*	listeContraintes->insert(listeContraintes->begin(), Contrainte(v1, v2));
	listeContraintes->insert(listeContraintes->begin(), Contrainte(v1, v4));
	listeContraintes->insert(listeContraintes->begin(), Contrainte(v1, v3));
	listeContraintes->insert(listeContraintes->begin(), Contrainte(v2, v3));
	listeContraintes->insert(listeContraintes->begin(), Contrainte(v1, v5));
	listeContraintes->insert(listeContraintes->begin(), Contrainte(v2, v5));
	listeContraintes->insert(listeContraintes->begin(), Contrainte(v1, v4));*/

	for (int i = 0; i < nombreVars - 1; i++) {
		for (int j = i + 1; j < nombreVars; j++) {
			listeContraintes->insert(listeContraintes->begin(), Contrainte(listeVariables->at(i), listeVariables->at(j)));
		//	listeContraintes->insert(listeContraintes->begin(), ContraintePlus(listeVariables->at(i), listeVariables->at(j), j-i));
			//listeContraintes->insert(listeContraintes->begin(), Contrainte(listeVariables->"at(i), listeVariables->at(j)));*/
		}
	}
	listeContraintes->insert(listeContraintes->begin(), Contrainte(listeVariables->at(2), listeVariables->at(1)));
	std::shared_ptr<std::vector<Contrainte>> sharedListContraintes(listeContraintes);
	Graphe graphe(sharedListVariable, sharedListContraintes,nombreVars);
	Propagation::chercher(*listeContraintes, graphe,sharedQv,ptrVariables,nombreVars);
	system("pause");


}