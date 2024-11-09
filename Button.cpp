#include "Button.h"

Button::Button(float x, float y, sf::Texture& texture)
{
	sprite.setTexture(texture);
	sprite.setPosition(x, y);
}

bool Button::IsPressed(const sf::Vector2f& mousePos)
{
	return sprite.getGlobalBounds().contains(mousePos);
}

void Button::SetOnClick(const std::function<void()>& handler)
{
	Click = handler;
}

void Button::Draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}