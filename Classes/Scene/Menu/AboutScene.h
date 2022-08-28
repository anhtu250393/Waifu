#pragma once
#include "Config.h"

class AboutScene : public Scene
{
public:
	static Scene* createScene();

	bool init();

private:
	void setupGUI();
	void GoToMainMenu();

	CREATE_FUNC(AboutScene);
};

