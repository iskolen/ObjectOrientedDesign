#pragma once
#include "CBaseShape.h"

class CTriangleShape : public CBaseShape
{
public:
	CTriangleShape(float x1, float y1, float x2, float y2, float x3, float y3);

	float GetSquare() const;
	float GetPerimeter() const;
	void Draw(sf::RenderWindow& window) const override;
	std::string ToString() const override;

private:
	sf::ConvexShape m_triangle;
	float GetDistance(const sf::Vector2f& point1, const sf::Vector2f& point2) const;
};