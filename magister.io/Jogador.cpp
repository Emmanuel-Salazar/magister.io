#include "Jogador.hpp"
#include "Inimigo.hpp"
#include "GerenciadorGrafico.hpp"
#include "Ente.hpp"

using namespace Magisterio;
using namespace Entidades;
using namespace Personagens;

#define VEL_PULO 500
#define VEL_FINAL 350

Jogador::Jogador():
	Personagem(3),
	pontos(0),
	velocidadeX(250.f),
	velocidadeY(0.f)
{
	coordenada.setPosicao({ 0.f, 500.f });
	coordAnt.setPosicao(coordenada.getPosicao());

	sf::Texture* tex = pGG->carregarTextura("assets/personagem.png");
	figura = new sf::Sprite(*tex);
	figura->setPosition(coordenada.getPosicao());
}

Jogador::~Jogador() = default;

void Jogador::mover(float deltaTime)
{
	sf::Vector2f desloc{ 0.f, 0.f };

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		if (pulavel)
		{
			pulavel = false;
			velocidadeY = -VEL_PULO;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		desloc.x -= velocidadeX * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		desloc.x += velocidadeX * deltaTime;

	velocidadeY += gravidade * deltaTime;
	if(velocidadeY > VEL_FINAL)
		velocidadeY = VEL_FINAL;

	desloc.y += velocidadeY * deltaTime;

	setCoordenada(getCoordenada() + desloc);
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

void Jogador::setVelocidadeX(float v)
{
	velocidadeX = v;
}

float Jogador::getVelocidadeX() const
{
	return velocidadeX;
}

void Jogador::setVelocidadeY(float v)
{
	velocidadeY = v;
}

float Jogador::getVelocidadeY() const
{
	return velocidadeY;
}
