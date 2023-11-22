#pragma once
#include "ICommand.h"
#include "IFigure.h"

class CChangeOutlineColorCommand : public ICommand
{
public:
	CChangeOutlineColorCommand(std::shared_ptr<IFigure> figure, sf::Color fill);
	virtual void Execute() override;

private:
	std::shared_ptr<IFigure> m_figure;
	sf::Color m_fill;
};

