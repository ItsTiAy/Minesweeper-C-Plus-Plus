#include "ResourceManager.h"

std::unordered_map<std::string, sf::Texture> ResourceManager::textures;
std::unordered_map<std::string, sf::Font> ResourceManager::fonts;
std::vector<std::pair<std::string, std::string>> ResourceManager::scores;
int ResourceManager::columns;
int ResourceManager::rows;
int ResourceManager::mines;
std::string ResourceManager::playerName;

bool ResourceManager::SetIcon(sf::RenderWindow& window)
{
    sf::Image icon;
    icon.loadFromFile("files/images/mine.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    return true;
}


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

bool ResourceManager::LoadScores()
{
    std::ifstream config("files/leaderboard.txt");
    scores.clear();

    std::string line;
    std::string time;
    std::string name;

    while (std::getline(config, line))
    {
        int delPos = line.find(",");

        time = line.substr(0, delPos);
        name = line.substr(delPos + 1);

        scores.push_back(std::make_pair(time,name));
    }

    return true;
}

bool ResourceManager::WriteScores(std::vector<std::pair<std::string, std::string>> newScores)
{
    std::ofstream file("files/leaderboard.txt");

    for (int i = 0; i < newScores.size(); i++)
    {
        file << newScores[i].first << "," << newScores[i].second << std::endl;
    }

    file.close();

    return true;
}

std::vector<std::pair<std::string, std::string>> ResourceManager::GetScores()
{
    return scores;
}

std::string ResourceManager::GetPlayerName()
{
    return playerName;
}

void ResourceManager::SetPlayerName(std::string& name)
{
    playerName = name;
}

