#pragma once

#include "GerenciadorColisoes.hpp"
#include "Jogador.hpp"
#include "FasePrimeira.hpp"
#include "Menu.hpp"
#include <SFML/Graphics.hpp>

class Jogo {
private:
	sf::RenderWindow janela;
	sf::Clock relogio;
	GerenciadorColisoes gerenciadorColisoes;
	Entidades::Jogador jogador;
	Fases::FasePrimeira fase;
	Menu menu;
	bool menuAtivo;

	void processarEventos();
	void atualizar(float deltaTime);
	void desenhar();

public:
	Jogo();
	~Jogo();

	void executar();
	Entidades::Jogador& getJogador();
	Fases::FasePrimeira& getFase();
};
