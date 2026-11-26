#include "Lava.hpp"
#include "Jogador.hpp"
#include "GerenciadorGrafico.hpp"
#include <cmath>
#include <cstdint>
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

    sf::Texture* tex = carregarTextura("assets/lava.png");
    if (!tex) {
        tex = carregarTextura("assets/plataforma.png");
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

void Lava::executar() {
    Obstaculo::executar();
    if (figura) {
        float t = relogioMovimento.getElapsedTime().asSeconds();
        float pulso = 0.5f + 0.5f * std::sin(t * 4.5f);
        std::uint8_t verde = static_cast<std::uint8_t>(185.f + 70.f * pulso);
        std::uint8_t azul = static_cast<std::uint8_t>(155.f + 75.f * pulso);
        figura->setColor(sf::Color(255, verde, azul));
    }
}

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
