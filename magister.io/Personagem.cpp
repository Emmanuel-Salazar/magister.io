#include "Personagem.hpp"
#include "GerenciadorGrafico.hpp"

using namespace Magisterio;
using namespace Entidades;
using namespace Personagens;

Personagem::Personagem(int vidas, float vel): 
	Entidade(),
	numVidas(vidas),
	velocidade(vel),
	velY(0.f),
	gravidade(1200.f),
	sofrendoDano(false)
{
	//sf::Texture* textura = pGG->carregarTextura("assets/personagem.png");
}

Personagem::~Personagem() = default;

void Personagem::desenhar(sf::RenderTarget& destino)
{
	if (figura) {
		if (sofrendoDano) {
			if (relogioPiscaDano.getElapsedTime().asSeconds() < 0.25f) {
				figura->setColor(sf::Color(255, 80, 80));
			}
			else {
				sofrendoDano = false;
				figura->setColor(sf::Color::White);
			}
		}
		else {
			figura->setColor(sf::Color::White);
		}
		figura->setPosition(coordenada.getPosicao());
		destino.draw(*figura);
	}
}

int Personagem::getNumVidas() const { return numVidas; }

void Personagem::setNumVidas(int vidas) { numVidas = vidas; }

float Personagem::getVelocidade() const { return velocidade; }

void Personagem::setVelocidade(float v) { velocidade = v; }

float Personagem::getVelY() const { return velY; }

void Personagem::setVelY(float v) { velY = v; }

void Personagem::operator++(int) { numVidas++; }

void Personagem::operator--(int) {
	if (numVidas > 0)
		numVidas--;
	sofrendoDano = true;
	relogioPiscaDano.restart();
}

float Personagem::getRaio() const { return largura / 2.f; }