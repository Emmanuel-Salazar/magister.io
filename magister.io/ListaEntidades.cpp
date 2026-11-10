#include "ListaEntidades.hpp"

namespace Entidades {
	ListaEntidades::ListaEntidades() = default;
	ListaEntidades::~ListaEntidades() = default;

	void ListaEntidades::inserir(Entidade* entidade)
	{
		if (entidade != nullptr)
			entidades.push_back(entidade);
	}

	void ListaEntidades::remover(Entidade* entidade) { entidades.remove(entidade); }
	std::size_t ListaEntidades::tamanho() const { return entidades.size(); }
	void ListaEntidades::limpar() { entidades.clear(); }
	std::list<Entidade*>& ListaEntidades::obter() { return entidades; }
	const std::list<Entidade*>& ListaEntidades::obter() const { return entidades; }
}
