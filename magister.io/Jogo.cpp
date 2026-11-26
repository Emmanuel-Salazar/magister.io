#include "Jogo.hpp"
#include <algorithm>

#include "GerenciadorGrafico.hpp"
#include "Jogador.hpp"
#include "Projetil.hpp"
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
	doisJogadores(false),
	faseSelecionada(1),
	jogadorUm(1),
	jogadorDois(2),
	fase(&jogadorUm),
	faseSegunda(&jogadorUm),
	faseAtual(&fase)
{
	menu.setJogo(this);
	jogadorUm.setFaseAtual(faseAtual);
}

Magisterio::Jogo::~Jogo() = default;

void Magisterio::Jogo::iniciarFase(int numFase, bool modoDoisJogadores)
{
	doisJogadores = modoDoisJogadores;
	faseSelecionada = numFase;

	jogadorUm.setNome(menu.getNomeJogador1());
	jogadorDois.setNome(menu.getNomeJogador2());
	jogadorUm.resetar();
	jogadorDois.resetar();

	if (numFase == 2)
		faseAtual = &faseSegunda;
	else
		faseAtual = &fase;

	faseAtual->reiniciar();
	faseAtual->setJogadores(&jogadorUm, doisJogadores ? &jogadorDois : nullptr);

	menu.ocultar();
	menuAtivo = false;
	relogio.restart();
}

void Magisterio::Jogo::registrarRanking()
{
	auto registrarJogador = [this](const Jogador& jog) {
		int pts = jog.getPontos();
		if (pts <= 0)
			return;

		const std::string& nomeStr = jog.getNome();
		std::wstring nomeW(nomeStr.begin(), nomeStr.end());

		auto it = std::find_if(ranking.begin(), ranking.end(), [&nomeW](const RegistroRanking& r) {
			return r.descricao == nomeW;
		});

		if (it != ranking.end()) {
			if (pts > it->pontos)
				it->pontos = pts;
		}
		else {
			ranking.push_back({ nomeW, pts });
		}
	};

	registrarJogador(jogadorUm);
	if (doisJogadores)
		registrarJogador(jogadorDois);

	std::sort(ranking.begin(), ranking.end(), [](const RegistroRanking& a, const RegistroRanking& b) {
		return a.pontos > b.pontos;
	});

	if (ranking.size() > 5)
		ranking.resize(5);
}

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
					faseSelecionada = 1;
					menu.mostrarSelecaoJogadores();
					break;

				case OpcaoMenu::JogarFase2:
					faseSelecionada = 2;
					menu.mostrarSelecaoJogadores();
					break;

				case OpcaoMenu::Iniciar1Jogador:
					iniciarFase(faseSelecionada, false);
					break;

				case OpcaoMenu::Iniciar2Jogadores:
					iniciarFase(faseSelecionada, true);
					break;

				case OpcaoMenu::Ranking:
					menu.mostrarRanking();
					break;

				case OpcaoMenu::Retomar:
					menu.ocultar();
					menuAtivo = false;
					jogadorUm.reiniciarRelogio();
					jogadorDois.reiniciarRelogio();
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
					registrarRanking();
					menu.ocultarConfirmacaoSaida();
					jogadorUm.resetar();
					jogadorDois.resetar();
					menu.mostrar();
					menuAtivo = true;
					break;
				case OpcaoMenu::CancelarSaida:
					menu.ocultarConfirmacaoSaida();
					jogadorUm.reiniciarRelogio();
					jogadorDois.reiniciarRelogio();
					relogio.restart();
					break;
				default:
					break;
				}
			}
			else if (const auto* tecla = event->getIf<sf::Event::KeyPressed>())
			{
				if (tecla->code == sf::Keyboard::Key::Escape)
				{
					menu.mostrarConfirmacaoSaida();
				}
				else if (tecla->code == sf::Keyboard::Key::F)
				{
					if (jogadorUm.getNumVidas() > 0)
						jogadorUm.atacar();
				}
				else if (tecla->code == sf::Keyboard::Key::J)
				{
					if (doisJogadores && jogadorDois.getNumVidas() > 0)
						jogadorDois.atacar();
				}
			}
			else if (const auto* clique = event->getIf<sf::Event::MouseButtonPressed>();
				clique != nullptr && clique->button == sf::Mouse::Button::Left)
			{
				if (!doisJogadores && jogadorUm.getNumVidas() > 0)
					jogadorUm.atacar();
			}
		}

		if (!menuAtivo && !menu.estaConfirmandoSaida()) {
			relogio.restart();

			if (jogadorUm.getNumVidas() > 0)
				jogadorUm.executar();

			if (doisJogadores && jogadorDois.getNumVidas() > 0)
				jogadorDois.executar();

			if (faseAtual)
				faseAtual->executar();

			bool todosMortos = (jogadorUm.getNumVidas() <= 0) &&
			                   (!doisJogadores || jogadorDois.getNumVidas() <= 0);
			bool faseConcluida = (faseAtual != nullptr && !faseAtual->temInimigosVivos());

			if (todosMortos || faseConcluida) {
				registrarRanking();
				jogadorUm.resetar();
				jogadorDois.resetar();
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

			if (jogadorUm.getNumVidas() > 0)
				jogadorUm.desenhar(*janela);
			jogadorUm.desenharBarraVida(*janela);

			if (doisJogadores) {
				if (jogadorDois.getNumVidas() > 0)
					jogadorDois.desenhar(*janela);
				jogadorDois.desenharBarraVida(*janela);
			}

			if (menu.estaConfirmandoSaida())
				menu.desenharConfirmacao(*janela);
		}

		janela->display();
	}
}

const Entidades::Personagens::Jogador& Magisterio::Jogo::getJogadorUm() const
{
	return jogadorUm;
}

const Entidades::Personagens::Jogador& Magisterio::Jogo::getJogadorDois() const
{
	return jogadorDois;
}

bool Magisterio::Jogo::isDoisJogadores() const
{
	return doisJogadores;
}

int Magisterio::Jogo::getPontosPartidaAtual() const
{
	return doisJogadores ? (jogadorUm.getPontos() + jogadorDois.getPontos()) : jogadorUm.getPontos();
}

const std::vector<RegistroRanking>& Magisterio::Jogo::getRanking() const
{
	return ranking;
}

const Fases::FasePrimeira& Magisterio::Jogo::getFase() const
{
	return fase;
}

const Fases::FaseSegunda& Magisterio::Jogo::getFaseSegunda() const
{
	return faseSegunda;
}
