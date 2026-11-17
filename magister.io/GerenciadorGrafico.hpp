#pragma once

#ifndef GERENCIADOR_GRAFICO_HPP_
#define GERENCIADOR_GRAFICO_HPP_


#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "Jogador.hpp"
#include "Menu.hpp"

namespace Magisterio::Gerenciadores {

	class GerenciadorGrafico {

	 private:

		sf::RenderWindow janela;
		Entidades::Personagens::Jogador jogador;
		Menu menu;
		bool menuAtivo;
		sf::Clock relogio;

		void processarEventos();
		void atualizar(float deltaTime);
		void desenhar();

	 public:

		GerenciadorGrafico();
		void executar();
	};
}
#endif