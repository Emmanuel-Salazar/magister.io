#pragma once

#ifndef _INIMMEDIO_HPP_
#define _INIMMEDIO_HPP_

#include "Inimigo.hpp"

namespace Magisterio::Entidades::Personagens {

    class InimMedio : public Inimigo 
    {
     private:

         int tamanho;

     public:
        InimMedio();
        ~InimMedio() override;

        void executar() override;
        void salvar() override;
    };
}
#endif