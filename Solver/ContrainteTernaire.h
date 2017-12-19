#pragma once
#include "ContrainteV2.h"
#include <string>
class ContrainteTernaire :
	public ContrainteV2
{
public:
	ContrainteTernaire::ContrainteTernaire(Variable *_v1, std::string _op, Variable *_v2, std::string _op2, Variable _v3);
	~ContrainteTernaire();
	std::string returnImpossible();
private:
	Variable v3;
	std::string op2;
};

