#pragma once
#include <vector>
#include "Variable.h"
#include "ContrainteV2.h"
#include "boost\any.hpp"
#include <memory>

class Graphe
{
public:
	Graphe( std::shared_ptr<std::vector<Variable>>  p1, std::shared_ptr<std::vector<ContrainteV2*>>  p2,int size);
	~Graphe();
	std::vector<std::vector<std::string>> getMatriceAdjacence(); //matrice de domaine

private:
	std::shared_ptr<std::vector<Variable>> listeVariables;
	std::shared_ptr<std::vector<ContrainteV2*>> listeContraintes;
	std::vector<std::vector<int>> matriceAdjacence;
	std::vector<std::vector<std::string>> matriceAdjacencev2;
};
