#include "GerenciadorGrafico.hpp"


using namespace Magisterio;
using namespace Gerenciadores;
using namespace Entidades;
using namespace Personagens;

GerenciadorGrafico* GerenciadorGrafico::pGrafico = nullptr;

GerenciadorGrafico::GerenciadorGrafico()
{
	janela.create(sf::VideoMode({ 704, 544}), "Magister.io - Setas: selecionar | Enter: jogar | Esc: sair");
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
	if (pE != nullptr)
	{
			janela.draw(pE->getFigura());
	}
}

sf::Texture* GerenciadorGrafico::carregarTextura(const std::string& caminho) {
	auto it = mapaTexturas.find(caminho);
	if (it != mapaTexturas.end())
		return it->second;

	sf::Texture* tex = new sf::Texture();
	if (!tex->loadFromFile(caminho)) {
		delete tex;
		return nullptr;
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

