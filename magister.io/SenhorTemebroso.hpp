#pragma once

#ifndef _SENHORTEMEBROSO_HPP_
#define _SENHORTEMEBROSO_HPP_

#include "Inimigo.hpp"

namespace Magisterio::Entidades {
    class Projetil;
}

namespace Magisterio::Entidades::Personagens {
 
    class SenhorTemebroso : public Inimigo {
     private:

        short forca;
        float velocidade;
        float distanciaAtivacao;
        bool ativo;
        float intervaloDisparo;
        Jogador* pAlvo;
        sf::Clock relogioMovimento;
        sf::Clock relogioDisparo;

     public:

        SenhorTemebroso(sf::Vector2f pos = sf::Vector2f(0.f, 0.f));
        ~SenhorTemebroso() override;
        void executar() override;
        void perseguir() override;
        void salvar() override;
        short getForca() const;
        void setAlvo(Jogador* pJ);
        Entidades::Projetil* tentarDisparar(Jogador* pAlvoAtual);
    };
}
#endif
