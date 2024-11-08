#include "GameWindow.h"
#include <SFML/Graphics.hpp>
#include <list>

GameWindow::GameWindow()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Minesweeper", sf::Style::Close);

    sf::Font font;
    font.loadFromFile("arial.ttf");

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

        window.clear(sf::Color::White);
        window.display();
    }
}

void GameWindow::GenerateGrid(int rows, int columns, int mines)
{
    /*
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            Tile tile;

            Canvas.SetLeft(tile, j * 32);
            Canvas.SetTop(tile, i * 32);

            tile.PreviewMouseDown += (o, e) = >
            {
                if (e.ChangedButton == MouseButton.Left)
                {
                    CheckTile(tile);
                }
                else if (e.ChangedButton == MouseButton.Right)
                {
                    tile.IsFlagged = !tile.IsFlagged;
                    tile.Content = tile.IsFlagged;
                }
            };

            tiles[j, i] = tile;
        }
    }

    Random random = new();

    int placedMines = 0;

    while (placedMines < mines)
    {
        int x = random.Next(columns);
        int y = random.Next(rows);

        if (tiles[x, y].AdjacentMinesCount != -1)
        {
            tiles[x, y].AdjacentMinesCount = -1;
            mineTiles[placedMines] = tiles[x, y];
            placedMines++;
        }
    }

    Tile currentTile;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            currentTile = tiles[j, i];

            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    if ((k == 0 && l == 0) || currentTile.AdjacentMinesCount == -1)
                    {
                        continue;
                    }

                    if ((l + j) >= 0 && (l + j) < columns && (k + i) >= 0 && (k + i) < rows)
                    {
                        if (tiles[l + j, k + i].AdjacentMinesCount != -1)
                        {
                            currentTile.AdjacentTiles.Add(tiles[l + j, k + i]);
                        }
                        else
                        {
                            currentTile.AdjacentMinesCount++;
                        }
                    }
                }
            }
        }
    }
    */
}

class Tile
{
private:
    bool isFlagged;
    bool isRevealed;
    int adjacentMinesCount;
    Tile* adjacentTiles[8];
public:
    void RevealTile()
    {
        if (isRevealed)
        {
            return;
        }

        isRevealed = true;

        if (adjacentMinesCount > 0)
        {
            //Content = adjacentMinesCount;
            return;
        }

        for (Tile* tile : adjacentTiles)
        {
            //tile.RevealTile();
        }
    }
};