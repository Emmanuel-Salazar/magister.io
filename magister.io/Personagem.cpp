#include "Personagem.hpp"

namespace Entidades {
	Personagem::Personagem() : numVidas(3), forma(24.f)
	{
		forma.setOrigin({ 24.f, 24.f });
		forma.setPosition({ 400.f, 300.f });
		forma.setFillColor(sf::Color::Green);
	}

	Personagem::~Personagem() = default;

	void Personagem::executar() {}

	void Personagem::salvar() {}

	void Personagem::mover(float deslocamentoX, float deslocamentoY)
	{
		forma.move({ deslocamentoX, deslocamentoY });
		coordenada->setX(static_cast<int>(forma.getPosition().x));
		coordenada->setY(static_cast<int>(forma.getPosition().y));
	}

	void Personagem::desenhar(sf::RenderTarget& destino)
	{
		destino.draw(forma);
	}
}
