#include "EndScene.h"
#include "Scene\Menu\MMainScene.h"
#include "Scene\Level\MapManager.h"

Scene* EndScene::createScene()
{
	return EndScene::create();
}

bool EndScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	setupGUI();

	return true;
}

void EndScene::setupGUI()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

#if defined(PREMIUM)
	Sprite* sprite = Sprite::create("Image/endgame.png");
#else
	Sprite* sprite = Sprite::create("Image/endgame_lite.png");
#endif

	sprite->setScaleX(SCREEN_WIDTH / sprite->getContentSize().width);
	sprite->setScaleY(SCREEN_HEIGHT / sprite->getContentSize().height);
	sprite->setAnchorPoint(Vec2(0, 0));
	addChild(sprite, 0);

	Button *btnExit = Button::create();
	btnExit->setTitleFontName("fonts/Marker Felt.ttf");
	btnExit->setTitleFontSize(70);
	btnExit->setTitleText("Main menu");
	btnExit->setPosition(Vec2(visibleSize.width - origin.x - btnExit->getContentSize().width, visibleSize.height - origin.y - btnExit->getContentSize().height));
	btnExit->addClickEventListener([=](Ref* event) {
		GoToMainMenu();
	});
	addChild(btnExit, 1);
}

void EndScene::GoToMainMenu()
{
	MapManager::getInstance()->DeleteObjects();
	Scene* scene = MMainScene::createScene();
	if (scene != nullptr)
	{
		Director::getInstance()->replaceScene(scene);
	}
}