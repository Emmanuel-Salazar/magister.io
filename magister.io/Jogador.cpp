#include "Jogador.hpp"
#include "Inimigo.hpp"
#include "Projetil.hpp"
#include "GerenciadorGrafico.hpp"
#include "Ente.hpp"
#include <algorithm>
#include <string>

using namespace Magisterio;
using namespace Entidades;
using namespace Personagens;

Jogador::Jogador():
	Personagem(7),
	pontos(0),
	velocidade(250.f),
	velocidadePadrao(250.f),
	velY(0.f),
	noChao(false),
	gravidade(1200.f),
	forcaPulo(-650.f),
	direcaoOlhar(1),
	texturasVida{}
{
	coordenada.setPosicao({ 0.f, 500.f });
	coordAnt.setPosicao(coordenada.getPosicao());

	sf::Texture* tex = pGG->carregarTextura("assets/personagem.png");
	if (tex) {
		figura = new sf::Sprite(*tex);
		figura->setPosition(coordenada.getPosicao());
	}

	for (int i = 0; i <= 7; i++) {
		std::string caminho = "assets/vida/" + std::to_string(i) + ".png";
		texturasVida[i] = pGG->carregarTextura(caminho);
		if (texturasVida[i]) {
			texturasVida[i]->setSmooth(false);
		}
	}

	if (texturasVida[7]) {
		spriteBarraVida.emplace(*texturasVida[7]);
		spriteBarraVida->setScale({ 3.5f, 3.5f });
		spriteBarraVida->setPosition({ 16.f, 16.f });
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
	{
		desloc.x -= velocidade * deltaTime;
		direcaoOlhar = -1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		desloc.x += velocidade * deltaTime;
		direcaoOlhar = 1;
	}

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

Projetil* Jogador::dispararProjetil()
{
	if (relogioAtaque.getElapsedTime().asSeconds() < 0.3f)
		return nullptr;

	relogioAtaque.restart();

	sf::Vector2f pos = getCoordenada();
	float saidaX = (direcaoOlhar >= 0) ? (pos.x + 35.f) : (pos.x - 45.f);
	float saidaY = pos.y + 18.f;

	Projetil* pProj = new Projetil({ saidaX, saidaY }, static_cast<float>(direcaoOlhar) * 480.f, true);
	pProj->lancar();
	return pProj;
}

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
	numVidas = 7;
	pontos = 0;
	velY = 0.f;
	noChao = false;
	direcaoOlhar = 1;
	resetarVelocidade();
	setCoordenada({ 0.f, 500.f });
	coordAnt.setPosicao({ 0.f, 500.f });
}

float Jogador::getVelY() const { return velY; }
void Jogador::setVelY(float v) { velY = v; }
bool Jogador::getNoChao() const { return noChao; }
void Jogador::setNoChao(bool v) { noChao = v; }

void Jogador::desenharBarraVida(sf::RenderTarget& destino)
{
	int idx = std::clamp(numVidas, 0, 7);
	sf::Texture* texVida = texturasVida[idx];
	if (!texVida)
		return;

	if (!spriteBarraVida.has_value()) {
		spriteBarraVida.emplace(*texVida);
		spriteBarraVida->setScale({ 3.5f, 3.5f });
		spriteBarraVida->setPosition({ 16.f, 16.f });
	}
	else {
		spriteBarraVida->setTexture(*texVida, true);
	}

	destino.draw(*spriteBarraVida);
}

