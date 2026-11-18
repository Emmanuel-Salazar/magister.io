#include "Fase.hpp"

using namespace Magisterio;
using namespace Fases;

Fase::Fase(int numero) : Ente() {}
Fase::~Fase() = default;

void Fase::executar() {}

void Fase::criarCenario() {
    chao.setSize(sf::Vector2f(1280, 15));
    sf::Color blue(27, 14, 10, 255);
    chao.setFillColor(blue);
    chao.setPosition(sf::Vector2f(0, 710));
}

Listas::ListaEntidades& Fase::getEntidades() { return entidades; }

