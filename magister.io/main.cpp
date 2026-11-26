#include "Jogo.hpp"
#include "Ente.hpp"
#include "GerenciadorGrafico.hpp"
#include <cstdlib>
#include <ctime>
#include <exception>
#include <iostream>

using namespace Magisterio;

int main() {
	try {
		std::srand(static_cast<unsigned int>(std::time(nullptr)));
		Ente::setGG(Gerenciadores::GerenciadorGrafico::getGerenciadorGrafico());
		Magisterio::Jogo jogo;
		jogo.executar();
	}
	catch (const std::exception& e) {
		std::cerr << "[Erro Fatal] " << e.what() << std::endl;
		return 1;
	}
	return 0;
}