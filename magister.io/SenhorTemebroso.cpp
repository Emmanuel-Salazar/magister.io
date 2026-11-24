#include "SenhorTemebroso.hpp"

using namespace Magisterio;
using namespace Entidades;
using namespace Personagens;

SenhorTemebroso::SenhorTemebroso() : Inimigo(3), forca(10) {}
SenhorTemebroso::~SenhorTemebroso() = default;
void SenhorTemebroso::executar() {}
void SenhorTemebroso::salvar() {}
short SenhorTemebroso::getForca() const { return forca; }
