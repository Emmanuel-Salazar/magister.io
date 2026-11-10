#include "Jogo.hpp"

#include <algorithm>

Jogo::Jogo()
	: janela(sf::VideoMode({ 800, 600 }), "Magister.io - Setas: selecionar | Enter: jogar | Esc: pausar"),
	  menuAtivo(true)
{
}

Jogo::~Jogo() = default;

void Jogo::executar()
{
	while (janela.isOpen())
	{
		processarEventos();
		atualizar(relogio.restart().asSeconds());
		desenhar();
	}
}

void Jogo::processarEventos()
{
	while (const std::optional evento = janela.pollEvent())
	{
		if (evento->is<sf::Event::Closed>())
		{
			janela.close();
			continue;
		}

		if (menuAtivo)
		{
			switch (menu.processarEvento(*evento))
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
		else if (const auto* tecla = evento->getIf<sf::Event::KeyPressed>();
			tecla != nullptr && tecla->code == sf::Keyboard::Key::Escape)
		{
			menu.mostrar();
			menuAtivo = true;
		}
	}
}

void Jogo::atualizar(float deltaTime)
{
	if (menuAtivo)
		return;

	constexpr float velocidade = 250.f;
	float deslocamentoX = 0.f;
	float deslocamentoY = 0.f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		deslocamentoY -= velocidade * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		deslocamentoY += velocidade * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		deslocamentoX -= velocidade * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		deslocamentoX += velocidade * deltaTime;

	jogador.mover(deslocamentoX, deslocamentoY);

	const auto tamanho = janela.getSize();
	const auto posicao = jogador.getPosicao();
	const float raio = jogador.getRaio();
	jogador.setPosicao({
		std::clamp(posicao.x, raio, static_cast<float>(tamanho.x) - raio),
		std::clamp(posicao.y, raio, static_cast<float>(tamanho.y) - raio)
	});
}

void Jogo::desenhar()
{
	janela.clear(sf::Color(30, 30, 45));

	if (menuAtivo)
		menu.desenhar(janela);
	else
		jogador.desenhar(janela);

	janela.display();
}

Entidades::Jogador& Jogo::getJogador()
{
	return jogador;
}

Fases::FasePrimeira& Jogo::getFase()
{
	return fase;
}
