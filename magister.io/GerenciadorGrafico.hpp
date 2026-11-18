#pragma once

#ifndef GERENCIADOR_GRAFICO_HPP_
#define GERENCIADOR_GRAFICO_HPP_

#include "stdafx.hpp"

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
		static GerenciadorGrafico* pGrafico;

	 public:
		GerenciadorGrafico();
		~GerenciadorGrafico();
		void processarEventos();
		void atualizar(float deltaTime);
		void desenhar();
		sf::RenderWindow* getJanela() { return &janela; }
		sf::Clock* getRelogio() { return &relogio; }
		GerenciadorGrafico* getGerenciadorGrafico();
		static void destruirGGrafico();
	};
}

#endif