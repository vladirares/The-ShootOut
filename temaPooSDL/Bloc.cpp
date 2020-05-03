#include "Bloc.h"

void Bloc::setXPosition(int xPosition) {
    this->xPosition = xPosition;
}

void Bloc::setYPosition(int yPosition) {
    this->yPosition = yPosition;
}

int Bloc::getXPosition() {
    return xPosition;
}

int Bloc::getYPosition() {
    return yPosition;
}

int Bloc::getAgentId() const{
    return agentId;
}

bool Bloc::isOccupied() const{
    return hasAgent;
}

int Bloc::getType() {
    return type;
}

void Bloc::setType(int x) {
    type = x;
}

void Bloc::setAgentId(int x) {
    agentId = x;
}

void Bloc::setIsOccupied(bool x) {
    hasAgent = x;
}