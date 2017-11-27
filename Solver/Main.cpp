#include <iostream>
#include "Variable.h"
#include "Contrainte.h"
#include "Propagation.h"
#include "Graphe.h"
#include <memory>

int main() {

	//4 variables ctout maggle

	Variable v1(-10, 10,0);
	Variable v2(-10, 10,1);
	Variable v3(-10, 10,2);
	Variable v4(-10, 10,3);	
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
	std::shared_ptr<std::vector<Variable>> sharedListVariable(listeVariables);	

	//Ici on a nos variables sur le heap, car gérés par un vector pas performant mais on verra plus tard TODO
	std::vector<Contrainte> *listeContraintes = new std::vector<Contrainte>();
	listeContraintes->insert(listeContraintes->begin(), Contrainte(v1, v2));
	listeContraintes->insert(listeContraintes->begin(), Contrainte(v1, v4));
	listeContraintes->insert(listeContraintes->begin(), Contrainte(v1, v3));
	listeContraintes->insert(listeContraintes->begin(), Contrainte(v2, v3));
	std::shared_ptr<std::vector<Contrainte>> sharedListContraintes(listeContraintes);

	Graphe graphe(sharedListVariable, sharedListContraintes);

	for (auto i : *listeContraintes) {
		std::cout << i<< " then ";
	}
	std::cout << "\n";
	Propagation::chercher(*listeContraintes, graphe);
	system("pause");


}