#include "Propagation.h"

void Propagation::chercher(std::vector<Contrainte> listeContraintes,Graphe graphe, std::shared_ptr<std::queue<Variable*>> p1,std::vector<Variable*> ptrVariables,int nombreVars)
{	
	int count = 0;
	int woua = 0;
	Variable *precV1 = NULL;
	Variable* v1 =NULL;
	while (p1.get()->size() != 0) {
		precV1 = v1;
		Variable* v1 = p1.get()->front();
		woua = v1->getFirstEV();
		p1.get()->front()->resetMarqueur();
		std::cout << "\n";
		v1->reduireDomaine(woua, 2);
		count++;
		woua++;
		std::cout << "variable :["<<v1->getIndice() + 1 << "] = ";
		v1->printDomaine();
		std::cout << "\n";
		if (count == nombreVars) {
				std::cout << "FIN : RESULTAT / \n";
			for (auto i : ptrVariables) {
				std::cout << "var[" << i->getIndice()+1 << "]=" << i->getFirstEV() << "\n";
			}
			break;
		}
		if (propager(listeContraintes, v1, graphe, p1, ptrVariables,nombreVars) == false) {
	
			for (int i = ptrVariables.size()-1; i >=v1->getIndice(); i--){
				std::cout << "domaine:\n";
				ptrVariables.at(i)->printDomaine();
				int size = ptrVariables.at(i)->sizeDomaine();
				std::cout << "delta:\n";
				double value = v1->getFirstEV();
				ptrVariables.at(i)->printDelta();
				//ptrVariables.at(i)->resetDelta();
				ptrVariables.at(i)->addToDelta(value);//TODO rename addtodomaine
			
				
				std::cout << "nouveau domaine:\n";

				ptrVariables.at(i)->printDomaine();
				std::cout << "\n";

			}
			count = 0;
			std::cout << "backtrack" << "\n";
		}
		else {
			p1.get()->pop();

		}
	}
	std::cout << "\nFIN : PAS DE RESULTAT / \n";


}

int Propagation::propager(std::vector<Contrainte> listeContraintes, Variable* v1, Graphe graphe, std::shared_ptr<std::queue<Variable*>> p1, std::vector<Variable*> ptrVariables, int nombreVars)
{
	for (int i = 0; i < nombreVars; i++) {
		if (graphe.getMatriceAdjacence().at(i).at(v1->getIndice())) {
			ptrVariables.at(i)->reduireDomaine(v1->getFirstEV(), 1);
			//ptrVariables.at(i)->reduireDomaine(v1->getFirstEV() + graphe.getMatriceAdjacence().at(i).at(v1->getIndice()), 1);
			if (!ptrVariables.at(i)->getMarqueur() && !ptrVariables.at(i)->sizeDomaine() != 1 ) {
				p1.get()->push(ptrVariables.at(i));
				ptrVariables.at(i)->resetMarqueur();
			}

			std::cout << "variable :[" << ptrVariables.at(i)->getIndice()+ 1 << "] = ";
			ptrVariables.at(i)->printDomaine();
			ptrVariables.at(i)->printDelta();

			if (ptrVariables.at(i)->sizeDomaine() == 0){
				return 0;
			}
		}
	}

	/*for (int i = 0; i < nombreVars; i++) {
		if (graphe.getMatriceAdjacence().at(v1->getIndice()).at(i)) {
		//	ptrVariables.at(i)->reduireDomaine(v1->getFirstEV()+ graphe.getMatriceAdjacence().at(i).at(v1->getIndice()), 1);
			ptrVariables.at(i)->reduireDomaine(v1->getFirstEV(), 1);
			if (!ptrVariables.at(i)->getMarqueur()) {
				p1.get()->push(ptrVariables.at(i));
				ptrVariables.at(i)->resetMarqueur();
			}

			std::cout << "variable :[" << ptrVariables.at(i)->getIndice()
				+ 1 << "] = ";
			ptrVariables.at(i)->printDomaine();

			if (ptrVariables.at(i)->sizeDomaine() == 0) {
				return 0;
			}
		}
	}*/
	return 1;
}
void Propagation::clear(std::shared_ptr<std::queue<Variable*>> q)
{
	while (q.get()->size()) {
		q.get()->pop();
	}
}

