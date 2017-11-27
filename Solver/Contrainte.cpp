#include "Contrainte.h"

Contrainte::Contrainte(Variable _v1, Variable _v2)
{
	v1 = _v1;
	v2 = _v2;
}
Variable Contrainte::getV1()
{
	return v1;
}
Variable Contrainte::getV2()
{
	return v2;
}
std::ostream& operator<<(std::ostream& os, const Contrainte& dt)
{
	os << dt.v1 << dt.v2;
	return os;
}