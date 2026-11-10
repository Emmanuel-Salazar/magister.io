#pragma once

#include <SFML/Graphics.hpp>

enum class OpcaoMenu {
	Nenhuma,
	Jogar,
	Retomar,
	Sair
};

class Menu {
private:
	bool visivel;
	unsigned int opcaoSelecionada;
	sf::RectangleShape botaoJogar;
	sf::RectangleShape botaoSair;

public:
	Menu()
		: visivel(true), opcaoSelecionada(0), botaoJogar({ 300.f, 80.f }), botaoSair({ 300.f, 80.f })
	{
		botaoJogar.setPosition({ 250.f, 210.f });
		botaoSair.setPosition({ 250.f, 310.f });
	}

	~Menu() = default;

	void executar() {}
	void mostrar() { visivel = true; }
	void ocultar() { visivel = false; }
	bool estaVisivel() const { return visivel; }

	OpcaoMenu processarEvento(const sf::Event& evento)
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

	void desenhar(sf::RenderTarget& destino)
	{
		if (!visivel)
			return;

		botaoJogar.setFillColor(opcaoSelecionada == 0 ? sf::Color::Green : sf::Color(70, 70, 90));
		botaoSair.setFillColor(opcaoSelecionada == 1 ? sf::Color::Red : sf::Color(70, 70, 90));
		destino.draw(botaoJogar);
		destino.draw(botaoSair);
	}
};
