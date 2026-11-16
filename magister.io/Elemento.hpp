#pragma once

#ifndef _ELEMENTO_HPP_
#define _ELEMENTO_HPP_

#include <cstddef>

namespace Magisterio::Listas {

	template <typename T>
	class Elemento {
	private:
		T valor{};
		Elemento<T>* proximo = nullptr;
		Elemento<T>* anterior = nullptr;

	public:
		Elemento() = default;
		explicit Elemento(const T& valor) : valor(valor) {}

		T& getValor() { return valor; }
		const T& getValor() const { return valor; }
		Elemento<T>* getProximo() const { return proximo; }
		Elemento<T>* getAnterior() const { return anterior; }
		void setProximo(Elemento<T>* elemento) { proximo = elemento; }
		void setAnterior(Elemento<T>* elemento) { anterior = elemento; }
	};
}
#endif