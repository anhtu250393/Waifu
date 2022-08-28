#include "PausePopup.h"
#include "Scene\Menu\MMainScene.h"
#include "Scene\Menu\InGameScene.h"
#include "Scene\Level\MapManager.h"

#define ALIGNMENT 100

bool PausePopup::init()
{
	if (!Popup::init())
		return false;

	setTitlePopup("Pause");

	Button *btnReturn = Button::create();
	btnReturn->setTitleFontName("fonts/Marker Felt.ttf");
	btnReturn->setTitleFontSize(70);
	btnReturn->setTitleText("Return");
	btnReturn->setPosition(Vec2(m_backGround->getPosition().x, m_backGround->getPosition().y));
	btnReturn->addClickEventListener([=](Ref* event) {
		Popup::disappear();
	});

	Button *btnExit = Button::create();
	btnExit->setTitleFontName("fonts/Marker Felt.ttf");
	btnExit->setTitleFontSize(70);
	btnExit->setTitleText("Main menu");
	btnExit->setPosition(Vec2(m_backGround->getPosition().x, btnReturn->getPosition().y - ALIGNMENT));
	btnExit->addClickEventListener([=](Ref* event) {
		GoToMainMenu();
	});

	Button *btnReset = Button::create();
	btnReset->setTitleFontName("fonts/Marker Felt.ttf");
	btnReset->setTitleFontSize(70);
	btnReset->setTitleText("Reset game");
	btnReset->setPosition(Vec2(m_backGround->getPosition().x, btnExit->getPosition().y - ALIGNMENT));
	btnReset->addClickEventListener([=](Ref* event) {
		ResetGame();
	});

	m_popupLayer->addChild(btnReturn);
	m_popupLayer->addChild(btnExit);
	m_popupLayer->addChild(btnReset);

	return true;
}

void PausePopup::GoToMainMenu()
{
	Popup::disappear();
	MapManager::getInstance()->DeleteObjects();
	Scene* scene = MMainScene::createScene();
	if (scene != nullptr)
	{
		Director::getInstance()->replaceScene(scene);
	}
}

void PausePopup::ResetGame()
{
	Popup::disappear();
	MapManager::getInstance()->DeleteObjects();
	Scene* scene = InGameScene::createScene();
	if (scene != nullptr) {
		Director::getInstance()->replaceScene(scene);
	}
}

void PausePopup::onExit()
{
	Popup::onExit();
}