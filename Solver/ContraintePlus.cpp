#include "ContraintePlus.h"

ContraintePlus::ContraintePlus()
{
	v1 = Variable();
	v2 = Variable();
	plusValue = NULL;
}

ContraintePlus::ContraintePlus(Variable _v1, Variable _v2,double _plusValue)
{
	v1 = _v1;
	v2 = _v2;
	plusValue = _plusValue;
}
