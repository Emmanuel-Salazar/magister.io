#pragma once

#include "Entidade.hpp"
#include <list>

namespace Entidades {
	class ListaEntidades {
	private:
		std::list<Entidade*> entidades;

	public:
		ListaEntidades() = default;
		~ListaEntidades() = default;

		void inserir(Entidade* entidade) { if (entidade != nullptr) entidades.push_back(entidade); }
		void remover(Entidade* entidade) { entidades.remove(entidade); }
		std::size_t tamanho() const { return entidades.size(); }
		void limpar() { entidades.clear(); }
		std::list<Entidade*>& obter() { return entidades; }
		const std::list<Entidade*>& obter() const { return entidades; }
	};
}
