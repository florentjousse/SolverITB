#include "Graphe.h"




Graphe::Graphe(std::shared_ptr<std::vector<Variable>> p1, std::shared_ptr<std::vector<Contrainte>> p2)
{
	listeVariables = p1;
	listeContraintes = p2;
	int j= 0;
	matriceAdjacence.resize(4);
	for (auto i : matriceAdjacence) {
		matriceAdjacence.at(j).resize(4);
		j++;
	}
	/*
	Matrice 
	j/i   0 1 2 3
	 
	 0  ((a b c d)
	 1   (e f g h)
	 2   (i j k l)
	 3   (m n o p))

		*/
	for (auto contrainte : *listeContraintes) {
		int v1 = contrainte.getV1().getIndice();
		int v2 = contrainte.getV2().getIndice();
		matriceAdjacence.at(v1).at(v2) = 1;
		matriceAdjacence.at(v2).at(v1) = 1;

	}
}

Graphe::~Graphe()
{
}
