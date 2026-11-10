#ifndef PERSONAGEM_HPP_
#define PERSONAGEM_HPP_

#include "Entidade.hpp"

namespace Entidades {
    class Personagem : public Entidade {
    protected:
        int numVidas;

    public:
        Personagem();
        ~Personagem();
        //void salvarDataBuffer() override;
        virtual void executar();
        virtual void salvar();
    };

}
#endif