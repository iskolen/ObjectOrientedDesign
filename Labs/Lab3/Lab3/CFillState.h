#pragma once
#include "IState.h"
#include "CDragAndDropState.h"

class CFillState : public IState
{
public:
	void HandleButtonClick(CController* controller, float mouseX, float mouseY) override;
	void HandleMouseClick(CController* controller, float mouseX, float mouseY) override;
};