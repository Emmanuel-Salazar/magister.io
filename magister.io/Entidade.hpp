#pragma once
#ifndef ENTIDADE_H_
#define ENTIDADE_H_

#include "stdafx.hpp"
#include "Coordenada.hpp"

namespace Entidades {
    class Entidade {
    protected:
        Coordenada* coordenada;
        ofstream* buffer;
        void salvarDataBuffer();

    public:
        Entidade();
        virtual ~Entidade();
        virtual void executar() = 0;
        virtual void salvar() = 0;

    };
}

#endif