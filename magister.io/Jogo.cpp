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
	menuAtivo(true),
	faseAtual(&fase)
{
	fase.setJogador(&jogadorUm);
	faseSegunda.setJogador(&jogadorUm);
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
					faseAtual = &fase;
					jogadorUm.resetar();
					menu.ocultar();
					menuAtivo = false;
					relogio.restart();
					break;

				case OpcaoMenu::JogarFase2:
					faseAtual = &faseSegunda;
					jogadorUm.resetar();
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
			else if (menu.estaConfirmandoSaida())
			{
				switch (menu.processarEventoConfirmacao(*event))
				{
				case OpcaoMenu::ConfirmarSaida:
					menu.ocultarConfirmacaoSaida();
					jogadorUm.resetar();
					menu.mostrar();
					menuAtivo = true;
					break;
				case OpcaoMenu::CancelarSaida:
					menu.ocultarConfirmacaoSaida();
					relogio.restart();
					break;
				default:
					break;
				}
			}
			else if (const auto* tecla = event->getIf<sf::Event::KeyPressed>();
				tecla != nullptr && tecla->code == sf::Keyboard::Key::Escape)
			{
				menu.mostrarConfirmacaoSaida();
			}
		}

		if (!menuAtivo && !menu.estaConfirmandoSaida()) {
			float deltaTime = relogio.restart().asSeconds();
			jogadorUm.mover(deltaTime);
			if (faseAtual)
				faseAtual->executar();

			if (jogadorUm.getNumVidas() <= 0) {
				std::cout << "[Jogo] Jogador sem vidas! Retornando ao menu." << std::endl;
				jogadorUm.resetar();
				menu.mostrar();
				menuAtivo = true;
			}
		}

		janela->clear(sf::Color(30, 30, 45));

		if (menuAtivo)
			menu.desenhar(*janela);
		else {
			if (faseAtual)
				faseAtual->desenhar();
			jogadorUm.desenhar(*janela);
			if (menu.estaConfirmandoSaida())
				menu.desenharConfirmacao(*janela);
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

Fases::FaseSegunda& Magisterio::Jogo::getFaseSegunda()
{
	return faseSegunda;
}
