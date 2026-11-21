#include "ListaEntidades.hpp"

using namespace Magisterio;
using namespace Listas;
using namespace Entidades;

ListaEntidades::ListaEntidades() = default;
ListaEntidades::~ListaEntidades() 
{
	limpar();
}

void ListaEntidades::inserir(Entidade* entidade)
{
	if (entidade != nullptr)
		LEs.push(entidade);
}

void ListaEntidades::remover(Entidade* entidade) { LEs.pop(entidade); }

int ListaEntidades::tamanho() const { return LEs.getLen(); }

void ListaEntidades::limpar() { LEs.limpar(); }

void ListaEntidades::executar()
{ 
	int tam = LEs.getLen();
	int i;
	for (i = 0; i < tam; i++)
	{
		LEs[i]->executar();
	}
}

Lista<Entidade>& ListaEntidades::obter() { return LEs; }
