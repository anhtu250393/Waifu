#include "Lever.h"
#include "GameObjects/AnimationObjects/Door.h"
#include "GameObjects/DynamicObjects/MovingPlatform.h"

enum STATE
{
	DEACTIVE = 0,
	ACTIVE,

	MAX_ACTION
};


Lever::Lever()
	: AnimationObject()
{
	m_target = nullptr;
	m_Collision = false;
	m_DelaTime = 0.0f;
}

Lever::~Lever()
{
}

bool Lever::Init(Layer* layer, ValueMap property, ValueMap box_collison, BaseObject* target)
{
	m_MaxACtion = MAX_ACTION;
	m_Animation.resize(m_MaxACtion);
	m_Animation.capacity();

	bool result = false;

	result = BaseObject::Init(layer, "Animation/Lever/1.png", property);
	result = AddAnimation("Animation/Lever/", 1, DEACTIVE);
	result = AddAnimation("Animation/Lever/", 1, ACTIVE, 2);

	if (box_collison.empty())
		result = setPhysical(false, BITMASK_LEVER);
	else
		result = setPhysical(box_collison, false, BITMASK_LEVER);

	m_target = target;
	if (dynamic_cast<MovingPlatform*>(m_target))
	{
		dynamic_cast<MovingPlatform*>(m_target)->SwitchActive();
	}

	return true;
}

void Lever::update(float dt)
{
	if (m_Collision)
	{
		m_DelaTime += dt;
		if (m_DelaTime >= 0.3)
		{
			m_DelaTime = 0.0f;
			getSprite()->setOpacity(getSprite()->getOpacity() == 255 ? 125 : 255);
			getSprite()->setColor(Color3B::BLACK);
		}
	}
	else if (!m_Collision)
	{
		m_DelaTime = 0.0f;
		getSprite()->setOpacity(255);
		getSprite()->setColor(Color3B::WHITE);
	}

	if (m_CurrentSate != m_NextState)
	{
		RunAction(m_NextState);
		m_CurrentSate = m_NextState;
	}
}

void Lever::SetConlision(bool state)
{
	m_Collision = state;
	if (m_Collision)
	{
		if (dynamic_cast<Door*>(m_target))
		{
			dynamic_cast<Door*>(m_target)->SetCollision(true);
		}
		else if (dynamic_cast<MovingPlatform*>(m_target))
		{
			dynamic_cast<MovingPlatform*>(m_target)->SetConlision(true);
		}
	}
	else
	{
		if (dynamic_cast<Door*>(m_target))
		{
			dynamic_cast<Door*>(m_target)->SetCollision(false);
		}
		else if (dynamic_cast<MovingPlatform*>(m_target))
		{
			dynamic_cast<MovingPlatform*>(m_target)->SetConlision(false);
		}
	}
}

bool Lever::SetActive()
{
	if (m_Collision)
	{
		if (dynamic_cast<Door*>(m_target))
		{
			dynamic_cast<Door*>(m_target)->SwitchState(m_CurrentSate == DEACTIVE ? ACTIVE : DEACTIVE);
		}
		else if (dynamic_cast<MovingPlatform*>(m_target))
		{
			dynamic_cast<MovingPlatform*>(m_target)->SwitchActive();
		}
		SwitchState(m_CurrentSate == DEACTIVE ? ACTIVE : DEACTIVE);

		return true;
	}

	return false;
}