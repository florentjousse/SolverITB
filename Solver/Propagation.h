#pragma once
#pragma once
#include <vector>
#include "Contrainte.h"
#include "Graphe.h"
#include <iostream>
#include <queue>

class Propagation {
public :
	static void chercher(std::vector<Contrainte> listeContraintes,Graphe graphe, std::shared_ptr<std::queue<Variable*>> p1, std::vector<Variable*> ptrVariables);
private :
	static int propager(std::vector<Contrainte> listeContraintes,Variable* v1, Graphe graphe, std::shared_ptr<std::queue<Variable*>> p1, std::vector<Variable*> ptrVariables);
};
