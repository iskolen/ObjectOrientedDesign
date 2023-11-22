#include "CAddTriangleCommand.h"

CAddTriangleCommand::CAddTriangleCommand(float x1, float y1, float x2, float y2, float x3, float y3)
    : m_x1(x1), m_y1(y1), m_x2(x2), m_y2(y2), m_x3(x3), m_y3(y3) 
{
}

void CAddTriangleCommand::Execute() 
{
	m_triangle = std::make_shared<CTriangle>(m_x1, m_y1, m_x2, m_y2, m_x3, m_y3);
}

std::shared_ptr<CTriangle> CAddTriangleCommand::GetTriangle() const
{
	return m_triangle;
}