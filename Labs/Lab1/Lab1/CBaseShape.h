#pragma once
#include "stdafx.h"

class CBaseShape
{
public:
	virtual ~CBaseShape() = default;
	virtual double GetSquare() const = 0;
	virtual double GetPerimeter() const = 0;
	virtual void Draw(sf::RenderWindow& window) const = 0;
	virtual std::string ToString() const = 0;
};