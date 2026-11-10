#ifndef GERENCIADOR_GRAFICO_CPP_
#define GERENCIADOR_GRAFICO_CPP_

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Personagem.hpp"
#include "Menu.hpp"

class GerenciadorGrafico {
private:
	sf::RenderWindow janela;
	Entidades::Personagem personagem;
	Menu menu;
	bool menuAtivo;
	sf::Clock relogio;

	void processarEventos();
	void atualizar(float deltaTime);
	void desenhar();

public:
	GerenciadorGrafico();
	void executar();
};

#endif