#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
class Button
{
private:
	sf::Sprite sprite;
	sf::Texture texture;
public:
	Button(float, float, sf::Texture&);
	bool IsPressed(const sf::Vector2f&);
	void Draw(sf::RenderWindow&);
	void SetOnClick(const std::function<void()>&);
	std::function<void()> Click;
};

