#include "ObstDificil.hpp"

using namespace Magisterio;
using namespace Entidades;
using  namespace Obstaculos;

ObstDificil::ObstDificil() : danosidade(1) {}
ObstDificil::~ObstDificil() = default;
void ObstDificil::obstaculizar() { }
short ObstDificil::getDanosidade() const { return danosidade; }
void ObstDificil::setDanosidade(short valor) { danosidade = valor; }

