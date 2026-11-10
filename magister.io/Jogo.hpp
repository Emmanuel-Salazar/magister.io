#pragma once

#include "GerenciadorGrafico.hpp"
#include "GerenciadorColisoes.hpp"
#include "Jogador.hpp"
#include "FasePrimeira.hpp"
#include "Menu.hpp"

class Jogo {
private:
	GerenciadorGrafico gerenciadorGrafico;
	GerenciadorColisoes gerenciadorColisoes;
	Entidades::Jogador jogador;
	Fases::FasePrimeira fase;
	Menu menu;

public:
	Jogo() = default;
	~Jogo() = default;

	void executar() { gerenciadorGrafico.executar(); }
	Entidades::Jogador& getJogador() { return jogador; }
	Fases::FasePrimeira& getFase() { return fase; }
};
