#include "Inimigo.hpp"

using namespace Magisterio;
using namespace Entidades;
using namespace Personagens;

Inimigo::Inimigo(int nivel) : Personagem(1), nivelMaldade(nivel) {}

Inimigo::~Inimigo() = default;

void Inimigo::mover(float deltaTime) {}
void Inimigo::atacar() {}
void Inimigo::perseguir() {}
void Inimigo::executar() {}
void Inimigo::salvar() {}
void Inimigo::danificar() {}

int Inimigo::getNivelMaldade() const { return nivelMaldade; }
