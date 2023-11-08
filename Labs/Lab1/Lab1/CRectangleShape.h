#pragma once
#include "CBaseShape.h"

class CRectangleShape final : public CBaseShape
{
public:
	CRectangleShape(float x1, float y1, float x2, float y2);

	float GetSquare() const;
	float GetPerimeter() const;
	void Draw(sf::RenderWindow& window) const override;
	std::string ToString() const override;

private:
	sf::RectangleShape m_rectangle;
};