#include "GerenciadorGrafico.hpp"

#include <algorithm>

GerenciadorGrafico::GerenciadorGrafico()
	: janela(sf::VideoMode({ 800, 600 }), "Magister.io - Setas: selecionar | Enter: jogar | Esc: sair"),
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

	constexpr float velocidade = 250.f;
	sf::Vector2f movimento;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		movimento.y -= velocidade * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		movimento.y += velocidade * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		movimento.x -= velocidade * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		movimento.x += velocidade * deltaTime;

	personagem.mover(movimento.x, movimento.y);

	const auto tamanho = janela.getSize();
	const auto posicao = personagem.getPosicao();
	const float raio = personagem.getRaio();
	personagem.setPosicao({
		std::clamp(posicao.x, raio, static_cast<float>(tamanho.x) - raio),
		std::clamp(posicao.y, raio, static_cast<float>(tamanho.y) - raio)
	});
}

void GerenciadorGrafico::desenhar()
{
	janela.clear(sf::Color(30, 30, 45));
	if (menuAtivo)
		menu.desenhar(janela);
	else
		personagem.desenhar(janela);
	janela.display();
}
