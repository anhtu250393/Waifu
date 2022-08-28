#include "MSelectLevelScene.h"
#include "Data.h"
#include "Scene\Menu\MMainScene.h"
#include "Scene\Menu\InGameScene.h"

Scene* MSelectLevelScene::createScene()
{
	return MSelectLevelScene::create();
}

bool MSelectLevelScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	//create scene's UI
	m_UILayer = Node::create();
	setupGUI();
	
	return true;
}

void MSelectLevelScene::gotoMainMenu()
{
	Scene* scene = MMainScene::createScene();
	if (scene != nullptr)
		Director::getInstance()->replaceScene(scene);
}

void MSelectLevelScene::setupGUI()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Label* label = Label::createWithTTF("Level select", "fonts/Marker Felt.ttf", 80);
	label->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - label->getContentSize().height));
	addChild(label, 1);

	//load tile map
	tileMap = TMXTiledMap::create("tilemap/level.tmx");
	tileMap->setScaleX(visibleSize.width / tileMap->getContentSize().width);
	tileMap->setScaleY(visibleSize.height / tileMap->getContentSize().height);
	addChild(tileMap, 0);
	auto groupLevel = tileMap->getObjectGroup("level");

	//add exit btn
	auto Exit = tileMap->getObjectGroup("ExitBtn")->objectNamed("Btn");
	auto posX = Exit.at("x").asFloat() * (visibleSize.width / tileMap->getContentSize().width);
	auto posY = Exit.at("y").asFloat() * (visibleSize.height / tileMap->getContentSize().height);

	//button exit
	auto btnExit = ui::Button::create("", "");
	btnExit->setPosition(Vec2(posX, posY));
	btnExit->setTitleText("Return");
	btnExit->setTitleFontName("fonts/Marker Felt.ttf");
	btnExit->setTitleFontSize(60);
	btnExit->setAnchorPoint(Vec2(0, 0));
	btnExit->addClickEventListener([&](Ref* event) {
		gotoMainMenu();
	});

	m_UILayer->addChild(btnExit);


	int numLevel = LocalData::getInstance()->getData("Id_Map");
	if (numLevel > NUMLEVEL)
	{
		numLevel = NUMLEVEL;
	}

	for (int i = 1; i <= numLevel; ++i)
	{
		string levelName = "level_" + to_string(i);
		auto level = groupLevel->objectNamed(levelName);
		float x = level.at("x").asFloat();
		float y = level.at("y").asFloat();
		float width = level.at("width").asFloat();
		float height = level.at("height").asFloat();
		//create button for level select
		Button *btnSelectLevel;
		if (i == numLevel)
		{
			btnSelectLevel = Button::create("Image/head_selector.png", "Image/head_selector.png");
		}
		else if (i < numLevel)
		{
			btnSelectLevel = Button::create("Image/btnNoneImage.png", "Image/btnNoneImage.png");
		}

		btnSelectLevel->setScaleX(width * 1.5 / btnSelectLevel->getContentSize().width);
		btnSelectLevel->setScaleY(height * 1.5 / btnSelectLevel->getContentSize().height);
		btnSelectLevel->setPosition(Vec2(x, y));
		btnSelectLevel->setAnchorPoint(Vec2(0.2, 0));

		arrMapNumber[i - 1] = i;
		btnSelectLevel->addClickEventListener([=](Ref* event) 
		{
			MapManager::getInstance()->SetMap(arrMapNumber[i - 1]);
			Scene* scene = InGameScene::createScene();
			if (scene != nullptr) {
				Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(0, 255, 255)));
			}
		});

		//add buttons
		m_UILayer->addChild(btnSelectLevel);
	}
	addChild(m_UILayer, 1);
}