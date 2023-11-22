#pragma once
#include "CSimpleFigure.h"

const float RECTANGLE_OUTLINE_THICKNESS = 4.0f;
const std::string RECTANGLE_LABEL = "RECTANGLE: ";

class CRectangle final : public CSimpleFigure
{
public:
	CRectangle(float x1, float y1, float x2, float y2);

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
	sf::RectangleShape m_rectangle;
	bool m_selected;

	float GetSquare() const;
	float GetPerimeter() const;
};