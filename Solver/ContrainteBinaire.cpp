#include "ContrainteBinaire.h"



ContrainteBinaire::ContrainteBinaire(Variable _v1, std::string _op, Variable _v2)
{
	v1 = _v1;
	op = _op;
	v2 = _v2;
}

std::string ContrainteBinaire::returnImpossible()
{
	return op;
}
Variable ContrainteBinaire::getV1()
{
	return v1;
}

Variable ContrainteBinaire::getV2()
{
	return v2;
}
ContrainteBinaire::~ContrainteBinaire()
{
}
