#pragma once

#ifndef _OBSTACULO_HPP_
#define _OBSTACULO_HPP_

#include "Entidade.hpp"

namespace Magisterio::Entidades {

	class Obstaculo : public Entidade {

	 protected:

		int dano;

	 public:

		Obstaculo();
		~Obstaculo() override;
		virtual bool obstacular() = 0;
		void executar() override;
		void salvar() override;
		int getDano() const;
		void setDano(int valor);
	};
}
#endif