#include "CApplication.h"

CApplication& CApplication::GetInstance()
{
	static CApplication instance;
	return instance;
}

void CApplication::Run()
{
	m_controller.Run();
}

void CApplication::LoadAndSaveFigures()
{
	m_controller.LoadFiguresFromFile(INPUT_FILE_NAME);
	m_controller.SaveFiguresToFile(OUTPUT_FILE_NAME);
}

void CApplication::HandleInput()
{
	m_controller.HandleEvents();
}

void CApplication::Render()
{
	m_controller.RenderFigures();
}