#pragma once

#ifndef _LISTAENTIDADES_HPP_
#define _LISTAENTIDADES_HPP_

#include "Lista.hpp"
#include "Entidade.hpp"
#include <list>


namespace Magisterio::Listas {

    class ListaEntidades {
     private:

         Lista<Entidades::Entidade> LEs;


        

     public:
        ListaEntidades();
        ~ListaEntidades();
        
        void inserir(Entidades::Entidade* entidade);
        void remover(Entidades::Entidade* entidade);
        int tamanho() const;
        void limpar();
        void executar();
        Lista<Entidades::Entidade>& obter();
    };
}
#endif