#pragma once

#ifndef _JOGADOR_HPP_
#define _JOGADOR_HPP_


#include "Personagem.hpp"
#include <array>
#include <optional>


namespace Magisterio::Entidades {
	class Projetil;
}

namespace Magisterio::Fases {
	class Fase;
}

namespace Magisterio::Entidades::Personagens {

	class Inimigo;

	class Jogador : public Personagem 
	{
	 protected:

		int pontos;
		const float velocidadePadrao;
		bool noChao;
		const float forcaPulo;
		int direcaoOlhar;
		sf::Clock relogioAtaque;
		Fases::Fase* pFaseAtual;

		std::array<sf::Texture*, 8> texturasVida;
		std::optional<sf::Sprite> spriteBarraVida;
			 
	 public:

		Jogador();
		~Jogador() override;

		void mover(float deltaTime) override;
		void colidir(Inimigo* pInimigo);
		void atacar() override;
		Entidades::Projetil* dispararProjetil();
		void executar() override;
		void salvar() override;

		//colidir

		void addPontos(int valor);
		int getPontos() const;

		float getVelocidadePadrao() const;
		void resetarVelocidade();
		void resetar();

		bool getNoChao() const;
		void setNoChao(bool v);

		void setFaseAtual(Fases::Fase* pF);
		Fases::Fase* getFaseAtual() const;

		void desenharBarraVida(sf::RenderTarget& destino);
	};
}
#endif