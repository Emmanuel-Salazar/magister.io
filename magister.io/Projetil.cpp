#include "Projetil.hpp"
#include "GerenciadorGrafico.hpp"

using namespace Magisterio;
using namespace Entidades;

Projetil::Projetil(sf::Vector2f pos, float velX, bool origemJogador, int valorDano, const std::string& caminhoTextura) :
	ativo(false),
	doJogador(origemJogador),
	velocidadeX(velX),
	dano(valorDano)
{
	sf::Texture* tex = pGG->carregarTextura(caminhoTextura);
	if (!tex && !origemJogador) {
		tex = pGG->carregarTextura("assets/bola_fogo_mago_tenebroso.png");
	}
	if (tex) {
		figura = new sf::Sprite(*tex);
		float texW = static_cast<float>(tex->getSize().x);
		float texH = static_cast<float>(tex->getSize().y);
		float escala = (texW > 0.f) ? (68.f / texW) : 0.15f;
		largura = texW * escala;
		altura = texH * escala;
		if (velocidadeX >= 0.f) {
			figura->setOrigin({ 0.f, 0.f });
			figura->setScale({ escala, escala });
		}
		else {
			figura->setOrigin({ texW, 0.f });
			figura->setScale({ -escala, escala });
		}
	}

	coordenada.setPosicao(pos);
	coordAnt.setPosicao(pos);
	if (figura)
		figura->setPosition(pos);
}

Projetil::~Projetil() = default;

void Projetil::executar() {
	if (!ativo)
		return;

	float dt = relogioMovimento.restart().asSeconds();
	if (dt > 0.05f)
		dt = 0.05f;

	sf::Vector2f pos = getCoordenada();
	pos.x += velocidadeX * dt;

	if (pos.x + largura < 0.f || pos.x > 800.f) {
		ativo = false;
		return;
	}

	setCoordenada(pos);
}

void Projetil::salvar() {}

void Projetil::lancar() {
	ativo = true;
	relogioMovimento.restart();
}

void Projetil::desativar() {
	ativo = false;
}

bool Projetil::estaAtivo() const { return ativo; }

bool Projetil::ehDoJogador() const { return doJogador; }

int Projetil::getDano() const { return dano; }
