#include "Goblin.hpp"
#include "Jogador.hpp"
#include "GerenciadorGrafico.hpp"
#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace Magisterio;
using namespace Entidades;
using namespace Personagens;

Goblin::Goblin(sf::Vector2f pos) :
    Inimigo(2, 45.f + static_cast<float>(std::rand() % 20))
{
    sf::Texture* tex = pGG->carregarTextura("assets/goblin.png");
    if (tex) {
        tex->setSmooth(false);
        this->figura = new sf::Sprite(*tex);
        float escala = 1.8f;
        figura->setScale({ escala, escala });
        largura = static_cast<float>(tex->getSize().x) * escala;
        altura = static_cast<float>(tex->getSize().y) * escala;
    }

    coordenada.setPosicao(pos);
    coordAnt.setPosicao(pos);
    if (figura)
        figura->setPosition(pos);
}

Goblin::~Goblin() = default;

void Goblin::perseguir() {
    float dt = relogioMovimento.restart().asSeconds();
    if (dt > 0.05f)
        dt = 0.05f;

    sf::Vector2f posGoblin = getCoordenada();

    if (pAlvo) {
        sf::Vector2f posAlvo = pAlvo->getCoordenada();
        float dx = posAlvo.x - posGoblin.x;

        if (dx > 8.f) {
            posGoblin.x += velocidade * dt;
        }
        else if (dx < -8.f) {
            posGoblin.x -= velocidade * dt;
        }
    }

    // Gravidade
    velY += gravidade * dt;
    posGoblin.y += velY * dt;

    if (posGoblin.x < 10.f)
        posGoblin.x = 10.f;
    else if (posGoblin.x + largura > 790.f)
        posGoblin.x = 790.f - largura;

    if (posGoblin.y + altura >= 585.f) {
        posGoblin.y = 585.f - altura;
        velY = 0.f;
    }

    setCoordenada(posGoblin);
}

void Goblin::executar() {
    perseguir();
}

void Goblin::salvar() {}

void Goblin::danificar(Jogador* pJogador) {
    if (!pJogador)
        return;

    if (!jaCausouDano || relogioDano.getElapsedTime().asSeconds() >= 1.0f) {
        (*pJogador)--;
        jaCausouDano = true;
        relogioDano.restart();
        std::cout << "[Goblin] Jogador atingido pelo goblin! Vidas restantes: "
                  << pJogador->getNumVidas() << std::endl;
    }
}
