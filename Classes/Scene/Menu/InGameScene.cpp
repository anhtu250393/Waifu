#include "InGameScene.h"
#include "GameObjects/DynamicObjects/MovingPlatform.h"
#include "GameObjects/DynamicObjects/CollapsePlatform.h"
#include "GameObjects/DynamicObjects/Collectible.h"
#include "GameObjects/AnimationObjects/Lever.h"
#include "GameObjects/AnimationObjects/Door.h"
#include "GameObjects/AnimationObjects/Goal.h"
#include "GameObjects/StaticObjects/BackGround.h"
#include "GameObjects/StaticObjects/Floor.h"
#include "GameObjects/StaticObjects/Pedestal.h"
#include "GameObjects/StaticObjects/Wall.h"
#include "GameObjects/MovingObjects/MainCharacter.h"
#include "GameObjects/MovingObjects/MonsterChase.h"
#include "Scene/Menu/MSelectLevelScene.h"

#if defined  ANDROID || CONTROLLER 
#include "Core/Control/CustomControl.h"
#endif

Scene* InGameScene::m_scene = nullptr;

Scene* InGameScene::createScene()
{
	m_scene = Scene::createWithPhysics();
#ifdef ANDROID
	m_scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
#else
	m_scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
#endif

	m_scene->getPhysicsWorld()->setGravity(Vec2(0.0f, -5.0f));
	auto layer = InGameScene::create();
	m_scene->addChild(layer);

	return m_scene;
}

#if defined(CONTROLLER)
void InGameScene::createController() 
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	mControllerLayer = Node::create();
	mControllerLayer->setContentSize(visibleSize);
	addChild(mControllerLayer);

	//Joystick
	Rect joystickBaseDimensions;
	joystickBaseDimensions = Rect(0, 0, 160.0f, 160.0f);

	Point joystickBasePosition;
	joystickBasePosition = Vec2(visibleSize.width * 0.05, visibleSize.height *0.25);

	joystickBase = new SneakyJoystickSkinnedBase();
	joystickBase->init();
	joystickBase->setPosition(joystickBasePosition);
	joystickBase->setBackgroundSprite(Sprite::create("Image/joystick-back.png"));
	joystickBase->setThumbSprite(Sprite::create("Image/stick.png"));
	joystickBase->setScale(0.5);

	SneakyJoystick *aJoystick = new SneakyJoystick();
	aJoystick->initWithRect(joystickBaseDimensions);

	aJoystick->autorelease();
	joystickBase->setJoystick(aJoystick);
	joystickBase->setPosition(joystickBasePosition);

	leftJoystick = joystickBase->getJoystick();
	leftJoystick->retain();
	mControllerLayer->addChild(joystickBase, 0);

	//jump control
	jumpBtn = ui::Button::create("Image/head.png", "Image/head.png");
	jumpBtn->setGlobalZOrder(4);
	jumpBtn->setOpacity(220);
	jumpBtn->setPosition(Vec2(visibleSize.width - 350, 200));
	jumpBtn->addTouchEventListener(CC_CALLBACK_2(InGameScene::playerJump, this));
	jumpBtn->setScale(0.5f);
	mControllerLayer->addChild(jumpBtn, 0);

	//hide/unhide
	hideBtn = ui::Button::create("Image/checkbox_checked.png", "Image/checkbox_checked_disable.png");
	hideBtn->setGlobalZOrder(4);
	hideBtn->setOpacity(220);
	hideBtn->setPosition(Vec2(visibleSize.width - 200, 350));
	hideBtn->addTouchEventListener(CC_CALLBACK_2(InGameScene::playerHide, this));
	hideBtn->setScale(2.0f);
	mControllerLayer->addChild(hideBtn, 0);
}

void InGameScene::playerJump(Ref* sender, Widget::TouchEventType type) 
{
	if (type == Widget::TouchEventType::BEGAN)
	{
		CustomControl::getInstance()->setIsMutiTap(true);
	}
}

void InGameScene::playerHide(Ref* sender, Widget::TouchEventType type) 
{
	if (type == Widget::TouchEventType::BEGAN)
	{
		if (!CustomControl::getInstance()->isSwipeDown())
		{
			CustomControl::getInstance()->setIsSwipeDown();
		}
		else
		{
			CustomControl::getInstance()->setIsSwipeUp();
		}
	}
}
#endif

bool InGameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	MapManager::getInstance()->InitMap(this);
#if defined(ANDROID) || defined(CONTROLLER)
	CustomControl::getInstance()->ResetAll();
#else
	MainCharacter::getInstance()->SetCurrentKey(EventKeyboard::KeyCode::KEY_NONE);
#endif

#if defined(CONTROLLER)
	createController();
#endif

	//create hud
	CreateHud();
	//add Listener: touch, key 
	addListener();

	//custom turn off auto step update physic World
	scheduleOnce(CC_SCHEDULE_SELECTOR(InGameScene::updateReady_dg), 1);
	this->scheduleUpdate();

#if USE_AUDIO_ENGINE
	AudioEngine::end();
#elif USE_SIMPLE_AUDIO_ENGINE
	SimpleAudioEngine::getInstance()->playEffect("Background.mid");
#endif

	return true;
}

void InGameScene::addListener()
{
	//collision event 
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(InGameScene::onContactBegin, this);
	contactListener->onContactPreSolve = CC_CALLBACK_2(InGameScene::onContactStay, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(InGameScene::onContactExit, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

#if defined (ANDROID)
	//tounch event (android)
	auto listenerTouch = EventListenerTouchAllAtOnce::create();
	listenerTouch->onTouchesBegan = CC_CALLBACK_2(InGameScene::onTouchBegan, this);
	listenerTouch->onTouchesMoved = CC_CALLBACK_2(InGameScene::onTouchMoved, this);
	listenerTouch->onTouchesEnded = CC_CALLBACK_2(InGameScene::onTouchEnded, this);
	listenerTouch->onTouchesCancelled = CC_CALLBACK_2(InGameScene::onTouchesCancelled, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerTouch, this);
#else
	//key event
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(InGameScene::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(InGameScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
#endif
}

void InGameScene::updateReady_dg(float dt)
{
	this->getScene()->getPhysicsWorld()->setAutoStep(false);
}

void InGameScene::update(float dt)
{
	//custom step update physic World
	this->getScene()->getPhysicsWorld()->step(1.5 * dt * 10);

	for (auto object : MapManager::getInstance()->getObjects())
	{
		if (object->isInit()) 
		{
			object->update(dt);
		}
	}

#ifdef CONTROLLER
	// Move Player by Joystick (If player attack, player will stop move)
	Point scaleVelocity = ccpMult(leftJoystick->getVelocity(), 120);
	if (scaleVelocity.x < 0)
	{
		CustomControl::getInstance()->setDirecLeft(true);
		CustomControl::getInstance()->setDirecRight(false);
	}
	else if (scaleVelocity.x > 0)
	{
		CustomControl::getInstance()->setDirecRight(true);
		CustomControl::getInstance()->setDirecLeft(false);
		
	}
	else 
	{
		CustomControl::getInstance()->setDirecRight(false);
		CustomControl::getInstance()->setDirecLeft(false);
	}
#endif
}

bool InGameScene::onContactBegin(cocos2d::PhysicsContact & contact)
{
	PhysicsBody* physicA = contact.getShapeA()->getBody();
	PhysicsBody* physicB = contact.getShapeB()->getBody();
	int spriteA = physicA->getCollisionBitmask();
	int spriteB = physicB->getCollisionBitmask();

	if (spriteA == -1 || spriteB == -1 || spriteA == spriteB)
	{
		return false;
	}

	vector<BaseObject*> m_Objects = MapManager::getInstance()->getObjects();

	if ((spriteA & BITMASK_CHARACTER) || (spriteB & BITMASK_CHARACTER))
	{
		int index = spriteA & BITMASK_CHARACTER ? physicA->getGroup() : physicB->getGroup();
		if (dynamic_cast<MainCharacter*>(m_Objects[index]))
			return dynamic_cast<MainCharacter*>(m_Objects[index])->onContactBegin(spriteA & BITMASK_CHARACTER ? physicB : physicA);
	}

	if ((spriteA & BITMASK_ENEMY) || (spriteB & BITMASK_ENEMY))
	{
		int index = spriteA & BITMASK_ENEMY ? physicA->getGroup() : physicB->getGroup();
		if (dynamic_cast<MonsterChase*>(m_Objects[index]))
			return dynamic_cast<MonsterChase*>(m_Objects[index])->onContactBegin(spriteA & BITMASK_ENEMY ? physicB : physicA);
	}

	return true;
}

bool InGameScene::onContactStay(PhysicsContact & contact, PhysicsContactPreSolve& solve)
{
	PhysicsBody* physicA = contact.getShapeA()->getBody();
	PhysicsBody* physicB = contact.getShapeB()->getBody();
	int spriteA = physicA->getCollisionBitmask();
	int spriteB = physicB->getCollisionBitmask();

	if (spriteA == -1 || spriteB == -1 || spriteA == spriteB)
	{
		return false;
	}

	vector<BaseObject*> m_Objects = MapManager::getInstance()->getObjects();

	if ((spriteA & BITMASK_CHARACTER) || (spriteB & BITMASK_CHARACTER))
	{
		int index = spriteA & BITMASK_CHARACTER ? physicA->getGroup() : physicB->getGroup();
		if (dynamic_cast<MainCharacter*>(m_Objects[index]))
			return dynamic_cast<MainCharacter*>(m_Objects[index])->onContactStay(spriteA & BITMASK_CHARACTER ? physicB : physicA);
	}

	if ((spriteA & BITMASK_ENEMY) || (spriteB & BITMASK_ENEMY))
	{
		int index = spriteA & BITMASK_ENEMY ? physicA->getGroup() : physicB->getGroup();
		if (dynamic_cast<MonsterChase*>(m_Objects[index]))
			return dynamic_cast<MonsterChase*>(m_Objects[index])->onContactStay(spriteA & BITMASK_ENEMY ? physicB : physicA);
	}

	return true;
}

bool InGameScene::onContactExit(PhysicsContact & contact)
{
	PhysicsBody* physicA = contact.getShapeA()->getBody();
	PhysicsBody* physicB = contact.getShapeB()->getBody();
	int spriteA = physicA->getCollisionBitmask();
	int spriteB = physicB->getCollisionBitmask();

	if (spriteA == -1 || spriteB == -1 || spriteA == spriteB)
	{
		return false;
	}

	vector<BaseObject*> m_Objects = MapManager::getInstance()->getObjects();

	if ((spriteA & BITMASK_CHARACTER) || (spriteB & BITMASK_CHARACTER))
	{
		int index = spriteA & BITMASK_CHARACTER ? physicA->getGroup() : physicB->getGroup();
		if (dynamic_cast<MainCharacter*>(m_Objects[index]))
			return dynamic_cast<MainCharacter*>(m_Objects[index])->onContactExit(spriteA & BITMASK_CHARACTER ? physicB : physicA);
	}

	if ((spriteA & BITMASK_ENEMY) || (spriteB & BITMASK_ENEMY))
	{
		int index = spriteA & BITMASK_ENEMY ? physicA->getGroup() : physicB->getGroup();
		if (dynamic_cast<MonsterChase*>(m_Objects[index]))
			return dynamic_cast<MonsterChase*>(m_Objects[index])->onContactExit(spriteA & BITMASK_ENEMY ? physicB : physicA);
	}

	return true;
}

#if defined (ANDROID)
void InGameScene::onTouchBegan(const std::vector<Touch*>& touch, Event  *event)
{
#if !defined (CONTROLLER) 
	CustomControl::getInstance()->Update(touch, CustomControl::_TouchEventType::BEGAN);
#endif
}

void InGameScene::onTouchMoved(const std::vector<Touch*>& touch, Event  *event)
{
#if !defined (CONTROLLER)  
	CustomControl::getInstance()->Update(touch, CustomControl::_TouchEventType::MOVED);
#endif
}

void InGameScene::onTouchEnded(const std::vector<Touch*>& touch, Event  *event)
{
	vector<BaseObject*> m_Objects = MapManager::getInstance()->getObjects();
	for (int i = 0; i < m_Objects.size(); ++i)
	{
		if (dynamic_cast<Lever*>(m_Objects[i]))
		{
			if (dynamic_cast<Lever*>(m_Objects[i])->getSprite()->getBoundingBox().containsPoint(touch[0]->getLocation()))
			{
				dynamic_cast<Lever*>(m_Objects[i])->SetActive();
			}
		}
	}
#if !defined (CONTROLLER) 
	CustomControl::getInstance()->Update(touch, CustomControl::_TouchEventType::ENDED);
#endif
}

void InGameScene::onTouchesCancelled(const std::vector<Touch*>& touch, Event  *event)
{
#if !defined (CONTROLLER) 
	CustomControl::getInstance()->Update(touch, CustomControl::_TouchEventType::CANCELED);
#endif
}
#else
void InGameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	MainCharacter::getInstance()->SetCurrentKey(keyCode);
}

void InGameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
	{
		vector<BaseObject*> m_Objects = MapManager::getInstance()->getObjects();
		for (int i = 0; i < m_Objects.size(); ++i)
		{
			if (dynamic_cast<Lever*>(m_Objects[i]))
			{
				dynamic_cast<Lever*>(m_Objects[i])->SetActive();
			}
		}
	}

	if(MainCharacter::getInstance()->GetCurrentKey() == keyCode)
	{
		MainCharacter::getInstance()->SetCurrentKey(EventKeyboard::KeyCode::KEY_NONE);
	}
}
#endif

void InGameScene::CreateHud()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Node* m_UILayer = Node::create();
	//add btn pause game 
	Button *btnPause = Button::create();
	btnPause->setTitleFontName("fonts/Marker Felt.ttf");
	btnPause->setTitleFontSize(70);
	btnPause->setTitleText("Pause Game");
	btnPause->setPosition(Vec2(visibleSize.width - origin.x, visibleSize.height - origin.y - btnPause->getContentSize().height));
	btnPause->addClickEventListener([=](Ref* event) {
		PausePopup  *m_PausePopup = PausePopup::create();
		addChild(m_PausePopup, 4);
		m_PausePopup->appear(m_UILayer);
		});
	m_UILayer->addChild(btnPause);
	this->addChild(m_UILayer, 2);
}
