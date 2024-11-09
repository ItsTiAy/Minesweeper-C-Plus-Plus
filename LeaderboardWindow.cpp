#include "LeaderboardWindow.h"

LeaderboardWindow::LeaderboardWindow()
{
    std::cout << "Leaderboard Window" << std::endl;

	sf::RenderWindow window(sf::VideoMode((ResourceManager::GetColumns() * 16.f), (ResourceManager::GetRows() * 16.f) + 50.f), "Minesweeper", sf::Style::Close);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear(sf::Color::Blue);

        window.display();
    }
}