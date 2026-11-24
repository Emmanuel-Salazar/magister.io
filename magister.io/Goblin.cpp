#include "Goblin.hpp"
#include "GerenciadorGrafico.hpp"

using namespace Magisterio;
using namespace Entidades;
using namespace Personagens;

Goblin::Goblin(sf::Vector2f pos) : Inimigo(2), tamanho(5)
{
    sf::Texture* tex = pGG->carregarTextura("assets/goblin.png");
    if (tex) {
        tex->setSmooth(false);
        figura = new sf::Sprite(*tex);
        float escala = 1.8f;
        figura->setScale({ escala, escala });
        largura = static_cast<float>(tex->getSize().x) * escala;
        altura = static_cast<float>(tex->getSize().y) * escala;
    }

    coordenada.setPosicao(pos);
    coordAnt.setPosicao(pos);
    if (figura)
        figura->setPosition(pos);
}

Goblin::~Goblin() = default;

void Goblin::executar() {}
void Goblin::salvar() {}
