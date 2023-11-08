#include "CTriangleShape.h"

CTriangleShape::CTriangleShape(float x1, float y1, float x2, float y2, float x3, float y3)
{
	m_triangle.setPointCount(3);
	m_triangle.setPoint(0, sf::Vector2f(x1, y1));
	m_triangle.setPoint(1, sf::Vector2f(x2, y2));
	m_triangle.setPoint(2, sf::Vector2f(x3, y3));
	m_triangle.setFillColor(sf::Color::Blue);
}

float CTriangleShape::GetSquare() const
{
	sf::Vector2f point1 = m_triangle.getPoint(0);
	sf::Vector2f point2 = m_triangle.getPoint(1);
	sf::Vector2f point3 = m_triangle.getPoint(2);

	float a = GetDistance(point1, point2);
	float b = GetDistance(point2, point3);
	float c = GetDistance(point3, point1);

	float p = (a + b + c) / 2.0f;
	return std::sqrt(p * (p - a) * (p - b) * (p - c));
}

float CTriangleShape::GetPerimeter() const
{
	sf::Vector2f point1 = m_triangle.getPoint(0);
	sf::Vector2f point2 = m_triangle.getPoint(1);
	sf::Vector2f point3 = m_triangle.getPoint(2);

	float a = GetDistance(point1, point2);
	float b = GetDistance(point2, point3);
	float c = GetDistance(point3, point1);

	return a + b + c;
}

void CTriangleShape::Draw(sf::RenderWindow& window) const
{
	window.draw(m_triangle);
}

std::string CTriangleShape::ToString() const
{
	std::stringstream ss;
	ss << "TRIANGLE: P=" << GetPerimeter() << "; S=" << GetSquare();
	return ss.str();
}

float CTriangleShape::GetDistance(const sf::Vector2f& point1, const sf::Vector2f& point2) const
{
	float dx = point2.x - point1.x;
	float dy = point2.y - point1.y;
	return std::sqrt(dx * dx + dy * dy);
}
