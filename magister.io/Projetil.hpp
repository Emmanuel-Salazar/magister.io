#pragma once

#ifndef _PROJETIL_HPP_
#define _PROJETIL_HPP_

#include "Entidade.hpp"

namespace Magisterio::Entidades {

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
#endif