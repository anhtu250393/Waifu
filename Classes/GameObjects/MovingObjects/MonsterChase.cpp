#include"MonsterChase.h"
#include "Scene/Level/MapManager.h"

#define DISTANCE_CHASE 80

enum
{
	IDLE = 0,
	MOVE,
	CHASE,

	MAX_ACTION
};

MonsterChase::MonsterChase()
	: MovingObject()
{
	x1 = 0;
	x2 = 0;
	m_MoveSpeed = 0;
}

MonsterChase::~MonsterChase()
{
}

void MonsterChase::Init(Layer *layer, ValueMap property, ValueMap box_collison)
{
	m_MaxACtion = MAX_ACTION;
	m_Animation.resize(m_MaxACtion);
	m_Animation.capacity();
	BaseObject::Init(layer, "Animation/Enemy/Idle/1.png", property);

	if (box_collison.empty())
		setPhysical(true, BITMASK_ENEMY);
	else
		setPhysical(box_collison, true, BITMASK_ENEMY);

	AddAnimation("Animation/Enemy/Idle/", 1, IDLE);
	AddAnimation("Animation/Enemy/Move/", 5, MOVE);
	AddAnimation("Animation/Enemy/Chase/", 5, CHASE);

	m_MoveSpeed = property.at("moveSpd").asFloat();
	float width = property.at("width").asFloat();
	x1 = property.at("x1").asFloat();
	x2 = property.at("x2").asFloat() - width;
	m_MainCharactor = MainCharacter::getInstance();

	setFlippedX(true);
}

void MonsterChase::update(float dt)
{
	switch (m_NextState)
	{
	case IDLE:
		SwitchState(MOVE);
		break;
	case MOVE:
		if (IsChase() == true)
		{
			SwitchState(CHASE);
		}
		else
		{
			RunRepeatAction();
			Patrol();
		}
		break;
	case CHASE:
		if (IsChase() == false)
		{
			SwitchState(MOVE);
		}
		else
		{
			RunRepeatAction();
			Chase();
		}
		break;
	default:
		break;
	}
}

bool MonsterChase::onContactBegin(PhysicsBody* body)
{
	int spriteBitmask = body->getCollisionBitmask();
	vector<BaseObject*> m_Objects = MapManager::getInstance()->getObjects();

	if (spriteBitmask & BITMASK_COLLECTIBLE)
	{
		return false;
	}

	if (spriteBitmask & BITMASK_GOAL)
	{
		return false;
	}

	if (spriteBitmask & BITMASK_LEVER)
	{
		return false;
	}

	return true;
}

bool MonsterChase::onContactStay(PhysicsBody* body)
{
	int spriteBitmask = body->getCollisionBitmask();
	vector<BaseObject*> m_Objects = MapManager::getInstance()->getObjects();

	return true;
}

bool MonsterChase::onContactExit(PhysicsBody* body)
{
	int spriteBitmask = body->getCollisionBitmask();
	vector<BaseObject*> m_Objects = MapManager::getInstance()->getObjects();

	return true;
}

void MonsterChase::Patrol()
{
	//move enemy	
	setVelocity(Vec2(m_MoveSpeed, getVelocity().y));

	//turn enemy
	if ((getPosition().x < x1 && m_MoveSpeed < 0) || (getPosition().x > x2 && m_MoveSpeed > 0))
	{
		m_MoveSpeed *= -1;
		setFlippedX(m_MoveSpeed > 0 ? true : false);
	}

}

void MonsterChase::Chase()
{
	//move enemy	
	setVelocity(Vec2(m_MoveSpeed * 1.5, getVelocity().y));

	//chase
	if (getPosition().x > m_MainCharactor->getPosition().x)
	{
		setFlippedX(false);
		m_MoveSpeed = -abs(m_MoveSpeed);
	}
	else if (getPosition().x < m_MainCharactor->getPosition().x)
	{
		setFlippedX(true);
		m_MoveSpeed = abs(m_MoveSpeed);
	}
}

bool MonsterChase::IsChase()
{
	if (!m_MainCharactor->IsHide())
	{
		float distance = 1000;
		if (getPosition().x > m_MainCharactor->getPosition().x && m_MoveSpeed < 0)
		{
			distance = ccpDistance(getPosition(), Vec2(m_MainCharactor->getPosition().x + m_MainCharactor->getContentSize().width, m_MainCharactor->getPosition().y));
		}
		else if (getPosition().x < m_MainCharactor->getPosition().x && m_MoveSpeed > 0)
		{
			distance = ccpDistance(Vec2(getPosition().x + getContentSize().width, getPosition().y), m_MainCharactor->getPosition());
		}
		return distance < DISTANCE_CHASE;
	}

	return false;
}
