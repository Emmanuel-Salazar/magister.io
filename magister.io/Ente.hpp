#pragma once

#ifndef _ENTE_HPP_
#define _ENTE_HPP_

#include "Coordenada.hpp"
#include "stdafx.hpp"

namespace Magisterio {
namespace Gerenciadores {
	class GerenciadorGrafico;
}
}



namespace Magisterio {

	class Ente {
	 protected:

		int id;
		float altura;
		float largura;
		static Gerenciadores::GerenciadorGrafico* pGG;
		sf::Sprite* figura;
		static int cont;
		Coordenada* coordenada;

	 public:

		 Ente();
		 virtual ~Ente();
		 virtual void executar() = 0;
		 void desenhar();
		 static void setGG(Gerenciadores::GerenciadorGrafico* pGG);

		 void setAltura(float a);
		 float getAltura() const;

		 void setLargura(float l);
		 float getLargura() const;

		 sf::Sprite getFigura();

		 virtual void desenhar(sf::RenderTarget& destino);
		 sf::Vector2f getCoordenada() const;
		 void setCoordenada(sf::Vector2f novaCoordenada);
	};
}
#endif