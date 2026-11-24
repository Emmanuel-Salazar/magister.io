#include "Fase.hpp"
#include "GerenciadorGrafico.hpp"
#include "Jogador.hpp"
#include "Plataforma.hpp"
#include <cstdlib>

using namespace Magisterio;
using namespace Fases;
using namespace Entidades;
using namespace Personagens;
using namespace Obstaculos;

Fase::Fase() :
    Ente(),
    numJogadores(0),
    pJ1(nullptr),
    pJ2(nullptr),
    minPlataformas(3),
    maxPlataformas(5)
{
	criarCenario();
}

Fase::~Fase() {
    limparEntidades();
}

void Fase::executar() {}

void Fase::criarCenario() {
    chao.setSize(sf::Vector2f(800.f, 30.f));
    sf::Color blue(27, 14, 10, 255);
    chao.setFillColor(blue);
    chao.setPosition(sf::Vector2f(0.f, 585.f));
}

void Fase::limparEntidades() {
    int tam = entidades.tamanho();
    for (int i = 0; i < tam; i++) {
        delete entidades[i];
    }
    entidades.limpar();
    gc.limparObstaculos();
    gc.limparInimigos();
}

std::vector<sf::Vector2f> Fase::gerarPosicoesNoChao(int qntd, float alt) const {
    const float topoChaoY = 585.f;
    const float y = topoChaoY - alt;

    // 6 zonas horizontais bem espaçadas após o spawn do jogador ({0, 500})
    std::vector<float> zonasX = { 120.f, 230.f, 340.f, 450.f, 560.f, 670.f };

    // Embaralha as zonas (Fisher-Yates)
    for (int i = static_cast<int>(zonasX.size()) - 1; i > 0; i--) {
        int j = std::rand() % (i + 1);
        std::swap(zonasX[i], zonasX[j]);
    }

    int total = (qntd < static_cast<int>(zonasX.size())) ? qntd : static_cast<int>(zonasX.size());
    std::vector<sf::Vector2f> posicoes;
    posicoes.reserve(total);

    for (int i = 0; i < total; i++) {
        float jitterX = static_cast<float>(std::rand() % 35); // pequena variação natural dentro da zona
        posicoes.emplace_back(zonasX[i] + jitterX, y);
    }

    return posicoes;
}

void Fase::criarPlataformas() {
    // Física do jogador: forcaPulo = -650, gravidade = 1200 -> altura máxima do pulo ≈ 176px.
    // Altura mínima em relação ao chão e entre andares próxima ao limite do pulo (155px, margem de ~21px):
    const float topoChaoY = 585.f;
    const float alturaPuloUtil = 155.f;
    const float yAndar1 = topoChaoY - alturaPuloUtil; // 430.f
    const float yAndar2 = yAndar1 - alturaPuloUtil;   // 275.f

    // Layout em 2 andares alinhados (160x35 cada plataforma):
    std::vector<sf::Vector2f> andar1 = {
        { 90.f,  yAndar1 },
        { 320.f, yAndar1 },
        { 550.f, yAndar1 }
    };

    std::vector<sf::Vector2f> andar2 = {
        { 205.f, yAndar2 },
        { 435.f, yAndar2 }
    };

    // Embaralha cada andar
    for (int i = static_cast<int>(andar1.size()) - 1; i > 0; i--) {
        int j = std::rand() % (i + 1);
        std::swap(andar1[i], andar1[j]);
    }
    for (int i = static_cast<int>(andar2.size()) - 1; i > 0; i--) {
        int j = std::rand() % (i + 1);
        std::swap(andar2[i], andar2[j]);
    }

    int qntd = std::rand() % (maxPlataformas - minPlataformas + 1) + minPlataformas;

    // Garante pelo menos 2 plataformas no Andar 1 para sempre ser possível subir ao Andar 2
    std::vector<sf::Vector2f> selecionadas;
    selecionadas.push_back(andar1[0]);
    selecionadas.push_back(andar1[1]);

    // Pool com os slots restantes (1 do andar 1 + 2 do andar 2)
    std::vector<sf::Vector2f> restantes = { andar1[2], andar2[0], andar2[1] };
    for (int i = static_cast<int>(restantes.size()) - 1; i > 0; i--) {
        int j = std::rand() % (i + 1);
        std::swap(restantes[i], restantes[j]);
    }

    for (size_t i = 0; i < restantes.size() && static_cast<int>(selecionadas.size()) < qntd; i++) {
        selecionadas.push_back(restantes[i]);
    }

    for (const auto& pos : selecionadas) {
        Plataforma* pPlat = new Plataforma(pos);
        if (pPlat) {
            entidades.inserir(pPlat);
            gc.incluirObstaculo(pPlat);
        }
    }
}

void Fase::reiniciar() {
    limparEntidades();
    criarPlataformas();
    criarObstaculos();
    criarInimigos();
}

void Fase::desenhar() 
{
    Ente::desenhar();
    if (pGG && pGG->getJanela()) 
    {
        pGG->getJanela()->draw(chao); 
        
        int i;
        for (i =0; i < entidades.tamanho(); i++) 
        {
            auto* ent = entidades[i];
            if(ent)
				ent->desenhar(*pGG->getJanela());
        }
    }
}

void Fase::setJogador(Jogador* pJ) 
{
    pJ1 = pJ;
    gc.setJogador1(pJ);
}

Listas::ListaEntidades& Fase::getEntidades() { return entidades; }

