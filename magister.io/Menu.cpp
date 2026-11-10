#include "Menu.hpp"

#include <stdexcept>

Menu::Menu()
	: visivel(true), opcaoSelecionada(0), botaoJogar({ 300.f, 80.f }), botaoSair({ 300.f, 80.f })
{
	botaoJogar.setPosition({ 250.f, 210.f });
	botaoSair.setPosition({ 250.f, 310.f });

	if (!fonte.openFromFile("assets/arial.ttf") && !fonte.openFromFile("C:/Windows/Fonts/arial.ttf"))
		throw std::runtime_error("Nao foi possivel carregar a fonte do menu.");

	textoJogar.emplace(fonte, "JOGAR", 30);
	textoSair.emplace(fonte, "SAIR", 30);
	textoJogar->setPosition({ 350.f, 232.f });
	textoSair->setPosition({ 365.f, 332.f });
	textoJogar->setFillColor(sf::Color::White);
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

	if (tecla->code == sf::Keyboard::Key::Up || tecla->code == sf::Keyboard::Key::Down)
		opcaoSelecionada = 1 - opcaoSelecionada;

	if (tecla->code == sf::Keyboard::Key::Enter)
		return opcaoSelecionada == 0 ? OpcaoMenu::Jogar : OpcaoMenu::Sair;

	if (tecla->code == sf::Keyboard::Key::Escape)
		return OpcaoMenu::Retomar;

	return OpcaoMenu::Nenhuma;
}

void Menu::desenhar(sf::RenderTarget& destino)
{
	if (!visivel)
		return;

	botaoJogar.setFillColor(opcaoSelecionada == 0 ? sf::Color::Green : sf::Color(70, 70, 90));
	botaoSair.setFillColor(opcaoSelecionada == 1 ? sf::Color::Red : sf::Color(70, 70, 90));
	destino.draw(botaoJogar);
	destino.draw(botaoSair);
	destino.draw(*textoJogar);
	destino.draw(*textoSair);
}
