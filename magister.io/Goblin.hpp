#pragma once

#ifndef _GOBLIN_HPP_
#define _GOBLIN_HPP_

#include "Inimigo.hpp"

namespace Magisterio::Entidades::Personagens {

    class Goblin : public Inimigo 
    {
     public:
        Goblin(sf::Vector2f pos = sf::Vector2f(0.f, 0.f));
        ~Goblin() override;

        void executar() override;
        void perseguir() override;
        void salvar() override;
        void danificar(Jogador* pJogador) override;
    };
}
#endif
