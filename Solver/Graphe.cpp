#include "Graphe.h"




Graphe::Graphe(std::shared_ptr<std::vector<Variable>> p1, std::shared_ptr<std::vector<ContrainteV2*>> p2,int size)
{
	listeVariables = p1;
	listeContraintes = p2;
	int j= 0;
	matriceAdjacencev2.resize(size);
	for (auto i : matriceAdjacencev2) {
		matriceAdjacencev2.at(j).resize(size);
		j++;
	}
	for (auto contrainte : *listeContraintes) {
		int v1 = contrainte->getV1().getIndice();
		int v2 = contrainte->getV2().getIndice();
		std::vector<int> vect1;
		std::vector<int> vect2;
		matriceAdjacencev2.at(v1).at(v2) = contrainte->returnImpossible();
		matriceAdjacencev2.at(v2).at(v1) = contrainte->returnImpossible();//
	}
}

Graphe::~Graphe()
{

}

std::vector<std::vector<std::string>> Graphe::getMatriceAdjacence()
{
	return matriceAdjacencev2;
}
