#pragma once

#ifndef _ESQUELETO_HPP_
#define _ESQUELETO_HPP_

#include "Inimigo.hpp"

namespace Magisterio::Entidades::Personagens {

    class Esqueleto : public Inimigo {

     private:

         float raio;

     public:

        Esqueleto();
        ~Esqueleto() override;

        void executar() override;
        void salvar() override;
    };
}
#endif
