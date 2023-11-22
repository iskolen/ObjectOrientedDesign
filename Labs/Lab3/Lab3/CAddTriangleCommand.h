#pragma once
#include "ICommand.h"
#include "IFigure.h"
#include "CTriangle.h"

class CAddTriangleCommand : public ICommand
{
public:
	CAddTriangleCommand(float x1, float y1, float x2, float y2, float x3, float y3);
	virtual void Execute() override;
	std::shared_ptr<CTriangle> GetTriangle() const;
private:
	float m_x1, m_y1, m_x2, m_y2, m_x3, m_y3;
	std::shared_ptr<CTriangle> m_triangle;
};

