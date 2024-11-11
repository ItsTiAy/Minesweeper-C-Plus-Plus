#include "LeaderboardWindow.h"

LeaderboardWindow::LeaderboardWindow()
{
    std::cout << "Leaderboard Window" << std::endl;
}

void LeaderboardWindow::PollWindow()
{
    if (!window.isOpen())
    {
        window.create(sf::VideoMode((ResourceManager::GetColumns() * 16.f), (ResourceManager::GetRows() * 16.f) + 50.f), "Minesweeper", sf::Style::Close);
    }

    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            GameManager::ResumeTimer();
            GameManager::SetState(GameManager::GetPreviousState());
            window.close();
        }
    }

    window.clear(sf::Color::Blue);

    window.display();
}