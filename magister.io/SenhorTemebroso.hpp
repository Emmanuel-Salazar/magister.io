#pragma once

#ifndef _SENHORTEMEBROSO_HPP_
#define _SENHORTEMEBROSO_HPP_

#include "Inimigo.hpp"

namespace Magisterio::Entidades::Personagens {
 
    class SenhorTemebroso : public Inimigo {
     private:

        short forca;

     public:

        SenhorTemebroso();
        ~SenhorTemebroso() override;
        void executar() override;
        void salvar() override;
        short getForca() const;
    };
}
#endif
