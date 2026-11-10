#pragma once

#include "Inimigo.hpp"

namespace Entidades {
	class InimMedio : public Inimigo {
	public:
		InimMedio() : Inimigo(2) {}
		~InimMedio() override = default;
		void executar() override {}
		void salvar() override {}
	};
}
