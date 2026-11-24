#pragma once

#ifndef _OBSTACULO_HPP_
#define _OBSTACULO_HPP_

#include "Entidade.hpp"

namespace Magisterio::Entidades::Personagens {
	class Jogador;
}

namespace Magisterio::Entidades::Obstaculos {

	class Obstaculo : public Entidade {

	 protected:
		bool danoso;
		bool solido;

	 public:

		Obstaculo();
		~Obstaculo() override;
		virtual void obstaculizar() {}
		virtual void obstaculizar(Personagens::Jogador* pJogador) = 0;
		void executar() override;
		void salvar() override;
		bool getDanoso() const;
		bool getSolido() const;
	};
}
#endif
