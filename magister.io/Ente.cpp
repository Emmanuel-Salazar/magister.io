#include "Ente.hpp"

using namespace Magisterio;

Gerenciadores::GerenciadorGrafico* Ente::pGG = nullptr;

Ente::Ente(int i):
	forma(sf::Vector2f(24.f, 24.f)),
	id(i),
	largura(1),
	altura(1)

{
}

Ente::~Ente(){}

void Ente::desenhar(){}
void Ente::setGG(Gerenciadores::GerenciadorGrafico* gerenciadorGrafico)
{
	pGG = gerenciadorGrafico;
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

 