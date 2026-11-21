
#include "Menu.hpp"
#include "Ente.hpp"
#include "GerenciadorGrafico.hpp"
#include <stdexcept>

using namespace Magisterio;

Menu::Menu()
    : visivel(true),
    opcaoSelecionada(0),
    botaoFase1({ 300.f, 80.f }),
    botaoFase2({ 300.f, 80.f }),
    botaoComoJogar({ 300.f, 80.f }),
    botaoSair({ 300.f, 80.f }),
    pJogo(nullptr),
    Ente()
{
    sf::Texture* textura = pGG->carregarTextura("assets/wallpaper.png");
    if (textura) {
        figura = new sf::Sprite(*textura);
        float escalaX = 800.f / static_cast<float>(textura->getSize().x);
        float escalaY = 600.f / static_cast<float>(textura->getSize().y);
        figura->setScale({ escalaX, escalaY });
    }

    botaoFase1.setPosition({ 250.f, 180.f });
    botaoFase2.setPosition({ 250.f, 280.f });
    botaoComoJogar.setPosition({ 250.f, 380.f });
    botaoSair.setPosition({ 250.f, 480.f });

    if (!fonte.openFromFile("assets/arial.ttf") &&
        !fonte.openFromFile("C:/Windows/Fonts/arial.ttf"))
        throw std::runtime_error("Nao foi possivel carregar a fonte do menu.");

    executar();
}

Menu::~Menu() = default;

void Menu::executar()
{
    opcoesMenu.clear();

    opcoesMenu.emplace_back(sf::Text(fonte, "FASE 1", 30));
    opcoesMenu.emplace_back(sf::Text(fonte, "FASE 2", 30));
    opcoesMenu.emplace_back(sf::Text(fonte, "COMO JOGAR?", 30));
    opcoesMenu.emplace_back(sf::Text(fonte, "SAIR", 30));

    auto it = opcoesMenu.begin();

    (*it)->setPosition({ 350.f, 202.f });
    ++it;

    (*it)->setPosition({ 360.f, 302.f });
    ++it;

    (*it)->setPosition({ 310.f, 402.f });
    ++it;

    (*it)->setPosition({ 375.f, 502.f });

    for (auto& texto : opcoesMenu)
        texto->setFillColor(sf::Color::White);
}

void Menu::mostrar()
{
    visivel = true;
}

void Menu::ocultar()
{
    visivel = false;
}

bool Menu::estaVisivel() const
{
    return visivel;
}

OpcaoMenu Menu::processarEvento(const sf::Event& evento)
{
    if (!visivel)
        return OpcaoMenu::Nenhuma;

    // EVENTOS DO TECLADO

    if (const auto* tecla = evento.getIf<sf::Event::KeyPressed>())
    {
        if (tecla->code == sf::Keyboard::Key::Up)
        {
            if (opcaoSelecionada > 0)
                opcaoSelecionada--;
            else
                opcaoSelecionada = 3;
        }

        else if (tecla->code == sf::Keyboard::Key::Down)
        {
            if (opcaoSelecionada < 3)
                opcaoSelecionada++;
            else
                opcaoSelecionada = 0;
        }

        else if (tecla->code == sf::Keyboard::Key::Enter)
        {
            switch (opcaoSelecionada)
            {
            case 0:
                return OpcaoMenu::JogarFase1;

            case 1:
                return OpcaoMenu::JogarFase2;

            case 2:
                return OpcaoMenu::ComoJogar;

            case 3:
                return OpcaoMenu::Sair;

            default:
                return OpcaoMenu::Nenhuma;
            }
        }

        else if (tecla->code == sf::Keyboard::Key::Escape)
        {
            return OpcaoMenu::Retomar;
        }
    }

    // MOVIMENTO DO MOUSE

    if (const auto* movimento = evento.getIf<sf::Event::MouseMoved>())
    {
        sf::Vector2f posMouse(
            static_cast<float>(movimento->position.x),
            static_cast<float>(movimento->position.y)
        );

        if (botaoFase1.getGlobalBounds().contains(posMouse))
        {
            opcaoSelecionada = 0;
        }

        else if (botaoFase2.getGlobalBounds().contains(posMouse))
        {
            opcaoSelecionada = 1;
        }

        else if (botaoComoJogar.getGlobalBounds().contains(posMouse))
        {
            opcaoSelecionada = 2;
        }

        else if (botaoSair.getGlobalBounds().contains(posMouse))
        {
            opcaoSelecionada = 3;
        }
    }


    // CLIQUE DO MOUSE

    if (const auto* clique = evento.getIf<sf::Event::MouseButtonPressed>())
    {
        if (clique->button == sf::Mouse::Button::Left)
        {
            sf::Vector2f posMouse(
                static_cast<float>(clique->position.x),
                static_cast<float>(clique->position.y)
            );

            if (botaoFase1.getGlobalBounds().contains(posMouse))
            {
                opcaoSelecionada = 0;
                return OpcaoMenu::JogarFase1;
            }

            else if (botaoFase2.getGlobalBounds().contains(posMouse))
            {
                opcaoSelecionada = 1;
                return OpcaoMenu::JogarFase2;
            }

            else if (botaoComoJogar.getGlobalBounds().contains(posMouse))
            {
                opcaoSelecionada = 2;
                return OpcaoMenu::ComoJogar;
            }

            else if (botaoSair.getGlobalBounds().contains(posMouse))
            {
                opcaoSelecionada = 3;
                return OpcaoMenu::Sair;
            }
        }
    }

    return OpcaoMenu::Nenhuma;
}


void Menu::desenhar(sf::RenderWindow& destino)
{
    if (!visivel)
        return;

    destino.draw(*figura);

    botaoFase1.setFillColor(opcaoSelecionada == 0 ?
        sf::Color::Green : sf::Color(70, 70, 90));

    botaoFase2.setFillColor(opcaoSelecionada == 1 ?
        sf::Color::Green : sf::Color(70, 70, 90));

    botaoComoJogar.setFillColor(opcaoSelecionada == 2 ?
        sf::Color::Green : sf::Color(70, 70, 90));

    botaoSair.setFillColor(opcaoSelecionada == 3 ?
        sf::Color::Red : sf::Color(70, 70, 90));

    destino.draw(botaoFase1);
    destino.draw(botaoFase2);
    destino.draw(botaoComoJogar);
    destino.draw(botaoSair);

    for (const auto& texto : opcoesMenu)
    {
        if (texto.has_value())
            destino.draw(*texto);
    }
}
