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
	virtual void Draw(sf::RenderWindow&);
	void SetOnClick(const std::function<bool()>&);
	std::function<bool()> Click;
	void ChangeTexture(sf::Texture&);
	virtual ~Button();
};

