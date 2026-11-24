#pragma once

#ifndef _LISTA_HPP_
#define _LISTA_HPP_

#include <cstddef>
#include <iostream>

using std::cerr;
using std::endl;

namespace Magisterio::Listas {

	template <class TL>
	class Lista
	{
	 private:

		template <class TE>
		class Elemento {
		 private:
			TE* valor;
			Elemento<TE>* proximo = nullptr;

	   	 public:
			Elemento();
			~Elemento();

			void setValor(TE* v);
			TE* getValor() const;

			void setProximo(Elemento<TE>* elemento);
			Elemento<TE>* getProximo() const;
		};


		Elemento<TL>* pPrimeiro;
		Elemento<TL>* pUltimo;
		int len;

	 public:

		Lista();
		~Lista();

		int getLen() const;
		TL* operator[](int posicao) const;
		void push(TL* item);
		void pop(TL* item);
		void limpar();

	};

	template<class TL>
	Lista<TL>::Lista() :
		pPrimeiro(nullptr),
		pUltimo(nullptr),
		len(0)
	{
	}

	template<class TL>
	Lista<TL>::~Lista()
	{
		limpar();
		pPrimeiro = NULL;
		pUltimo = NULL;
		len = -1;
	}

	template<class TL>
	int Lista<TL>::getLen() const
	{
		return len;
	}

	template<class TL>
	TL* Lista<TL>::operator[](int posicao) const
	{
		if (posicao < 0 || posicao >= len)
			return nullptr;

		Elemento<TL>* atual = pPrimeiro;

		if (posicao == 0)
			return atual->getValor();

		for (int i = 0; i < posicao; ++i)
		{
			atual = atual->getProximo();
		}
		return atual->getValor();
	}

	template<class TL>
	void Lista<TL>::push(TL* item)
	{
		if (pPrimeiro == nullptr)
		{
			pPrimeiro = new Elemento<TL>;
			pPrimeiro->setValor(item);
			pUltimo = pPrimeiro;
		}
		else
		{
			Elemento<TL>* temp = new Elemento<TL>;
			temp->setValor(item);
			pUltimo->setProximo(temp);
			pUltimo = temp;
		}
		len++;
	}

	template<class TL>
	void Lista<TL>::pop(TL* item)
	{
		if (pPrimeiro == NULL)
		{
			return;
		}

		Elemento<TL>* temp = pPrimeiro;
		Elemento<TL>* tempAnt = nullptr;

		while (temp != nullptr && temp->getValor() != item)
		{
			tempAnt = temp;
			temp = temp->getProximo();
		}
		if (temp == nullptr)
		{
			return;
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

	template<class TL>
	void Lista<TL>::limpar()
	{
		Elemento<TL>* pAux = NULL;

		while (pPrimeiro != NULL)
		{
			pAux = pPrimeiro->getProximo();
			delete pPrimeiro;
			pPrimeiro = pAux;
		}

		pUltimo = NULL;
		len = 0;
	}
	
	template <class TL>
	template <class TE>
	inline Lista<TL>::Elemento<TE>::Elemento() :
		valor(nullptr),
		proximo(nullptr)
	{
	}

	template <class TL>
	template <class TE>
	inline Lista<TL>::Elemento<TE>::~Elemento()
	{
		proximo = NULL;
		valor = NULL;
	}

	template <class TL>
	template <class TE>
	inline void Lista<TL>::Elemento<TE>::setValor(TE* v)
	{
		if (v == nullptr)
			cerr << "Ponteiro Nulo!" << endl;
		else
			valor = v;
	}

	template <class TL>
	template <class TE>
	inline TE* Lista<TL>::Elemento<TE>::getValor() const
	{
		return valor;
	}

	template <class TL>
	template <class TE>
	inline void Lista<TL>::Elemento<TE>::setProximo(Elemento<TE>* elemento)
	{
		proximo = elemento;
	}

	template <class TL>
	template <class TE>
	inline Lista<TL>::Elemento<TE>* Lista<TL>::Elemento<TE>::getProximo() const
	{
		return proximo;
	}
}
#endif 