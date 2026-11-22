#include "Jogo.hpp"
#include <algorithm>

#include "GerenciadorGrafico.hpp"
#include "Jogador.hpp"
#include "Coordenada.hpp"
#include "Ente.hpp"
#include "stdafx.hpp"

using namespace Magisterio;
using namespace Entidades;
using namespace Gerenciadores;
using namespace Personagens;

Magisterio::Jogo::Jogo():
	pGG(Gerenciadores::GerenciadorGrafico::getGerenciadorGrafico()),
	menuAtivo(true)
{
	fase.setJogador(&jogadorUm);
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
				case OpcaoMenu::JogarFase1:
					menu.ocultar();
					menuAtivo = false;
					relogio.restart();
					break;

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
			fase.executar();
		}

		janela->clear(sf::Color(30, 30, 45));

		if (menuAtivo)
			menu.desenhar(*janela);
		else {
			fase.desenhar();
			jogadorUm.desenhar(*janela);
			
		}

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
