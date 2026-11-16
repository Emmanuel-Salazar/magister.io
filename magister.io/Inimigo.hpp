#pragma once

#ifndef _INIMIGO_HPP_
#define _INIMIGO_HPP_

#include "Personagem.hpp"

namespace Magisterio::Entidades::Personagens {

	class Inimigo : public Personagem
	{
	protected:

		int nivelMaldade;

	public:

		explicit Inimigo(int nivel = 1);
		~Inimigo() override;

		virtual void perseguir() = 0;
		virtual void executar() = 0;
		virtual void danificar() = 0;

		int getNivelMaldade() const;
	};
}
#endif