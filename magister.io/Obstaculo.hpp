#pragma once

#ifndef _OBSTACULO_HPP_
#define _OBSTACULO_HPP_

#include "Entidade.hpp"

namespace Magisterio::Entidades {

	class Obstaculo : public Entidade {

	 protected:
		bool danoso;

	 public:

		Obstaculo();
		~Obstaculo() override;
		virtual void obstaculizar() = 0;
		void executar() override;
		void salvar() override;
	};
}
#endif