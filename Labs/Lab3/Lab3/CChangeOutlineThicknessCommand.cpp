#include "CChangeOutlineThicknessCommand.h"

CChangeOutlineThicknessCommand::CChangeOutlineThicknessCommand(std::shared_ptr<IFigure> figure, float newThickness)
	: m_figure(figure), m_newThickness(newThickness)
{
}

void CChangeOutlineThicknessCommand::Execute()
{
	if (m_figure)
	{
		m_figure->SetOutlineThickness(m_newThickness);
	}
}