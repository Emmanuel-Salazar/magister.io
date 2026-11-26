#include "Menu.hpp"
#include "Jogo.hpp"
#include "Ente.hpp"
#include "GerenciadorGrafico.hpp"
#include <stdexcept>
#include <string>

using namespace Magisterio;

Menu::Menu()
    : visivel(true),
    confirmandoSaida(false),
    telaAtual(TelaMenu::Principal),
    opcaoSelecionada(0),
    opcaoJogadores(0),
    opcaoConfirmacao(0),
    pedindoDoisJogadores(false),
    campoNomeAtivo(0),
    nomeJogador1(""),
    nomeJogador2(""),
    botaoFase1({ 300.f, 64.f }),
    botaoFase2({ 300.f, 64.f }),
    botaoRanking({ 300.f, 64.f }),
    botaoComoJogar({ 300.f, 64.f }),
    botaoSair({ 300.f, 64.f }),
    botao1Jogador({ 300.f, 80.f }),
    botao2Jogadores({ 300.f, 80.f }),
    botaoVoltarJogadores({ 300.f, 80.f }),
    caixaNomes({ 580.f, 340.f }),
    campoNome1({ 380.f, 52.f }),
    campoNome2({ 380.f, 52.f }),
    botaoVoltarNomes({ 220.f, 70.f }),
    botaoIniciarNomes({ 220.f, 70.f }),
    caixaRanking({ 580.f, 320.f }),
    botaoVoltarRanking({ 300.f, 70.f }),
    fundoConfirmacao({ 800.f, 600.f }),
    caixaConfirmacao({ 580.f, 270.f }),
    botaoRecusar({ 220.f, 80.f }),
    botaoAceitar({ 220.f, 80.f }),
    pJogo(nullptr),
    Ente()
{
    sf::Texture* textura = carregarTextura("assets/wallpaper.png");
    if (textura) {
        figura = new sf::Sprite(*textura);
        float escalaX = 800.f / static_cast<float>(textura->getSize().x);
        float escalaY = 600.f / static_cast<float>(textura->getSize().y);
        figura->setScale({ escalaX, escalaY });
    }

    // Menu principal (5 botoes)
    botaoFase1.setPosition({ 250.f, 130.f });
    botaoFase2.setPosition({ 250.f, 212.f });
    botaoRanking.setPosition({ 250.f, 294.f });
    botaoComoJogar.setPosition({ 250.f, 376.f });
    botaoSair.setPosition({ 250.f, 458.f });

    // Submenu de selecao de jogadores
    botao1Jogador.setPosition({ 250.f, 200.f });
    botao2Jogadores.setPosition({ 250.f, 300.f });
    botaoVoltarJogadores.setPosition({ 250.f, 400.f });

    // Tela de entrada de nomes
    caixaNomes.setPosition({ 110.f, 115.f });
    caixaNomes.setFillColor(sf::Color(30, 30, 45, 235));
    caixaNomes.setOutlineThickness(2.f);
    caixaNomes.setOutlineColor(sf::Color(70, 70, 90));

    campoNome1.setPosition({ 210.f, 225.f });
    campoNome1.setFillColor(sf::Color(20, 20, 32));
    campoNome1.setOutlineThickness(2.f);

    campoNome2.setPosition({ 210.f, 325.f });
    campoNome2.setFillColor(sf::Color(20, 20, 32));
    campoNome2.setOutlineThickness(2.f);

    botaoVoltarNomes.setPosition({ 150.f, 480.f });
    botaoIniciarNomes.setPosition({ 430.f, 480.f });

    // Tela de ranking
    caixaRanking.setPosition({ 110.f, 130.f });
    caixaRanking.setFillColor(sf::Color(30, 30, 45, 235));
    caixaRanking.setOutlineThickness(2.f);
    caixaRanking.setOutlineColor(sf::Color(70, 70, 90));
    botaoVoltarRanking.setPosition({ 250.f, 475.f });

    // Modal de confirmacao de saida
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

    auto centralizarNoBotao = [](sf::Text& texto, const sf::RectangleShape& botao) {
        sf::FloatRect bTexto = texto.getLocalBounds();
        sf::Vector2f posBotao = botao.getPosition();
        sf::Vector2f tamBotao = botao.getSize();
        texto.setPosition({
            posBotao.x + (tamBotao.x - bTexto.size.x) / 2.f - bTexto.position.x,
            posBotao.y + (tamBotao.y - bTexto.size.y) / 2.f - bTexto.position.y
        });
    };

    // Textos da selecao de jogadores
    textoTituloJogadores.emplace(fonte, sf::String("QUANTOS JOGADORES?"), 32);
    textoTituloJogadores->setFillColor(sf::Color::White);
    sf::FloatRect bTitJog = textoTituloJogadores->getLocalBounds();
    textoTituloJogadores->setPosition({ 400.f - (bTitJog.size.x / 2.f) - bTitJog.position.x, 125.f });

    texto1Jogador.emplace(fonte, sf::String("1 JOGADOR"), 30);
    texto1Jogador->setFillColor(sf::Color::White);
    centralizarNoBotao(*texto1Jogador, botao1Jogador);

    texto2Jogadores.emplace(fonte, sf::String("2 JOGADORES"), 30);
    texto2Jogadores->setFillColor(sf::Color::White);
    centralizarNoBotao(*texto2Jogadores, botao2Jogadores);

    textoVoltarJogadores.emplace(fonte, sf::String("VOLTAR"), 30);
    textoVoltarJogadores->setFillColor(sf::Color::White);
    centralizarNoBotao(*textoVoltarJogadores, botaoVoltarJogadores);

    textoControlesJogadores.emplace(fonte, sf::String("J1: WASD + F   |   J2: SETAS + J"), 18);
    textoControlesJogadores->setFillColor(sf::Color(220, 220, 235));
    sf::FloatRect bCtrl = textoControlesJogadores->getLocalBounds();
    textoControlesJogadores->setPosition({ 400.f - (bCtrl.size.x / 2.f) - bCtrl.position.x, 510.f });

    // Textos da entrada de nomes
    textoTituloNomes.emplace(fonte, sf::String("DIGITE O NOME"), 30);
    textoTituloNomes->setFillColor(sf::Color::White);
    sf::FloatRect bTitNome = textoTituloNomes->getLocalBounds();
    textoTituloNomes->setPosition({ 400.f - (bTitNome.size.x / 2.f) - bTitNome.position.x, 135.f });

    textoLabelNome1.emplace(fonte, sf::String("JOGADOR 1:"), 20);
    textoLabelNome1->setFillColor(sf::Color(200, 200, 215));
    textoLabelNome1->setPosition({ 210.f, 195.f });

    textoLabelNome2.emplace(fonte, sf::String("JOGADOR 2:"), 20);
    textoLabelNome2->setFillColor(sf::Color(150, 210, 255));
    textoLabelNome2->setPosition({ 210.f, 295.f });

    textoVoltarNomes.emplace(fonte, sf::String("VOLTAR"), 28);
    textoVoltarNomes->setFillColor(sf::Color::White);
    centralizarNoBotao(*textoVoltarNomes, botaoVoltarNomes);

    textoIniciarNomes.emplace(fonte, sf::String("INICIAR"), 28);
    textoIniciarNomes->setFillColor(sf::Color::White);
    centralizarNoBotao(*textoIniciarNomes, botaoIniciarNomes);

    // Textos da tela de ranking
    textoTituloRanking.emplace(fonte, sf::String("RANKING"), 32);
    textoTituloRanking->setFillColor(sf::Color::White);
    sf::FloatRect bTitRank = textoTituloRanking->getLocalBounds();
    textoTituloRanking->setPosition({ 400.f - (bTitRank.size.x / 2.f) - bTitRank.position.x, 148.f });

    textoVoltarRanking.emplace(fonte, sf::String("VOLTAR"), 30);
    textoVoltarRanking->setFillColor(sf::Color::White);
    centralizarNoBotao(*textoVoltarRanking, botaoVoltarRanking);

    // Textos do modal de confirmacao
    textoTituloConfirmacao.emplace(fonte, sf::String("SAIR PARA O MENU?"), 30);
    textoTituloConfirmacao->setFillColor(sf::Color::White);
    sf::FloatRect boundsTitulo = textoTituloConfirmacao->getLocalBounds();
    textoTituloConfirmacao->setPosition({
        400.f - (boundsTitulo.size.x / 2.f) - boundsTitulo.position.x,
        195.f
    });

    textoAvisoConfirmacao.emplace(fonte, sf::String(L"Voc\u00EA perder\u00E1 o progresso caso saia."), 19);
    textoAvisoConfirmacao->setFillColor(sf::Color(200, 200, 215));
    sf::FloatRect boundsAviso = textoAvisoConfirmacao->getLocalBounds();
    textoAvisoConfirmacao->setPosition({
        400.f - (boundsAviso.size.x / 2.f) - boundsAviso.position.x,
        255.f
    });

    textoRecusar.emplace(fonte, sf::String("RECUSAR"), 30);
    textoRecusar->setFillColor(sf::Color::White);
    centralizarNoBotao(*textoRecusar, botaoRecusar);

    textoAceitar.emplace(fonte, sf::String("ACEITAR"), 30);
    textoAceitar->setFillColor(sf::Color::White);
    centralizarNoBotao(*textoAceitar, botaoAceitar);

    executar();
}

Menu::~Menu() = default;

void Menu::setJogo(Jogo* pJ)
{
    pJogo = pJ;
}

void Menu::executar()
{
    opcoesMenu.clear();

    opcoesMenu.emplace_back(sf::Text(fonte, "FASE 1", 28));
    opcoesMenu.emplace_back(sf::Text(fonte, "FASE 2", 28));
    opcoesMenu.emplace_back(sf::Text(fonte, "RANKING", 28));
    opcoesMenu.emplace_back(sf::Text(fonte, "COMO JOGAR?", 28));
    opcoesMenu.emplace_back(sf::Text(fonte, "SAIR", 28));

    const sf::RectangleShape* botoes[5] = {
        &botaoFase1, &botaoFase2, &botaoRanking, &botaoComoJogar, &botaoSair
    };

    int idx = 0;
    for (auto& texto : opcoesMenu)
    {
        texto->setFillColor(sf::Color::White);
        sf::FloatRect b = texto->getLocalBounds();
        sf::Vector2f pos = botoes[idx]->getPosition();
        sf::Vector2f tam = botoes[idx]->getSize();
        texto->setPosition({
            pos.x + (tam.x - b.size.x) / 2.f - b.position.x,
            pos.y + (tam.y - b.size.y) / 2.f - b.position.y
        });
        idx++;
    }
}

void Menu::mostrar()
{
    visivel = true;
    telaAtual = TelaMenu::Principal;
}

void Menu::ocultar()
{
    visivel = false;
}

bool Menu::estaVisivel() const
{
    return visivel;
}

void Menu::mostrarSelecaoJogadores()
{
    telaAtual = TelaMenu::SelecaoJogadores;
    opcaoJogadores = 0;
}

void Menu::mostrarEntradaNomes(bool doisJogadores)
{
    pedindoDoisJogadores = doisJogadores;
    telaAtual = TelaMenu::EntradaNomes;
    campoNomeAtivo = 0;

    if (textoTituloNomes.has_value()) {
        textoTituloNomes->setString(sf::String(doisJogadores ? "DIGITE OS NOMES" : "DIGITE O NOME"));
        sf::FloatRect b = textoTituloNomes->getLocalBounds();
        textoTituloNomes->setPosition({ 400.f - (b.size.x / 2.f) - b.position.x, 135.f });
    }
}

void Menu::mostrarRanking()
{
    telaAtual = TelaMenu::Ranking;
}

void Menu::voltarPrincipal()
{
    telaAtual = TelaMenu::Principal;
}

const std::string& Menu::getNomeJogador1() const
{
    return nomeJogador1;
}

const std::string& Menu::getNomeJogador2() const
{
    return nomeJogador2;
}

OpcaoMenu Menu::processarEvento(const sf::Event& evento)
{
    if (!visivel)
        return OpcaoMenu::Nenhuma;

    // --- TELA DE SELECAO DE JOGADORES (1 OU 2) ---
    if (telaAtual == TelaMenu::SelecaoJogadores)
    {
        if (const auto* tecla = evento.getIf<sf::Event::KeyPressed>())
        {
            if (tecla->code == sf::Keyboard::Key::Up)
                opcaoJogadores = (opcaoJogadores > 0) ? opcaoJogadores - 1 : 2;
            else if (tecla->code == sf::Keyboard::Key::Down)
                opcaoJogadores = (opcaoJogadores < 2) ? opcaoJogadores + 1 : 0;
            else if (tecla->code == sf::Keyboard::Key::Escape)
                voltarPrincipal();
            else if (tecla->code == sf::Keyboard::Key::Enter)
            {
                if (opcaoJogadores == 0)
                    mostrarEntradaNomes(false);
                else if (opcaoJogadores == 1)
                    mostrarEntradaNomes(true);
                else
                    voltarPrincipal();
            }
        }
        else if (const auto* mov = evento.getIf<sf::Event::MouseMoved>())
        {
            sf::Vector2f pos(static_cast<float>(mov->position.x), static_cast<float>(mov->position.y));
            if (botao1Jogador.getGlobalBounds().contains(pos))
                opcaoJogadores = 0;
            else if (botao2Jogadores.getGlobalBounds().contains(pos))
                opcaoJogadores = 1;
            else if (botaoVoltarJogadores.getGlobalBounds().contains(pos))
                opcaoJogadores = 2;
        }
        else if (const auto* clique = evento.getIf<sf::Event::MouseButtonPressed>())
        {
            if (clique->button == sf::Mouse::Button::Left)
            {
                sf::Vector2f pos(static_cast<float>(clique->position.x), static_cast<float>(clique->position.y));
                if (botao1Jogador.getGlobalBounds().contains(pos))
                {
                    opcaoJogadores = 0;
                    mostrarEntradaNomes(false);
                }
                else if (botao2Jogadores.getGlobalBounds().contains(pos))
                {
                    opcaoJogadores = 1;
                    mostrarEntradaNomes(true);
                }
                else if (botaoVoltarJogadores.getGlobalBounds().contains(pos))
                {
                    voltarPrincipal();
                }
            }
        }
        return OpcaoMenu::Nenhuma;
    }

    // --- TELA DE ENTRADA DE NOMES ---
    if (telaAtual == TelaMenu::EntradaNomes)
    {
        if (const auto* textoEvt = evento.getIf<sf::Event::TextEntered>())
        {
            char32_t code = textoEvt->unicode;
            std::string& alvo = (pedindoDoisJogadores && campoNomeAtivo == 1) ? nomeJogador2 : nomeJogador1;

            if (code == 8) // Backspace
            {
                if (!alvo.empty())
                    alvo.pop_back();
            }
            else if (code >= 32 && code <= 126 && alvo.size() < 14)
            {
                alvo.push_back(static_cast<char>(code));
            }
        }
        else if (const auto* tecla = evento.getIf<sf::Event::KeyPressed>())
        {
            if (tecla->code == sf::Keyboard::Key::Escape)
            {
                mostrarSelecaoJogadores();
            }
            else if (tecla->code == sf::Keyboard::Key::Tab ||
                     tecla->code == sf::Keyboard::Key::Up ||
                     tecla->code == sf::Keyboard::Key::Down)
            {
                if (pedindoDoisJogadores)
                    campoNomeAtivo = (campoNomeAtivo == 0) ? 1 : 0;
            }
            else if (tecla->code == sf::Keyboard::Key::Enter)
            {
                if (pedindoDoisJogadores && campoNomeAtivo == 0)
                {
                    campoNomeAtivo = 1;
                }
                else
                {
                    return pedindoDoisJogadores ? OpcaoMenu::Iniciar2Jogadores : OpcaoMenu::Iniciar1Jogador;
                }
            }
        }
        else if (const auto* clique = evento.getIf<sf::Event::MouseButtonPressed>())
        {
            if (clique->button == sf::Mouse::Button::Left)
            {
                sf::Vector2f pos(static_cast<float>(clique->position.x), static_cast<float>(clique->position.y));
                if (campoNome1.getGlobalBounds().contains(pos))
                {
                    campoNomeAtivo = 0;
                }
                else if (pedindoDoisJogadores && campoNome2.getGlobalBounds().contains(pos))
                {
                    campoNomeAtivo = 1;
                }
                else if (botaoVoltarNomes.getGlobalBounds().contains(pos))
                {
                    mostrarSelecaoJogadores();
                }
                else if (botaoIniciarNomes.getGlobalBounds().contains(pos))
                {
                    return pedindoDoisJogadores ? OpcaoMenu::Iniciar2Jogadores : OpcaoMenu::Iniciar1Jogador;
                }
            }
        }
        return OpcaoMenu::Nenhuma;
    }

    // --- TELA DE RANKING ---
    if (telaAtual == TelaMenu::Ranking)
    {
        if (const auto* tecla = evento.getIf<sf::Event::KeyPressed>())
        {
            if (tecla->code == sf::Keyboard::Key::Escape || tecla->code == sf::Keyboard::Key::Enter)
                voltarPrincipal();
        }
        else if (const auto* clique = evento.getIf<sf::Event::MouseButtonPressed>())
        {
            if (clique->button == sf::Mouse::Button::Left)
            {
                sf::Vector2f pos(static_cast<float>(clique->position.x), static_cast<float>(clique->position.y));
                if (botaoVoltarRanking.getGlobalBounds().contains(pos))
                    voltarPrincipal();
            }
        }
        return OpcaoMenu::Nenhuma;
    }

    // --- MENU PRINCIPAL ---
    if (const auto* tecla = evento.getIf<sf::Event::KeyPressed>())
    {
        if (tecla->code == sf::Keyboard::Key::Up)
        {
            opcaoSelecionada = (opcaoSelecionada > 0) ? opcaoSelecionada - 1 : 4;
        }
        else if (tecla->code == sf::Keyboard::Key::Down)
        {
            opcaoSelecionada = (opcaoSelecionada < 4) ? opcaoSelecionada + 1 : 0;
        }
        else if (tecla->code == sf::Keyboard::Key::Enter)
        {
            switch (opcaoSelecionada)
            {
            case 0: return OpcaoMenu::JogarFase1;
            case 1: return OpcaoMenu::JogarFase2;
            case 2: return OpcaoMenu::Ranking;
            case 3: return OpcaoMenu::ComoJogar;
            case 4: return OpcaoMenu::Sair;
            default: return OpcaoMenu::Nenhuma;
            }
        }
        else if (tecla->code == sf::Keyboard::Key::Escape)
        {
            return OpcaoMenu::Retomar;
        }
    }

    if (const auto* movimento = evento.getIf<sf::Event::MouseMoved>())
    {
        sf::Vector2f posMouse(
            static_cast<float>(movimento->position.x),
            static_cast<float>(movimento->position.y)
        );

        if (botaoFase1.getGlobalBounds().contains(posMouse))
            opcaoSelecionada = 0;
        else if (botaoFase2.getGlobalBounds().contains(posMouse))
            opcaoSelecionada = 1;
        else if (botaoRanking.getGlobalBounds().contains(posMouse))
            opcaoSelecionada = 2;
        else if (botaoComoJogar.getGlobalBounds().contains(posMouse))
            opcaoSelecionada = 3;
        else if (botaoSair.getGlobalBounds().contains(posMouse))
            opcaoSelecionada = 4;
    }

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
            else if (botaoRanking.getGlobalBounds().contains(posMouse))
            {
                opcaoSelecionada = 2;
                return OpcaoMenu::Ranking;
            }
            else if (botaoComoJogar.getGlobalBounds().contains(posMouse))
            {
                opcaoSelecionada = 3;
                return OpcaoMenu::ComoJogar;
            }
            else if (botaoSair.getGlobalBounds().contains(posMouse))
            {
                opcaoSelecionada = 4;
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

    if (figura)
        destino.draw(*figura);

    if (telaAtual == TelaMenu::SelecaoJogadores)
    {
        botao1Jogador.setFillColor(opcaoJogadores == 0 ? sf::Color::Green : sf::Color(70, 70, 90));
        botao2Jogadores.setFillColor(opcaoJogadores == 1 ? sf::Color::Green : sf::Color(70, 70, 90));
        botaoVoltarJogadores.setFillColor(opcaoJogadores == 2 ? sf::Color::Red : sf::Color(70, 70, 90));

        destino.draw(botao1Jogador);
        destino.draw(botao2Jogadores);
        destino.draw(botaoVoltarJogadores);

        if (textoTituloJogadores.has_value())
            destino.draw(*textoTituloJogadores);
        if (texto1Jogador.has_value())
            destino.draw(*texto1Jogador);
        if (texto2Jogadores.has_value())
            destino.draw(*texto2Jogadores);
        if (textoVoltarJogadores.has_value())
            destino.draw(*textoVoltarJogadores);
        if (textoControlesJogadores.has_value())
            destino.draw(*textoControlesJogadores);
        return;
    }

    if (telaAtual == TelaMenu::EntradaNomes)
    {
        destino.draw(caixaNomes);
        if (textoTituloNomes.has_value())
            destino.draw(*textoTituloNomes);

        // Campo Jogador 1
        campoNome1.setOutlineColor(campoNomeAtivo == 0 ? sf::Color::Green : sf::Color(70, 70, 90));
        destino.draw(campoNome1);
        if (textoLabelNome1.has_value())
            destino.draw(*textoLabelNome1);

        std::string exib1 = nomeJogador1.empty() ? "Jogador 1" : nomeJogador1;
        if (campoNomeAtivo == 0)
            exib1 += "_";
        sf::Text txt1(fonte, sf::String(exib1), 24);
        txt1.setFillColor(nomeJogador1.empty() ? sf::Color(140, 140, 160) : sf::Color::White);
        txt1.setPosition({ 225.f, 236.f });
        destino.draw(txt1);

        // Campo Jogador 2 (apenas modo 2P)
        if (pedindoDoisJogadores)
        {
            campoNome2.setOutlineColor(campoNomeAtivo == 1 ? sf::Color::Green : sf::Color(70, 70, 90));
            destino.draw(campoNome2);
            if (textoLabelNome2.has_value())
                destino.draw(*textoLabelNome2);

            std::string exib2 = nomeJogador2.empty() ? "Jogador 2" : nomeJogador2;
            if (campoNomeAtivo == 1)
                exib2 += "_";
            sf::Text txt2(fonte, sf::String(exib2), 24);
            txt2.setFillColor(nomeJogador2.empty() ? sf::Color(140, 140, 160) : sf::Color::White);
            txt2.setPosition({ 225.f, 336.f });
            destino.draw(txt2);
        }

        sf::Text dica(fonte, sf::String(pedindoDoisJogadores ? "TAB ou clique para trocar | ENTER para iniciar" : "Digite seu nome e aperte ENTER"), 16);
        dica.setFillColor(sf::Color(190, 190, 210));
        sf::FloatRect bDica = dica.getLocalBounds();
        dica.setPosition({ 400.f - (bDica.size.x / 2.f) - bDica.position.x, 412.f });
        destino.draw(dica);

        botaoVoltarNomes.setFillColor(sf::Color::Red);
        botaoIniciarNomes.setFillColor(sf::Color::Green);
        destino.draw(botaoVoltarNomes);
        destino.draw(botaoIniciarNomes);

        if (textoVoltarNomes.has_value())
            destino.draw(*textoVoltarNomes);
        if (textoIniciarNomes.has_value())
            destino.draw(*textoIniciarNomes);
        return;
    }

    if (telaAtual == TelaMenu::Ranking)
    {
        destino.draw(caixaRanking);
        if (textoTituloRanking.has_value())
            destino.draw(*textoTituloRanking);

        if (pJogo && !pJogo->getRanking().empty())
        {
            const auto& lista = pJogo->getRanking();
            float y = 215.f;
            for (size_t i = 0; i < lista.size() && i < 5; i++)
            {
                std::wstring linha = std::to_wstring(i + 1) + L". " +
                                     lista[i].descricao + L" - " +
                                     std::to_wstring(lista[i].pontos) + L" pts";
                sf::Text textoLinha(fonte, sf::String(linha), 22);
                textoLinha.setFillColor(i == 0 ? sf::Color(255, 220, 90) : sf::Color::White);
                sf::FloatRect b = textoLinha.getLocalBounds();
                textoLinha.setPosition({ 400.f - (b.size.x / 2.f) - b.position.x, y });
                destino.draw(textoLinha);
                y += 42.f;
            }
        }
        else
        {
            sf::Text vazio(fonte, sf::String(L"Nenhuma pontua\u00E7\u00E3o registrada ainda."), 22);
            vazio.setFillColor(sf::Color(200, 200, 215));
            sf::FloatRect b = vazio.getLocalBounds();
            vazio.setPosition({ 400.f - (b.size.x / 2.f) - b.position.x, 285.f });
            destino.draw(vazio);
        }

        botaoVoltarRanking.setFillColor(sf::Color::Red);
        destino.draw(botaoVoltarRanking);
        if (textoVoltarRanking.has_value())
            destino.draw(*textoVoltarRanking);
        return;
    }

    // Menu principal
    botaoFase1.setFillColor(opcaoSelecionada == 0 ? sf::Color::Green : sf::Color(70, 70, 90));
    botaoFase2.setFillColor(opcaoSelecionada == 1 ? sf::Color::Green : sf::Color(70, 70, 90));
    botaoRanking.setFillColor(opcaoSelecionada == 2 ? sf::Color::Green : sf::Color(70, 70, 90));
    botaoComoJogar.setFillColor(opcaoSelecionada == 3 ? sf::Color::Green : sf::Color(70, 70, 90));
    botaoSair.setFillColor(opcaoSelecionada == 4 ? sf::Color::Red : sf::Color(70, 70, 90));

    destino.draw(botaoFase1);
    destino.draw(botaoFase2);
    destino.draw(botaoRanking);
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
    opcaoConfirmacao = 0; // Recusar selecionado por padrao

    if (textoAvisoConfirmacao.has_value()) {
        std::wstring msg = L"Voc\u00EA perder\u00E1 o progresso caso saia.";
        if (pJogo) {
            msg = L"Voc\u00EA perder\u00E1 o progresso (" +
                  std::to_wstring(pJogo->getPontosPartidaAtual()) +
                  L" pts) caso saia.";
        }
        textoAvisoConfirmacao->setString(sf::String(msg));
        sf::FloatRect boundsAviso = textoAvisoConfirmacao->getLocalBounds();
        textoAvisoConfirmacao->setPosition({
            400.f - (boundsAviso.size.x / 2.f) - boundsAviso.position.x,
            255.f
        });
    }
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
            opcaoConfirmacao = 0;
        else if (tecla->code == sf::Keyboard::Key::Right || tecla->code == sf::Keyboard::Key::D)
            opcaoConfirmacao = 1;
        else if (tecla->code == sf::Keyboard::Key::Enter)
            return opcaoConfirmacao == 1 ? OpcaoMenu::ConfirmarSaida : OpcaoMenu::CancelarSaida;
        else if (tecla->code == sf::Keyboard::Key::Escape)
            return OpcaoMenu::CancelarSaida;
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

    botaoRecusar.setFillColor(opcaoConfirmacao == 0 ? sf::Color::Green : sf::Color(70, 70, 90));
    botaoAceitar.setFillColor(opcaoConfirmacao == 1 ? sf::Color::Red : sf::Color(70, 70, 90));

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
