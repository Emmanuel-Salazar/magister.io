#include "Coordenada.hpp"

using namespace Magisterio;

Coordenada::Coordenada() {
    this->x = 0;
    this->y = 0;
}

Coordenada::Coordenada(int x, int y) {
    this->x = x;
    this->y = y;
}

int Coordenada::getX() {
    return this->x;
}

int Coordenada::getY() {
    return this->y;
}

void Coordenada::setX(int x) {
    this->x = x;
}

void Coordenada::setY(int y) {
    this->y = y;
}

Coordenada::~Coordenada() {
    this->x = -1;
    this->y = -1;
}