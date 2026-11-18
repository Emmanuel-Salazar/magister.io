#pragma once

#ifndef _ENTE_HPP_
#define _ENTE_HPP_

#include <SFML/Graphics.hpp>

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
		sf::RectangleShape forma;

	 public:

		 Ente(int i);
		 virtual ~Ente();

		 virtual void executar() = 0;
		 void desenhar();

		 static void setGG(Gerenciadores::GerenciadorGrafico* pGG);
		 sf::Drawable* getForma();

		 void setAltura(float a);
		 float getAltura() const;

		 void setLargura(float l);
		 float getLargura() const;
	};
}
#endif // !_ENTE_HPP_