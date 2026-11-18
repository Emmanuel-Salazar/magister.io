#include "Jogo.hpp"
#include <algorithm>

#include "GerenciadorGrafico.hpp"
#include "Jogador.hpp"
#include "Coordenada.hpp"
#include "Ente.hpp"
#include "stdafx.hpp"
#include "GerenciadorGrafico.hpp"

using namespace Magisterio;
using namespace Entidades;
using namespace Gerenciadores;
using namespace Personagens;

Magisterio::Jogo::Jogo():
	pGG(Gerenciadores::GerenciadorGrafico::getGerenciadorGrafico()),
	menuAtivo(true)
{
}

Magisterio::Jogo::~Jogo() = default;

void Magisterio::Jogo::executar()
{
	sf::RenderWindow* janela = pGG->getJanela();

	while (janela->isOpen())
	{

		while (const std::optional event = janela->pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				janela->close();
				continue;
			}

			if (menuAtivo)
			{
				switch (menu.processarEvento(*event))
				{
				case OpcaoMenu::Jogar:
				case OpcaoMenu::Retomar:
					menu.ocultar();
					menuAtivo = false;
					relogio.restart();
					break;
				case OpcaoMenu::Sair:
					janela->close();
					break;
				default:
					break;
				}
			}
			else if (const auto* tecla = event->getIf<sf::Event::KeyPressed>();
				tecla != nullptr && tecla->code == sf::Keyboard::Key::Escape)
			{
				menu.mostrar();
				menuAtivo = true;
			}
		}

		if (!menuAtivo) {
			float deltaTime = relogio.restart().asSeconds();
			jogadorUm.mover(deltaTime);
		}

		const auto  tamanho = janela->getSize();
		sf::Vector2f posicao = jogadorUm.getCoordenada();

		const float maxX = static_cast<float>(tamanho.x) - static_cast<float>(jogadorUm.getLargura());
		const float maxY = static_cast<float>(tamanho.y) - static_cast<float>(jogadorUm.getAltura());


		float xLimitado = std::clamp<float>(posicao.x, 0.0f, maxX);
		float yLimitado = std::clamp<float>(posicao.y, 0.0f, maxY);

		jogadorUm.setCoordenada({
			sf::Vector2f(static_cast<float>(xLimitado), static_cast<float>(yLimitado))
			});

		janela->clear(sf::Color(30, 30, 45));

		if (menuAtivo)
			menu.desenhar(*janela);
		else
			jogadorUm.desenhar(*janela);

		janela->display();

	} 
}


Entidades::Personagens::Jogador& Magisterio::Jogo::getJogadorUm()
{
	return jogadorUm;
}

Fases::FasePrimeira& Magisterio::Jogo::getFase()
{
	return fase;
}
