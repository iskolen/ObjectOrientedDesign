#pragma once
#include "ICommand.h"
#include "IFigure.h"

class CChangeOutlineThicknessCommand : public ICommand
{
public:
	CChangeOutlineThicknessCommand(std::shared_ptr<IFigure> figure, float newThickness);
	virtual void Execute() override;

private:
	std::shared_ptr<IFigure> m_figure;
	float m_newThickness;
};

