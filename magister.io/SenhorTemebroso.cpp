#include "SenhorTemebroso.hpp"
#include "Jogador.hpp"
#include "Projetil.hpp"
#include "GerenciadorGrafico.hpp"
#include <cmath>
#include <cstdlib>

using namespace Magisterio;
using namespace Entidades;
using namespace Personagens;

SenhorTemebroso::SenhorTemebroso(sf::Vector2f pos) :
    Inimigo(3, 85.f),
    forca(3),
    distanciaAtivacao(350.f),
    ativo(false),
    intervaloDisparo(2.0f + static_cast<float>(std::rand() % 16) * 0.1f)
{
    sf::Texture* tex = pGG->carregarTextura("assets/mago_tenebroso.png");
    if (tex) {
        tex->setSmooth(false);
        figura = new sf::Sprite(*tex);
        float escala = 1.6f;
        figura->setScale({ escala, escala });
        largura = static_cast<float>(tex->getSize().x) * escala;
        altura = static_cast<float>(tex->getSize().y) * escala;
    }

    coordenada.setPosicao(pos);
    coordAnt.setPosicao(pos);
    if (figura)
        figura->setPosition(pos);
}

SenhorTemebroso::~SenhorTemebroso() = default;

void SenhorTemebroso::perseguir() {
    float dt = relogioMovimento.restart().asSeconds();
    if (dt > 0.05f)
        dt = 0.05f;

    if (!pAlvo)
        return;

    sf::Vector2f posMago = getCoordenada();
    sf::Vector2f posAlvo = pAlvo->getCoordenada();

    float centroMagoX = posMago.x + (largura * 0.5f);
    float centroAlvoX = posAlvo.x + 28.f;
    float dx = centroAlvoX - centroMagoX;
    float dy = posAlvo.y - posMago.y;
    float dist = std::hypot(dx, dy);

    if (!ativo) {
        if (dist <= distanciaAtivacao) {
            ativo = true;
            relogioDisparo.restart();
        }
        return;
    }

    if (dx > 10.f) {
        posMago.x += velocidade * dt;
    }
    else if (dx < -10.f) {
        posMago.x -= velocidade * dt;
    }

    if (posMago.x < limiteMinX) {
        posMago.x = limiteMinX;
    }
    else if (posMago.x + largura > limiteMaxX) {
        posMago.x = limiteMaxX - largura;
    }

    setCoordenada(posMago);
}

void SenhorTemebroso::executar() {
    perseguir();
}

void SenhorTemebroso::salvar() {}

short SenhorTemebroso::getForca() const { return forca; }

Projetil* SenhorTemebroso::tentarDisparar(Jogador* pAlvoAtual) {
    if (pAlvoAtual)
        pAlvo = pAlvoAtual;

    if (!pAlvo || !ativo)
        return nullptr;

    if (relogioDisparo.getElapsedTime().asSeconds() < intervaloDisparo)
        return nullptr;

    relogioDisparo.restart();
    intervaloDisparo = 2.0f + static_cast<float>(std::rand() % 16) * 0.1f;

    sf::Vector2f posMago = getCoordenada();
    sf::Vector2f posAlvo = pAlvo->getCoordenada();

    float dir = (posAlvo.x >= posMago.x) ? 1.f : -1.f;
    float saidaX = (dir >= 0.f) ? (posMago.x + largura) : (posMago.x - 68.f);
    float saidaY = posMago.y + (altura * 0.45f);

    Projetil* pProj = new Projetil(
        { saidaX, saidaY },
        dir * 340.f,
        false,
        static_cast<int>(forca),
        "assets/bola_fogo_jogador_mago_tenebroso.png"
    );
    pProj->lancar();
    return pProj;
}
