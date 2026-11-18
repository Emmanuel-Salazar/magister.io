#pragma once

#ifndef _ENTIDADE_HPP_
#define _ENTIDADE_HPP_

#include "stdafx.hpp"
#include "Coordenada.hpp"
#include "Ente.hpp"

#include <SFML/Graphics.hpp>

namespace Magisterio::Entidades{
    
	float const Entidade::gravidade = 10.f;

    class Entidade : public Ente 
    {
     protected:

        Coordenada* coordenada;
        
        ofstream* buffer;

        sf::RectangleShape forma;

        void salvarDataBuffer();

     public:

        Entidade();
        virtual ~Entidade();

        virtual void executar() = 0;
        virtual void salvar() = 0;

        void desenhar(sf::RenderTarget& destino);
        
        sf::Vector2f getPosicao() const;
        void setPosicao(sf::Vector2f posicao);

        Coordenada* getCoordenada() const;
    };
}
#endif