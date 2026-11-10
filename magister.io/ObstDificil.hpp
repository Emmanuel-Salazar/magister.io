#pragma once

#include "Obstaculo.hpp"

namespace Entidades {
	class ObstDificil : public Obstaculo {
	private:
		short danosidade;

	public:
		ObstDificil() : danosidade(1) {}
		~ObstDificil() override = default;
		bool obstacular() override { return true; }
		short getDanosidade() const { return danosidade; }
		void setDanosidade(short valor) { danosidade = valor; }
	};
}
