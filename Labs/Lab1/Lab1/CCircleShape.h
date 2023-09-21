#pragma once
#include "CBaseShape.h"

class CCircleShape final : public CBaseShape
{
public:
	CCircleShape(const sf::Vector2f& center, float radius);

	double GetSquare() const override;
	double GetPerimeter() const override;
	void Draw(sf::RenderWindow& window) const override;
	std::string ToString() const override;

private:
	sf::Vector2f m_center;
	double m_radius;
};

