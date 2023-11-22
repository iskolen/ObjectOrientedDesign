#pragma once
#include "CSimpleFigure.h"

const float TRIANGLE_OUTLINE_THICKNESS = 4.0f;
const std::string TRIANGLE_LABEL = "TRIANGLE: ";

class CTriangle final : public CSimpleFigure
{
public:
	CTriangle(float x1, float y1, float x2, float y2, float x3, float y3);

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
	sf::ConvexShape m_triangle;
	bool m_selected;
	float GetLength(const sf::Vector2f& point1, const sf::Vector2f& point2) const;

	float GetSquare() const;
	float GetPerimeter() const;
};