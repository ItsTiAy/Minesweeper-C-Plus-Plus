#include "Button.h"

Button::Button(float x, float y, sf::Texture& texture)
{
	sprite.setTexture(texture);
	sprite.setPosition(x, y);
}

// Returns if the mouse pointer is over the button
bool Button::IsPressed(const sf::Vector2f& mousePos)
{
	return sprite.getGlobalBounds().contains(mousePos);
}

// Sets the click functionality of the button
void Button::SetOnClick(const std::function<bool()>& handler)
{
	Click = handler;
}

// Changes the buttons texture
void Button::ChangeTexture(sf::Texture& newTexture)
{
	sprite.setTexture(newTexture);
}

// Renders the button on the window
void Button::Draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

Button::~Button() {};