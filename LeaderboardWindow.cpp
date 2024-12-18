#include "LeaderboardWindow.h"

LeaderboardWindow::LeaderboardWindow()
{
    std::cout << "Leaderboard Window" << std::endl;

    // Sets leaderboard text settings
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

    // Sets leaderboard score text settings
    content.setString(stringContent);
    content.setFont(ResourceManager::GetFont("font.ttf"));
    content.setCharacterSize(18);
    content.setStyle(sf::Text::Bold);
    content.setFillColor(sf::Color::White);
}

// Updates the leaderboard scores
void LeaderboardWindow::UpdateLeaderboard(int score)
{
    std::vector<std::pair<std::string, std::string>> scores = ResourceManager::GetScores();

    bool scoreAdded = false;

    int mins;
    int seconds;
    int total;

    std::vector<std::pair<std::string, std::string>> scoresForFile(scores);
    std::string playerName = ResourceManager::GetPlayerName();

    // Sets time format
    std::ostringstream oss;

    oss << std::setfill('0') << std::setw(2) << (score / 60) << ":";
    oss << std::setfill('0') << std::setw(2) << (score % 60);

    std::string time = oss.str();

    for (int i = 0; i < scores.size(); i++)
    {
        // Gets score from file and converts it to second
        int delPos = scores[i].first.find(":");
        mins = std::stoi(scores[i].first.substr(0, delPos));
        seconds = std::stoi(scores[i].first.substr(delPos + 1));

        total = (mins * 60) + seconds;

        // Adds score if better than one on the leaderboard
        if (score <= total)
        {
            scoresForFile.insert(scoresForFile.begin() + i, std::make_pair(time, playerName));

            if (scoresForFile.size() > 5)
            {
                scoresForFile.pop_back();
            }

            ResourceManager::WriteScores(scoresForFile);
            ResourceManager::LoadScores();

            playerName += "*";

            scores.insert(scores.begin() + i, std::make_pair(time, playerName));

            if (scores.size() > 5)
            {
                scores.pop_back();
            }

            scoreAdded = true;
            break;
        }
    }

    // Adds score to end if leaderboard has less than 5 scores and wasn't added before
    if (!scoreAdded && scores.size() < 5)
    {
        scoresForFile.push_back(std::make_pair(time, playerName));

        ResourceManager::WriteScores(scoresForFile);
        ResourceManager::LoadScores();

        playerName += "*";

        scores.push_back(std::make_pair(time, playerName));
    }   

    // Formats leaderboard scores
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

// Opens the leaderboard window
void LeaderboardWindow::OpenWindow()
{
    window.create(sf::VideoMode((ResourceManager::GetColumns() * 16.f), (ResourceManager::GetRows() * 16.f) + 50.f), "Minesweeper", sf::Style::Close);
    ResourceManager::SetIcon(window);
    GameManager::SetTextPosition(leaderboardText, window.getSize().x / 2.f, (window.getSize().y / 2.f) - 120.f);;
    GameManager::SetTextPosition(content, window.getSize().x / 2.f, (window.getSize().y / 2.f) + 20.f);;
}

// Checks for events on the leaderboard window
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