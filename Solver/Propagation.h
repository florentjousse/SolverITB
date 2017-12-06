#pragma once
#pragma once
#include <vector>
#include "Contrainte.h"
#include "Graphe.h"
#include <iostream>
#include <queue>
#include <memory>
#include <utility>
class Propagation {
public :
	static void chercher(std::vector<Contrainte> listeContraintes,Graphe graphe, std::shared_ptr<std::queue<Variable*>> p1, std::vector<Variable*> ptrVariables,int nombreVars);
private :
	static int propager(std::vector<Contrainte> listeContraintes,Variable* v1, Graphe graphe, std::shared_ptr<std::queue<Variable*>> p1, std::vector<Variable*> ptrVariables, int nombreVars);
	static void clear(std::shared_ptr<std::queue<Variable*>> q);
};

