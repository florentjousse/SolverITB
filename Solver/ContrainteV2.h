#pragma once
#include "Variable.h"

class ContrainteV2 {
public:
	/*ContrainteV2();
	ContrainteV2(Variable _v1,std::string _op, Variable _v2);*/
	virtual Variable* getV1();
	virtual Variable* getV2();
	virtual std::string returnImpossible();

protected:
	std::vector<int> toDel;
	Variable *v1;
	Variable *v2;
	std::string op;
private:
	friend std::ostream& operator<<(std::ostream& os, const ContrainteV2& dt);
};