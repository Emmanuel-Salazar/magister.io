#include "Jogador.hpp"

namespace Entidades {
	Jogador::Jogador() : pontos(0) {}

	Jogador::~Jogador() = default;

	void Jogador::mover(float deslocamentoX, float deslocamentoY)
	{
		Personagem::mover(deslocamentoX, deslocamentoY);
	}

	void Jogador::atacar() {}

	void Jogador::executar() {}

	void Jogador::salvar() {}

	void Jogador::adicionarPontos(int valor)
	{
		pontos += valor;
	}

	int Jogador::getPontos() const
	{
		return pontos;
	}
}
