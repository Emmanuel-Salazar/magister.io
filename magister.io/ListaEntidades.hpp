#pragma once

#include "Entidade.hpp"
#include <list>


namespace Magisterio {
    namespace Entidades { 

        class ListaEntidades {
        private:
            std::list<Entidade*> entidades;

        public:
            ListaEntidades();
            ~ListaEntidades();
            void inserir(Entidade* entidade);
            void remover(Entidade* entidade);
            std::size_t tamanho() const;
            void limpar();
            std::list<Entidade*>& obter();
            const std::list<Entidade*>& obter() const;
        };
    }
}