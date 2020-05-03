#pragma once
#include "Agent.h"
#include <vector>
using namespace std;

class ObjectManager
{
	vector<Agent*> Agents;
public:
	vector<Agent*> getAgents();
	void setAgents(vector<Agent*>);
	void pushAgent(Agent*);
};
