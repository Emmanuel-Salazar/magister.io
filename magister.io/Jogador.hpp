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
		float velocidade;
		const float velocidadePadrao;
		float velY;
		bool noChao;
		const float gravidade;
		const float forcaPulo;
			 
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

		float getVelocidade() const;
		void setVelocidade(float v);
		float getVelocidadePadrao() const;
		void resetarVelocidade();
		void resetar();

		float getVelY() const;
		void setVelY(float v);
		bool getNoChao() const;
		void setNoChao(bool v);
	};
}
#endif