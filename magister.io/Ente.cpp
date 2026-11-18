#include "Ente.hpp"
#include "GerenciadorGrafico.hpp"

using namespace Magisterio;
using namespace Gerenciadores;

GerenciadorGrafico* Ente::pGG = nullptr;

Ente::Ente(int i):
	forma(sf::Vector2f(24.f, 24.f)),
	id(i),
	largura(1),
	altura(1)
{
}

Ente::~Ente(){}

void Ente::setGG(Gerenciadores::GerenciadorGrafico* gerenciadorGrafico)
{
	pGG = gerenciadorGrafico;
}

void Ente::desenhar()
{
	if (pGG != nullptr)
		pGG->desenharEnte(this);

}

sf::Drawable* Ente::getForma()
{
	return &forma;
}

void Ente::setAltura(float a)
{
	altura = a;
}

float Ente::getAltura() const
{
	return altura;
}

void Ente::setLargura(float l)
{
	largura = l;
}

float Ente::getLargura() const
{
	return largura;
}

 