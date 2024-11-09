#include "WelcomeWindow.h"

WelcomeWindow::WelcomeWindow()
{
    std::cout << "Welcome Window" << std::endl;

    sf::RenderWindow window(sf::VideoMode((ResourceManager::GetColumns() * 32.f), (ResourceManager::GetRows() * 32.f) + 100.f), "Minesweeper", sf::Style::Close);

    sf::Font font = ResourceManager::GetFont("arial.ttf");

    sf::Text welcomeText("WELCOME TO MINESWEEPER!", font, 24);
    welcomeText.setStyle(sf::Text::Underlined | sf::Text::Bold);
    welcomeText.setFillColor(sf::Color::White);

    SetTextPosition(welcomeText, window.getSize().x / 2.f, (window.getSize().y / 2.f) - 150.f);

    sf::Text enterNameText("Enter your name:", font, 20);
    enterNameText.setStyle(sf::Text::Bold);
    enterNameText.setFillColor(sf::Color::White);

    SetTextPosition(enterNameText, window.getSize().x / 2.f, (window.getSize().y / 2.f) - 75.f);

    sf::Text inputText("|", font, 18);
    inputText.setStyle(sf::Text::Bold);
    inputText.setFillColor(sf::Color::Yellow);

    SetTextPosition(inputText, window.getSize().x / 2.f, (window.getSize().y / 2.f) - 45.f);

    std::string inputString = "";

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::TextEntered)
            {
                if (std::isalpha(event.text.unicode) && inputString.length() < 10)
                {
                    char letter = static_cast<char>(event.text.unicode);

                    if (inputString.empty())
                    {
                        letter = std::toupper(letter);
                    }

                    inputString += letter;
                }
                else if (event.text.unicode == '\b' && !inputString.empty())
                {
                    inputString.pop_back();
                }
                else if (event.text.unicode == '\r' && !inputString.empty())
                {
                    window.close();
                    GameWindow gameWindow;
                }

                inputText.setString(inputString + "|");
                SetTextPosition(inputText, window.getSize().x / 2.f, (window.getSize().y / 2.f) - 45.f);
            }
        }

        window.clear(sf::Color::Blue);

        window.draw(welcomeText);
        window.draw(enterNameText);
        window.draw(inputText);

        window.display();
    }
}

void WelcomeWindow::SetTextPosition(sf::Text& text, float x, float y)
{
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(x, y));
}
