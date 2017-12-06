#include "Graphe.h"




Graphe::Graphe(std::shared_ptr<std::vector<Variable>> p1, std::shared_ptr<std::vector<Contrainte>> p2,int size)
{
	listeVariables = p1;
	listeContraintes = p2;
	int j= 0;
	matriceAdjacence.resize(size);
	for (auto i : matriceAdjacence) {
		matriceAdjacence.at(j).resize(size);
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
		std::vector<double> vect1;
		std::vector<double> vect2;
		matriceAdjacence.at(v1).at(v2) = contrainte.returnImpossible();
		matriceAdjacence.at(v2).at(v1) = contrainte.returnImpossible();//

	}
}

Graphe::~Graphe()
{
}

std::vector<std::vector<double>> Graphe::getMatriceAdjacence()
{
	return matriceAdjacence;
}
