#include "Propagation.h"
#include "boost\any.hpp"
#include <regex>
#include <stack>

int Propagation::backtrack(std::vector<Variable> unlabelled, std::vector<Variable>labelled, std::vector<Variable> *ptListeVariables, std::vector<ContrainteV2*> listeContraintes, Graphe graphe, std::shared_ptr<std::queue<Variable*>> p1, std::vector<Variable*> ptrVariables, int nombreVars)
{
	if (unlabelled.size() == 0)
	{/*
		std::cout << "\nsolution trouvee";
		for (auto i : labelled) {
			std::cout << "\nvar[" << i.getIndice()+1 << "]=" << i.getLabel();
		}*/
		return 1;
		//system("pause");
	}
	else {
		Variable v2 = unlabelled.at(unlabelled.size() - 1);
		for (auto i : v2.getDomaine()) {
			v2.setLabel(i);
		
			//std::cout << "var[" << v2.getIndice() + 1 << "] = " << i << std::endl;
			if (consistant(push_back(labelled, v2), graphe, nombreVars)) {
				//	std::cout << "consistant";
				int r = backtrack(pop_back(unlabelled), push_back(labelled, v2), ptListeVariables, listeContraintes, graphe, p1, ptrVariables, nombreVars);
				if (r != 0) {
					return r;
				}
			}
		}
	}
	
//	std::cout << "backtrack -------------------------------------\n";
	
	return 0;
}

std::vector<Variable> Propagation::push_back(std::vector<Variable> vec,Variable v) {
	
	vec.push_back(v);

	return vec;
}
std::vector<Variable> Propagation::pop_back(std::vector<Variable> vec) {
	std::vector<Variable> res;
	vec.pop_back();
	res = vec;
	return res;
}
int Propagation::consistant(std::vector<Variable> labelled, Graphe graphe, int nombreVars) {
	std::regex pattern1("!=-.");
	std::regex pattern2("!=\\+.");
	std::regex pattern3(">");
	std::regex pattern4("<");
	std::regex pattern5(" !=");
	std::smatch sm1;
	std::smatch sm2;
	std::smatch sm3;
	std::smatch sm4;
	std::smatch sm5;
	int size = labelled.size();
	for (auto var1 : labelled) {
		for (auto var2 : labelled) {
			if (var1.getIndice() != var2.getIndice()) {
				std::string str = graphe.getMatriceAdjacence().at(var2.getIndice()).at(var1.getIndice());
				if (std::regex_search(str, sm5, pattern5)) {// case !=
					if (var2.getLabel() == var1.getLabel())
						return false; //
				}
				if (std::regex_search(str, sm3, pattern3)) { // case" >
					if (var2.getLabel() > var1.getLabel())
						return false;
				}
				if (std::regex_search(str, sm4, pattern4)) {//case <
					if (var2.getLabel() < var1.getLabel())
						return false;
				}
				if (std::regex_search(str, sm1, pattern1)) {//case"x!=y-b"
					std::string str1 = sm1[0];
					str1.erase(0, 3);
					if (var2.getLabel() == var1.getLabel() - std::stoi(str1))
						return false; //

				}
				if (std::regex_search(str, sm2, pattern2)) {//case"x!=y+b"
					std::string str2 = sm2[0];
					str2.erase(0, 3);
					if (var2.getLabel() == var1.getLabel() + std::stoi(str2))
						return false; //
				}
			}
		}
	}
	return 1;

}

void Propagation::chercher2(std::vector<ContrainteV2*> listeContraintes,Graphe graphe, std::shared_ptr<std::queue<Variable*>> p1,std::vector<Variable*> ptrVariables,int nombreVars)

{	
	int count = 0;
	int woua = 0;
	int flag = 0;
	std::vector<int> valTests(nombreVars);
	std::stack<Variable*> stackBacktrk;
	Variable *precV1 = NULL;
	Variable* v1 =NULL;
	while (p1.get()->size() != 0) {
		flag = 0;
		print_queue(*p1.get());
		precV1 = v1;
		v1 = p1.get()->front();
		//v1 = stackBacktrk.top();
		valTests.at(v1->getIndice()) = v1->getFirstEV();//first elem of domain
		p1.get()->front()->resetMarqueur();// Flag if the variable is in queue
		std::cout << "\n";
		v1->reduireDomaine(valTests.at(v1->getIndice()), 2);
		for (auto i : ptrVariables)
			if (i != v1) {
				i->pushBackn();
			}
		/*while(i!=nombreVars){
			if (graphe.getMatriceAdjacence().at(i).at(v1->getIndice()) != "") {
				ptrVariables.at(i)->pushBackn();
			}
			i++;
		}*/
		count++;
		//	std::cout << "variable :["<<v1->getIndice() + 1 << "] = ";
		
	etiq1:
		stackBacktrk.push(v1);
		v1->printDomaine();
		v1->printDelta();
		if (propager(listeContraintes, v1, graphe, p1, ptrVariables, nombreVars,flag) == false) {
			v1 = stackBacktrk.top();
			flag++;
			//p1.get()->pop();
			//v1->resetMarqueur();
			
			std::cout << "===============>backtrack vers [" <<v1->getIndice()+1<< "]\n";
			stackBacktrk.pop();
			for (auto k : ptrVariables) {
				k->printDomaine();
				k->printDelta();
				k->resetDelta();
				k->printDomaine();
				k->printDelta();
			}
			int e = 0;
			while (valTests.at(v1->getIndice()) != v1->getElemDomain(e)) {
				e++;
			}
			e++;

			valTests.at(v1->getIndice()) = v1->getElemDomain(e);

			v1->reduireDomaine(valTests.at(v1->getIndice()), 2);
			print_queue(*p1.get());
			/*for (int i = ptrVariables.size() - 1; i >= v1->getIndice(); i--) {
				//std::cout << "domaine:\n";
				ptrVariables.at(i)->printDomaine();


				ptrVariables.at(i)->printDelta();
				for (auto i : ptrVariables.at(i)->getDelta().back()) {
					ptrVariables.at(i)->addToDomaine(i);
				}

				std::cout << "nouveau domaine:\n";
				ptrVariables.at(i)->printDomaine();
				std::cout << "\n";
			}*/
			count = 0;
			goto etiq1;
		}

		else {
			/*if (flag == 0) {
				v1->resetMarqueur();
				p1.get()->pop();
			}*/
			
		}
		if (count == nombreVars) {
			std::cout << "FIN : RESULTAT / \n";
			for (auto i : ptrVariables) {
				std::cout << "var[" << i->getIndice() + 1 << "]=" << i->getFirstEV() << "\n";
			}
			break;
		}
	}
	std::cout << "\nFIN : PAS DE RESULTAT / \n";
}


int Propagation::propager(std::vector<ContrainteV2*> listeContraintes, Variable* v1, Graphe graphe, std::shared_ptr<std::queue<Variable*>> p1, std::vector<Variable*> ptrVariables, int nombreVars,int flag)
//Coupe les domaines de toutes les variables en contrainte avec v1 et renvoie faux si un domaine est vidé
{
	std::cout << "=================>propagation<======== \n";
	std::regex pattern1("!=-." );
	std::regex pattern2("!=\\+.");
	std::regex pattern3(">");
	std::regex pattern4("<");
	std::regex pattern5(" !=");
	std::smatch sm1;
	std::smatch sm2;
	std::smatch sm3;
	std::smatch sm4;
	std::smatch sm5;
	
	for (int i = 0; i < nombreVars; i++) {

			std::string str = graphe.getMatriceAdjacence().at(i).at(v1->getIndice());
			if (std::regex_search(str, sm5, pattern5)) {// case !=
				ptrVariables.at(i)->reduireDomaine(v1->getFirstEV(), 1);

			}
			if (std::regex_search(str, sm3, pattern3)) { // case" >
														 //ptrVariables.at(i)->resetDelta();
				int aoi = 0;//
				for (int itt = 0; itt < ptrVariables.at(i)->sizeDomaine() + aoi; itt++) {
					if (ptrVariables.at(i)->getElemDomain(itt - aoi) >= v1->getFirstEV()) {
						ptrVariables.at(i)->reduireDomaine(ptrVariables.at(i)->getElemDomain(itt - aoi), 1);
						aoi++;
					}
				}
			}
			if (std::regex_search(str, sm4, pattern4)) {//case <
				int aoi = 0;//
				for (int itt = 0; itt < ptrVariables.at(i)->sizeDomaine() + aoi; itt++) {
					if (ptrVariables.at(i)->getElemDomain(itt - aoi) <= v1->getFirstEV()) {
						ptrVariables.at(i)->reduireDomaine(ptrVariables.at(i)->getElemDomain(itt - aoi), 1);
						aoi++;
					}
				}
			}
			if (std::regex_search(str, sm1, pattern1)) {//case"x!=y-b"
				std::string str1 = sm1[0];
				str1.erase(0, 3);
				ptrVariables.at(i)->reduireDomaine(v1->getFirstEV() - std::stoi(str1), 1);

			}
			if (std::regex_search(str, sm2, pattern2)) {//case"x!=y+b"
				std::string str2 = sm2[0];
				str2.erase(0, 3);
				ptrVariables.at(i)->reduireDomaine(v1->getFirstEV() + std::stoi(str2), 1);
			}
		ptrVariables.at(i)->printDomaine();
		ptrVariables.at(i)->printDelta();
		
		
		if (ptrVariables.at(i)->sizeDomaine() == 0) {
			return 0;
		}
	}
	return 1;
}
void Propagation::clear(std::shared_ptr<std::queue<Variable*>> q)
{
	while (q.get()->size()) {
		q.get()->pop();
	}
}

void Propagation::print_queue(std::queue<Variable*> q)
{
	while (!q.empty())
	{
		std::cout <<" var [" <<q.front()->getIndice()+1 << "] ";
		q.pop();
	}
	std::cout << std::endl;
}


int Propagation::backtrackAC3(std::vector<Variable> unlabelled, std::vector<Variable>labelled, std::vector<Variable> *ptListeVariables, std::vector<ContrainteV2*> listeContraintes, Graphe graphe,  std::vector<Variable*> ptrVariables, int nombreVars)
{

	if (unlabelled.size() == 0)
	{
		/*std::cout << "\nsolution trouvee";
		for (auto i : labelled) {
			std::cout << "\nvar[" << i.getIndice() + 1 << "]=" << i.getLabel();
		}*/
		return 1;
		//system("pause");
	}
	else {
		Variable v2 = unlabelled.at(unlabelled.size() - 1);
		for (auto i : v2.getDomaine()) {
			v2.setLabel(i);
		    //std::cout << "\nvar[" << v2.getIndice() + 1 << "] = " << i << std::endl;
			std::vector<Variable> copyUnlabelled = unlabelled;
			Variable copyV2 = v2;
			copyV2.reduireDomaine(i, 2);
			if (forwardCheckingAC3(&copyV2, &copyUnlabelled, listeContraintes)) {
				//	std::cout << "consistant";
				int r = backtrackAC3(pop_back(copyUnlabelled), push_back(labelled, v2), ptListeVariables, listeContraintes, graphe,ptrVariables, nombreVars);
				if (r != 0) {
					return r;
				}
			}
		}
	}
	resetTool(listeContraintes);
	return 0;
}

int Propagation::forwardCheckingAC3(Variable *var1, std::vector<Variable> *listeVariables, std::vector<ContrainteV2*> listeContraintes) {
	std::queue<ContrainteV2*> _queue;
	for (auto contrainte : listeContraintes) {
		if (contrainte->getV2()->getIndice() == var1->getIndice() && contrainte->getV1()->getIndice() > var1->getIndice())
			_queue.push(contrainte);
	}
	int consistent = 1;
	ContrainteV2 *cc;
	while (_queue.size() != 0 && consistent) {
		//select and delete any arc (xj,xi) from Q
		cc = _queue.front();
		_queue.pop();
		if (reviser(cc->getV1(),var1, cc->returnImpossible(),listeVariables)) {
			consistent = cc->getV1()->sizeDomaine();
		}
		int itt = 0;
		while (listeVariables->at(itt).getIndice() != cc->getV1()->getIndice()) {
			itt++;
		}
		for (auto hash : cc->getV1()->getDelta()) {
			listeVariables->at(itt).reduireDomaine(hash, 1);
		}

	}
	return consistent;
}



bool Propagation::reviser(Variable *var1, Variable *var2, std::string contrainte,std::vector<Variable> *listeVariables) {
	
	std::regex pattern1("!=-.");
	std::regex pattern2("!=\\+.");
	std::regex pattern3(">");
	std::regex pattern4("<");
	std::regex pattern5("!=");
	std::smatch sm1;
	std::smatch sm2;
	std::smatch sm3;
	std::smatch sm4;
	std::smatch sm5;
	bool retraitValeur = false;
	for (auto i : var1->getDomaine()) {
		bool trouveSupport = false;
			for (auto j : var2->getDomaine()) {
				if (std::regex_match(contrainte, sm5, pattern5)) {// case !=
					if (i != j) {
						trouveSupport = true; //TODO add break maybe
					}
				}
				if (std::regex_search(contrainte, sm3, pattern3)) { // case" >
					if (i > j)
						trouveSupport = true;
				}
				if (std::regex_search(contrainte, sm4, pattern4)) {//case <
					if (i < j)
						trouveSupport = true;
				}
				if (std::regex_search(contrainte, sm1, pattern1)) {//case"x!=y-b"
					std::string str1 = sm1[0];
					str1.erase(0, 3);
					if (i != j - std::stoi(str1))
						trouveSupport = true;  //

				}
				if (std::regex_search(contrainte, sm2, pattern2)) {//case"x!=y+b"
					std::string str2 = sm2[0];
					str2.erase(0, 3);
					if (i != j + std::stoi(str2))
						trouveSupport = true;  //
				}
			}
			if (trouveSupport == false) {
				var1->reduireDomaine(i, 1);
				retraitValeur = true;
		
			}
	}
	return retraitValeur;
	
}
//TODO 
void Propagation::resetTool(std::vector<ContrainteV2*> listeContraintes) {
	for (auto i : listeContraintes) {
		i->getV1()->resetDelta();
		i->getV2()->resetDelta();
	}
}