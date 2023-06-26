#include "Button.h"
#include <iostream>

Button::Button(std::string text, sf::Vector2f position, int size)
{
    this->initFont();
    this->text.setFont(font);

    this->text.setString(text);
	this->text.setCharacterSize(size);
	this->text.setFillColor(sf::Color::White);
	this->text.setPosition(position);

    color = sf::Color::White;
}

void Button::initFont()
{
    font.loadFromFile("Fonts/Arial.ttf");
}

void Button::illuminate(sf::Vector2f& mousePosition)
{
    if (this->text.getGlobalBounds().contains(mousePosition))
    {
        this->text.setFillColor(sf::Color::Red);
    }
    else
    {
        this->text.setFillColor(this->color);
    }
}

bool Button::isClicked(sf::Vector2f mousePosition)
{
    if (this->text.getGlobalBounds().contains(mousePosition))
    {
        return true;
    }
	else
		return false;
}

std::string Button::getText() const
{
    return this->text.getString();
}

void Button::render(sf::RenderTarget* Target)
{
	Target->draw(text);
}

void Button::setColor(sf::Color color)
{
    this->color = color;
}
