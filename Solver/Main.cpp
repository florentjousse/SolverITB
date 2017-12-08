#include <iostream>
#include "Variable.h"
#include "ContrainteV2.h"
#include "Propagation.h"
#include "Graphe.h"
#include <memory>
#include "ContrainteBinaire.h"
#include "ContrainteTernaire.h"

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
	Variable v2(1, 5, 1, sharedQv);
	Variable v3(1, 5, 2, sharedQv);
	Variable v4(1, 5, 3, sharedQv);
	Variable v5(1, 5, 4, sharedQv);

	sharedQv.get()->push(&v1);
	v1.resetMarqueur();

	std::vector<Variable*> ptrVariables;

	ptrVariables.insert(ptrVariables.begin(), &v5);
	ptrVariables.insert(ptrVariables.begin(), &v4);
	ptrVariables.insert(ptrVariables.begin(), &v3);
	ptrVariables.insert(ptrVariables.begin(), &v2);
	ptrVariables.insert(ptrVariables.begin(), &v1);

	
	int nombreVars = ptrVariables.size();


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

	std::vector<ContrainteV2*> *listeContraintes = new std::vector<ContrainteV2*>();
	
	
	for (int i = 0; i < nombreVars - 1; i++) {
		for (int j = i + 1; j < nombreVars; j++) {
		ContrainteBinaire *cb= new ContrainteBinaire(listeVariables->at(i), "!=", listeVariables->at(j));
		Variable vconst(j-i);
		ContrainteTernaire *ct1 = new ContrainteTernaire(listeVariables->at(i), "!=", listeVariables->at(j),"-",vconst);
		ContrainteTernaire *ct2 = new ContrainteTernaire(listeVariables->at(i), "!=", listeVariables->at(j), "+", vconst);
		listeContraintes->insert(listeContraintes->begin(), cb);
		listeContraintes->insert(listeContraintes->begin(), ct1);
		listeContraintes->insert(listeContraintes->begin(), ct2);

		
		}
	}
	for (auto i : *listeVariables) {
		i.printDomaine();
		std::cout << "\n";
	}
	

	std::shared_ptr<std::vector<ContrainteV2*>> sharedListContraintes(listeContraintes);
	Graphe graphe(sharedListVariable, sharedListContraintes,nombreVars);
	Propagation::chercher(*listeContraintes, graphe,sharedQv,ptrVariables,nombreVars);
	system("pause");


}