#include "Jogo.hpp"
#include "Ente.hpp"
#include "GerenciadorGrafico.hpp"
#include <cstdlib>
#include <ctime>

using namespace Magisterio;

int main() {
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	Ente::setGG(Gerenciadores::GerenciadorGrafico::getGerenciadorGrafico());
	Magisterio::Jogo jogo;
	jogo.executar();
}