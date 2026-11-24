#include "Lava.hpp"
#include "Jogador.hpp"
#include "GerenciadorGrafico.hpp"
#include <iostream>

using namespace Magisterio;
using namespace Entidades;
using namespace Obstaculos;
using namespace Personagens;

Lava::Lava(sf::Vector2f pos, short dano) : 
    Obstaculo(),
    danosidade(dano)
{
    danoso = true;
    solido = false;

    sf::Texture* tex = pGG->carregarTextura("assets/lava.png");
    if (!tex) {
        tex = pGG->carregarTextura("assets/plataforma.png");
    }

    if (tex) {
        figura = new sf::Sprite(*tex);
        float escala = 0.11f;
        if (tex->getSize().x <= 64) {
            escala = 0.8f;
        }
        largura = static_cast<float>(tex->getSize().x) * escala;
        altura = static_cast<float>(tex->getSize().y) * escala;
        figura->setScale({ escala, escala });
    }
    coordenada.setPosicao(pos);
    if (figura)
        figura->setPosition(pos);
}

Lava::~Lava() = default;

void Lava::obstaculizar() {}

void Lava::obstaculizar(Jogador* pJogador) {
    if (pJogador && relogioDano.getElapsedTime().asSeconds() >= 1.0f) {
        for (short i = 0; i < danosidade; i++) {
            (*pJogador)--;
        }
        relogioDano.restart();
        std::cout << "[Lava] Jogador sofreu dano da lava! Vidas restantes: " 
                  << pJogador->getNumVidas() << std::endl;
    }
}

short Lava::getDanosidade() const {
    return danosidade;
}

void Lava::setDanosidade(short valor) {
    danosidade = valor;
}
