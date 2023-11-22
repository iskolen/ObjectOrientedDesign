#pragma once
#include "IState.h"
#include "CFillState.h"

class CDragAndDropState : public IState
{
public:
	void HandleButtonClick(CController* controller, float mouseX, float mouseY) override;
	void HandleMouseClick(CController* controller, float mouseX, float mouseY) override;
};