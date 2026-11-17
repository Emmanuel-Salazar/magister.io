#pragma once

#ifndef _JOGADOR_HPP_
#define _JOGADOR_HPP_


#include "Personagem.hpp"


namespace Magisterio::Entidades::Personagens {

	class Inimigo;

	class Jogador : public Personagem 
	{
	 protected:

		int pontos;
			 
	 public:

		Jogador();
		~Jogador() override;

		void mover(float deltaTime) override;
		void colidir(Inimigo* pInimigo);
		void atacar() override;
		void executar() override;
		void salvar() override;

		//colidir

		void addPontos(int valor);
		int getPontos() const;
	};
}
#endif