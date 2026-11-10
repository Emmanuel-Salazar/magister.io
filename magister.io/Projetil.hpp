#pragma once

#include "Entidade.hpp"

namespace Entidades {
	class Projetil : public Entidade {
	private:
		bool ativo;

	public:
		Projetil();
		~Projetil() override;
		void executar() override;
		void salvar() override;
		void lancar();
		bool estaAtivo() const;
	};
}
