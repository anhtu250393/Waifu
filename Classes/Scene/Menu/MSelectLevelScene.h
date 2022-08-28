#pragma once

#include "Config.h"

class MSelectLevelScene : public Scene
{
public:
	static Scene* createScene();

	bool init();
	void setupGUI();

	CREATE_FUNC(MSelectLevelScene);
private:

	void gotoMainMenu();
	Node* m_UILayer;
	TMXTiledMap* tileMap;

	int arrMapNumber[20];
};

