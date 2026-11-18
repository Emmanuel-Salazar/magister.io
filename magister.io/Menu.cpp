#include "Menu.hpp"
#include <stdexcept>

using namespace Magisterio;

Menu::Menu()
	: visivel(true), 
    opcaoSelecionada(0), 
    botaoFase1({ 300.f, 80.f }), 
    botaoFase2({ 300.f, 80.f }), 
    botaoSair({ 300.f, 80.f }),
	pJogo(nullptr)
{
	botaoFase1.setPosition({ 250.f, 210.f });
	botaoFase2.setPosition({ 250.f, 310.f });
	botaoSair.setPosition({ 250.f, 410.f });

	if (!fonte.openFromFile("assets/arial.ttf") && !fonte.openFromFile("C:/Windows/Fonts/arial.ttf"))
		throw std::runtime_error("Nao foi possivel carregar a fonte do menu.");

	textoFase1.emplace(fonte, "FASE 1", 30);
	textoFase2.emplace(fonte, "FASE 2", 30);
	textoSair.emplace(fonte, "SAIR", 30);

	textoFase1->setPosition({ 350.f, 232.f });
	textoFase2->setPosition({ 360.f, 332.f });
	textoSair->setPosition({ 375.f, 432.f });

	textoFase1->setFillColor(sf::Color::White);
	textoFase2->setFillColor(sf::Color::White);
	textoSair->setFillColor(sf::Color::White);
}

Menu::~Menu() = default;

void Menu::executar() {}

void Menu::mostrar() { visivel = true; }

void Menu::ocultar() { visivel = false; }

bool Menu::estaVisivel() const { return visivel; }

OpcaoMenu Menu::processarEvento(const sf::Event& evento)
{
    const auto* tecla = evento.getIf<sf::Event::KeyPressed>();
    if (tecla == nullptr)
        return OpcaoMenu::Nenhuma;

    if (tecla->code == sf::Keyboard::Key::Up)
    {
        if (opcaoSelecionada > 0)
            opcaoSelecionada--;
        else
            opcaoSelecionada = 2; 
    }
    else if (tecla->code == sf::Keyboard::Key::Down)
    {
        if (opcaoSelecionada < 2)
            opcaoSelecionada++;
        else
            opcaoSelecionada = 0;
    }
    if (tecla->code == sf::Keyboard::Key::Enter)
    {
        switch (opcaoSelecionada)
        {
        case 0: return OpcaoMenu::Jogar;
        case 1: return OpcaoMenu::Retomar; 
        case 2: return OpcaoMenu::Sair;
        default: return OpcaoMenu::Nenhuma;
        }
    }

    if (tecla->code == sf::Keyboard::Key::Escape)
        return OpcaoMenu::Retomar;

    return OpcaoMenu::Nenhuma;
}

void Menu::desenhar(sf::RenderWindow& destino)
{
	if (!visivel)
		return;

	botaoFase1.setFillColor(opcaoSelecionada == 0 ? sf::Color::Green : sf::Color(70, 70, 90));
	botaoFase2.setFillColor(opcaoSelecionada == 1 ? sf::Color::Green : sf::Color(70, 70, 90));
	botaoSair.setFillColor(opcaoSelecionada == 2 ? sf::Color::Red : sf::Color(70, 70, 90));
	destino.draw(botaoFase1);
	destino.draw(botaoFase2);
	destino.draw(botaoSair);
	destino.draw(*textoFase1);
	destino.draw(*textoFase2);
	destino.draw(*textoSair);
}
