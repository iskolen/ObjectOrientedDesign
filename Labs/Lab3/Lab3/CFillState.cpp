#include "CFillState.h"

void CFillState::HandleButtonClick(CController * controller, float mouseX, float mouseY)
{
	controller->SetCurrentColor(mouseX, mouseY);
	controller->SetCurrentThickness(mouseX, mouseY);
	controller->SetCurrentEditMode(mouseX, mouseY);

	if (controller->GetToolPanel().IsSwitchModeButton(mouseX, mouseY))
	{
		controller->SetState(new CDragAndDropState());
		std::cout << "Set State -> DragAndDropState" << std::endl;
	}
}

void CFillState::HandleMouseClick(CController * controller, float mouseX, float mouseY)
{
	controller->HandleEditFigure(mouseX, mouseY);
}