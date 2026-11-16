#pragma once

#ifndef _INIMFACIL_HPP_
#define _INIMFACIL_HPP_

#include "Inimigo.hpp"

namespace Magisterio::Entidades::Personagens {

    class InimFacil : public Inimigo {

     private:

         float raio;

     public:

        InimFacil();
        ~InimFacil() override;

        void executar() override;
        void salvar() override;
    };
}
#endif