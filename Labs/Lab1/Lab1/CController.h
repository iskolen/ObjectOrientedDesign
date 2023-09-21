#pragma once

#include "CBaseShape.h"
#include "CCircleShape.h"
#include "CRectangleShape.h"
#include "CTriangleShape.h"

class CController
{
public:
	CController();
	void Run();

private:
	sf::RenderWindow m_window;
	std::vector<std::unique_ptr<CBaseShape>> m_shapes;

	sf::Vector2f ParseCoordinates(const std::string& str);
	void ReadShapesFromFile(const std::string& fileName);
	void WriteShapesToFile(const std::string& fileName);
	void HandleEvents();
	void DrawShapes();
};