#pragma once

#include "Fase.hpp"

namespace Fases {
	class FaseSegunda : public Fase {
	public:
		FaseSegunda() : Fase(2) {}
		~FaseSegunda() override = default;
		void criarObstaculos() override {}
		void criarInimigos() override {}
		void criarProjetis() override {}
	};
}
