#pragma once
#include "CBaseShape.h"

class CCircleShape final : public CBaseShape
{
public:
	CCircleShape(float centerX, float centerY, float radius);

	float GetSquare() const;
	float GetPerimeter() const;
	void Draw(sf::RenderWindow& window) const override;
	std::string ToString() const override;
private:
	sf::CircleShape m_circle;
};