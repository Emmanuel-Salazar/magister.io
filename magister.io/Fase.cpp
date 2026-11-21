#include "Fase.hpp"
#include "GerenciadorGrafico.hpp"
using namespace Magisterio;
using namespace Fases;

Fase::Fase() : Ente() {
	criarCenario();
}
Fase::~Fase() = default;

void Fase::executar() {}

void Fase::criarCenario() {
    chao.setSize(sf::Vector2f(800.f, 30.f));
    sf::Color blue(27, 14, 10, 255);
    chao.setFillColor(blue);
    chao.setPosition(sf::Vector2f(0.f, 585.f));
}

void Fase::desenhar() {
    Ente::desenhar();
    if (pGG && pGG->getJanela()) {
        pGG->getJanela()->draw(chao); 
        for (auto* ent : entidades.obter()) 
            if(ent)
				ent->desenhar(*pGG->getJanela());
    }
}

Listas::ListaEntidades& Fase::getEntidades() { return entidades; }

