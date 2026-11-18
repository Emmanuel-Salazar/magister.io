#include "Jogo.hpp"
#include <algorithm>

#include "GerenciadorGrafico.hpp"

using namespace Magisterio;
using namespace Entidades;
using namespace Gerenciadores;
using namespace Personagens;

Magisterio::Jogo::Jogo():
	pGG(pGG->getGerenciadorGrafico())
{
	menuAtivo = true;
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

		const auto tamanho = janela->getSize();
		const auto posicao = jogadorUm.getPosicao();

		jogadorUm.setPosicao({
			std::clamp(posicao.x, 0.0f, static_cast<float>(tamanho.x) - jogadorUm.getLargura()),
			std::clamp(posicao.y, 0.0f, static_cast<float>(tamanho.y) - jogadorUm.getAltura())
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
