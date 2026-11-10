#pragma once

#include "Inimigo.hpp"

namespace Entidades {
	class InimChefe : public Inimigo {
	private:
		short forca;

	public:
		InimChefe() : Inimigo(3), forca(10) {}
		~InimChefe() override = default;
		void executar() override {}
		void salvar() override {}
		short getForca() const { return forca; }
	};
}
