#include "CDragAndDropState.h"

void CDragAndDropState::HandleButtonClick(CController * controller, float mouseX, float mouseY)
{
	if (controller->GetToolPanel().IsSwitchModeButton(mouseX, mouseY))
	{
		controller->SetState(new CFillState());
		std::cout << "Set State -> FillState" << std::endl;
	}
}

void CDragAndDropState::HandleMouseClick(CController * controller, float mouseX, float mouseY)
{
	controller->HandleMoveFigure(mouseX, mouseY);
}