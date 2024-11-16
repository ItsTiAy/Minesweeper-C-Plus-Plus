#include "WelcomeWindow.h"

WelcomeWindow::WelcomeWindow()
{
    std::cout << "Welcome Window" << std::endl;

    sf::RenderWindow window(sf::VideoMode((ResourceManager::GetColumns() * 32), (ResourceManager::GetRows() * 32) + 100), "Minesweeper", sf::Style::Close);
    ResourceManager::SetIcon(window);

    sf::Font font = ResourceManager::GetFont("font.ttf");
    
    // Sets text attributes
    sf::Text welcomeText("WELCOME TO MINESWEEPER!", font, 24);
    welcomeText.setStyle(sf::Text::Underlined | sf::Text::Bold);
    welcomeText.setFillColor(sf::Color::White);
    GameManager::SetTextPosition(welcomeText, window.getSize().x / 2.f, (window.getSize().y / 2.f) - 150.f);

    sf::Text enterNameText("Enter your name:", font, 20);
    enterNameText.setStyle(sf::Text::Bold);
    enterNameText.setFillColor(sf::Color::White);
    GameManager::SetTextPosition(enterNameText, window.getSize().x / 2.f, (window.getSize().y / 2.f) - 75.f);

    sf::Text inputText("|", font, 18);
    inputText.setStyle(sf::Text::Bold);
    inputText.setFillColor(sf::Color::Yellow);
    GameManager::SetTextPosition(inputText, window.getSize().x / 2.f, (window.getSize().y / 2.f) - 45.f);

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
                // Makes the text capitalise the first letter and lowercase the rest
                if (std::isalpha(event.text.unicode) && inputString.length() < 10)
                {
                    char letter = static_cast<char>(event.text.unicode);

                    letter = inputString.empty() ? std::toupper(letter) : std::tolower(letter);

                    inputString += letter;
                }
                // Removes end of string if backspace pressed
                else if (event.text.unicode == '\b' && !inputString.empty())
                {
                    inputString.pop_back();
                }
                // Opens game window if enter pressed 
                else if (event.text.unicode == '\r' && !inputString.empty())
                {
                    window.close();
                    ResourceManager::SetPlayerName(inputString);
                    GameWindow gameWindow;
                }

                // Adds the carot to the end of the string
                inputText.setString(inputString + "|");
                GameManager::SetTextPosition(inputText, window.getSize().x / 2.f, (window.getSize().y / 2.f) - 45.f);
            }
        }

        window.clear(sf::Color::Blue);

        window.draw(welcomeText);
        window.draw(enterNameText);
        window.draw(inputText);

        window.display();
    }
}