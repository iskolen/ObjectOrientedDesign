#include "CCompositeFigure.h"

std::string CCompositeFigure::ToString() const
{
	return "CompositeFigure";
}

void CCompositeFigure::Render(sf::RenderWindow& window)
{
	for (const auto& figure : m_figures)
	{
		figure->Render(window);
	}
}

sf::FloatRect CCompositeFigure::GetBounds() const
{
	sf::FloatRect bounds;
	return bounds;
}

bool CCompositeFigure::IsContainsPoint(float x, float y) const
{
	for (const auto& figure : m_figures)
	{
		if (figure->IsContainsPoint(x, y))
		{
			return true;
		}
	}
	return false;
}

bool CCompositeFigure::IsSelected() const
{
	return m_selected;
}

void CCompositeFigure::SetSelected(bool selected)
{
	m_selected = selected;
	for (const auto& figure : m_figures)
	{
		figure->SetSelected(selected);
	}
}

void CCompositeFigure::AddFigure(std::shared_ptr<IFigure> figure)
{
	m_figures.push_back(figure);
}

void CCompositeFigure::RemoveFigure(std::shared_ptr<IFigure> figure)
{
	m_figures.erase(std::remove(m_figures.begin(), m_figures.end(), figure), m_figures.end());
}

std::vector<std::shared_ptr<IFigure>> CCompositeFigure::GetFigures() const
{
	return m_figures;
}

void CCompositeFigure::MoveTo(float x, float y)
{
	sf::Vector2f currentPosition = GetPosition();
	sf::Vector2f offset = sf::Vector2f(x, y) - currentPosition;

	for (auto& figure : m_figures)
	{
		figure->MoveTo(figure->GetPosition().x + offset.x, figure->GetPosition().y + offset.y);
	}
}

sf::Vector2f CCompositeFigure::GetPosition() const
{
	if (!m_figures.empty())
	{
		return m_figures[0]->GetPosition();
	}
	return sf::Vector2f(0, 0);
}

void CCompositeFigure::SetFigureColor(const sf::Color& fill)
{
	for (auto& figure : m_figures)
	{
		figure->SetFigureColor(fill);
	}
}

void CCompositeFigure::SetOutlineThickness(float thickness)
{
	for (auto& figure : m_figures)
	{
		figure->SetOutlineThickness(thickness);
	}
}

void CCompositeFigure::SetOutlineColor(const sf::Color& fill)
{
	for (auto& figure : m_figures)
	{
		figure->SetOutlineColor(fill);
	}
}