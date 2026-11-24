#pragma once

#ifndef _INIMIGO_HPP_
#define _INIMIGO_HPP_

#include "Personagem.hpp"

namespace Magisterio::Entidades::Personagens {

	class Jogador;

	class Inimigo : public Personagem
	{
	protected:

		int nivelMaldade;
		sf::Clock relogioDano;
		bool jaCausouDano;
		float limiteMinX;
		float limiteMaxX;

	public:

		explicit Inimigo(int nivel = 1);
		~Inimigo() override;

		void mover(float deltaTime) override;
		void atacar() override;
		virtual void perseguir();
		void executar() override;
		void salvar() override;
		virtual void danificar();
		virtual void danificar(Jogador* pJogador);

		void setLimitesPatrulha(float minX, float maxX);
		int getNivelMaldade() const;
	};
}
#endif
