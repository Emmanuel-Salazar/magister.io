#include "Fase.hpp"
#include "GerenciadorGrafico.hpp"
#include "Jogador.hpp"
using namespace Magisterio;
using namespace Fases;
using namespace Entidades;
using namespace Personagens;

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

void Fase::desenhar() 
{
    Ente::desenhar();
    if (pGG && pGG->getJanela()) 
    {
        pGG->getJanela()->draw(chao); 
        
        int i;
        for (i =0; i < entidades.tamanho(); i++) 
        {
            auto* ent = entidades[i];
            if (ent)
                pGG->desenharEnte(ent);
        }
    }
}

void Fase::setJogador(Jogador* pJ) 
{
    pJ1 = pJ;
    gc.setJogador1(pJ);
}

Listas::ListaEntidades& Fase::getEntidades() { return entidades; }

