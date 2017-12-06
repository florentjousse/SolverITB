#pragma once
#include "Variable.h"

class ContrainteV2 {
public:
	ContrainteV2();
	ContrainteV2(Variable _v1,std::string _op, Variable _v2);
	Variable getV1();
	Variable getV2();
	std::string returnImpossible();

protected:
	std::vector<double> toDel;
	Variable v1;
	Variable v2;
	std::string op;
private:
	friend std::ostream& operator<<(std::ostream& os, const ContrainteV2& dt);
};