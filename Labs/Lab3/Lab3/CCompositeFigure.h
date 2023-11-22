#pragma once
#include "IFigure.h"

class CCompositeFigure : public IFigure
{
public:
	std::string ToString() const override;

	bool IsContainsPoint(float x, float y) const override;
	bool IsSelected() const override;

	void Render(sf::RenderWindow& window) override;
	void SetSelected(bool selected) override;
	void MoveTo(float x, float y) override;

	sf::FloatRect GetBounds() const override;
	sf::Vector2f GetPosition() const override;

	void AddFigure(std::shared_ptr<IFigure> figure);
	void RemoveFigure(std::shared_ptr<IFigure> figure);
	std::vector<std::shared_ptr<IFigure>> GetFigures() const;

	void SetFigureColor(const sf::Color& fill) override;
	void SetOutlineThickness(float thickness)  override;
	void SetOutlineColor(const sf::Color& fill) override;

private:
	std::vector<std::shared_ptr<IFigure>> m_figures;
	bool m_selected;
};