#pragma once

#ifndef _ELEMENTO_HPP_
#define _ELEMENTO_HPP_

#include <cstddef>

namespace Magisterio::Listas {

	template <class T>
	class Elemento {
	private:
		T valor{};
		Elemento<T>* proximo = nullptr;

	public:
		Elemento();
		~Elemento();

		void setValor(T* valor) { this->valor = valor }
		T& getValor() const { return valor; }

		void setProximo(Elemento<T>* elemento) { proximo = elemento; }
		Elemento<T>* getProximo() const { return proximo; }


	};

	template <class T>
	inline Elemento<T>::Elemento() :
		proximo(nullptr),
		anterior(nullptr)
	{
	}

	template <class T>
	inline Elemento<T>::~Elemento()
	{
	}

	template <class T>
	inline void  Elemento<T>::setValor(T* valor)
	{
		this->valor = valor;
	}

	template <class T>
	inline T& Elemento<T>::getValor() const
	{
		return valor;
	}

	template <class T>
	inline void Elemento<T>::setProximo(Elemento<T>* elemento)
	{
		proximo = elemento;
	}

	template <class T>
	inline Elemento<T>* Elemento<T>::getProximo() const
	{
		return proximo;
	}
}
#endif