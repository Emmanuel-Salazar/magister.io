#pragma once

#include "Inimigo.hpp"

namespace Entidades {
	class InimFacil : public Inimigo {
	public:
		InimFacil() : Inimigo(1) {}
		~InimFacil() override = default;
		void executar() override {}
		void salvar() override {}
	};
}
