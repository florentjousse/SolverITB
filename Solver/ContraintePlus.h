#pragma once
#include "Contrainte.h"

class ContraintePlus : public Contrainte {
public :
	ContraintePlus();
	ContraintePlus(Variable _v1, Variable _v2,double _plusValue);
//TODO plusValue en public pour debuggage
private:
};