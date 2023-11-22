#pragma once

#include "CToolPanel.h"
#include "IFigure.h"
#include "CSimpleFigure.h"
#include "CCompositeFigure.h"
#include "CCircle.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include "CAddCircleCommand.h"
#include "CAddRectangleCommand.h"
#include "CAddTriangleCommand.h"
#include "CChangeFigureColorCommand.h"
#include "CChangeOutlineColorCommand.h"
#include "CChangeOutlineThicknessCommand.h"
#include "IState.h"

class IState;

const float DEFAULT_POINT_VALUE = 0.0f;

const float TRIANGLE_X1 = 100;
const float TRIANGLE_Y1 = 100;
const float TRIANGLE_X2 = 200;
const float TRIANGLE_Y2 = 200;
const float TRIANGLE_X3 = 300;
const float TRIANGLE_Y3 = 100;

const float RECTANGLE_X1 = 200;
const float RECTANGLE_Y1 = 200;
const float RECTANGLE_X2 = 300;
const float RECTANGLE_Y2 = 300;

const float CIRCLE_CENTER_X = 100;
const float CIRCLE_CENTER_Y = 100;
const float CIRCLE_RADIUS = 50;

const float THICKNESS_SMALL = 4.0f;
const float THICKNESS_BIG = 8.0f;

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

const int FIGURE_COLOR_EDIT_MODE = 1;
const int OUTLINE_COLOR_EDIT_MODE = 2;
const int OUTLINE_THICKNESS_EDIT_MODE = 3;

const char POINT_DELIMITER = ',';
const char EQUAL_SIGN = '=';

class CController
{
public:
	CController();
	void Run();

	void LoadFiguresFromFile(const std::string& filename);
	void SaveFiguresToFile(const std::string& fileName);
	void HandleEvents();
	void RenderFigures();

	CToolPanel GetToolPanel();
	void SetState(IState* state);
	void SetCurrentColor(float mouseX, float mouseY);
	void SetCurrentThickness(float mouseX, float mouseY);
	void SetCurrentEditMode(float mouseX, float mouseY);
	void HandleEditFigure(float mouseX, float mouseY);
	void HandleMoveFigure(float mouseX, float mouseY);

private:
	sf::RenderWindow m_window;
	std::vector<std::shared_ptr<IFigure>> m_figures;
	std::shared_ptr<IFigure> m_draggedFigure;
	Point m_dragOffset;
	CToolPanel m_toolPanel;

	sf::Color m_currentColor;
	float m_currentThickness;
	IState* m_currentState;
	int m_currentEditMode;

private:
	void ParseLine(const std::string& line);
	void ParseTriangle(std::istringstream& iss);
	void ParseRectangle(std::istringstream& iss);
	void ParseCircle(std::istringstream& iss);
	Point ParsePointFromString(std::string& pointString);

	void HandleMouseClick(float mouseX, float mouseY);
	void HandleMouseDrag(float mouseX, float mouseY);
	void HandleButtonClick(float mouseX, float mouseY);
	void HandleMouseRelease();
	void HandleKeyPressed();

	void GroupSelectedFigures();
	void UngroupSelectedFigures();

	void AddFigure(std::shared_ptr<IFigure> figure);
};