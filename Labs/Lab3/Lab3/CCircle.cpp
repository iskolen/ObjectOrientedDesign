#include "CCircle.h"

CCircle::CCircle(float centerX, float centerY, float radius)
	: m_circle(radius)
{
	m_circle.setPosition(centerX - radius, centerY - radius);
	m_circle.setFillColor(sf::Color::Red);

	m_selected = false;
}

float CCircle::GetSquare() const
{
	float radius = m_circle.getRadius();
	return static_cast<float>(M_PI) * radius * radius; // Формула расчёта площади круга: S = π * r^2
}

float CCircle::GetPerimeter() const
{
	float radius = m_circle.getRadius();
	return 2.0f * static_cast<float>(M_PI) * radius; // Формула расчета периметра круга: P = 2 * π * r
}

void CCircle::Render(sf::RenderWindow& window)
{
	if (m_selected)
	{
		sf::FloatRect globalBounds = m_circle.getGlobalBounds();
		sf::RectangleShape boundingBox(sf::Vector2f(globalBounds.width, globalBounds.height));
		boundingBox.setPosition(globalBounds.left, globalBounds.top);
		boundingBox.setOutlineThickness(CIRCLE_OUTLINE_THICKNESS);
		boundingBox.setOutlineColor(sf::Color::White);
		boundingBox.setFillColor(sf::Color::Transparent);

		window.draw(boundingBox);
	}

	window.draw(m_circle);
}

std::string CCircle::ToString() const
{
	std::stringstream ss;
	ss << CIRCLE_LABEL << PERIMETER_LABEL << GetPerimeter() << SEPARATOR << SQUARE_LABEL << GetSquare();
	return ss.str();
}

bool CCircle::IsContainsPoint(float x, float y) const
{
	sf::FloatRect bounds = m_circle.getGlobalBounds();
	return bounds.contains(x, y);
}

sf::FloatRect CCircle::GetBounds() const
{
	sf::FloatRect bounds = m_circle.getGlobalBounds();
	return bounds;
}

void CCircle::SetSelected(bool selected)
{
	m_selected = selected;
}

bool CCircle::IsSelected() const
{
	return m_selected;
}

void CCircle::MoveTo(float x, float y)
{
	m_circle.setPosition(x, y);
}

sf::Vector2f CCircle::GetPosition() const
{
	return m_circle.getPosition();
}

void CCircle::SetFigureColor(const sf::Color& fill)
{
	m_circle.setFillColor(fill);
}

void CCircle::SetOutlineThickness(float thickness)
{
	m_circle.setOutlineThickness(thickness);
}

void CCircle::SetOutlineColor(const sf::Color& fill)
{
	m_circle.setOutlineColor(fill);
}