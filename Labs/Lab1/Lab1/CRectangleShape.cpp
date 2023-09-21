#include "CRectangleShape.h"


CRectangleShape::CRectangleShape(const sf::Vector2f& point1, const sf::Vector2f& point2)
	: m_point1(point1), m_point2(point2) {}

double CRectangleShape::GetSquare() const
{
	return GetWidth() * GetHeight();
}

double CRectangleShape::GetPerimeter() const
{
	return 2 * (GetWidth() + GetHeight());
}

void CRectangleShape::Draw(sf::RenderWindow& window) const
{
	sf::RectangleShape rectangle;
	rectangle.setPosition(m_point1);
	rectangle.setSize(sf::Vector2f(GetWidth(), GetHeight()));
	rectangle.setFillColor(sf::Color::Red);
	window.draw(rectangle);
}

std::string CRectangleShape::ToString() const
{
	std::stringstream ss;
	ss << "RECTANGLE: P=" << GetPerimeter() << "; S=" << GetSquare();
	return ss.str();
}

double CRectangleShape::GetWidth() const
{
	return m_point2.x - m_point1.x;
}

double CRectangleShape::GetHeight() const
{
	return m_point2.y - m_point1.y;
}
