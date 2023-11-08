#include "CRectangle.h"

CRectangle::CRectangle(float x1, float y1, float x2, float y2)
{
	sf::Vector2f position1(x1, y1);
	sf::Vector2f position2(x2, y2);

	float width = std::abs(x2 - x1);
	float height = std::abs(y2 - y1);

	m_rectangle.setPosition(position1);
	m_rectangle.setSize(sf::Vector2f(width, height));
	m_rectangle.setFillColor(sf::Color::Green);

	m_selected = false;
}

float CRectangle::GetSquare() const
{
	sf::Vector2f size = m_rectangle.getSize();
	float width = size.x;
	float height = size.y;

	return width * height;
}

float CRectangle::GetPerimeter() const
{
	sf::Vector2f size = m_rectangle.getSize();
	float width = size.x;
	float height = size.y;

	return 2 * (width + height); // Формула расчета периметра прямоугольника: P = 2 * (a + b)
}

void CRectangle::Render(sf::RenderWindow& window)
{
	m_rectangle.setOutlineThickness(RECTANGLE_OUTLINE_THICKNESS);

	if (m_selected)
	{
		m_rectangle.setOutlineColor(sf::Color::White);
	}
	else
	{
		m_rectangle.setOutlineColor(sf::Color::Transparent);
	}

	window.draw(m_rectangle);
}

std::string CRectangle::ToString() const
{
	std::stringstream ss;
	ss << RECTANGLE_LABEL << PERIMETER_LABEL << GetPerimeter() << SEPARATOR << SQUARE_LABEL << GetSquare();
	return ss.str();
}

bool CRectangle::IsContainsPoint(float x, float y) const
{
	sf::FloatRect bounds = m_rectangle.getGlobalBounds();
	return bounds.contains(x, y);
}

sf::FloatRect CRectangle::GetBounds() const
{
	sf::FloatRect bounds = m_rectangle.getGlobalBounds();
	return bounds;
}

void CRectangle::SetSelected(bool selected)
{
	m_selected = selected;
}

bool CRectangle::IsSelected() const
{
	return m_selected;
}

void CRectangle::MoveTo(float x, float y)
{
	m_rectangle.setPosition(x, y);
}

sf::Vector2f CRectangle::GetPosition() const
{
	return m_rectangle.getPosition();
}