#include "GameWindow.h"

GameWindow::GameWindow()
{
    std::cout << "Game Window" << std::endl;

    int columns = ResourceManager::GetColumns();
    int rows = ResourceManager::GetRows();
    int mines = ResourceManager::GetMines();

    sf::RenderWindow window(sf::VideoMode((columns * 32.f), (rows * 32.f) + 100.f), "Minesweeper", sf::Style::Close);

    tiles = std::vector<std::vector<Tile*>>(columns, std::vector<Tile*>(rows, nullptr));

    Button faceButton(((columns / 2.f) * 32) - 32.f, 32.f * (rows + 0.5f), ResourceManager::GetTexture("face_happy.png"));
    Button debugButton((columns * 32) - 304.f, 32.f * (rows + 0.5f), ResourceManager::GetTexture("debug.png"));
    Button playPauseButton((columns * 32) - 240.f, 32.f * (rows + 0.5f), ResourceManager::GetTexture("pause.png"));
    Button leaderboardButton((columns * 32) - 176.f, 32.f * (rows + 0.5f), ResourceManager::GetTexture("leaderboard.png"));

    faceButton.SetOnClick([&]() -> bool
    {
        std::cout << "Face Button" << std::endl;

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
            GameManager::SetState(GameManager::GameState::Playing);
            playPauseButton.ChangeTexture(ResourceManager::GetTexture("pause.png"));
        }
        else
        {
            GameManager::SetState(GameManager::GameState::Paused);
            playPauseButton.ChangeTexture(ResourceManager::GetTexture("play.png"));
        }

        return true;
    });

    leaderboardButton.SetOnClick([&]() -> bool
    {
        std::cout << "Leaderboard Button" << std::endl;
        GameManager::GameState previousState = GameManager::GetState();
        GameManager::SetState(GameManager::GameState::LeaderboardOpen);

        LeaderboardWindow leaderboardWindow; //Need fix, stops gamewindow doing anything

        GameManager::SetState(previousState);
        return true;
    });

    GenerateGrid(columns, rows, mines);

    while (window.isOpen())
    {
        sf::Vector2f mousePos(sf::Mouse::getPosition(window));

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonReleased && interactable)
            {
                for (int i = 0; i < rows; i++)
                {
                    for (int j = 0; j < columns; j++)
                    {
                        if (tiles[j][i] -> IsPressed(mousePos) && !GameManager::IsGameOver() && GameManager::GetState() != GameManager::GameState::Paused)
                        {
                            if (event.mouseButton.button == sf::Mouse::Left)
                            {
                                if (!tiles[j][i] -> Click())
                                {
                                    std::cout << "Game Lose" << std::endl;
                                    faceButton.ChangeTexture(ResourceManager::GetTexture("face_lose.png"));
                                    GameManager::SetState(GameManager::GameState::Lose);
                                }
                                else
                                {
                                    if ((columns * rows) - mines == GameManager::GetNumTilesRevealed())
                                    {
                                        std::cout << "Game Win" << std::endl;
                                        faceButton.ChangeTexture(ResourceManager::GetTexture("face_win.png"));
                                        GameManager::SetState(GameManager::GameState::Win);
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
            tiles[j][i] = new Tile(j * 32.f, i * 32.f, ResourceManager::GetTexture("tile_up.png"));
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

    GameManager::SetState(GameManager::GameState::Playing);
}