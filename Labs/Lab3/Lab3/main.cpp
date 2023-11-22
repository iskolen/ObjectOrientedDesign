#include "CApplication.h"

int main()
{
	CApplication& app = CApplication::GetInstance();
	app.LoadAndSaveFigures();

	while (true)
	{
		app.HandleInput();
		app.Render();
	}

	return 0;
}