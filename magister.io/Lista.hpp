#pragma once

#include <list>
#include <cstddef>

template <typename T>
class Lista {
private:
	std::list<T> elementos;

public:
	Lista() = default;
	~Lista() = default;

	void inserir(const T& elemento) { elementos.push_back(elemento); }
	void remover(const T& elemento) { elementos.remove(elemento); }
	std::size_t tamanho() const { return elementos.size(); }
	bool vazia() const { return elementos.empty(); }
	void limpar() { elementos.clear(); }

	typename std::list<T>::iterator begin() { return elementos.begin(); }
	typename std::list<T>::iterator end() { return elementos.end(); }
	typename std::list<T>::const_iterator begin() const { return elementos.begin(); }
	typename std::list<T>::const_iterator end() const { return elementos.end(); }
};
