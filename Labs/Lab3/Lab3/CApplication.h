#pragma once
#include "CController.h"

class CApplication
{
public:
	static CApplication& GetInstance();

	void Run();
	void LoadAndSaveFigures();
	void HandleInput();
	void Render();

private:
	CController m_controller;
};