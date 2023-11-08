#include "CCircleShape.h"

CCircleShape::CCircleShape(float centerX, float centerY, float radius)
	: m_circle(radius)
{
	m_circle.setPosition(centerX - radius, centerY - radius);
	m_circle.setFillColor(sf::Color::Red);
}

float CCircleShape::GetSquare() const
{
	float radius = m_circle.getRadius();
	return static_cast<float>(M_PI) * radius * radius;
}

float CCircleShape::GetPerimeter() const
{
	float radius = m_circle.getRadius();
	return 2.0f * static_cast<float>(M_PI) * radius;
}

void CCircleShape::Draw(sf::RenderWindow& window) const
{
	window.draw(m_circle);
}

std::string CCircleShape::ToString() const 
{
	std::stringstream ss;
	ss << "CIRCLE: P=" << GetPerimeter() << "; S=" << GetSquare();
	return ss.str();
}