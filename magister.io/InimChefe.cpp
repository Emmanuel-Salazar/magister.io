#include "InimChefe.hpp"

namespace Entidades {
	InimChefe::InimChefe() : Inimigo(3), forca(10) {}
	InimChefe::~InimChefe() = default;
	void InimChefe::executar() {}
	void InimChefe::salvar() {}
	short InimChefe::getForca() const { return forca; }
}
