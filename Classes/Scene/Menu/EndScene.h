#pragma once
#include "Config.h"

class EndScene : public Scene
{
public:
	static Scene* createScene();

	bool init();

private:
	void setupGUI();
	void GoToMainMenu();

	CREATE_FUNC(EndScene);
};

