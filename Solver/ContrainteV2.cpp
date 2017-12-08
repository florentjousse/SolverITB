#include "ContrainteV2.h"



Variable ContrainteV2::getV1()
{
	return v1;
}

Variable ContrainteV2::getV2()
{
	return v2;
}


std::ostream& operator<<(std::ostream& os, const ContrainteV2& dt)
{
	os << dt.v1 << dt.v2;
	return os;
}

std::string ContrainteV2::returnImpossible()
{
	return std::string();
}
