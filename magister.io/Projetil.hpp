#pragma once

#ifndef _PROJETIL_HPP_
#define _PROJETIL_HPP_

#include "Entidade.hpp"
#include <string>

namespace Magisterio::Entidades::Personagens {
	class Jogador;
}

namespace Magisterio::Entidades {

	class Projetil : public Entidade {
	 private:
		bool ativo;
		bool doJogador;
		float velocidadeX;
		int dano;
		Personagens::Jogador* pDono;

	 public:
		Projetil(sf::Vector2f pos = sf::Vector2f(0.f, 0.f),
		         float velX = 480.f,
		         bool origemJogador = true,
		         int valorDano = 1,
		         const std::string& caminhoTextura = "assets/bola_fogo_jogador.png",
		         Personagens::Jogador* dono = nullptr);
		~Projetil() override;
		void executar() override;
		void salvar() override;
		void lancar();
		void desativar();
		bool estaAtivo() const;
		bool ehDoJogador() const;
		int getDano() const;
		Personagens::Jogador* getDono() const;
	};
}
#endif