#pragma once
#include "ICommand.h"
#include "IFigure.h"
#include "CCircle.h"

class CAddCircleCommand : public ICommand
{
public:
	CAddCircleCommand(float centerX, float centerY, float radius);
	virtual void Execute() override;
	std::shared_ptr<CCircle> GetCircle() const;
private:
	float m_centerX, m_centerY, m_radius;
	std::shared_ptr<CCircle> m_circle;
};