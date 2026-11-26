#include "Plataforma.hpp"
#include "GerenciadorGrafico.hpp"

using namespace Magisterio;
using namespace Entidades;
using namespace Obstaculos;

Plataforma::Plataforma(sf::Vector2f pos) : Obstaculo() {
	danoso = false;

    sf::Texture* tex = carregarTextura("assets/plataforma.png");
    if (tex) {
        figura = new sf::Sprite(*tex);
        largura = static_cast<float>(tex->getSize().x); // 64px
        altura = static_cast<float>(tex->getSize().y);  // 14px
		//para aumentar o tamanho da plataforma 
        figura->setScale({ 2.5f, 2.5f });
        largura *= 2.5f;
        altura *= 2.5f;
    }
    coordenada.setPosicao(pos);
    if (figura)
        figura->setPosition(pos);
}

Plataforma::~Plataforma() = default;

void Plataforma::obstaculizar() {}

void Plataforma::obstaculizar(Personagens::Jogador* pJogador) {}
