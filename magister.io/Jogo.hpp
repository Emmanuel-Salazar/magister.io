#pragma once

#ifndef _JOGO_HPP_
#define _JOGO_HPP_

#include "GerenciadorColisoes.hpp"
#include "Jogador.hpp"
#include "FasePrimeira.hpp"
#include "Menu.hpp"
#include <SFML/Graphics.hpp>

namespace Magisterio {

	class Jogo {
	 private:
		sf::RenderWindow janela;
		sf::Clock relogio;
		Gerenciadores::GerenciadorColisoes gerenciadorColisoes;
		Entidades::Personagens::Jogador jogador;
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
		Entidades::Personagens::Jogador& getJogador();
		Fases::FasePrimeira& getFase();
	};
}
#endif