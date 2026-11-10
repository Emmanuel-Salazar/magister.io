#pragma once

#include "Entidade.hpp"

namespace Entidades {
	class Projetil : public Entidade {
	private:
		bool ativo;

	public:
		Projetil() : ativo(false) {}
		~Projetil() override = default;
		void executar() override {}
		void salvar() override {}
		void lancar() { ativo = true; }
		bool estaAtivo() const { return ativo; }
	};
}
