#include "AboutScene.h"
#include "Scene\Menu\MMainScene.h"
#include "Scene\Level\MapManager.h"

#define ALIGNMENT 30

Scene* AboutScene::createScene()
{
	return AboutScene::create();
}

bool AboutScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	setupGUI();

	return true;
}

void AboutScene::setupGUI()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite* sprite = Sprite::create("mainmenu.png");
	sprite->setScaleX(SCREEN_WIDTH / sprite->getContentSize().width);
	sprite->setScaleY(SCREEN_HEIGHT / sprite->getContentSize().height);
	sprite->setAnchorPoint(Vec2(0, 0));
	addChild(sprite, 0);

	//Designer
	Label* designer = Label::createWithTTF("Designer", "fonts/Marker Felt.ttf", 70);
	designer->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 200));
	addChild(designer, 1);

	Label* designerName = Label::createWithTTF("Eddie Luu", "fonts/Marker Felt.ttf", 50);
	designerName->setPosition(Vec2(visibleSize.width / 2, designer->getPosition().y - designerName->getContentSize().height - ALIGNMENT));
	addChild(designerName, 1);

	//Programming
	Label* dev = Label::createWithTTF("Programming", "fonts/Marker Felt.ttf", 70);
	dev->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 500));
	addChild(dev, 1);

	Label* devName1 = Label::createWithTTF("Tu Anh", "fonts/Marker Felt.ttf", 50);
	devName1->setPosition(Vec2(visibleSize.width / 2, dev->getPosition().y - devName1->getContentSize().height - ALIGNMENT));
	addChild(devName1, 1);

	Label* devName2 = Label::createWithTTF("Dinh Darkness", "fonts/Marker Felt.ttf", 50);
	devName2->setPosition(Vec2(visibleSize.width / 2, devName1->getPosition().y - devName2->getContentSize().height - ALIGNMENT));
	addChild(devName2, 1);

	Label* devName3 = Label::createWithTTF("Binh Ton", "fonts/Marker Felt.ttf", 50);
	devName3->setPosition(Vec2(visibleSize.width / 2, devName2->getPosition().y - devName3->getContentSize().height - ALIGNMENT));
	addChild(devName3, 1);

	//Art
	Label* art = Label::createWithTTF("Art", "fonts/Marker Felt.ttf", 70);
	art->setPosition(Vec2(visibleSize.width * 3 / 4, visibleSize.height - 200));
	addChild(art, 1);

	Label* artName = Label::createWithTTF("Rin", "fonts/Marker Felt.ttf", 50);
	artName->setPosition(Vec2(visibleSize.width * 3 / 4, art->getPosition().y - artName->getContentSize().height - ALIGNMENT));
	addChild(artName, 1);

	//Art
	Label* scrum = Label::createWithTTF("Scrum", "fonts/Marker Felt.ttf", 70);
	scrum->setPosition(Vec2(visibleSize.width * 3 / 4, visibleSize.height - 500));
	addChild(scrum, 1);

	Label* scrumName = Label::createWithTTF("Man Nguyen", "fonts/Marker Felt.ttf", 50);
	scrumName->setPosition(Vec2(visibleSize.width * 3 / 4, scrum->getPosition().y - scrumName->getContentSize().height - ALIGNMENT));
	addChild(scrumName, 1);

	Label* cocos = Label::createWithTTF("This game runs on Cocos2d-x Engine.", "fonts/Marker Felt.ttf", 70);
	cocos->setPosition(Vec2(visibleSize.width * 2 / 3, visibleSize.height - 900));
	addChild(cocos, 1);

	Button *btnExit = Button::create();
	btnExit->setTitleFontName("fonts/Marker Felt.ttf");
	btnExit->setTitleFontSize(70);
	btnExit->setTitleText("Return");
	btnExit->setPosition(Vec2(visibleSize.width - origin.x - btnExit->getContentSize().width, visibleSize.height - origin.y - btnExit->getContentSize().height));
	btnExit->addClickEventListener([=](Ref* event) {
		GoToMainMenu();
	});
	addChild(btnExit, 1);
}

void AboutScene::GoToMainMenu()
{
	MapManager::getInstance()->DeleteObjects();
	Scene* scene = MMainScene::createScene();
	if (scene != nullptr)
	{
		Director::getInstance()->replaceScene(scene);
	}
}