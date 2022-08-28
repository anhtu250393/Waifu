#include "MainCharacter.h"
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
#include "GameObjects/MovingObjects/MonsterChase.h"
#include "Scene/Level/MapManager.h"

#if defined  ANDROID || CONTROLLER 
#include "Core/Control/CustomControl.h"
#endif

#define MOVE_SPEED 20
#define JUMP_HEIGHT 50

enum
{
	IDLE = 0,
	MOVE,
	JUMP,
	FALL,
	LANDING,
	HIDE,
	UNHIDE,

	MAX_ACTION
};

MainCharacter* MainCharacter::sInstance = nullptr;

MainCharacter* MainCharacter::getInstance()
{
	if (sInstance == nullptr)
	{
		sInstance = new MainCharacter();
	}
	return sInstance;
}

MainCharacter::MainCharacter()
	: MovingObject()
{
	m_CurrentKey = EventKeyboard::KeyCode::KEY_NONE;
	m_VelocityX = 0;
	m_VelocityY = 0;
	m_Object = nullptr;

	canMove = true;
}

MainCharacter::~MainCharacter()
{
	if (sInstance != nullptr)
	{
		sInstance = nullptr;
	}
}

void MainCharacter::Init(Layer* layer, ValueMap property, ValueMap box_collison)
{ 
	m_MaxACtion = MAX_ACTION;
	m_Animation.resize(m_MaxACtion);
	m_Animation.capacity();
	setLayerIndex(3);
	BaseObject::Init(layer, "Animation/MainCharactor/Idle/1.png", property);

	if(box_collison.empty())
		setPhysical(true, BITMASK_CHARACTER);
	else
		setPhysical(box_collison, true, BITMASK_CHARACTER);

	AddAnimation("Animation/MainCharactor/Idle/", 1, IDLE);
	AddAnimation("Animation/MainCharactor/Move/", 6, MOVE);
	AddAnimation("Animation/MainCharactor/Jump/", 2, JUMP, 1);
	AddAnimation("Animation/MainCharactor/Jump/", 1, FALL, 3);
	AddAnimation("Animation/MainCharactor/Jump/", 1, LANDING, 4);
	AddAnimation("Animation/MainCharactor/Hide/", 5, HIDE);
	AddAnimation("Animation/MainCharactor/Unhide/", 5, UNHIDE);

	SwitchState(FALL);
}

void MainCharacter::update(float dt)
{
#if defined  ANDROID || CONTROLLER 
	HanldeAnimationTouch();
#else
	HanldeAnimationKey();
#endif

	switch (m_NextState)
	{
	case IDLE:
		RunAction();
		break;
	case MOVE:
		RunRepeatAction();
		break;
	case JUMP:
		RunActionNext(FALL);
		break;
	case FALL:
		RunAction();
		break;
	case LANDING:
		RunActionNext(IDLE);
		break;
	case HIDE:
		RunAction();
		break;
	case UNHIDE:
		RunActionNext(IDLE);
		break;
	default:
		break;
	}

	if (m_Object && dynamic_cast<MovingPlatform*>(m_Object))
	{
		Vec2 pos = getSprite()->getPosition();
		Vec2 delta = dynamic_cast<MovingPlatform*>(m_Object)->GetDelta();
		pos += delta;
		getSprite()->setPosition(pos);
	}

	if (getPosition().y < -50)
	{
		MapManager::getInstance()->ResetMap();
	}
}

bool MainCharacter::onContactBegin(PhysicsBody* body)
{
	int spriteBitmask = body->getCollisionBitmask();
	int index = body->getGroup();
	vector<BaseObject*> m_Objects = MapManager::getInstance()->getObjects();

	if (spriteBitmask & BITMASK_CAN_MOVE_JUMP) 
	{
		if (GetCurrentState() == FALL)
		{
			if (IsOutAbove(m_Objects[index]))
			{
				canMove = true;
				SwitchState(LANDING);
			}
			else
			{
				canMove = false;
			}
		}
	}

	if (spriteBitmask & BITMASK_WALL)
	{
		if (GetCurrentState() == JUMP)
		{
			canMove = false;
			SwitchState(FALL);
		}
		else if (GetCurrentState() == FALL)
		{
			canMove = true;
			SwitchState(LANDING);
		}
	}

	if (spriteBitmask & BITMASK_LEVER)
	{
		dynamic_cast<Lever*>(m_Objects[index])->SetConlision(true);
		return false;
	}

	if (spriteBitmask & BITMASK_DOOR)
	{
		if (dynamic_cast<Door*>(m_Objects[index])->IsActive())
		{
			return false;
		}
		else if (GetCurrentState() == JUMP)
		{
			SwitchState(FALL);
		}
		else if (GetCurrentState() == FALL)
		{
			int rotation = m_Objects[index]->getSprite()->getRotation();
			if (rotation == 90)
			{
				canMove = true;
				SwitchState(LANDING);
			}
		}
	}

	if (spriteBitmask & BITMASK_GOAL)
	{
		dynamic_cast<Goal*>(m_Objects[index])->Active();
		return false;
	}

	if (spriteBitmask & BITMASK_ENEMY)
	{
		if (!IsHide())
		{
			MapManager::getInstance()->ResetMap();
		}

		return false;
	}

	if (spriteBitmask & BITMASK_COLLECTIBLE)
	{
		dynamic_cast<Collectible*>(m_Objects[index])->SwitchState(3);
		for (auto object : m_Objects)
		{
			if (dynamic_cast<Goal*>(object))
			{
				dynamic_cast<Goal*>(object)->SwitchState(dynamic_cast<Goal*>(object)->GetCurrentState() + 1);
			}
		}

		return false;
	}

	if (spriteBitmask & BITMASK_MOVING_PLATFORM)
	{
		AttachObject(m_Objects[index]);
	}

	if (spriteBitmask & BITMASK_COLLAPSE_PLATFORM)
	{
		dynamic_cast<CollapsePlatform*>(m_Objects[index])->SwitchState(1);
	}

	return true;
}

bool MainCharacter::onContactStay(PhysicsBody* body)
{
	int spriteBitmask = body->getCollisionBitmask();
	int index = body->getGroup();
	vector<BaseObject*> m_Objects = MapManager::getInstance()->getObjects();

	if (spriteBitmask & BITMASK_CAN_MOVE_JUMP)
	{
		if (GetCurrentState() == FALL)
		{
			if (IsOutAbove(m_Objects[index]))
			{
				canMove = true;
				SwitchState(LANDING);
			}
		}
	}

	if (spriteBitmask & BITMASK_ENEMY)
	{
		if (!IsHide())
		{
			MapManager::getInstance()->ResetMap();
		}

		return false;
	}

	return true;
}

bool MainCharacter::onContactExit(PhysicsBody* body)
{
	int spriteBitmask = body->getCollisionBitmask();
	int index = body->getGroup();
	vector<BaseObject*> m_Objects = MapManager::getInstance()->getObjects();

	if (spriteBitmask & BITMASK_CAN_MOVE_JUMP)
	{
		if (GetCurrentState() == MOVE)
		{
			canMove = true;
			SwitchState(FALL);
		}
		else if (GetCurrentState() == FALL)
		{
			canMove = true;
		}
	}

	if (spriteBitmask & BITMASK_LEVER)
	{
		dynamic_cast<Lever*>(m_Objects[index])->SetConlision(false);
		return false;
	}

	if (spriteBitmask & BITMASK_ENEMY)
	{
		if (!IsHide())
		{
			MapManager::getInstance()->ResetMap();
		}

		return false;
	}

	if (spriteBitmask & BITMASK_MOVING_PLATFORM)
	{
		DetachObject();
	}

	return true;
}

#if defined  ANDROID || CONTROLLER 
void MainCharacter::HanldeAnimationTouch()
{
	if (CustomControl::getInstance()->isSwipeDown()) //hide
	{
		if (GetCurrentState() == LANDING || GetCurrentState() == MOVE || GetCurrentState() == IDLE)
		{
			SwitchState(HIDE);
#ifndef CONTROLLER
			CustomControl::getInstance()->Reset();
#endif
		}
	}
	else if (CustomControl::getInstance()->isSwipeUp()) //unhide
	{
		if (GetCurrentState() == HIDE)
		{
			SwitchState(UNHIDE);
			CustomControl::getInstance()->Reset();
		}
	}
	else if (CustomControl::getInstance()->isMutiTap()) //jump
	{
		if (GetCurrentState() == LANDING || GetCurrentState() == MOVE || GetCurrentState() == IDLE)
		{
			Jump();
			SwitchState(JUMP);
#ifdef CONTROLLER
			CustomControl::getInstance()->setIsMutiTap(false);
#endif
		}
	}
	if (CustomControl::getInstance()->isDirectLeft()) //move left
	{
		if (GetCurrentState() == LANDING || GetCurrentState() == MOVE || GetCurrentState() == IDLE)
		{
			if (canMove)
			{
				MoveLeft();
				SwitchState(MOVE);
			}
		}
		else if (GetCurrentState() == FALL)
		{
			if (canMove)
			{
				MoveLeft();
			}
		}
	}
	else if (CustomControl::getInstance()->isDirectRight()) //move right
	{
		if (GetCurrentState() == LANDING || GetCurrentState() == MOVE || GetCurrentState() == IDLE)
		{
			if (canMove)
			{
				MoveRight();
				SwitchState(MOVE);
			}
		}
		else if (GetCurrentState() == FALL)
		{
			if (canMove)
			{
				MoveRight();
			}
		}
	}
	else
	{
		if (GetCurrentState() == MOVE)
		{
			SwitchState(IDLE);
		}
		else if (GetCurrentState() == FALL || GetCurrentState() == JUMP)
		{
			if (m_VelocityX != 0)
			{
				Reset();
			}
		}
	}
}
#else
void MainCharacter::HanldeAnimationKey()
{
	if (m_CurrentKey == EventKeyboard::KeyCode::KEY_LEFT_ARROW || m_CurrentKey == EventKeyboard::KeyCode::KEY_A) //move left
	{
		if (GetCurrentState() == LANDING || GetCurrentState() == MOVE || GetCurrentState() == IDLE)
		{
			if (canMove)
			{
				MoveLeft();
				SwitchState(MOVE);
			}
		}
		else if (GetCurrentState() == FALL)
		{
			if (canMove)
			{
				MoveLeft();
			}
		}
	}
	else if (m_CurrentKey == EventKeyboard::KeyCode::KEY_RIGHT_ARROW || m_CurrentKey == EventKeyboard::KeyCode::KEY_D) //move right
	{
		if (GetCurrentState() == LANDING || GetCurrentState() == MOVE || GetCurrentState() == IDLE)
		{
			if (canMove)
			{
				MoveRight();
				SwitchState(MOVE);
			}
		}
		else if (GetCurrentState() == FALL)
		{
			if (canMove)
			{
				MoveRight();
			}
		}
	}
	else if (m_CurrentKey == EventKeyboard::KeyCode::KEY_DOWN_ARROW || m_CurrentKey == EventKeyboard::KeyCode::KEY_S)
	{
		if (GetCurrentState() == LANDING || GetCurrentState() == MOVE || GetCurrentState() == IDLE)
		{
			SwitchState(HIDE);
		}
	}
	else if (m_CurrentKey == EventKeyboard::KeyCode::KEY_UP_ARROW || m_CurrentKey == EventKeyboard::KeyCode::KEY_W)
	{
		if (GetCurrentState() == HIDE)
		{
			SwitchState(UNHIDE);
		}
		else if (GetCurrentState() == LANDING || GetCurrentState() == MOVE || GetCurrentState() == IDLE)
		{
			Jump();
			SwitchState(JUMP);
		}
	}
	else
	{
		if (GetCurrentState() == MOVE)
		{
			SwitchState(IDLE);
		}
		else if (GetCurrentState() == FALL || GetCurrentState() == JUMP)
		{
			if (m_VelocityX != 0)
			{
				Reset();
			}
		}
	}
}
#endif

void MainCharacter::MoveLeft()
{
	setFlippedX(true);
	m_VelocityX = -MOVE_SPEED;
	m_VelocityY = getVelocity().y;
	setVelocity(Vec2(m_VelocityX, m_VelocityY));
}

void MainCharacter::MoveRight()
{
	setFlippedX(false);
	m_VelocityX = MOVE_SPEED;
	m_VelocityY = getVelocity().y;
	setVelocity(Vec2(m_VelocityX, m_VelocityY));
}

void MainCharacter::Jump()
{
	m_VelocityX = getVelocity().x;
	m_VelocityY = JUMP_HEIGHT;
	setVelocity(Vec2(m_VelocityX, m_VelocityY));
}

void MainCharacter::Reset()
{
	m_VelocityX = 0;
	m_VelocityY = getVelocity().y;
	setVelocity(Vec2(m_VelocityX, m_VelocityY));
}

void MainCharacter::SetCurrentKey(EventKeyboard::KeyCode key)
{
	m_CurrentKey = key;
}

EventKeyboard::KeyCode MainCharacter::GetCurrentKey()
{
	return m_CurrentKey;
}

void MainCharacter::AttachObject(BaseObject * Object)
{
	m_Object = Object;
}

void MainCharacter::DetachObject()
{
	m_Object = nullptr;
}

bool MainCharacter::IsHide()
{
	return GetCurrentState() == HIDE;
}
