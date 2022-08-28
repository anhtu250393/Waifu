#include "Collectible.h"
#include "Scene/Level/MapManager.h"
#include "GameObjects/StaticObjects/BackGround.h"

enum ACTION
{
	IDE = 0,
	UP,
	DOWN,
	HIDE,
	FREE,

	MAX_ACTION
};

Collectible::Collectible()
	: DynamicObject()
{
	m_Time = 1;
	m_Range = Vec2(0, 40);
	m_Move = nullptr;

	flip = -1;
}

Collectible::~Collectible()
{
}

bool Collectible::Init(Layer* layer, ValueMap value)
{
	bool result = false;
	int type = value.at("type").asInt();

	switch (type)
	{
	case 1:
		result = BaseObject::Init(layer, "Image/collectibles/glass.png", value);
		break;
	case 2:
		result = BaseObject::Init(layer, "Image/collectibles/organic.png", value);
		break;
	case 3:
		result = BaseObject::Init(layer, "Image/collectibles/plastic.png", value);
		break;
	default:
		break;
	}

	result = setPhysical(false, BITMASK_COLLECTIBLE);

	return result;
}

void Collectible::update(float dt)
{
	switch (m_State)
	{
	case IDE:
		SwitchState(UP);
		break;
	case UP:
		flip *= -1;

		m_Move = MoveBy::create(m_Time, m_Range * flip);
		m_Move->retain();
		getSprite()->runAction(m_Move);

		SwitchState(DOWN);
		break;
	case DOWN:
		if (m_Move && m_Move->isDone())
		{
			SwitchState(UP);

			m_Move->release();
			m_Move = nullptr;
		}
		break;
	case HIDE:
		setPosition(Vec2(-500, -500));

		if (m_Move && m_Move->isDone())
		{
			m_Move->release();
			m_Move = nullptr;

			vector<BaseObject*> m_Objects = MapManager::getInstance()->getObjects();
			dynamic_cast<BackGround*>(m_Objects[0])->UpdateLight(dt);
			SwitchState(FREE);
		}
		break;
	case FREE:
		break;
	default:
		break;
	}
}
