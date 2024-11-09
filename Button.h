#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
class Button
{
protected:
	sf::Sprite sprite;
	sf::Texture texture;
public:
	Button(float, float, sf::Texture&);
	bool IsPressed(const sf::Vector2f&);
	virtual void Draw(sf::RenderWindow&) const;
	void SetOnClick(const std::function<void()>&);
	std::function<void()> Click;
	virtual ~Button();
};

