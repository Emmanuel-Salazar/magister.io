#include "Jogador.hpp"
#include "Inimigo.hpp"
#include "GerenciadorGrafico.hpp"
#include "Ente.hpp"

using namespace Magisterio;
using namespace Entidades;
using namespace Personagens;

Jogador::Jogador():
	Personagem(10),
	pontos(0),
	velocidade(250.f),
	velocidadePadrao(250.f)
{
	coordenada.setPosicao({ 0.f, 500.f });
	coordAnt.setPosicao(coordenada.getPosicao());

	sf::Texture* tex = pGG->carregarTextura("assets/personagem.png");
	if (tex) {
		figura = new sf::Sprite(*tex);
		figura->setPosition(coordenada.getPosicao());
	}
}

Jogador::~Jogador() = default;

void Jogador::mover(float deltaTime)
{
	sf::Vector2f desloc{ 0.f, 0.f };

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		desloc.y -= velocidade * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		desloc.y += velocidade * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		desloc.x -= velocidade * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		desloc.x += velocidade * deltaTime;

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

void Jogador::setVelocidade(float v)
{
	velocidade = v;
}

float Jogador::getVelocidade() const
{
	return velocidade;
}

float Jogador::getVelocidadePadrao() const
{
	return velocidadePadrao;
}

void Jogador::resetarVelocidade()
{
	velocidade = velocidadePadrao;
}

void Jogador::resetar()
{
	numVidas = 10;
	pontos = 0;
	resetarVelocidade();
	setCoordenada({ 0.f, 500.f });
	coordAnt.setPosicao({ 0.f, 500.f });
}

