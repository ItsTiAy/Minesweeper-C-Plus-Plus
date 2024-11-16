#include "GameWindow.h"

GameWindow::GameWindow()
{
    std::cout << "Game Window" << std::endl;

    int columns = ResourceManager::GetColumns();
    int rows = ResourceManager::GetRows();
    int mines = ResourceManager::GetMines();

    sf::RenderWindow window(sf::VideoMode((columns * 32.f), (rows * 32.f) + 100.f), "Minesweeper", sf::Style::Close);
    ResourceManager::SetIcon(window);
    sf::RectangleShape overlay(sf::Vector2f(window.getSize().x, window.getSize().y));
    overlay.setFillColor(sf::Color(0, 0, 0, 150));

    tiles = std::vector<std::vector<Tile*>>(columns, std::vector<Tile*>(rows, nullptr));

    Button faceButton(((columns / 2.f) * 32) - 32.f, 32.f * (rows + 0.5f), ResourceManager::GetTexture("face_happy.png"));
    Button debugButton((columns * 32) - 304.f, 32.f * (rows + 0.5f), ResourceManager::GetTexture("debug.png"));
    Button playPauseButton((columns * 32) - 240.f, 32.f * (rows + 0.5f), ResourceManager::GetTexture("pause.png"));
    Button leaderboardButton((columns * 32) - 176.f, 32.f * (rows + 0.5f), ResourceManager::GetTexture("leaderboard.png"));

    faceButton.SetOnClick([&]() -> bool
    {
        std::cout << "Face Button" << std::endl;

        faceButton.ChangeTexture(ResourceManager::GetTexture("face_happy.png"));
        ResetGame();

        return true;
    });

    debugButton.SetOnClick([&]() -> bool
    {
        std::cout << "Debug Button" << std::endl;

        GameManager::ToggleDebug();

        return true;
    });

    playPauseButton.SetOnClick([&]() -> bool
    {
        std::cout << "Play Pause Button" << std::endl;

        if (GameManager::GetState() == GameManager::GameState::Paused)
        {
            GameManager::ResumeTimer();
            GameManager::SetState(GameManager::GameState::Playing);
            playPauseButton.ChangeTexture(ResourceManager::GetTexture("pause.png"));
        }
        else
        {
            GameManager::PauseTimer();
            GameManager::SetState(GameManager::GameState::Paused);
            playPauseButton.ChangeTexture(ResourceManager::GetTexture("play.png"));
        }

        return true;
    });

    leaderboardButton.SetOnClick([&]() -> bool
    {
        std::cout << "Leaderboard Button" << std::endl;

        GameManager::PauseTimer();
        GameManager::SetPreviousState(GameManager::GetState());
        GameManager::SetState(GameManager::GameState::LeaderboardOpen);
        leaderboardWindow.OpenWindow();

        return true;
    });

    sf::Sprite timerMinsTens, timerMinsUnits, timerSecondsTens, timerSecondsUnits, counterNegative, counterHundreds, counterTens, counterUnits;

    timerMinsTens.setTexture(ResourceManager::GetTexture("digits.png"));
    timerMinsUnits.setTexture(ResourceManager::GetTexture("digits.png"));
    timerSecondsTens.setTexture(ResourceManager::GetTexture("digits.png"));
    timerSecondsUnits.setTexture(ResourceManager::GetTexture("digits.png"));

    counterNegative.setTexture(ResourceManager::GetTexture("digits.png"));
    counterHundreds.setTexture(ResourceManager::GetTexture("digits.png"));
    counterTens.setTexture(ResourceManager::GetTexture("digits.png"));
    counterUnits.setTexture(ResourceManager::GetTexture("digits.png"));

    timerMinsTens.setPosition((columns * 32) - 97, 32 * (rows + 0.5f) + 16);
    timerMinsUnits.setPosition((columns * 32) - 76, 32 * (rows + 0.5f) + 16);
    timerSecondsTens.setPosition((columns * 32) - 54, 32 * (rows + 0.5f) + 16);
    timerSecondsUnits.setPosition((columns * 32) - 33, 32 * (rows + 0.5f) + 16);

    counterNegative.setPosition(12, 32 * (rows + 0.5f) + 16);
    counterHundreds.setPosition(33, 32 * (rows + 0.5f) + 16);
    counterTens.setPosition(54, 32 * (rows + 0.5f) + 16);
    counterUnits.setPosition(75, 32 * (rows + 0.5f) + 16);

    int timeMins = 0;
    int timeSeconds = 0;

    int counter = 0;

    GenerateGrid(columns, rows, mines);

    GameManager::ResetTimer();

    while (window.isOpen())
    {
        if (GameManager::GetState() == GameManager::GameState::LeaderboardOpen)
        {
            leaderboardWindow.PollWindow();
        }
        else
        {
            timeMins = GameManager::GetTime() / 60;
            timeSeconds = GameManager::GetTime() % 60;

            counter = GameManager::GetNumTilesFlagged();

            timerMinsTens.setTextureRect(sf::IntRect(21 * ((timeMins / 10) % 10), 0, 21, 32));
            timerMinsUnits.setTextureRect(sf::IntRect(21 * (timeMins % 10), 0, 21, 32));
            timerSecondsTens.setTextureRect(sf::IntRect(21 * ((timeSeconds / 10) % 10), 0, 21, 32));
            timerSecondsUnits.setTextureRect(sf::IntRect(21 * (timeSeconds % 10), 0, 21, 32));

            counterNegative.setTextureRect(sf::IntRect(210, 0, 21, 32));
            counterHundreds.setTextureRect(sf::IntRect(21 * ((std::abs(counter) / 100) % 10), 0, 21, 32));
            counterTens.setTextureRect(sf::IntRect(21 * ((std::abs(counter) / 10) % 10), 0, 21, 32));
            counterUnits.setTextureRect(sf::IntRect(21 * (std::abs(counter) % 10), 0, 21, 32));

            sf::Vector2f mousePos(sf::Mouse::getPosition(window));
            sf::Event event;

            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }

                if (event.type == sf::Event::MouseButtonReleased)
                {
                    for (int i = 0; i < rows; i++)
                    {
                        for (int j = 0; j < columns; j++)
                        {
                            if (tiles[j][i]->IsPressed(mousePos) && !GameManager::IsGameOver() && GameManager::GetState() != GameManager::GameState::Paused)
                            {
                                if (event.mouseButton.button == sf::Mouse::Left)
                                {
                                    if (!tiles[j][i]->Click())
                                    {
                                        std::cout << "Game Lose" << std::endl;
                                        faceButton.ChangeTexture(ResourceManager::GetTexture("face_lose.png"));
                                        GameManager::SetState(GameManager::GameState::Lose);
                                        GameManager::PauseTimer();
                                    }
                                    else
                                    {
                                        if ((columns * rows) - mines == GameManager::GetNumTilesRevealed())
                                        {
                                            std::cout << "Game Win" << std::endl;
                                            faceButton.ChangeTexture(ResourceManager::GetTexture("face_win.png"));
                                            leaderboardWindow.UpdateLeaderboard(GameManager::GetTime());
                                            GameManager::PauseTimer();
                                            GameManager::SetPreviousState(GameManager::GameState::Win);
                                            GameManager::SetState(GameManager::GameState::LeaderboardOpen);
                                            leaderboardWindow.OpenWindow();
                                        }
                                    }
                                }
                                else if (event.mouseButton.button == sf::Mouse::Right)
                                {
                                    tiles[j][i] -> ToggleFlagged();
                                }
                            }
                        }
                    }

                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        if (faceButton.IsPressed(mousePos))
                        {
                            faceButton.Click();
                        }

                        if (debugButton.IsPressed(mousePos) && !GameManager::IsGameOver())
                        {
                            debugButton.Click();
                        }

                        if (playPauseButton.IsPressed(mousePos) && !GameManager::IsGameOver())
                        {
                            playPauseButton.Click();
                        }

                        if (leaderboardButton.IsPressed(mousePos) && !GameManager::IsGameOver())
                        {
                            leaderboardButton.Click();
                        }
                    }
                }
            }
        }

        window.clear(sf::Color::White);

        for (std::vector<Tile*> row : tiles)
        {
            for (Tile* tile : row)
            {
                tile -> Draw(window);
            }
        }

        faceButton.Draw(window);
        debugButton.Draw(window);
        playPauseButton.Draw(window);
        leaderboardButton.Draw(window);

        window.draw(timerMinsTens);
        window.draw(timerMinsUnits);
        window.draw(timerSecondsTens);
        window.draw(timerSecondsUnits);

        window.draw(counterHundreds);
        window.draw(counterTens);
        window.draw(counterUnits);

        if (GameManager::GetState() == GameManager::GameState::LeaderboardOpen)
        {
            window.draw(overlay);
        }

        if (GameManager::GetNumTilesFlagged() < 0)
        {
            window.draw(counterNegative);
        }

        window.display();
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            delete tiles[j][i];
        }
    }
}

void GameWindow::GenerateGrid(int columns, int rows, int mines)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            tiles[j][i] = new Tile(j * 32.f, i * 32.f, ResourceManager::GetTexture("tile_hidden.png"));
        }
    }

    srand(time(0));

    int placedMines = 0;

    while (placedMines < mines)
    {
        int x = rand() % columns;
        int y = rand() % rows;

        if (tiles[x][y] -> GetAdjacentMinesCount() != -1)
        {
            tiles[x][y] -> SetAsMine();
            mineTiles.push_back(tiles[x][y]);
            placedMines++;
        }
    }

    Tile* currentTile;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            currentTile = tiles[j][i];

            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    if ((k == 0 && l == 0) || currentTile -> GetAdjacentMinesCount() == -1)
                    {
                        continue;
                    }

                    if ((l + j) >= 0 && (l + j) < columns && (k + i) >= 0 && (k + i) < rows)
                    {
                        if (tiles[l + j][k + i] -> GetAdjacentMinesCount() != -1)
                        {
                            currentTile -> AddAdjacentTile(tiles[l + j][k + i]);
                        }
                        else
                        {
                            currentTile -> IncreaseAdjacentMinesCount();
                        }
                    }
                }
            }
        }
    }
}

void GameWindow::ResetGame()
{
    int columns = ResourceManager::GetColumns();
    int rows = ResourceManager::GetRows();
    int mines = ResourceManager::GetMines();

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            delete tiles[j][i];
        }
    }

    tiles.clear();
    tiles = std::vector<std::vector<Tile*>>(columns, std::vector<Tile*>(rows, nullptr));

    GenerateGrid(columns, rows, mines);

    GameManager::ResetData();
}