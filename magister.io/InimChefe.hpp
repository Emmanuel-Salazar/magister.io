#pragma once

#ifndef _INIMCHEFE_HPP_
#define _INIMCHEFE_HPP_

#include "Inimigo.hpp"

namespace Magisterio::Entidades::Personagens {
 
    class InimChefe : public Inimigo {
     private:

        short forca;

     public:

        InimChefe();
        ~InimChefe() override;
        void executar() override;
        void salvar() override;
        short getForca() const;
    };
}
#endif