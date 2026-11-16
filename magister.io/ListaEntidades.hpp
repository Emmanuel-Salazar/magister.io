#pragma once

#ifndef _LISTAENTIDADES_HPP_
#define _LISTAENTIDADES_HPP_

#include "Entidade.hpp"
#include <list>


namespace Magisterio::Listas {

    class ListaEntidades {
     private:
        std::list<Entidades::Entidade*> entidades;

     public:
        ListaEntidades();
        ~ListaEntidades();
        void inserir(Entidades::Entidade* entidade);
        void remover(Entidades::Entidade* entidade);
        std::size_t tamanho() const;
        void limpar();
        std::list<Entidades::Entidade*>& obter();
        const std::list<Entidades::Entidade*>& obter() const;
    };
}
#endif // !_LISTAENTIDADES_HPP_