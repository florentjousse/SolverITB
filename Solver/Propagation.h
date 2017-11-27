#pragma once
#include <vector>
#include "Contrainte.h"
#include "Graphe.h"
#include <iostream>
class Propagation {
public :
	static void chercher(std::vector<Contrainte> listeContraintes, Graphe graphe);
private :
	void propager();
};
