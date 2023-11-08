#include "CTriangle.h"

CTriangle::CTriangle(float x1, float y1, float x2, float y2, float x3, float y3)
{
	m_triangle.setPointCount(3);
	m_triangle.setPoint(0, sf::Vector2f(x1, y1));
	m_triangle.setPoint(1, sf::Vector2f(x2, y2));
	m_triangle.setPoint(2, sf::Vector2f(x3, y3));
	m_triangle.setFillColor(sf::Color::Blue);

	m_selected = false;
}

float CTriangle::GetSquare() const
{
	sf::Vector2f point1 = m_triangle.getPoint(0);
	sf::Vector2f point2 = m_triangle.getPoint(1);
	sf::Vector2f point3 = m_triangle.getPoint(2);

	float a = GetLength(point1, point2);
	float b = GetLength(point2, point3);
	float c = GetLength(point3, point1);

	float p = (a + b + c) / 2.0f; // ѕолупериметр
	return std::sqrt(p * (p - a) * (p - b) * (p - c)); /*ѕлощадь треугольника равна квадратному корню из произведени€ 
													   его полупериметра на разности полупериметра и каждой из его 
													   сторон.*/
}

float CTriangle::GetPerimeter() const
{
	sf::Vector2f point1 = m_triangle.getPoint(0);
	sf::Vector2f point2 = m_triangle.getPoint(1);
	sf::Vector2f point3 = m_triangle.getPoint(2);

	float a = GetLength(point1, point2);
	float b = GetLength(point2, point3);
	float c = GetLength(point3, point1);

	return a + b + c;
}

void CTriangle::Render(sf::RenderWindow& window)
{
	m_triangle.setOutlineThickness(TRIANGLE_OUTLINE_THICKNESS);

	if (m_selected)
	{
		m_triangle.setOutlineColor(sf::Color::White);
	}
	else
	{
		m_triangle.setOutlineColor(sf::Color::Transparent);
	}

	window.draw(m_triangle);
}

std::string CTriangle::ToString() const
{
	std::stringstream ss;
	ss << TRIANGLE_LABEL << PERIMETER_LABEL << GetPerimeter() << SEPARATOR << SQUARE_LABEL << GetSquare();
	return ss.str();
}

float CTriangle::GetLength(const sf::Vector2f& point1, const sf::Vector2f& point2) const
{
	float dx = point2.x - point1.x;
	float dy = point2.y - point1.y;
	return std::sqrt(dx * dx + dy * dy);
}

bool CTriangle::IsContainsPoint(float x, float y) const
{
	sf::FloatRect bounds = m_triangle.getGlobalBounds();
	return bounds.contains(x, y);
}

sf::FloatRect CTriangle::GetBounds() const
{
	sf::FloatRect bounds = m_triangle.getGlobalBounds();
	return bounds;
}

void CTriangle::SetSelected(bool selected)
{
	m_selected = selected;
}

bool CTriangle::IsSelected() const
{
	return m_selected;
}

void CTriangle::MoveTo(float x, float y)
{
	m_triangle.setPosition(x, y);
}

sf::Vector2f CTriangle::GetPosition() const
{
	return m_triangle.getPosition();
}