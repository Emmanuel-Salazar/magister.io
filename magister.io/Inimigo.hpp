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

		void mover(float deltaTime) override;
		void atacar() override;
		virtual void perseguir();
		void executar() override;
		void salvar() override;
		virtual void danificar();

		int getNivelMaldade() const;
	};
}
#endif
