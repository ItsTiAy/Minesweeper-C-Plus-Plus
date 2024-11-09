#include "ResourceManager.h"

std::unordered_map<std::string, sf::Texture> ResourceManager::textures;
std::unordered_map<std::string, sf::Font> ResourceManager::fonts;
int ResourceManager::columns;
int ResourceManager::rows;
int ResourceManager::mines;
ResourceManager::GameState ResourceManager::state;

bool ResourceManager::LoadTexture(const std::string& fileName)
{
    if (textures.find(fileName) != textures.end())
    {
        return true;
    }

    sf::Texture texture;
    if (!texture.loadFromFile("files/images/" + fileName))
    {
        std::cerr << "Error loading texture: " << fileName << std::endl;
        return false;
    }

    textures[fileName] = texture;
    return true;
}

bool ResourceManager::LoadFont(const std::string& fileName)
{
    if (fonts.find(fileName) != fonts.end())
    {
        return true;
    }

    sf::Font font;
    if (!font.loadFromFile("files/" + fileName))
    {
        std::cerr << "Error loading texture: " << fileName << std::endl;
        return false;
    }

    fonts[fileName] = font;
    return true;
}

bool ResourceManager::LoadConfig()
{
    std::ifstream config("files/config.cfg");

    std::string columnsString;
    std::string rowsString;
    std::string minesString;

    std::getline(config, columnsString);
    std::getline(config, rowsString);
    std::getline(config, minesString);

    columns = std::max(std::stoi(columnsString), 22);
    rows = std::max(std::stoi(rowsString), 16);
    mines = std::min(std::stoi(minesString), rows * columns);

    if (mines < 1)
    {
        mines = 1;
    }

    return true;
}

sf::Texture& ResourceManager::GetTexture(const std::string& fileName)
{
    if (textures.find(fileName) == textures.end())
    {
        LoadTexture(fileName);
    }

    return textures[fileName];
}

sf::Font& ResourceManager::GetFont(const std::string& fileName)
{
    if (fonts.find(fileName) == fonts.end())
    {
        LoadFont(fileName);
    }

    return fonts[fileName];
}

int ResourceManager::GetColumns()
{
    return columns;
}

int ResourceManager::GetRows()
{
    return rows;
}

int ResourceManager::GetMines()
{
    return mines;
}

void ResourceManager::SetState(GameState newState)
{
    state = newState;
}

ResourceManager::GameState ResourceManager::GetState()
{
    return state;
}