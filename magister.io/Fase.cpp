#include "Fase.hpp"

namespace Fases {
	Fase::Fase(int numero) : numero(numero) {}
	Fase::~Fase() = default;
	void Fase::criarObstaculos() {}
	void Fase::criarInimigos() {}
	void Fase::criarProjetis() {}
	void Fase::executar() {}
	void Fase::salvar() {}
	int Fase::getNumero() const { return numero; }
	Entidades::ListaEntidades& Fase::getEntidades() { return entidades; }
}
