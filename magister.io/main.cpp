#include "Jogo.hpp"
#include "Ente.hpp"
#include "GerenciadorGrafico.hpp"

using namespace Magisterio;

int main() {
	Ente::setGG(Gerenciadores::GerenciadorGrafico::getGerenciadorGrafico());
	Magisterio::Jogo jogo;
	jogo.executar();
}