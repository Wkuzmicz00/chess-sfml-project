#ifndef BUTTON_H
#define BUTTON_H


#include <SFML/Graphics.hpp>


class Button
{
private:
	sf::Font font;
	sf::Text text;

	sf::Vector2f buttonPos;

	sf::Color color;

	void initFont();

public:
	Button(std::string text, sf::Vector2f position, int size);

	void illuminate(sf::Vector2f& mousePosition);

	bool isClicked(sf::Vector2f mousePosition);

	std::string getText() const;

	void setColor(sf::Color color);

	//Functions
	void render(sf::RenderTarget* Target);
};

#endif // BUTTON_H
