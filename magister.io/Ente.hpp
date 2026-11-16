#pragma once

#ifndef _ENTE_HPP_
#define  _ENTE_HPP_

class GerenciadorGrafico;

namespace Magisterio {

	class Ente {

	 protected:

		int id;
		static GerenciadorGrafico* pGG;

	 public:

		 Ente();
		 virtual ~Ente();
		 virtual void executar() = 0;
		 void desenhar();
		 static void setGG(GerenciadorGrafico* pGG);
	};
}
#endif // !_ENTE_HPP_