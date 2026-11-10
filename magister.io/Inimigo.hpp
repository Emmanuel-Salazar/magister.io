#pragma once

#include "Personagem.hpp"

namespace Entidades {
	class Inimigo : public Personagem {
	protected:
		int nivelMaldade;

	public:
		explicit Inimigo(int nivel = 1);
		~Inimigo() override;
		virtual void perseguir();
		int getNivelMaldade() const;
	};
}
