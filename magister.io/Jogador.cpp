#include "Jogador.hpp"
#include "Inimigo.hpp"
#include "Projetil.hpp"
#include "Fase.hpp"
#include "GerenciadorGrafico.hpp"
#include "Ente.hpp"
#include <algorithm>
#include <string>

using namespace Magisterio;
using namespace Entidades;
using namespace Personagens;

Jogador::Jogador() : Jogador(1) {}

Jogador::Jogador(int numJogador):
	Personagem(7, 250.f),
	idJogador(numJogador == 2 ? 2 : 1),
	nome(numJogador == 2 ? "Jogador 2" : "Jogador 1"),
	pontos(0),
	velocidadePadrao(250.f),
	noChao(false),
	forcaPulo(-650.f),
	direcaoOlhar(1),
	posInicial(numJogador == 2 ? sf::Vector2f(65.f, 500.f) : sf::Vector2f(0.f, 500.f)),
	pFaseAtual(nullptr),
	texturasVida{}
{
	coordenada.setPosicao(posInicial);
	coordAnt.setPosicao(posInicial);

	sf::Texture* tex = carregarTextura("assets/personagem.png");
	if (tex) {
		figura = new sf::Sprite(*tex);
		figura->setPosition(coordenada.getPosicao());
	}

	for (int i = 0; i <= 7; i++) {
		std::string caminho = "assets/vida/" + std::to_string(i) + ".png";
		texturasVida[i] = carregarTextura(caminho);
		if (texturasVida[i]) {
			texturasVida[i]->setSmooth(false);
		}
	}

	if (texturasVida[7]) {
		spriteBarraVida.emplace(*texturasVida[7]);
		spriteBarraVida->setScale({ 3.5f, 3.5f });
		float hudX = (idJogador == 2) ? (800.f - 16.f - 37.f * 3.5f) : 16.f;
		spriteBarraVida->setPosition({ hudX, 16.f });
	}
}

Jogador::~Jogador() = default;

void Jogador::mover(float deltaTime)
{
	if (deltaTime > 0.05f)
		deltaTime = 0.05f;

	sf::Vector2f desloc{ 0.f, 0.f };

	if (idJogador == 1)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			desloc.x -= velocidade * deltaTime;
			direcaoOlhar = -1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			desloc.x += velocidade * deltaTime;
			direcaoOlhar = 1;
		}
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) ||
			 sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) && noChao)
		{
			velY = forcaPulo;
			noChao = false;
		}
	}
	else
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		{
			desloc.x -= velocidade * deltaTime;
			direcaoOlhar = -1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		{
			desloc.x += velocidade * deltaTime;
			direcaoOlhar = 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && noChao)
		{
			velY = forcaPulo;
			noChao = false;
		}
	}

	velY += gravidade * deltaTime;
	desloc.y = velY * deltaTime;

	setCoordenada(getCoordenada() + desloc);
}

void Jogador::desenhar(sf::RenderTarget& destino)
{
	if (figura) {
		sf::Color corBase = (idJogador == 2) ? sf::Color(150, 210, 255) : sf::Color::White;
		if (sofrendoDano) {
			if (relogioPiscaDano.getElapsedTime().asSeconds() < 0.25f) {
				figura->setColor(sf::Color(255, 80, 80));
			}
			else {
				sofrendoDano = false;
				figura->setColor(corBase);
			}
		}
		else {
			figura->setColor(corBase);
		}
		figura->setPosition(coordenada.getPosicao());
		destino.draw(*figura);
	}
}

void Jogador::colidir(Inimigo* pInimigo){}

void Jogador::atacar()
{
	if (!pFaseAtual)
		return;

	if (Projetil* pProj = dispararProjetil())
		pFaseAtual->incluirProjetil(pProj);
}

Projetil* Jogador::dispararProjetil()
{
	if (relogioAtaque.getElapsedTime().asSeconds() < 0.3f)
		return nullptr;

	relogioAtaque.restart();

	sf::Vector2f pos = getCoordenada();
	float saidaX = (direcaoOlhar >= 0) ? (pos.x + 35.f) : (pos.x - 45.f);
	float saidaY = pos.y + 18.f;

	Projetil* pProj = new Projetil({ saidaX, saidaY }, static_cast<float>(direcaoOlhar) * 480.f, true, 1, "assets/bola_fogo_jogador.png", this);
	pProj->lancar();
	return pProj;
}

void Jogador::executar()
{
	float dt = relogioMovimento.restart().asSeconds();
	mover(dt);
}

void Jogador::salvar() {}

void Jogador::addPontos(int valor)
{
	pontos += valor;
}

int Jogador::getPontos() const
{
	return pontos;
}

int Jogador::getIdJogador() const
{
	return idJogador;
}

void Jogador::setNome(const std::string& novoNome)
{
	if (!novoNome.empty())
		nome = novoNome;
	else
		nome = (idJogador == 2) ? "Jogador 2" : "Jogador 1";
}

const std::string& Jogador::getNome() const
{
	return nome;
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
	sofrendoDano = false;
	relogioMovimento.restart();
	if (figura)
		figura->setColor((idJogador == 2) ? sf::Color(150, 210, 255) : sf::Color::White);
	resetarVelocidade();
	setCoordenada(posInicial);
	coordAnt.setPosicao(posInicial);
}

void Jogador::reiniciarRelogio()
{
	relogioMovimento.restart();
}

bool Jogador::getNoChao() const { return noChao; }
void Jogador::setNoChao(bool v) { noChao = v; }

void Jogador::setFaseAtual(Fases::Fase* pF) { pFaseAtual = pF; }
Fases::Fase* Jogador::getFaseAtual() const { return pFaseAtual; }

void Jogador::desenharBarraVida(sf::RenderTarget& destino)
{
	int idx = std::clamp(numVidas, 0, 7);
	sf::Texture* texVida = texturasVida[idx];
	if (!texVida)
		return;

	if (!spriteBarraVida.has_value()) {
		spriteBarraVida.emplace(*texVida);
		spriteBarraVida->setScale({ 3.5f, 3.5f });
		float hudX = (idJogador == 2) ? (800.f - 16.f - 37.f * 3.5f) : 16.f;
		spriteBarraVida->setPosition({ hudX, 16.f });
	}
	else {
		spriteBarraVida->setTexture(*texVida, true);
	}

	destino.draw(*spriteBarraVida);
}

