#include "Esqueleto.hpp"
#include "Jogador.hpp"
#include "GerenciadorGrafico.hpp"
#include <cstdlib>
#include <iostream>

using namespace Magisterio;
using namespace Entidades;
using namespace Personagens;

Esqueleto::Esqueleto(sf::Vector2f pos) :
    Inimigo(1),
    raio(3.f),
    velocidade((65.f + static_cast<float>(std::rand() % 45)) * ((std::rand() % 2 == 0) ? 1.f : -1.f)),
    intervaloTroca(1.2f + static_cast<float>(std::rand() % 23) * 0.1f)
{
    sf::Texture* tex = pGG->carregarTextura("assets/esqueleto.png");
    if (tex) {
        tex->setSmooth(false);
        figura = new sf::Sprite(*tex);
        float escala = 1.5f;
        figura->setScale({ escala, escala });
        largura = static_cast<float>(tex->getSize().x) * escala;
        altura = static_cast<float>(tex->getSize().y) * escala;
    }

    coordenada.setPosicao(pos);
    coordAnt.setPosicao(pos);
    if (figura)
        figura->setPosition(pos);
}

Esqueleto::~Esqueleto() = default;

void Esqueleto::executar() {
    float dt = relogioMovimento.restart().asSeconds();
    if (dt > 0.05f)
        dt = 0.05f;

    if (relogioTrocaDirecao.getElapsedTime().asSeconds() >= intervaloTroca) {
        if (std::rand() % 2 == 0)
            velocidade = -velocidade;
        intervaloTroca = 1.2f + static_cast<float>(std::rand() % 23) * 0.1f;
        relogioTrocaDirecao.restart();
    }

    sf::Vector2f pos = getCoordenada();
    pos.x += velocidade * dt;

    if (pos.x < limiteMinX) {
        pos.x = limiteMinX;
        if (velocidade < 0.f)
            velocidade = -velocidade;
    }
    else if (pos.x + largura > limiteMaxX) {
        pos.x = limiteMaxX - largura;
        if (pos.x < limiteMinX)
            pos.x = limiteMinX;
        if (velocidade > 0.f)
            velocidade = -velocidade;
    }

    setCoordenada(pos);
}

void Esqueleto::salvar() {}

void Esqueleto::danificar(Jogador* pJogador) {
    if (!pJogador)
        return;

    if (!jaCausouDano || relogioDano.getElapsedTime().asSeconds() >= 1.0f) {
        (*pJogador)--;
        jaCausouDano = true;
        relogioDano.restart();
        std::cout << "[Esqueleto] Jogador atingido pelo esqueleto! Vidas restantes: "
                  << pJogador->getNumVidas() << std::endl;
    }
}
