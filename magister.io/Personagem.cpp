#include "Personagem.hpp"
#include "GerenciadorGrafico.hpp"

using namespace Magisterio;
using namespace Entidades;
using namespace Personagens;

Personagem::Personagem(int vidas): 
	Entidade(),
	numVidas(vidas)
{
	//sf::Texture* textura = pGG->carregarTextura("assets/personagem.png");
}

Personagem::~Personagem() = default;

void Personagem::desenhar(sf::RenderTarget& destino)
{
	if (figura) {
		figura->setPosition(coordenada.getPosicao());
		destino.draw(*figura);
	}
}

int Personagem::getNumVidas() const { return numVidas; }

void Personagem::setNumVidas(int vidas) { numVidas = vidas; }

void Personagem::operator++(int) { numVidas++; }

void Personagem::operator--(int) { numVidas--; }

float Personagem::getRaio() const { return largura / 2.f; }