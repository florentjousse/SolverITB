#include "ContrainteV2.h"

ContrainteV2::ContrainteV2()
{
	v1 = Variable();

	v2 = Variable();
}

ContrainteV2::ContrainteV2(Variable _v1,std::string _op, Variable _v2)
{
	v1 = _v1;
	op = _op;
	v2 = _v2;
}

Variable ContrainteV2::getV1()
{
	return v1;
}

Variable ContrainteV2::getV2()
{
	return v2;
}

std::string ContrainteV2::returnImpossible()
{
	return op;
}

std::ostream& operator<<(std::ostream& os, const ContrainteV2& dt)
{
	os << dt.v1 << dt.v2;
	return os;
}