#pragma once
#include "ICommand.h"
#include "IFigure.h"
#include "CRectangle.h"

class CAddRectangleCommand : public ICommand
{
public:
	CAddRectangleCommand(float x1, float y1, float x2, float y2);
	virtual void Execute() override;
	std::shared_ptr<CRectangle> GetRectangle() const;
private:
	float m_x1, m_y1, m_x2, m_y2;
	std::shared_ptr<CRectangle> m_rectangle;
};
