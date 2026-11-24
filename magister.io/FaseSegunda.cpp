#include "FaseSegunda.hpp"

using namespace Magisterio;
using namespace Fases;

FaseSegunda::FaseSegunda():
	maxSenhorTemebrosos (2),
	maxGoblins (rand() % 5 + 3)
{
}

FaseSegunda::~FaseSegunda() = default;

void FaseSegunda::criarObstaculos() {}
void FaseSegunda::criarInimigos() {}

