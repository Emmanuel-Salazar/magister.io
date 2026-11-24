#include "Ente.hpp"
#include "GerenciadorGrafico.hpp"
using namespace Magisterio;
using namespace Gerenciadores;

Gerenciadores::GerenciadorGrafico* Ente::pGG = nullptr;
int Ente::cont = 0;

Ente::Ente():
	id(cont++),
	figura(nullptr)
{
	
}

Ente::~Ente(){
	delete figura;
	figura = nullptr;
}

void Ente::setGG(Gerenciadores::GerenciadorGrafico* p) { pGG = p; }

void Ente::desenhar() {
	if (pGG && figura)
		pGG->desenharEnte(this);

}

sf::Sprite* Ente::getFigura()
{
	return figura;
}

void Ente::desenhar(sf::RenderTarget& destino) {
	if (figura) {
		figura->setPosition(coordenada.getPosicao());
		destino.draw(*figura);
	}
}

sf::Vector2f Ente::getCoordenada() const
{
	return coordenada.getPosicao();
}

void Ente::setCoordenada(sf::Vector2f novaCoordenada)
{
	coordAnt.setPosicao(coordenada.getPosicao());
	coordenada.setPosicao(novaCoordenada);

	if (figura)
		figura->setPosition(novaCoordenada);
}

sf::Vector2f Ente::getCoordAnt() const
{
	return coordAnt.getPosicao();
}