#include "Ente.hpp"
#include "GerenciadorGrafico.hpp"
using namespace Magisterio;
using namespace Gerenciadores;

Gerenciadores::GerenciadorGrafico* Ente::pGG = nullptr;
int Ente::cont = 0;

Ente::Ente():
	id(cont++),
	largura(1),
	altura(1),
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

sf::Sprite Ente::getFigura()
{
	return *figura;
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

 