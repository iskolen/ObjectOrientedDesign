#pragma once

#include "IFigure.h"
#include "CSimpleFigure.h"
#include "CCompositeFigure.h"
#include "CCircle.h"
#include "CRectangle.h"
#include "CTriangle.h"

const float DEFAULT_POINT_VALUE = 0.0f;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

const std::string WINDOW_TITLE = "Figures";

const std::string INPUT_FILE_NAME = "input.txt";
const std::string OUTPUT_FILE_NAME = "output.txt";
const std::string FILE_OPEN_ERROR_MESSAGE = "Ошибка при открытии файла: ";
const std::string INVALID_POINT_FORMAT_ERROR_MESSAGE = "Неверный формат точки: ";

const std::string FIGURE_TRIANGLE_LABEL = "TRIANGLE:";
const std::string FIGURE_RECTANGLE_LABEL = "RECTANGLE:";
const std::string FIGURE_CIRCLE_LABEL = "CIRCLE:";

const char POINT_DELIMITER = ',';
const char EQUAL_SIGN = '=';


class CController
{
public:
	CController();
	void Run();

private:
	sf::RenderWindow m_window;

	std::vector<std::shared_ptr<IFigure>> m_figures;
	std::shared_ptr<IFigure> m_draggedFigure;
	Point m_dragOffset;

	void LoadFiguresFromFile(const std::string& filename);
	void SaveFiguresToFile(const std::string& fileName);

	void ParseLine(const std::string& line);
	void ParseTriangle(std::istringstream& iss);
	void ParseRectangle(std::istringstream& iss);
	void ParseCircle(std::istringstream& iss);
	Point ParsePointFromString(std::string& pointString);

	void HandleEvents();
	void HandleMouseClick(float mouseX, float mouseY);
	void HandleMouseDrag(float mouseX, float mouseY);
	void HandleMouseRelease();
	void HandleKeyPressed();
	void RenderFigures();

	void GroupSelectedFigures();
	void UngroupSelectedFigures();
};

