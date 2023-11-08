#include "CRectangleShape.h"


CRectangleShape::CRectangleShape(float x1, float y1, float x2, float y2)
{
	sf::Vector2f position1(x1, y1);
	sf::Vector2f position2(x2, y2);

	float width = std::abs(x2 - x1);
	float height = std::abs(y2 - y1);

	m_rectangle.setPosition(position1);
	m_rectangle.setSize(sf::Vector2f(width, height));
	m_rectangle.setFillColor(sf::Color::Green);
}

float CRectangleShape::GetSquare() const
{
	sf::Vector2f size = m_rectangle.getSize();
	float width = size.x;
	float height = size.y;

	return width * height;
}

float CRectangleShape::GetPerimeter() const
{
	sf::Vector2f size = m_rectangle.getSize();
	float width = size.x;
	float height = size.y;

	return 2 * (width + height);
}

void CRectangleShape::Draw(sf::RenderWindow& window) const
{
	window.draw(m_rectangle);
}

std::string CRectangleShape::ToString() const
{
	std::stringstream ss;
	ss << "RECTANGLE: P=" << GetPerimeter() << "; S=" << GetSquare();
	return ss.str();
}