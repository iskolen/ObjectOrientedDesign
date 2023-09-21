#pragma once
#include "CBaseShape.h"

class CRectangleShape final : public CBaseShape
{
public:
	CRectangleShape(const sf::Vector2f& point1, const sf::Vector2f& point2);

	double GetSquare() const override;
	double GetPerimeter() const override;
	void Draw(sf::RenderWindow& window) const override;
	std::string ToString() const override;

private:
	sf::Vector2f m_point1;
	sf::Vector2f m_point2;
	double GetWidth() const;
	double GetHeight() const;
};