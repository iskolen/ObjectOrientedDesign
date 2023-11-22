#include "CChangeFigureColorCommand.h"

CChangeFigureColorCommand::CChangeFigureColorCommand(std::shared_ptr<IFigure> figure, sf::Color fill)
	: m_figure(figure), m_fill(fill)
{
}

void CChangeFigureColorCommand::Execute()
{
	if (m_figure)
	{
		m_figure->SetFigureColor(m_fill);
	}
}