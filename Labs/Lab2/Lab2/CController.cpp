#include "CController.h"

CController::CController() : m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE), 
							 m_draggedFigure(nullptr) 
{
}

void CController::Run()
{
	LoadFiguresFromFile(INPUT_FILE_NAME);
	SaveFiguresToFile(OUTPUT_FILE_NAME);

	while (m_window.isOpen())
	{
		HandleEvents();
		RenderFigures();
	}
}

void CController::HandleEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			m_window.close();
			break;

		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left)
				HandleMouseClick(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
			break;

		case sf::Event::MouseMoved:
			HandleMouseDrag(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y));
			break;

		case sf::Event::MouseButtonReleased:
			HandleMouseRelease();
			break;

		case sf::Event::KeyPressed:
			HandleKeyPressed();
			break;

		default:
			break;
		}
	}
}

void CController::HandleKeyPressed()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
		{
			GroupSelectedFigures();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
		{
			UngroupSelectedFigures();
		}
	}
}

void CController::HandleMouseDrag(float mouseX, float mouseY)
{
	if (m_draggedFigure)
	{
		float newX = mouseX - m_dragOffset.x;
		float newY = mouseY - m_dragOffset.y;
		m_draggedFigure->MoveTo(newX, newY);
	}
}

void CController::HandleMouseRelease()
{
	m_draggedFigure = nullptr;
}

void CController::HandleMouseClick(float mouseX, float mouseY)
{
	bool isShiftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);

	if (!isShiftPressed)
		for (auto& figure : m_figures)
			figure->SetSelected(false);

	for (auto& figure : m_figures)
	{
		bool isContained = figure->IsContainsPoint(mouseX, mouseY);

		if (isContained)
		{
			m_draggedFigure = figure;
			figure->SetSelected(true);
			m_dragOffset.x = mouseX - figure->GetPosition().x;
			m_dragOffset.y = mouseY - figure->GetPosition().y;
			break;
		}
	}
}

void CController::GroupSelectedFigures()
{
	std::vector<std::shared_ptr<IFigure>> selectedFigures;

	for (auto it = m_figures.begin(); it != m_figures.end();)
	{
		if ((*it)->IsSelected())
		{
			selectedFigures.push_back(*it);
			it = m_figures.erase(it);
		}
		else
		{
			++it;
		}
	}

	if (!selectedFigures.empty())
	{
		std::shared_ptr<CCompositeFigure> group = std::make_shared<CCompositeFigure>();
		for (const auto& figure : selectedFigures)
		{
			group->AddFigure(figure);
		}
		m_figures.push_back(group);
	}
}

void CController::UngroupSelectedFigures()
{
    std::vector<std::shared_ptr<IFigure>> selectedFigures;

    for (const auto& figure : m_figures)
    {
        if (figure->IsSelected())
        {
            selectedFigures.push_back(figure);
        }
    }

    std::vector<std::shared_ptr<CCompositeFigure>> groupsToRemove;
    for (const auto& figure : selectedFigures)
    {
        if (auto group = std::dynamic_pointer_cast<CCompositeFigure>(figure))
        {
            groupsToRemove.push_back(group);
        }
    }

    for (const auto& group : groupsToRemove)
    {
        for (const auto& subFigure : group->GetFigures())
        {
            m_figures.push_back(subFigure);
        }
        m_figures.erase(std::remove(m_figures.begin(), m_figures.end(), group), m_figures.end());
    }
}

void CController::RenderFigures()
{
	m_window.clear();

	for (const auto& figure : m_figures)
	{
		figure->Render(m_window);
	}

	m_window.display();
}

void CController::LoadFiguresFromFile(const std::string& filename)
{
	std::ifstream inputFile(filename);
	if (!inputFile.is_open())
	{
		std::cerr << FILE_OPEN_ERROR_MESSAGE << filename << std::endl;
		return;
	}

	std::string line;
	while (std::getline(inputFile, line))
	{
		ParseLine(line);
	}
}

void CController::SaveFiguresToFile(const std::string& fileName)
{
	std::ofstream output(fileName);
	if (!output)
	{
		std::cerr << FILE_OPEN_ERROR_MESSAGE << fileName << std::endl;
		return;
	}
	for (const auto& figure : m_figures)
	{
		output << figure->ToString() << std::endl;
	}
}

void CController::ParseLine(const std::string& line)
{
	std::istringstream iss(line);
	std::string figureType;
	iss >> figureType;

	if (figureType == FIGURE_TRIANGLE_LABEL)
	{
		ParseTriangle(iss);
	}
	if (figureType == FIGURE_RECTANGLE_LABEL)
	{
		ParseRectangle(iss);
	}
	if (figureType == FIGURE_CIRCLE_LABEL)
	{
		ParseCircle(iss);
	}
}

Point CController::ParsePointFromString(std::string& pointString)
{
	Point point;

	size_t equalSignPos = pointString.find(EQUAL_SIGN);
	size_t commaPos = pointString.find(POINT_DELIMITER);

	if (equalSignPos != std::string::npos && commaPos != std::string::npos)
	{
		point.x = std::stof(pointString.substr(equalSignPos + 1, commaPos - equalSignPos - 1));
		point.y = std::stof(pointString.substr(commaPos + 1));
	}
	else
	{
		std::cerr << INVALID_POINT_FORMAT_ERROR_MESSAGE << pointString << std::endl;
		point.x = point.y = DEFAULT_POINT_VALUE;
	}

	return point;
}

void CController::ParseTriangle(std::istringstream& iss)
{
	Point point1, point2, point3;
	std::string pointString1, pointString2, pointString3;
	iss >> pointString1 >> pointString2 >> pointString3;

	point1 = ParsePointFromString(pointString1);
	point2 = ParsePointFromString(pointString2);
	point3 = ParsePointFromString(pointString3);

	m_figures.push_back(std::make_shared<CTriangle>(point1.x, point1.y, point2.x, point2.y, point3.x, point3.y));
}

void CController::ParseRectangle(std::istringstream& iss)
{
	Point point1, point2;
	std::string pointString1, pointString2;
	iss >> pointString1 >> pointString2;

	point1 = ParsePointFromString(pointString1);
	point2 = ParsePointFromString(pointString2);

	m_figures.push_back(std::make_shared<CRectangle>(point1.x, point1.y, point2.x, point2.y));
}

void CController::ParseCircle(std::istringstream& iss)
{
	Point centerPoint;
	float radius;
	std::string centerPointString, radiusString;
	iss >> centerPointString >> radiusString;

	size_t radiusPosition = radiusString.find(EQUAL_SIGN);
	if (radiusPosition != std::string::npos)
		radius = std::stof(radiusString.substr(radiusPosition + 1));

	centerPoint = ParsePointFromString(centerPointString);

	m_figures.push_back(std::make_shared<CCircle>(centerPoint.x, centerPoint.y, radius));
}