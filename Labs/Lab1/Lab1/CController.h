#pragma once

#include "CBaseShape.h"
#include "CCircleShape.h"
#include "CRectangleShape.h"
#include "CTriangleShape.h"

struct Point
{
	float x;
	float y;
};

class CController
{
public:
	CController();
	void Run();

private:
	sf::RenderWindow m_window;
	std::vector<std::unique_ptr<CBaseShape>> m_shapes;
	
	void ReadShapesFromFile(const std::string& filename);
	void WriteShapesToFile(const std::string& fileName);

	void ProcessLine(const std::string& line);
	void ProcessTriangle(std::istringstream& iss);
	void ProcessRectangle(std::istringstream& iss);
	void ProcessCircle(std::istringstream& iss);

	Point ParsePointFromString(std::string& pointString);
	void DrawShapes();
};