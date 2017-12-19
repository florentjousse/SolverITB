#pragma once
#include "ContrainteV2.h"
class ContrainteBinaire :
	public ContrainteV2
{
public:
		Variable* getV1();
	   Variable* getV2();
	   std::string returnImpossible();

	ContrainteBinaire(Variable *_v1, std::string _op, Variable *_v2);
	~ContrainteBinaire();
};

