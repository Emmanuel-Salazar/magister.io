#include "Fase.hpp"


Fase::Fase(int numero) : numero(numero) {}
Fase::~Fase() = default;
void Fase::criarObstaculos() {}
void Fase::criarInimigos() {}
void Fase::criarProjetis() {}
void Fase::executar() {}
void Fase::salvar() {}
int Fase::getNumero() const { return numero; }
Magisterio::Entidades::ListaEntidades& Fase::getEntidades() { return entidades; }

