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
    velocidade(65.f + static_cast<float>(std::rand() % 45)),
    direcao((std::rand() % 2 == 0) ? 1 : -1),
    intervaloTroca(1.2f + static_cast<float>(std::rand() % 23) * 0.1f)
{
    sf::Texture* tex = pGG->carregarTextura("assets/esqueleto.png");
    if (tex) {
        tex->setSmooth(false);
        figura = new sf::Sprite(*tex);
        float escala = 1.5f;
        float texW = static_cast<float>(tex->getSize().x);
        float texH = static_cast<float>(tex->getSize().y);
        largura = texW * escala;
        altura = texH * escala;
        if (direcao >= 0) {
            figura->setOrigin({ 0.f, 0.f });
            figura->setScale({ escala, escala });
        }
        else {
            figura->setOrigin({ texW, 0.f });
            figura->setScale({ -escala, escala });
        }
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
        direcao = (std::rand() % 2 == 0) ? 1 : -1;
        intervaloTroca = 1.2f + static_cast<float>(std::rand() % 23) * 0.1f;
        relogioTrocaDirecao.restart();
    }

    sf::Vector2f pos = getCoordenada();
    pos.x += static_cast<float>(direcao) * velocidade * dt;

    if (pos.x < 10.f) {
        pos.x = 10.f;
        direcao = 1;
    }
    else if (pos.x + largura > 790.f) {
        pos.x = 790.f - largura;
        direcao = -1;
    }

    if (figura) {
        float escala = 1.5f;
        float texW = static_cast<float>(figura->getTexture().getSize().x);
        if (direcao >= 0) {
            figura->setOrigin({ 0.f, 0.f });
            figura->setScale({ escala, escala });
        }
        else {
            figura->setOrigin({ texW, 0.f });
            figura->setScale({ -escala, escala });
        }
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
