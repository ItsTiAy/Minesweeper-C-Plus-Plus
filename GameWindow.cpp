#include "GameWindow.h"
#include "Tile.h"
#include "Button.h"
#include <SFML/Graphics.hpp>
#include <list>
#include <vector>
#include <string>
#include <random>
#include <iostream>

GameWindow::GameWindow()
{
    int columns = 25;
    int rows = 16;

    sf::RenderWindow window(sf::VideoMode(800, 600), "Minesweeper", sf::Style::Close);

    tiles = std::vector<std::vector<Tile*>>(columns, std::vector<Tile*>(rows, nullptr));

    tileUpTexture.loadFromFile("files/images/tile_up.png");
    tileDownTexture.loadFromFile("files/images/tile_down.png");

    happyFaceTexture.loadFromFile("files/images/face_happy.png");
    debugTexture.loadFromFile("files/images/debug.png");
    pauseTexture.loadFromFile("files/images/pause.png");
    playTexture.loadFromFile("files/images/play.png");
    leaderboardTexture.loadFromFile("files/images/leaderboard.png");

    font.loadFromFile("arial.ttf");

    Button faceButton(((columns / 2.f) * 32) - 32.f, 32.f * (rows + 0.5f), happyFaceTexture);
    Button debugButton((columns * 32) - 304.f, 32.f * (rows + 0.5f), debugTexture);
    Button playPauseButton((columns * 32) - 240.f, 32.f * (rows + 0.5f), pauseTexture);
    Button leaderboardButton((columns * 32) - 176.f, 32.f * (rows + 0.5f), leaderboardTexture);

    faceButton.SetOnClick([]() 
    {
        std::cout << "Face Button" << std::endl;
    });

    debugButton.SetOnClick([]()
    {
        std::cout << "Debug Button" << std::endl;
    });

    playPauseButton.SetOnClick([]()
    {
        std::cout << "Play Pause Button" << std::endl;
    });

    leaderboardButton.SetOnClick([]()
    {
        std::cout << "Leaderboard Button" << std::endl;
    });

    GenerateGrid(rows, columns, 50);

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

            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                for (int i = 0; i < rows; i++)
                {
                    for (int j = 0; j < columns; j++)
                    {
                        if(tiles[j][i] -> IsMouseOver(mousePos))
                        {
                            tiles[j][i] -> RevealTile();
                        }
                    }
                }

                if (faceButton.IsPressed(mousePos))
                {
                    faceButton.Click();
                }

                if (debugButton.IsPressed(mousePos))
                {
                    debugButton.Click();
                }

                if (playPauseButton.IsPressed(mousePos))
                {
                    playPauseButton.Click();
                }

                if (leaderboardButton.IsPressed(mousePos))
                {
                    leaderboardButton.Click();
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

void GameWindow::GenerateGrid(int rows, int columns, int mines)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            tiles[j][i] = new Tile(j * 32.f, i * 32.f, tileUpTexture, tileDownTexture, font);
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