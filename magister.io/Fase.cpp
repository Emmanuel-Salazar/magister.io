#include "Fase.hpp"
#include "GerenciadorGrafico.hpp"
#include "Jogador.hpp"
#include "Inimigo.hpp"
#include "Plataforma.hpp"
#include "Projetil.hpp"
#include <cmath>
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
    maxPlataformas(5),
    minGoblins(2),
    maxGoblins(rand() % 2 + 3)
{
	criarCenario();
}

Fase::Fase(Jogador* pJog1, Jogador* pJog2) :
    Fase()
{
    setJogadores(pJog1, pJog2);
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
    plataformasCriadas.clear();
    gc.limparObstaculos();
    gc.limparInimigos();
    gc.limparProjeteis();
}

//a partir de ajuda dos monitores Pedro, Gico e dicas do pessoal do PETECO
std::vector<sf::Vector2f> Fase::gerarPosicoesNoChao(int qntd, float alt) const {
    const float topoChaoY = 585.f;
    const float y = topoChaoY - alt;

    // 6 zonas horizontais bem espaçadas após o spawn do jogador ({0, 500})
    std::vector<float> zonasX = { 120.f, 230.f, 340.f, 450.f, 560.f, 670.f };

    for (int i = static_cast<int>(zonasX.size()) - 1; i > 0; i--) {
        int j = std::rand() % (i + 1);
        std::swap(zonasX[i], zonasX[j]);
    }

    int total = (qntd < static_cast<int>(zonasX.size())) ? qntd : static_cast<int>(zonasX.size());
    std::vector<sf::Vector2f> posicoes;
    posicoes.reserve(total);

    for (int i = 0; i < total; i++) {
        float jitterX = static_cast<float>(std::rand() % 35);
        posicoes.emplace_back(zonasX[i] + jitterX, y);
    }

    return posicoes;
}

//com ajuda do integrante do PETECO João Pedro
void Fase::criarPlataformas() {
    // Física do jogador: forcaPulo = -650, gravidade = 1200 -> altura máxima do pulo ≈ 176px.
    // Altura mínima em relação ao chão e entre andares próxima ao limite do pulo (155px, margem de ~21px):
    const float topoChaoY = 585.f;
    const float alturaPuloUtil = 155.f;
    const float yAndar1 = topoChaoY - alturaPuloUtil;
    const float yAndar2 = yAndar1 - alturaPuloUtil;   

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
            if (pPlat->getFigura()) {
                plataformasCriadas.push_back(pPlat->getFigura()->getGlobalBounds());
            }
            entidades.inserir(pPlat);
            gc.incluirObstaculo(pPlat);
        }
    }
}

void Fase::posicionarInimigo(Inimigo* pInim, bool emPlataforma, std::vector<size_t>& plataformasLivres) {
    if (!pInim)
        return;

    float larg = 72.f;
    float alt = 78.f;
    if (pInim->getFigura()) {
        sf::FloatRect bounds = pInim->getFigura()->getGlobalBounds();
        larg = bounds.size.x;
        alt = bounds.size.y;
    }

    if (emPlataforma && !plataformasLivres.empty()) {
        size_t idx = plataformasLivres.back();
        plataformasLivres.pop_back();
        const sf::FloatRect& plat = plataformasCriadas[idx];

        float faixaPlat = plat.size.x - larg;
        float offsetX = (faixaPlat > 1.f) ? static_cast<float>(std::rand() % static_cast<int>(faixaPlat)) : 0.f;
        float posX = plat.position.x + offsetX;
        float posY = plat.position.y - alt;

        pInim->setCoordenada({ posX, posY });
        pInim->setLimitesPatrulha(plat.position.x, plat.position.x + plat.size.x);
    }
    else {
        float minX = 180.f;
        int faixaX = static_cast<int>(790.f - larg - minX);
        if (faixaX < 1) faixaX = 1;

        float posX = minX + static_cast<float>(std::rand() % faixaX);
        float posY = 585.f - alt;

        pInim->setCoordenada({ posX, posY });
        pInim->setLimitesPatrulha(10.f, 790.f);
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
    setJogadores(pJ, nullptr);
}

//base do monitor Pedro
void Fase::setJogadores(Jogador* pJog1, Jogador* pJog2)
{
    pJ1 = pJog1;
    pJ2 = pJog2;
    numJogadores = (pJ1 ? 1 : 0) + (pJ2 ? 1 : 0);
    gc.setJogador1(pJ1);
    gc.setJogador2(pJ2);
    if (pJ1)
        pJ1->setFaseAtual(this);
    if (pJ2)
        pJ2->setFaseAtual(this);
}

Jogador* Fase::obterAlvoMaisProximo(const sf::Vector2f& pos) const
{
    bool j1Vivo = (pJ1 != nullptr && pJ1->getNumVidas() > 0);
    bool j2Vivo = (pJ2 != nullptr && pJ2->getNumVidas() > 0);

    if (j1Vivo && !j2Vivo)
        return pJ1;
    if (!j1Vivo && j2Vivo)
        return pJ2;
    if (!j1Vivo && !j2Vivo)
        return pJ1;

    sf::Vector2f pos1 = pJ1->getCoordenada();
    sf::Vector2f pos2 = pJ2->getCoordenada();
    float d1 = std::hypot(pos1.x - pos.x, pos1.y - pos.y);
    float d2 = std::hypot(pos2.x - pos.x, pos2.y - pos.y);
    return (d1 <= d2) ? pJ1 : pJ2;
}

void Fase::incluirProjetil(Projetil* pProj)
{
    if (pProj) {
        entidades.inserir(pProj);
        gc.incluirProjetil(pProj);
    }
}

bool Fase::temInimigosVivos() const
{
    int tam = entidades.tamanho();
    for (int i = 0; i < tam; i++) {
        Inimigo* pInim = dynamic_cast<Inimigo*>(entidades[i]);
        if (pInim && pInim->getNumVidas() > 0)
            return true;
    }
    return false;
}

const Listas::ListaEntidades& Fase::getEntidades() const { return entidades; }

