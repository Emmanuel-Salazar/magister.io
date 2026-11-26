#include "GerenciadorGrafico.hpp"
#include <iostream>
#include <stdexcept>


using namespace Magisterio;
using namespace Gerenciadores;
using namespace Entidades;
using namespace Personagens;

GerenciadorGrafico* GerenciadorGrafico::pGrafico = nullptr;

//A partir do vídeo do YouTube do monitor 
GerenciadorGrafico::GerenciadorGrafico()
{
	janela.create(sf::VideoMode({ 800, 600}), "Magister.io - Setas: selecionar | Enter: jogar | Esc: sair");
}

GerenciadorGrafico::~GerenciadorGrafico(){}

void GerenciadorGrafico::destruirGGrafico()
{
	if (pGrafico != NULL)
	{
		delete pGrafico;
		pGrafico = NULL;
	}
}

void GerenciadorGrafico::desenharEnte(Ente* pE)
{
	if (!pE) return;

	sf::Sprite* sprite = pE->getFigura();
	if (sprite)
		janela.draw(*sprite);
}

//Trecho de código do GerenciadorGrafico::carregarTextura() retirado do monitor Giovanni (atual)
sf::Texture* GerenciadorGrafico::carregarTextura(const std::string& caminho) {
	auto it = mapaTexturas.find(caminho);
	if (it != mapaTexturas.end())
		return it->second;

	sf::Texture* tex = new sf::Texture();
	bool carregou = tex->loadFromFile(caminho);
	if (!carregou) {
		carregou = tex->loadFromFile("../" + caminho) ||
		           tex->loadFromFile("../../" + caminho) ||
		           tex->loadFromFile("magister.io/" + caminho);
	}

	if (!carregou) {
		delete tex;
		throw std::runtime_error("Nao foi possivel carregar a textura: " + caminho);
	}

	mapaTexturas[caminho] = tex;
	return tex;
}

GerenciadorGrafico* GerenciadorGrafico::getGerenciadorGrafico()
{
	if (pGrafico == NULL)
	{
		pGrafico = new GerenciadorGrafico();
		std::atexit(destruirGGrafico);
	}

	return pGrafico;
}

