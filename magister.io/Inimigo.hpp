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
		Jogador* pAlvo;

	public:

		explicit Inimigo(int nivel = 1, float vel = 0.f);
		~Inimigo() override;

		virtual void danificar();
		virtual void danificar(Jogador* pJogador);
		void salvar() override;
		void mover(float deltaTime) override;
		virtual void atacar();
		virtual void perseguir();
		void executar() override;

		void setLimitesPatrulha(float minX, float maxX);
		void setAlvo(Jogador* pJ);
		int getNivelMaldade() const;
	};
}
#endif
