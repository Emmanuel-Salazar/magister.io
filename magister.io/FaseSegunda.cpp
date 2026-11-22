#include "FaseSegunda.hpp"

using namespace Magisterio;
using namespace Fases;

FaseSegunda::FaseSegunda():
	maxChefoes (2),
	maxInimMedios (rand() % 5 + 3)
{
}

FaseSegunda::~FaseSegunda() = default;

void FaseSegunda::criarObstaculos() {}
void FaseSegunda::criarInimigos() {}

