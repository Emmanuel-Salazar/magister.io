#pragma once

#ifndef _ESQUELETO_HPP_
#define _ESQUELETO_HPP_

#include "Inimigo.hpp"

namespace Magisterio::Entidades::Personagens {

    class Esqueleto : public Inimigo {

     private:

         float raio;
         float velocidade;
         int direcao;
         float intervaloTroca;
         sf::Clock relogioMovimento;
         sf::Clock relogioTrocaDirecao;

     public:

        Esqueleto(sf::Vector2f pos = sf::Vector2f(0.f, 0.f));
        ~Esqueleto() override;

        void executar() override;
        void salvar() override;
        void danificar(Jogador* pJogador) override;
    };
}
#endif
