#include "MMainScene.h"
#include "Data.h"
#include "Scene\Menu\MSelectLevelScene.h"
#include "Scene\Menu\AboutScene.h"
#include "Scene\Menu\InGameScene.h"
#include "Scene\Popup\PausePopup.h"

#define ALIGNMENT 50

Scene* MMainScene::createScene()
{
    return MMainScene::create();
}

bool MMainScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

	setupGUI();

    return true;
}

void MMainScene::setupGUI()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//add background
	Sprite* spriteBG = Sprite::create("mainmenu.png");
	spriteBG->setScaleX(SCREEN_WIDTH / spriteBG->getContentSize().width);
	spriteBG->setScaleY(SCREEN_HEIGHT / spriteBG->getContentSize().height);
	spriteBG->setAnchorPoint(Vec2(0, 0));
	addChild(spriteBG, 0);

	//add logo Cocos
	Sprite* logo_cocos = Sprite::create("Cocos2dx.png");
	logo_cocos->setPosition(Vec2(SCREEN_WIDTH - 195, SCREEN_HEIGHT - 270));
	logo_cocos->setAnchorPoint(Vec2(0, 0));
	addChild(logo_cocos, 1);

	// create and initialize a label
#if defined(PREMIUM)
	Sprite* spriteTitle = Sprite::create("Image/title.png");
#else
	Sprite* spriteTitle = Sprite::create("Image/title_lite.png");
#endif
	spriteTitle->setAnchorPoint(Vec2(0, 0));
	spriteTitle->setPosition(Vec2(origin.x + visibleSize.width / 2 - spriteTitle->getContentSize().width / 2, origin.y + visibleSize.height - spriteTitle->getContentSize().height));
	addChild(spriteTitle, 1);

	//add btn continue 
	Button *btnContinue = Button::create();
	btnContinue->setTitleFontName("fonts/Marker Felt.ttf");
	btnContinue->setTitleFontSize(70);
	btnContinue->setTitleText("Continue");
	btnContinue->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2  + btnContinue->getContentSize().height + 200));
	btnContinue->addClickEventListener([&](Ref* event) {
		ContinueGame();
	});

	//add btn start game 
	Button *btnStart = Button::create();
	btnStart->setTitleFontName("fonts/Marker Felt.ttf");
	btnStart->setTitleFontSize(70);
	btnStart->setTitleText("Start Game");
	btnStart->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 150));
	btnStart->addClickEventListener([&](Ref* event) {
		StartGame();
	});

	//add btn select level
	Button *btnMenu = Button::create();
	btnMenu->setTitleFontName("fonts/Marker Felt.ttf");
	btnMenu->setTitleFontSize(70);
	btnMenu->setTitleText("Select level");
	btnMenu->setPosition(Vec2(visibleSize.width / 2, btnStart->getPosition().y - btnStart->getContentSize().height - ALIGNMENT));
	btnMenu->addClickEventListener([&](Ref* event) {
		SelectLevel();
	});

	//add btn exit
	Button *btnAbout = Button::create();
	btnAbout->setTitleFontName("fonts/Marker Felt.ttf");
	btnAbout->setTitleFontSize(70);
	btnAbout->setTitleText("About");
	btnAbout->setPosition(Vec2(visibleSize.width / 2, btnMenu->getPosition().y - btnMenu->getContentSize().height - ALIGNMENT));
	btnAbout->addClickEventListener([&](Ref* event)
		{
			About();
		});

	//add btn exit
	Button *btnExit = Button::create();
	btnExit->setTitleFontName("fonts/Marker Felt.ttf");
	btnExit->setTitleFontSize(70);
	btnExit->setTitleText("Exit");
	btnExit->setPosition(Vec2(visibleSize.width / 2, btnAbout->getPosition().y - btnAbout->getContentSize().height - ALIGNMENT));
	btnExit->addClickEventListener([&](Ref* event) 
	{
		Close();
	});

	//add btn item 
	int numLevel = LocalData::getInstance()->getData("Id_Map");
	if (numLevel >= 2)
	{
		addChild(btnContinue);
	}
	addChild(btnStart);
	addChild(btnMenu);
	addChild(btnAbout);
	addChild(btnExit);
}

void MMainScene::ContinueGame()
{
	int numLevel = LocalData::getInstance()->getData("Id_Map");
	if (numLevel > NUMLEVEL)
	{
		numLevel = NUMLEVEL;
	}

	MapManager::getInstance()->SetMap(numLevel);
	Scene* scene = InGameScene::createScene();
	if (scene != nullptr)
		Director::getInstance()->replaceScene(scene);
}

void MMainScene::StartGame()
{
	//run level 1 scene
	MapManager::getInstance()->SetMap(1);
	Scene* scene = InGameScene::createScene();
	if (scene != nullptr)
		Director::getInstance()->replaceScene(scene);
}

void MMainScene::SelectLevel()
{
	Scene* scene = MSelectLevelScene::createScene();
	if (scene != nullptr)
		Director::getInstance()->replaceScene(scene);
}

void MMainScene::Close()
{
	Director::getInstance()->end();
}

void MMainScene::About()
{
	Scene* scene = AboutScene::createScene();
	if (scene != nullptr)
		Director::getInstance()->replaceScene(scene);
}
