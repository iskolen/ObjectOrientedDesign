#include "CChangeOutlineColorCommand.h"

CChangeOutlineColorCommand::CChangeOutlineColorCommand(std::shared_ptr<IFigure> figure, sf::Color fill)
	: m_figure(figure), m_fill(fill)
{
}

void CChangeOutlineColorCommand::Execute()
{
	if (m_figure)
	{
		m_figure->SetOutlineColor(m_fill);
	}
}