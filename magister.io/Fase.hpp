#pragma once

#include "Entidade.hpp"
#include "ListaEntidades.hpp"

namespace Fases {
    class Fase : public Entidades::Entidade {
    protected:
        Entidades::ListaEntidades entidades;
        int numero;

    public:
        explicit Fase(int numero = 0);
        ~Fase() override;
        virtual void criarObstaculos();
        virtual void criarInimigos();
        virtual void criarProjetis();
        void executar() override;
        void salvar() override;
        int getNumero() const;
        Entidades::ListaEntidades& getEntidades();
    };
}
