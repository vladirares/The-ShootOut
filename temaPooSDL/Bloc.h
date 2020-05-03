#pragma once
#include<iostream>
using namespace std;

class Bloc {
    int xPosition;
    int yPosition;
    bool hasAgent;
    int agentId;
    int type;

public:
    int getType();
    int getAgentId() const;
    void setType(int);
    void setAgentId(int);
    void setXPosition(int);
    void setYPosition(int);
    void setIsOccupied(bool);
    int getXPosition();
    int getYPosition();
    bool isOccupied() const;
};
