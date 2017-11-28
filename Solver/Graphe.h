#pragma once
#include <vector>
#include "Variable.h"
#include "Contrainte.h"
#include <memory>

class Graphe
{
public:
	Graphe( std::shared_ptr<std::vector<Variable>>  p1, std::shared_ptr<std::vector<Contrainte>>  p2);
	~Graphe();
	std::vector<std::vector<int>> getMatriceAdjacence();

private:
	std::shared_ptr<std::vector<Variable>> listeVariables;
	std::shared_ptr<std::vector<Contrainte>> listeContraintes;
	std::vector<std::vector<int>> matriceAdjacence;
};

