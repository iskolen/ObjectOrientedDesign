#include "CAddCircleCommand.h"

CAddCircleCommand::CAddCircleCommand(float centerX, float centerY, float radius)
	: m_centerX(centerX), m_centerY(centerY), m_radius(radius) 
{
}

void CAddCircleCommand::Execute() 
{
	m_circle = std::make_shared<CCircle>(m_centerX, m_centerY, m_radius);
}

std::shared_ptr<CCircle> CAddCircleCommand::GetCircle() const
{
	return m_circle;
}