#include "Personagem.hpp"

using namespace Magisterio;
using namespace Entidades;
using namespace Personagens;

Personagem::Personagem() : numVidas(0), forma(sf::CircleShape(24.f))
{
}
Personagem::~Personagem() = default;

void Personagem::desenhar(sf::RenderTarget& destino)
{
	destino.draw(forma);
}

sf::Vector2f Personagem::getPosicao() const { return forma.getPosition(); }

void Personagem::setPosicao(sf::Vector2f posicao) { forma.setPosition(posicao); }


float Personagem::getRaio() const { return forma.getRadius(); }


int Personagem::getNumVidas() const { return numVidas; }

void Personagem::setNumVidas(int vidas) { numVidas = vidas; }

