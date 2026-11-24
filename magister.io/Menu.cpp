
#include "Menu.hpp"
#include "Ente.hpp"
#include "GerenciadorGrafico.hpp"
#include <stdexcept>

using namespace Magisterio;

Menu::Menu()
    : visivel(true),
    confirmandoSaida(false),
    opcaoSelecionada(0),
    opcaoConfirmacao(0),
    botaoFase1({ 300.f, 80.f }),
    botaoFase2({ 300.f, 80.f }),
    botaoComoJogar({ 300.f, 80.f }),
    botaoSair({ 300.f, 80.f }),
    fundoConfirmacao({ 800.f, 600.f }),
    caixaConfirmacao({ 580.f, 270.f }),
    botaoRecusar({ 220.f, 80.f }),
    botaoAceitar({ 220.f, 80.f }),
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

    fundoConfirmacao.setPosition({ 0.f, 0.f });
    fundoConfirmacao.setFillColor(sf::Color(0, 0, 0, 180));

    caixaConfirmacao.setPosition({ 110.f, 165.f });
    caixaConfirmacao.setFillColor(sf::Color(30, 30, 45, 240));
    caixaConfirmacao.setOutlineThickness(2.f);
    caixaConfirmacao.setOutlineColor(sf::Color(70, 70, 90));

    botaoRecusar.setPosition({ 150.f, 320.f });
    botaoAceitar.setPosition({ 430.f, 320.f });

    if (!fonte.openFromFile("assets/arial.ttf") &&
        !fonte.openFromFile("C:/Windows/Fonts/arial.ttf"))
        throw std::runtime_error("Nao foi possivel carregar a fonte do menu.");

    textoTituloConfirmacao.emplace(fonte, sf::String("SAIR PARA O MENU?"), 30);
    textoTituloConfirmacao->setFillColor(sf::Color::White);
    sf::FloatRect boundsTitulo = textoTituloConfirmacao->getLocalBounds();
    textoTituloConfirmacao->setPosition({
        400.f - (boundsTitulo.size.x / 2.f) - boundsTitulo.position.x,
        195.f
    });

    textoAvisoConfirmacao.emplace(fonte, sf::String("Vai perder o progresso caso saia."), 20);
    textoAvisoConfirmacao->setFillColor(sf::Color(200, 200, 215));
    sf::FloatRect boundsAviso = textoAvisoConfirmacao->getLocalBounds();
    textoAvisoConfirmacao->setPosition({
        400.f - (boundsAviso.size.x / 2.f) - boundsAviso.position.x,
        255.f
    });

    textoRecusar.emplace(fonte, sf::String("RECUSAR"), 30);
    textoRecusar->setFillColor(sf::Color::White);
    sf::FloatRect boundsRecusar = textoRecusar->getLocalBounds();
    textoRecusar->setPosition({
        150.f + (220.f - boundsRecusar.size.x) / 2.f - boundsRecusar.position.x,
        320.f + (80.f - boundsRecusar.size.y) / 2.f - boundsRecusar.position.y
    });

    textoAceitar.emplace(fonte, sf::String("ACEITAR"), 30);
    textoAceitar->setFillColor(sf::Color::White);
    sf::FloatRect boundsAceitar = textoAceitar->getLocalBounds();
    textoAceitar->setPosition({
        430.f + (220.f - boundsAceitar.size.x) / 2.f - boundsAceitar.position.x,
        320.f + (80.f - boundsAceitar.size.y) / 2.f - boundsAceitar.position.y
    });

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

void Menu::mostrarConfirmacaoSaida()
{
    confirmandoSaida = true;
    opcaoConfirmacao = 0; // Recusar selecionado por padrão
}

void Menu::ocultarConfirmacaoSaida()
{
    confirmandoSaida = false;
}

bool Menu::estaConfirmandoSaida() const
{
    return confirmandoSaida;
}

OpcaoMenu Menu::processarEventoConfirmacao(const sf::Event& evento)
{
    if (!confirmandoSaida)
        return OpcaoMenu::Nenhuma;

    if (const auto* tecla = evento.getIf<sf::Event::KeyPressed>())
    {
        if (tecla->code == sf::Keyboard::Key::Left || tecla->code == sf::Keyboard::Key::A)
        {
            opcaoConfirmacao = 0;
        }
        else if (tecla->code == sf::Keyboard::Key::Right || tecla->code == sf::Keyboard::Key::D)
        {
            opcaoConfirmacao = 1; 
        }
        else if (tecla->code == sf::Keyboard::Key::Enter)
        {
            return opcaoConfirmacao == 1 ? OpcaoMenu::ConfirmarSaida : OpcaoMenu::CancelarSaida;
        }
        else if (tecla->code == sf::Keyboard::Key::Escape)
        {
            return OpcaoMenu::CancelarSaida;
        }
    }

    if (const auto* movimento = evento.getIf<sf::Event::MouseMoved>())
    {
        sf::Vector2f posMouse(
            static_cast<float>(movimento->position.x),
            static_cast<float>(movimento->position.y)
        );

        if (botaoRecusar.getGlobalBounds().contains(posMouse))
            opcaoConfirmacao = 0;
        else if (botaoAceitar.getGlobalBounds().contains(posMouse))
            opcaoConfirmacao = 1;
    }

    if (const auto* clique = evento.getIf<sf::Event::MouseButtonPressed>())
    {
        if (clique->button == sf::Mouse::Button::Left)
        {
            sf::Vector2f posMouse(
                static_cast<float>(clique->position.x),
                static_cast<float>(clique->position.y)
            );

            if (botaoRecusar.getGlobalBounds().contains(posMouse))
            {
                opcaoConfirmacao = 0;
                return OpcaoMenu::CancelarSaida;
            }
            else if (botaoAceitar.getGlobalBounds().contains(posMouse))
            {
                opcaoConfirmacao = 1;
                return OpcaoMenu::ConfirmarSaida;
            }
        }
    }

    return OpcaoMenu::Nenhuma;
}

void Menu::desenharConfirmacao(sf::RenderWindow& destino)
{
    if (!confirmandoSaida)
        return;

    destino.draw(fundoConfirmacao);
    destino.draw(caixaConfirmacao);

    botaoRecusar.setFillColor(opcaoConfirmacao == 0 ?
        sf::Color::Green : sf::Color(70, 70, 90));

    botaoAceitar.setFillColor(opcaoConfirmacao == 1 ?
        sf::Color::Red : sf::Color(70, 70, 90));

    destino.draw(botaoRecusar);
    destino.draw(botaoAceitar);

    if (textoTituloConfirmacao.has_value())
        destino.draw(*textoTituloConfirmacao);
    if (textoAvisoConfirmacao.has_value())
        destino.draw(*textoAvisoConfirmacao);
    if (textoRecusar.has_value())
        destino.draw(*textoRecusar);
    if (textoAceitar.has_value())
        destino.draw(*textoAceitar);
}
