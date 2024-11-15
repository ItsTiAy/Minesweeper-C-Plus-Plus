#include "LeaderboardWindow.h"

LeaderboardWindow::LeaderboardWindow()
{
    std::cout << "Leaderboard Window" << std::endl;

    leaderboardText.setString("LEADERBOARD");
    leaderboardText.setFont(ResourceManager::GetFont("font.ttf"));
    leaderboardText.setCharacterSize(20);
    leaderboardText.setStyle(sf::Text::Underlined | sf::Text::Bold);
    leaderboardText.setFillColor(sf::Color::White);

    std::vector<std::pair<std::string, std::string>> scores = ResourceManager::GetScores();
    std::string stringContent = "";

    for (int i = 0; i < scores.size(); i++)
    {
        stringContent += std::to_string(i + 1) + ".\t" + scores[i].first + "\t" + scores[i].second + "\n\n";
    }

    content.setString(stringContent);
    content.setFont(ResourceManager::GetFont("font.ttf"));
    content.setCharacterSize(18);
    content.setStyle(sf::Text::Bold);
    content.setFillColor(sf::Color::White);
}

void LeaderboardWindow::UpdateLeaderboard(int score)
{
    std::vector<std::pair<std::string, std::string>> scores = ResourceManager::GetScores();

    int mins;
    int seconds;
    int total;

    for (int i = 0; i < scores.size(); i++)
    {
        int delPos = scores[i].first.find(":");
        mins = std::stoi(scores[i].first.substr(0, delPos));
        seconds = std::stoi(scores[i].first.substr(delPos + 1));

        total = (mins * 60) + seconds;

        if (score <= total)
        {
            std::vector<std::pair<std::string, std::string>> scoresForFile(scores);
            std::string playerName = ResourceManager::GetPlayerName();

            std::ostringstream oss;

            oss << std::setfill('0') << std::setw(2) << (score / 60) << ":";
            oss << std::setfill('0') << std::setw(2) << (score % 60);

            std::string time = oss.str();

            std::cout << score << std::endl;
            std::cout << time << std::endl;

            scoresForFile.insert(scoresForFile.begin() + i, std::make_pair(time, playerName));
            scoresForFile.pop_back();

            ResourceManager::WriteScores(scoresForFile);
            ResourceManager::LoadScores();

            playerName += "*";

            scores.insert(scores.begin() + i, std::make_pair(time, playerName));
            scores.pop_back();

            break;
        }
    }

    std::string stringContent = "";

    for (int i = 0; i < scores.size(); i++)
    {
        stringContent += std::to_string(i + 1) + ".\t" + scores[i].first + "\t" + scores[i].second + "\n\n";
    }

    content.setString(stringContent);
    content.setFont(ResourceManager::GetFont("font.ttf"));
    content.setCharacterSize(18);
    content.setStyle(sf::Text::Bold);
    content.setFillColor(sf::Color::White);
}

void LeaderboardWindow::OpenWindow()
{
    window.create(sf::VideoMode((ResourceManager::GetColumns() * 16.f), (ResourceManager::GetRows() * 16.f) + 50.f), "Minesweeper", sf::Style::Close);
    GameManager::SetTextPosition(leaderboardText, window.getSize().x / 2.f, (window.getSize().y / 2.f) - 120.f);;
    GameManager::SetTextPosition(content, window.getSize().x / 2.f, (window.getSize().y / 2.f) + 20.f);;
}

void LeaderboardWindow::PollWindow()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            if (GameManager::GetPreviousState() != GameManager::GameState::Win)
            {
                GameManager::ResumeTimer();
            }

            GameManager::SetState(GameManager::GetPreviousState());
            window.close();
        }
    }

    window.clear(sf::Color::Blue);

    window.draw(leaderboardText);
    window.draw(content);

    window.display();
}