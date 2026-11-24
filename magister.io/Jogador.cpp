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
	velocidadePadrao(250.f),
	velY(0.f),
	noChao(false),
	gravidade(1200.f),
	forcaPulo(-650.f)
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
	if (deltaTime > 0.05f)
		deltaTime = 0.05f;

	sf::Vector2f desloc{ 0.f, 0.f };

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		desloc.x -= velocidade * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		desloc.x += velocidade * deltaTime;

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) ||
		 sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) ||
		 sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) && noChao)
	{
		velY = forcaPulo;
		noChao = false;
	}

	velY += gravidade * deltaTime;
	desloc.y = velY * deltaTime;

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
	velY = 0.f;
	noChao = false;
	resetarVelocidade();
	setCoordenada({ 0.f, 500.f });
	coordAnt.setPosicao({ 0.f, 500.f });
}

float Jogador::getVelY() const { return velY; }
void Jogador::setVelY(float v) { velY = v; }
bool Jogador::getNoChao() const { return noChao; }
void Jogador::setNoChao(bool v) { noChao = v; }

