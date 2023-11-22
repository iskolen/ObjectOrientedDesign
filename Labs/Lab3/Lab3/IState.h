#pragma once
#include "CController.h"

class CController;

class IState
{
public:
	virtual void HandleButtonClick(CController* controller, float mouseX, float mouseY) = 0;
	virtual void HandleMouseClick(CController* controller, float mouseX, float mouseY) = 0;
};