#include "ObjectManager.h"

vector<Agent*>  ObjectManager::getAgents() {
	return Agents;
}

void ObjectManager::pushAgent(Agent* agent) {
	Agents.push_back(agent);
}

void ObjectManager::setAgents(vector<Agent*> agenti) {
	this->Agents = agenti;
}