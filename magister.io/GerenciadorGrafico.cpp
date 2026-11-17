#include "GerenciadorGrafico.hpp"
#include <algorithm>

using namespace Magisterio;
using namespace Gerenciadores;
using namespace Entidades;
using namespace Personagens;

GerenciadorGrafico::GerenciadorGrafico(): 
	janela(sf::VideoMode({ 800, 600 }), "Magister.io - Setas: selecionar | Enter: jogar | Esc: sair"),
	menuAtivo(true)
{
}

void GerenciadorGrafico::executar()
{
	while (janela.isOpen())
	{
		processarEventos();
		atualizar(relogio.restart().asSeconds());
		desenhar();
	}
}

void GerenciadorGrafico::processarEventos()
{
	while (const std::optional event = janela.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
		{
			janela.close();
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
				janela.close();
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
}

void GerenciadorGrafico::atualizar(float deltaTime)
{
	if (menuAtivo)
		return;

	jogador.mover(deltaTime);

	const auto tamanho = janela.getSize();
	const auto posicao = jogador.getPosicao();
	

	jogador.setPosicao({
		std::clamp(posicao.x, 0.0f, static_cast<float>(tamanho.x) - jogador.getLargura()),
		std::clamp(posicao.y, 0.0f, static_cast<float>(tamanho.y) - jogador.getAltura())
	});
}
            
void GerenciadorGrafico::desenhar()
{
	janela.clear(sf::Color(30, 30, 45));
	if (menuAtivo)
		menu.desenhar(janela);
	else
		jogador.desenhar(janela);
	janela.display();
}
