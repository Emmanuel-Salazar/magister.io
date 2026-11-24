#pragma once

#ifndef _GOBLIN_HPP_
#define _GOBLIN_HPP_

#include "Inimigo.hpp"

namespace Magisterio::Entidades::Personagens {

    class Goblin : public Inimigo 
    {
     private:

         int tamanho;

     public:
        Goblin();
        ~Goblin() override;

        void executar() override;
        void salvar() override;
    };
}
#endif
