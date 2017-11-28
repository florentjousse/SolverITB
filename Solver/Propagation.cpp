#include "Propagation.h"

void Propagation::chercher(std::vector<Contrainte> listeContraintes,Graphe graphe, std::shared_ptr<std::queue<Variable*>> p1,std::vector<Variable*> ptrVariables)
{
	while (p1.get()->size() != 0) {
		Variable* v1 = p1.get()->front();
		p1.get()->front()->resetMarqueur();
		p1.get()->pop();
		if (p1.get()->size() == 0) {
			std::cout << "test";
		}
		std::cout << "\n";
		v1->reduireDomaine(v1->getFirstEV(), 2);
		std::cout << "variable :["<<v1->getIndice() + 1 << "] = ";
		v1->printDomaine();
		if (propager(listeContraintes,v1, graphe, p1, ptrVariables) == false) {
			//TODO Pas de solutions
		}
	}
}

int Propagation::propager(std::vector<Contrainte> listeContraintes, Variable* v1, Graphe graphe, std::shared_ptr<std::queue<Variable*>> p1, std::vector<Variable*> ptrVariables)
{
	for (int i = 0; i < 4; i++) {
		if (graphe.getMatriceAdjacence().at(i).at(v1->getIndice())) {
			ptrVariables.at(i)->reduireDomaine(ptrVariables.at(v1->getIndice())->getFirstEV(), 1);
			std::cout << "variable :[" << ptrVariables.at(i)->getIndice()
				+ 1 << "] = ";
			ptrVariables.at(i)->printDomaine();
		}
	}

	for (int i = 0; i < 4; i++) {
		if (graphe.getMatriceAdjacence().at(v1->getIndice()).at(i)) {
			ptrVariables.at(i)->reduireDomaine(ptrVariables.at(v1->getIndice())->getFirstEV(), 1);
			std::cout << "variable :[" << ptrVariables.at(i)->getIndice()
				+ 1 << "] = ";
			ptrVariables.at(i)->printDomaine();
		}
	}
	//v1.resetDelta();
	return 1;
	
}
