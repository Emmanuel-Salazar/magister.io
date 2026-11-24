#pragma once

#ifndef _PROJETIL_HPP_
#define _PROJETIL_HPP_

#include "Entidade.hpp"

namespace Magisterio::Entidades {

	class Projetil : public Entidade {
	 private:
		bool ativo;
		bool doJogador;
		float velocidadeX;
		sf::Clock relogioMovimento;

	 public:
		Projetil(sf::Vector2f pos = sf::Vector2f(0.f, 0.f), float velX = 480.f, bool origemJogador = true);
		~Projetil() override;
		void executar() override;
		void salvar() override;
		void lancar();
		void desativar();
		bool estaAtivo() const;
		bool ehDoJogador() const;
	};
}
#endif