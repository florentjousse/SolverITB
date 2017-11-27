#pragma once
#include "Variable.h"

class Contrainte {
public:
	Contrainte(Variable _v1, Variable _v2);
	Variable getV1();
	Variable getV2();
private:
	//v1 != v2 pour l'instant unique contrainte possible
	Variable v1;
	Variable v2;
	friend std::ostream& operator<<(std::ostream& os, const Contrainte& dt);
};