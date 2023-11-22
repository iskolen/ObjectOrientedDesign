#pragma once
#include "CSimpleFigure.h"

const float CIRCLE_OUTLINE_THICKNESS = 4.0f;
const std::string CIRCLE_LABEL = "CIRCLE: ";

class CCircle final : public CSimpleFigure
{
public:
	CCircle(float centerX, float centerY, float radius);

	std::string ToString() const override;

	bool IsContainsPoint(float x, float y) const override;
	bool IsSelected() const override;

	void Render(sf::RenderWindow& window) override;
	void SetSelected(bool selected) override;
	void MoveTo(float x, float y) override;

	sf::FloatRect GetBounds() const override;
	sf::Vector2f GetPosition() const override;

	void SetFigureColor(const sf::Color& fill) override;
	void SetOutlineThickness(float thickness)  override;
	void SetOutlineColor(const sf::Color& fill) override;

private:
	sf::CircleShape m_circle;
	bool m_selected;

	float GetSquare() const;
	float GetPerimeter() const;
};