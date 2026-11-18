#pragma once

#ifndef _LISTA_HPP_
#define _LISTA_HPP_

#include "Elemento.hpp"
#include <list>
#include <cstddef>

namespace Magisterio::Listas {

	template <class T>
	class Lista 
	{
	 private:

		 Elemento<T>* pPrimeiro;
		 Elemento<T>* pUltimo;
		 int len;

	 public:

		Lista() = default;
		~Lista() = default;

		int getLen() const;
		T* getItem(int posicao) const;
		void push(T* item);
		void pop(T* item);
		
	};

	template<class T>
	Lista<T>::Lista(): 
		pPrimeiro(nullptr), 
		pUltimo(nullptr), 
		len(0)
	{ }

	template<class T>
	int Lista<T>::getLen() const
	{
		return len;
	}

	template<class T>
	T* Lista<T>::getItem(int posicao) const
	{
		if (posicao < 0 || posicao >= len)
			return nullptr;

		Elemento<T>* atual = pPrimeiro;

		if(posicao == 0)
			return atual->getValor();

		for (int i = 0; i < posicao; ++i)
		{
			atual = atual->getProximo();
		}
		return atual->getValor();
	}

	template<class T>
	void Lista<T>::push(T* item)
	{
		if (pPrimeiro == nullptr) 
		{
			pPrimeiro = new Elemento<T>;
			pPrimeiro->setValor(item);
			pUltimo = pPrimeiro;
		}
		else
		{
			Elemento<T>* temp = new Elemento<T>;
			temp->setValor(item);
			pUltimo->setProximo(temp);
			pUltimo = temp;
		}
		len++;
	}

	template<class T>
	void Lista<T>::pop(T* item)
	{
		Elemento<T>* temp = pPrimeiro;
		Elemento<T>*tempAnt = nullptr;

		while (temp->getValor() != item)
		{
			tempAnt = temp;
			temp = temp->getProximo();
		}
		if (temp == pPrimeiro)
		{
			pPrimeiro = temp->getProximo();

		}
		else if (temp == pUltimo)
		{
			pUltimo = tempAnt;
			pUltimo->setProximo(nullptr);
		}
		else
		{
			tempAnt->setProximo(temp->getProximo());
		}
		delete temp;
		len--;
	}
}
#endif // !_LISTA_HPP_