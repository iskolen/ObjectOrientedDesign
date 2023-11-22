#pragma once
#include "stdafx.h"
#include "Point.h"

class IFigure
{
public:
	virtual std::string ToString() const = 0;
	virtual void Render(sf::RenderWindow& window) = 0;
	virtual bool IsContainsPoint(float x, float y) const = 0;
	virtual bool IsSelected() const = 0;
	virtual void SetSelected(bool selected) = 0;
	virtual sf::FloatRect GetBounds() const = 0;
	virtual void MoveTo(float x, float y) = 0;
	virtual sf::Vector2f GetPosition() const = 0;

	virtual void SetFigureColor(const sf::Color& fill) = 0;
	virtual void SetOutlineThickness(float thickness) = 0;
	virtual void SetOutlineColor(const sf::Color& fill) = 0;
};