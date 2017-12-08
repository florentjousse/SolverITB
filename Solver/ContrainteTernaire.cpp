#include "ContrainteTernaire.h"



ContrainteTernaire::ContrainteTernaire(Variable _v1, std::string _op, Variable _v2, std::string _op2, Variable _v3)
{
	v1 = _v1;
	op = _op;
	v2 = _v2;
	op2 = _op2;
	v3 = _v3;
}


ContrainteTernaire::~ContrainteTernaire()
{

}

std::string ContrainteTernaire::returnImpossible()
{
	std::string str2 = std::to_string(v2.getFirstEV());
	std::string str = "z"+op + op2 + str2;
	return str;
}