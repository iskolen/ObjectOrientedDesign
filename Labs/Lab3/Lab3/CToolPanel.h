#pragma once
#include "stdafx.h"

class CToolPanel
{
public:
	CToolPanel();

	void SetTriangleCreateButtonPosition(float x, float y);
	bool IsTriangleCreateButtonPressed(float mouseX, float mouseY);
	bool IsRectangleCreateButtonPressed(float mouseX, float mouseY);
	bool IsCircleCreateButtonPressed(float mouseX, float mouseY);
	bool IsSwitchModeButton(float mouseX, float mouseY);
	bool IsChangeFigureColor(float mouseX, float mouseY);
	bool IsChangeOutlineColor(float mouseX, float mouseY);
	bool IsChangeOutlineThickness(float mouseX, float mouseY);
	bool IsChangeOutlineThickness4(float mouseX, float mouseY);
	bool IsChangeOutlineThickness8(float mouseX, float mouseY);
	bool IsChangeColorGreen(float mouseX, float mouseY);
	bool IsChangeColorRed(float mouseX, float mouseY);
	bool IsChangeColorBlue(float mouseX, float mouseY);

	void Render(sf::RenderWindow& window);

private:
	sf::Font m_font;
	sf::ConvexShape m_triangleCreateButton;
	sf::RectangleShape m_rectangleCreateButton;
	sf::CircleShape m_circleCreateButton;

	sf::RectangleShape m_switchModeButton;
	sf::Text m_switchModeButtonText;

	sf::RectangleShape m_changeFigureColor;
	sf::Text m_changeFigureColorText;

	sf::RectangleShape m_changeOutlineColor;
	sf::Text m_changeOutlineColorText;

	sf::RectangleShape m_changeOutlineThickness;
	sf::Text m_changeOutlineThicknessText;

	sf::RectangleShape m_changeOutlineThickness4;
	sf::RectangleShape m_changeOutlineThickness8;

	sf::RectangleShape m_changeColorGreen;
	sf::RectangleShape m_changeColorRed;
	sf::RectangleShape m_changeColorBlue;

	sf::RectangleShape m_backgroundChangeOutlineThickness4;
	sf::RectangleShape m_backgroundChangeOutlineThickness8;

	void CreateButtonEditMode(sf::RectangleShape& button, sf::Text& buttonText, sf::Vector2f buttonSize, sf::Color buttonColor, std::string text, sf::Vector2f buttonPosition, sf::Vector2f textPosition);
	void CreateButtonSetThickness(sf::RectangleShape& button, const sf::Color& buttonColor, sf::Vector2f buttonPosition, float outlineThickness);
	void CreateButtonSetColor(sf::RectangleShape& button, const sf::Color& buttonColor, sf::Vector2f buttonPosition);
};