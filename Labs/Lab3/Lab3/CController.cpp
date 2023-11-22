#include "CController.h"
#include "CDragAndDropState.h"

CController::CController() : m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE), 
							 m_draggedFigure(nullptr),
							 m_currentState(new CDragAndDropState()),
							 m_currentColor(sf::Color::Green),
							 m_currentThickness(THICKNESS_SMALL),
							 m_currentEditMode(FIGURE_COLOR_EDIT_MODE)
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

void CController::AddFigure(std::shared_ptr<IFigure> figure)
{
	if (figure)
		m_figures.push_back(figure);
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
			{
				HandleMouseClick(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
				HandleButtonClick(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
			}
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

void CController::HandleMoveFigure(float mouseX, float mouseY)
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

void CController::HandleEditFigure(float mouseX, float mouseY)
{
	for (auto& figure : m_figures)
		figure->SetSelected(false);

	for (auto& figure : m_figures)
	{
		bool isContained = figure->IsContainsPoint(mouseX, mouseY);

		if (isContained)
		{
			if (m_currentEditMode == FIGURE_COLOR_EDIT_MODE)
			{
				CChangeFigureColorCommand changeFigureColorCommand(figure, m_currentColor);
				changeFigureColorCommand.Execute();
			}

			if (m_currentEditMode == OUTLINE_COLOR_EDIT_MODE)
			{
				CChangeOutlineColorCommand changeOutlineColorCommand(figure, m_currentColor);
				changeOutlineColorCommand.Execute();
			}

			if (m_currentEditMode == OUTLINE_THICKNESS_EDIT_MODE)
			{
				CChangeOutlineThicknessCommand changeOutlineThicknessCommand(figure, m_currentThickness);
				changeOutlineThicknessCommand.Execute();
			}

			figure->SetSelected(true);
			break;
		}
	}
}

void CController::HandleMouseClick(float mouseX, float mouseY)
{
	if (m_currentState)
	{
		m_currentState->HandleMouseClick(this, mouseX, mouseY);
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

bool ArePointsCollinear(const Point& p1, const Point& p2, const Point& p3)
{
	return ((p2.y - p1.y) * (p3.x - p2.x) == (p3.y - p2.y) * (p2.x - p1.x));
}

void CController::ParseTriangle(std::istringstream& iss)
{
	Point point1, point2, point3;
	std::string pointString1, pointString2, pointString3;
	iss >> pointString1 >> pointString2 >> pointString3;

	point1 = ParsePointFromString(pointString1);
	point2 = ParsePointFromString(pointString2);
	point3 = ParsePointFromString(pointString3);

	if (ArePointsCollinear(point1, point2, point3))
	{
		throw std::invalid_argument("Три точки находятся на одной прямой. Невозможно создать треугольник.");
	}

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

void CController::HandleButtonClick(float mouseX, float mouseY)
{
	if (m_currentState)
	{
		m_currentState->HandleButtonClick(this, mouseX, mouseY);
	}

	if (m_toolPanel.IsTriangleCreateButtonPressed(mouseX, mouseY))
	{
		std::cout << "Triangle Create!" << std::endl;

		CAddTriangleCommand addTriangleCommand(TRIANGLE_X1, TRIANGLE_Y1, TRIANGLE_X2, TRIANGLE_Y2, TRIANGLE_X3, TRIANGLE_Y3);
		addTriangleCommand.Execute();
		AddFigure(addTriangleCommand.GetTriangle());
	}

	if (m_toolPanel.IsRectangleCreateButtonPressed(mouseX, mouseY))
	{
		std::cout << "Rectangle Create!" << std::endl;

		CAddRectangleCommand addRectangleCommand(RECTANGLE_X1, RECTANGLE_Y1, RECTANGLE_X2, RECTANGLE_Y2);
		addRectangleCommand.Execute();
		AddFigure(addRectangleCommand.GetRectangle());
	}

	if (m_toolPanel.IsCircleCreateButtonPressed(mouseX, mouseY))
	{
		std::cout << "Circle Create!" << std::endl;

		CAddCircleCommand addCircleCommand(CIRCLE_CENTER_X, CIRCLE_CENTER_Y, CIRCLE_RADIUS);
		addCircleCommand.Execute();
		AddFigure(addCircleCommand.GetCircle());
	}
}

void CController::SetCurrentColor(float mouseX, float mouseY)
{
	if (m_toolPanel.IsChangeColorBlue(mouseX, mouseY))
	{
		std::cout << "Select color - Blue" << std::endl;
		m_currentColor = sf::Color::Blue;
	}

	if (m_toolPanel.IsChangeColorGreen(mouseX, mouseY))
	{
		std::cout << "Select color - Green" << std::endl;
		m_currentColor = sf::Color::Green;
	}

	if (m_toolPanel.IsChangeColorRed(mouseX, mouseY))
	{
		std::cout << "Select color - Red" << std::endl;
		m_currentColor = sf::Color::Red;
	}
}

void CController::SetCurrentThickness(float mouseX, float mouseY)
{
	if (m_toolPanel.IsChangeOutlineThickness4(mouseX, mouseY))
	{
		std::cout << "Outline Thickness - 4" << std::endl;
		m_currentThickness = THICKNESS_SMALL;
	}

	if (m_toolPanel.IsChangeOutlineThickness8(mouseX, mouseY))
	{
		std::cout << "Outline Thickness - 8" << std::endl;
		m_currentThickness = THICKNESS_BIG;
	}
}

void CController::SetState(IState* state)
{
	m_currentState = state;
}

void CController::SetCurrentEditMode(float mouseX, float mouseY)
{
	if (m_toolPanel.IsChangeFigureColor(mouseX, mouseY))
	{
		m_currentEditMode = FIGURE_COLOR_EDIT_MODE; // FigureColor
		std::cout << "Edit mode -> FigureColor" << std::endl;
	}
	if (m_toolPanel.IsChangeOutlineColor(mouseX, mouseY))
	{
		m_currentEditMode = OUTLINE_COLOR_EDIT_MODE; // OutlineColor
		std::cout << "Edit mode -> OutlineColor" << std::endl;
	}
	if (m_toolPanel.IsChangeOutlineThickness(mouseX, mouseY))
	{
		m_currentEditMode = OUTLINE_THICKNESS_EDIT_MODE; // OutlineThickness
		std::cout << "Edit mode -> OutlineThickness" << std::endl;
	}
}

void CController::RenderFigures()
{
	m_window.clear();

	m_toolPanel.Render(m_window);

	for (const auto& figure : m_figures)
	{
		figure->Render(m_window);
	}

	m_window.display();
}

CToolPanel CController::GetToolPanel()
{
	return m_toolPanel;
}