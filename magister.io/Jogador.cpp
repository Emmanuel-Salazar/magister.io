#include "Jogador.hpp"
#include "Inimigo.hpp"
#include "GerenciadorGrafico.hpp"
#include "Ente.hpp"

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

	sf::Texture* tex = pGG->carregarTextura("assets/personagem.png");
	figura = new sf::Sprite(*tex);
	if (coordenada)
		figura->setPosition(coordenada->getPosicao());
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

	figura->move({ deslocamentoX, deslocamentoY });
	coordenada->setPosicao(static_cast<sf::Vector2f>(figura->getPosition()));
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

