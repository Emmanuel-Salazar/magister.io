#pragma once

#include "Personagem.hpp"

namespace Entidades {
	class Jogador : public Personagem {
	private:
		int pontos;

	public:
		Jogador() : pontos(0) {}
		~Jogador() override = default;
		void mover(float, float) override {}
		void atacar() override {}
		void executar() override {}
		void salvar() override {}
		void adicionarPontos(int valor) { pontos += valor; }
		int getPontos() const { return pontos; }
	};
}
