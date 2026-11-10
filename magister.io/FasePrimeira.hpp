#pragma once

#include "Fase.hpp"

namespace Fases {
	class FasePrimeira : public Fase {
	public:
		FasePrimeira() : Fase(1) {}
		~FasePrimeira() override = default;
		void criarObstaculos() override {}
		void criarInimigos() override {}
		void criarProjetis() override {}
	};
}
