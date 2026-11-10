#pragma once

#include "Obstaculo.hpp"

namespace Entidades {
	class ObstMedio : public Obstaculo {
	private:
		float largura;

	public:
		ObstMedio() : largura(0.0f) {}
		~ObstMedio() override = default;
		bool obstacular() override { return true; }
		float getLargura() const { return largura; }
		void setLargura(float valor) { largura = valor; }
	};
}
