#include "CController.h"

CController::CController() : m_window(sf::VideoMode(800, 600), "Shapes") {}

void CController::Run()
{
	ReadShapesFromFile("input.txt");
	WriteShapesToFile("output.txt");

	sf::Event event;
	while (m_window.isOpen())
	{
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				m_window.close();
		}

		m_window.clear();

		for (const auto& shape : m_shapes)
		{
			shape->Draw(m_window);
		}

		m_window.display();
	}
}

void CController::ReadShapesFromFile(const std::string& filename)
{
	std::ifstream inputFile(filename);
	if (!inputFile.is_open())
	{
		std::cerr << "Failed to open file: " << filename << std::endl;
		return;
	}

	std::string line;
	while (std::getline(inputFile, line))
	{
		ProcessLine(line);
	}
}

void CController::WriteShapesToFile(const std::string& fileName)
{
	std::ofstream output(fileName);
	if (!output)
	{
		std::cerr << "Ошибка при открытии файла: " << fileName << std::endl;
		return;
	}
	for (const auto& shape : m_shapes)
	{
		output << shape->ToString() << std::endl;
	}
}

void CController::ProcessLine(const std::string& line)
{
	std::istringstream iss(line);
	std::string shapeType;
	iss >> shapeType;

	if (shapeType == "TRIANGLE:")
	{
		ProcessTriangle(iss);
	}
	if (shapeType == "RECTANGLE:")
	{
		ProcessRectangle(iss);
	}
	if (shapeType == "CIRCLE:")
	{
		ProcessCircle(iss);
	}
}

Point CController::ParsePointFromString(std::string& pointString)
{
	Point point;

	size_t equalSignPos = pointString.find('=');
	size_t commaPos = pointString.find(',');

	if (equalSignPos != std::string::npos && commaPos != std::string::npos)
	{
		point.x = std::stof(pointString.substr(equalSignPos + 1, commaPos - equalSignPos - 1));
		point.y = std::stof(pointString.substr(commaPos + 1));
	}
	else
	{
		std::cerr << "Error: Invalid point format: " << pointString << std::endl;
		point.x = point.y = 0.0f;
	}

	return point;
}

void CController::ProcessTriangle(std::istringstream& iss)
{
	Point point1, point2, point3;
	std::string pointString1, pointString2, pointString3;
	iss >> pointString1 >> pointString2 >> pointString3;

	point1 = ParsePointFromString(pointString1);
	point2 = ParsePointFromString(pointString2);
	point3 = ParsePointFromString(pointString3);

	m_shapes.push_back(std::make_unique<CTriangleShape>(point1.x, point1.y, point2.x, point2.y, point3.x, point3.y));
}

void CController::ProcessRectangle(std::istringstream& iss)
{
	Point point1, point2;
	std::string pointString1, pointString2;
	iss >> pointString1 >> pointString2;

	point1 = ParsePointFromString(pointString1);
	point2 = ParsePointFromString(pointString2);

	m_shapes.push_back(std::make_unique<CRectangleShape>(point1.x, point1.y, point2.x, point2.y));
}

void CController::ProcessCircle(std::istringstream& iss)
{
	Point centerPoint;
	float radius;
	std::string centerPointString, radiusString;
	iss >> centerPointString >> radiusString;

	size_t radiusPosition = radiusString.find('=');
	if (radiusPosition != std::string::npos)
		radius = std::stof(radiusString.substr(radiusPosition + 1));

	centerPoint = ParsePointFromString(centerPointString);

	m_shapes.push_back(std::make_unique<CCircleShape>(centerPoint.x, centerPoint.y, radius));
}

void CController::DrawShapes()
{
	for (const auto& shape : m_shapes)
	{
		shape->Draw(m_window);
	}
}