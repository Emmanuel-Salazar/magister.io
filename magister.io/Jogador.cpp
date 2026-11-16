#include "Jogador.hpp"
#include "Inimigo.hpp"

using namespace Magisterio;
using namespace Entidades;
using namespace Personagens;

Jogador::Jogador():
Personagem(3),
pontos(0)
{
	numVidas = 3;
	forma = sf::CircleShape(24.f);

	forma.setOrigin({ 24.f, 24.f });
	forma.setPosition({ 400.f, 300.f });
	forma.setFillColor(sf::Color::Green);
}

Jogador::~Jogador() = default;

void Jogador::mover(float deslocamentoX, float deslocamentoY)
{
	forma.move({ deslocamentoX, deslocamentoY });
	coordenada->setX(static_cast<int>(forma.getPosition().x));
	coordenada->setY(static_cast<int>(forma.getPosition().y));
}

void Jogador::colidir(Inimigo* pInimigo){}

void Jogador::atacar() {}

void Jogador::executar() {}

void Jogador::salvar() {}

void Jogador::addPontos(int valor)
{
	pontos += valor;
}

int Jogador::getPontos() const
{
	return pontos;
}

