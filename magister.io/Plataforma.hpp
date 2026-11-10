#pragma once

#include "Obstaculo.hpp"

namespace Entidades {
	class Plataforma : public Obstaculo {
	private:
		int altura;

	public:
		Plataforma() : altura(0) {}
		~Plataforma() override = default;
		bool obstacular() override { return true; }
		int getAltura() const { return altura; }
		void setAltura(int valor) { altura = valor; }
	};
}
