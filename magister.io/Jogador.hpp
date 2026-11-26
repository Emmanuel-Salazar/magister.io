#pragma once

#ifndef _JOGADOR_HPP_
#define _JOGADOR_HPP_


#include "Personagem.hpp"
#include <array>
#include <optional>
#include <string>


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

		int idJogador;
		std::string nome;
		int pontos;
		const float velocidadePadrao;
		bool noChao;
		const float forcaPulo;
		int direcaoOlhar;
		sf::Vector2f posInicial;
		sf::Clock relogioAtaque;
		Fases::Fase* pFaseAtual;

		std::array<sf::Texture*, 8> texturasVida;
		std::optional<sf::Sprite> spriteBarraVida;
			 
	 public:

		Jogador();
		explicit Jogador(int numJogador);
		~Jogador() override;

		void mover(float deltaTime) override;
		void colidir(Inimigo* pInimigo);
		void atacar() override;
		Entidades::Projetil* dispararProjetil();
		void executar() override;
		void salvar() override;
		void desenhar(sf::RenderTarget& destino) override;

		//colidir

		void addPontos(int valor);
		int getPontos() const;
		int getIdJogador() const;
		void setNome(const std::string& novoNome);
		const std::string& getNome() const;

		float getVelocidadePadrao() const;
		void resetarVelocidade();
		void resetar();
		void reiniciarRelogio();

		bool getNoChao() const;
		void setNoChao(bool v);

		void setFaseAtual(Fases::Fase* pF);
		Fases::Fase* getFaseAtual() const;

		void desenharBarraVida(sf::RenderTarget& destino);
	};
}
#endif