#pragma once

#ifndef _LISTAENTIDADES_HPP_
#define _LISTAENTIDADES_HPP_

#include "Entidade.hpp"
#include "Lista.hpp"
#include <list>


namespace Magisterio::Listas {

	using namespace Entidades;

    class ListaEntidades 
    {
     public:

         Lista<Entidade> LEs;

         ListaEntidades();
		 ~ListaEntidades();
    };
}
#endif // !_LISTAENTIDADES_HPP_