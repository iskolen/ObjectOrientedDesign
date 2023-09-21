#include "CController.h"

CController::CController() : m_window(sf::VideoMode(800, 600), "Shapes") {}

void CController::Run()
{
	ReadShapesFromFile("input.txt");
	WriteShapesToFile("output.txt");

	while (m_window.isOpen())
	{
		HandleEvents();
		DrawShapes();
	}
}

sf::Vector2f CController::ParseCoordinates(const std::string & str)
{
	sf::Vector2f result(0.0f, 0.0f);
	size_t equalPos = str.find('=');
	if (equalPos != std::string::npos)
	{
		result.x = std::stof(str.substr(equalPos + 1));
		size_t commaPos = str.find(',', equalPos);
		if (commaPos != std::string::npos)
		{
			result.y = std::stof(str.substr(commaPos + 1));
		}
	}
	return result;
}

void CController::ReadShapesFromFile(const std::string& fileName)
{
	std::ifstream input(fileName);
	if (!input)
	{
		std::cerr << "Ошибка при открытии файла" << fileName << std::endl;
		return;
	}

	std::string line;
	while (std::getline(input, line))
	{
		std::istringstream iss(line);
		std::string type;
		iss >> type;

		if (type == "CIRCLE:")
		{
			sf::Vector2f center;
			float radius;

			std::string centerStr, radiusStr;
			iss >> centerStr >> radiusStr;

			center = ParseCoordinates(centerStr);

			size_t radiusPos = radiusStr.find('=');
			if (radiusPos != std::string::npos)
				radius = std::stof(radiusStr.substr(radiusPos + 1));

			m_shapes.push_back(std::make_unique<CCircleShape>(center, radius));
		}
		if (type == "TRIANGLE:")
		{
			sf::Vector2f p1, p2, p3;

			std::string p1Str, p2Str, p3Str;
			iss >> p1Str >> p2Str >> p3Str;
			
			p1 = ParseCoordinates(p1Str);
			p2 = ParseCoordinates(p2Str);
			p3 = ParseCoordinates(p3Str);

			m_shapes.push_back(std::make_unique<CTriangleShape>(p1, p2, p3));
		}
		if (type == "RECTANGLE:")
		{
			sf::Vector2f p1, p2;

			std::string p1Str, p2Str;
			iss >> p1Str >> p2Str;

			p1 = ParseCoordinates(p1Str);
			p2 = ParseCoordinates(p2Str);

			m_shapes.push_back(std::make_unique<CRectangleShape>(p1, p2));
		}
	}
}

void CController::WriteShapesToFile(const std::string& fileName)
{
	std::ofstream output(fileName);
	if (!output)
	{
		std::cerr << "Ошибка при открытии файла" << fileName << std::endl;
		return;
	}
	for (const auto& shape : m_shapes)
	{
		output << shape->ToString() << std::endl;
	}
}

void CController::HandleEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_window.close();
	}
}

void CController::DrawShapes()
{
	m_window.clear();

	for (const auto& shape : m_shapes)
	{
		shape->Draw(m_window);
	}

	m_window.display();
}
