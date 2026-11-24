#include "Gelo.hpp"
#include "Jogador.hpp"
#include "GerenciadorGrafico.hpp"

using namespace Magisterio;
using namespace Entidades;
using namespace Obstaculos;
using namespace Personagens;

Gelo::Gelo(sf::Vector2f pos, float coefAtrito) : 
    Obstaculo(),
    atrito(coefAtrito)
{
    danoso = false;

    sf::Texture* tex = pGG->carregarTextura("assets/gelo.png");
    if (!tex) {
        tex = pGG->carregarTextura("assets/plataforma.png");
    }

    if (tex) {
        figura = new sf::Sprite(*tex);
        float escala = 0.35f;
        if (tex->getSize().x <= 64) {
            escala = 2.5f;
        }
        largura = static_cast<float>(tex->getSize().x) * escala;
        altura = static_cast<float>(tex->getSize().y) * escala;
        figura->setScale({ escala, escala });
    }
    coordenada.setPosicao(pos);
    if (figura)
        figura->setPosition(pos);
}

Gelo::~Gelo() = default;

void Gelo::obstaculizar() {}

void Gelo::obstaculizar(Jogador* pJogador) {
    if (pJogador) {
        pJogador->setVelocidade(pJogador->getVelocidadePadrao() * atrito);
    }
}

float Gelo::getAtrito() const {
    return atrito;
}

void Gelo::setAtrito(float coef) {
    atrito = coef;
}
