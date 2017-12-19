#pragma once
#pragma once
#include <vector>
#include "ContrainteV2.h"
#include "Graphe.h"
#include <iostream>
#include <queue>
#include <memory>
#include <utility>
class Propagation {
public :
	static int backtrack(std::vector<Variable> unlabelled, std::vector<Variable>labelled, std::vector<Variable> *ptListeVariables, std::vector<ContrainteV2*> listeContraintes, Graphe graphe, std::shared_ptr<std::queue<Variable*>> p1, std::vector<Variable*> ptrVariables, int nombreVars);
	static std::vector<Variable> push_back(std::vector<Variable> vec, Variable v);
	static std::vector<Variable> pop_back(std::vector<Variable> vec);
	static int consistant(std::vector<Variable> labelled, Graphe graphe, int nombreVars);
	void chercher2(std::vector<ContrainteV2*> listeContraintes, Graphe graphe, std::shared_ptr<std::queue<Variable*>> p1, std::vector<Variable*> ptrVariables, int nombreVars);
	static int forwardCheckingAC3(Variable * var1, std::vector<Variable> *listeVariables, std::vector<ContrainteV2*> listeContraintes);
	static int backtrackAC3(std::vector<Variable> unlabelled, std::vector<Variable> labelled, std::vector<Variable>* ptListeVariables, std::vector<ContrainteV2*> listeContraintes, Graphe graphe,  std::vector<Variable*> ptrVariables, int nombreVars);
	static bool reviser(Variable *var1, Variable *var2, std::string contrainte, std::vector<Variable> *listVariables);
	static void resetTool(std::vector<ContrainteV2*> listeContraintes);
private :
	static int propager(std::vector<ContrainteV2*> listeContraintes,Variable* v1, Graphe graphe, std::shared_ptr<std::queue<Variable*>> p1, std::vector<Variable*> ptrVariables, int nombreVars,int flag);
	static void clear(std::shared_ptr<std::queue<Variable*>> q);
	static void print_queue(std::queue<Variable*> q);
};

