#pragma once
#include "stdafx.h"

class CBaseShape
{
public:
	virtual std::string ToString() const = 0;
	virtual void Draw(sf::RenderWindow& window) const = 0;
};