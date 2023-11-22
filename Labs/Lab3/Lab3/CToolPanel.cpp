#include "CToolPanel.h"

void CToolPanel::CreateButtonEditMode(sf::RectangleShape& button, sf::Text& buttonText, sf::Vector2f buttonSize, sf::Color buttonColor, std::string text, sf::Vector2f buttonPosition, sf::Vector2f textPosition)
{
	button.setSize(buttonSize);
	button.setFillColor(buttonColor);
	button.setPosition(buttonPosition);

	buttonText.setFont(m_font);
	buttonText.setString(text);
	buttonText.setCharacterSize(16);
	buttonText.setFillColor(sf::Color::Black);
	buttonText.setPosition(textPosition);
}

void CToolPanel::CreateButtonSetThickness(sf::RectangleShape& button, const sf::Color& buttonColor, sf::Vector2f buttonPosition, float outlineThickness)
{
	button.setFillColor(buttonColor);
	button.setSize(sf::Vector2f(50, 0));
	button.setPosition(buttonPosition);
	button.setOutlineThickness(outlineThickness);
}

void CToolPanel::CreateButtonSetColor(sf::RectangleShape& button, const sf::Color& buttonColor, sf::Vector2f buttonPosition)
{
	button.setFillColor(buttonColor);
	button.setSize(sf::Vector2f(50, 50));
	button.setPosition(buttonPosition);
}

CToolPanel::CToolPanel()
{
	if (!m_font.loadFromFile("C:\\GitHub\\OOD\\Labs\\Lab3\\Lab3\\arial.ttf"))
	{
		std::cout << "Font dont load!" << std::endl;
	}

	m_triangleCreateButton.setPointCount(3);
	m_triangleCreateButton.setFillColor(sf::Color::Blue);
	SetTriangleCreateButtonPosition(10, 10);

	m_rectangleCreateButton.setSize(sf::Vector2f(20, 20));
	m_rectangleCreateButton.setFillColor(sf::Color::Green);
	m_rectangleCreateButton.setPosition(10, 50);

	m_circleCreateButton.setRadius(10);
	m_circleCreateButton.setFillColor(sf::Color::Red);
	m_circleCreateButton.setPosition(10, 90);

	CreateButtonEditMode(m_switchModeButton, m_switchModeButtonText,
				sf::Vector2f(150, 30), sf::Color::Yellow, "Switch State", 
				sf::Vector2f(10, 130), sf::Vector2f(17, 135));

	CreateButtonEditMode(m_changeFigureColor, m_changeFigureColorText,
				sf::Vector2f(150, 30), sf::Color::Green, "Figure Color", 
				sf::Vector2f(10, 180), sf::Vector2f(17, 185));

	CreateButtonEditMode(m_changeOutlineColor, m_changeOutlineColorText,
				sf::Vector2f(150, 30), sf::Color::Green, "Outline Color", 
				sf::Vector2f(10, 230), sf::Vector2f(17, 235));

	CreateButtonEditMode(m_changeOutlineThickness, m_changeOutlineThicknessText,
				sf::Vector2f(150, 30), sf::Color::Green, "Outline Thickness", 
				sf::Vector2f(10, 280), sf::Vector2f(17, 285));

	CreateButtonSetThickness(m_changeOutlineThickness4, sf::Color::White, sf::Vector2f(16, 575), 2.0f);
	CreateButtonSetThickness(m_changeOutlineThickness8, sf::Color::White, sf::Vector2f(80, 575), 4.0f);

	CreateButtonSetColor(m_backgroundChangeOutlineThickness4, sf::Color(68, 68, 68), sf::Vector2f(16, 550));
	CreateButtonSetColor(m_backgroundChangeOutlineThickness8, sf::Color(68, 68, 68), sf::Vector2f(80, 550));

	CreateButtonSetColor(m_changeColorRed, sf::Color::Red, sf::Vector2f(150, 550));
	CreateButtonSetColor(m_changeColorGreen, sf::Color::Green, sf::Vector2f(220, 550));
	CreateButtonSetColor(m_changeColorBlue, sf::Color::Blue, sf::Vector2f(290, 550));

}

void CToolPanel::SetTriangleCreateButtonPosition(float x, float y)
{
	m_triangleCreateButton.setPoint(0, sf::Vector2f(x, y));
	m_triangleCreateButton.setPoint(1, sf::Vector2f(x + 20, y));
	m_triangleCreateButton.setPoint(2, sf::Vector2f(x + 10, y + 20));
}

bool CToolPanel::IsTriangleCreateButtonPressed(float mouseX, float mouseY)
{
	return m_triangleCreateButton.getGlobalBounds().contains(mouseX, mouseY);
}

bool CToolPanel::IsRectangleCreateButtonPressed(float mouseX, float mouseY)
{
	return m_rectangleCreateButton.getGlobalBounds().contains(mouseX, mouseY);
}

bool CToolPanel::IsCircleCreateButtonPressed(float mouseX, float mouseY)
{
	return m_circleCreateButton.getGlobalBounds().contains(mouseX, mouseY);
}

bool CToolPanel::IsSwitchModeButton(float mouseX, float mouseY)
{
	return m_switchModeButton.getGlobalBounds().contains(mouseX, mouseY);
}

bool CToolPanel::IsChangeFigureColor(float mouseX, float mouseY)
{
	return m_changeFigureColor.getGlobalBounds().contains(mouseX, mouseY);
}

bool CToolPanel::IsChangeOutlineColor(float mouseX, float mouseY)
{
	return m_changeOutlineColor.getGlobalBounds().contains(mouseX, mouseY);
}

bool CToolPanel::IsChangeOutlineThickness(float mouseX, float mouseY)
{
	return m_changeOutlineThickness.getGlobalBounds().contains(mouseX, mouseY);
}

bool CToolPanel::IsChangeOutlineThickness4(float mouseX, float mouseY)
{
	return m_changeOutlineThickness4.getGlobalBounds().contains(mouseX, mouseY) ||
		   m_backgroundChangeOutlineThickness4.getGlobalBounds().contains(mouseX, mouseY);
}

bool CToolPanel::IsChangeOutlineThickness8(float mouseX, float mouseY)
{
	return m_changeOutlineThickness8.getGlobalBounds().contains(mouseX, mouseY) ||
		   m_backgroundChangeOutlineThickness8.getGlobalBounds().contains(mouseX, mouseY);;
}

bool CToolPanel::IsChangeColorGreen(float mouseX, float mouseY)
{
	return m_changeColorGreen.getGlobalBounds().contains(mouseX, mouseY);
}

bool CToolPanel::IsChangeColorRed(float mouseX, float mouseY)
{
	return m_changeColorRed.getGlobalBounds().contains(mouseX, mouseY);
}

bool CToolPanel::IsChangeColorBlue(float mouseX, float mouseY)
{
	return m_changeColorBlue.getGlobalBounds().contains(mouseX, mouseY);
}


void CToolPanel::Render(sf::RenderWindow& window)
{
	window.draw(m_backgroundChangeOutlineThickness4);

	window.draw(m_backgroundChangeOutlineThickness8);

	window.draw(m_triangleCreateButton);

	window.draw(m_rectangleCreateButton);

	window.draw(m_circleCreateButton);

	window.draw(m_switchModeButton);

	window.draw(m_switchModeButtonText);

	window.draw(m_changeFigureColor);

	window.draw(m_changeFigureColorText);

	window.draw(m_changeOutlineColor);

	window.draw(m_changeOutlineColorText);

	window.draw(m_changeOutlineThickness);

	window.draw(m_changeOutlineThicknessText);

	window.draw(m_changeOutlineThickness4);

	window.draw(m_changeOutlineThickness8);

	window.draw(m_changeColorBlue);

	window.draw(m_changeColorGreen);

	window.draw(m_changeColorRed);
}