#include "Inimigo.hpp"
#include "Jogador.hpp"
#include <iostream>

using namespace Magisterio;
using namespace Entidades;
using namespace Personagens;

Inimigo::Inimigo(int nivel) :
	Personagem(nivel),
	nivelMaldade(nivel),
	jaCausouDano(false),
	limiteMinX(10.f),
	limiteMaxX(790.f)
{
}

Inimigo::~Inimigo() = default;

void Inimigo::mover(float deltaTime) {}
void Inimigo::atacar() {}
void Inimigo::perseguir() {}
void Inimigo::executar() {}
void Inimigo::salvar() {}
void Inimigo::danificar() {}

void Inimigo::danificar(Jogador* pJogador) {
	if (!pJogador)
		return;

	if (!jaCausouDano || relogioDano.getElapsedTime().asSeconds() >= 1.0f) {
		(*pJogador)--;
		jaCausouDano = true;
		relogioDano.restart();
		std::cout << "[Inimigo] Jogador atingido! Vidas restantes: "
		          << pJogador->getNumVidas() << std::endl;
	}
}

void Inimigo::setLimitesPatrulha(float minX, float maxX) {
	limiteMinX = minX;
	limiteMaxX = maxX;
}

int Inimigo::getNivelMaldade() const { return nivelMaldade; }
