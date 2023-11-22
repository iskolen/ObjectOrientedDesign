#include "CAddRectangleCommand.h"

CAddRectangleCommand::CAddRectangleCommand(float x1, float y1, float x2, float y2)
	: m_x1(x1), m_y1(y1), m_x2(x2), m_y2(y2) 
{
}

void CAddRectangleCommand::Execute() 
{
	m_rectangle = std::make_shared<CRectangle>(m_x1, m_y1, m_x2, m_y2);
}

std::shared_ptr<CRectangle> CAddRectangleCommand::GetRectangle() const
{
	return m_rectangle;
}