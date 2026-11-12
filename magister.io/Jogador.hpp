#pragma once

#include "Personagem.hpp"

namespace Magisterio {
	namespace Entidades {
		namespace Personagens {

			class Jogador : public Personagem 
			{
			 protected:

				int pontos;
			 
			public:

				Jogador();
				~Jogador() override;

				void mover(float deslocamentoX, float deslocamentoY);
				void atacar() override;
				void executar() override;
				void salvar() override;

				//colidir

				void addPontos(int valor);
				int getPontos() const;
			};
		}
	}
}