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
	largura = 36.f;
	altura = largura;
	forma = sf::RectangleShape(sf::Vector2f(largura, largura));

	forma.setPosition({ 400.f, 300.f });
	forma.setFillColor(sf::Color::Green);
}

Jogador::~Jogador() = default;

void Jogador::mover(float deltaTime)
{
	constexpr float velocidade = 250.f;
	float deslocamentoX = 0.f;
	float deslocamentoY = 0.f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		deslocamentoY -= velocidade * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		deslocamentoY += velocidade * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		deslocamentoX -= velocidade * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		deslocamentoX += velocidade * deltaTime;

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

