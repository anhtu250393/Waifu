#include "Door.h"

enum STATE
{
	CLOSE = 0,
	OPEN,

	MAX_ACTION
};


Door::Door()
	: AnimationObject()
{
	m_DelaTime = 0.0f;
	m_Collision = false;
}

Door::~Door()
{

}

bool Door::Init(Layer* layer, ValueMap property, ValueMap box_collison)
{
	bool result = false;
	m_MaxACtion = MAX_ACTION;
	m_Animation.resize(m_MaxACtion);
	m_Animation.capacity();

	result = BaseObject::Init(layer, "Animation/OpenDoor/1.png", property);
	result = AddAnimation("Animation/CloseDoor/", 3, CLOSE);
	result = AddAnimation("Animation/OpenDoor/", 3, OPEN);
	if (box_collison.empty())
		result = setPhysical(false, BITMASK_DOOR);
	else
		result = setPhysical(box_collison, false, BITMASK_DOOR);

	return result;
}

void Door::update(float dt)
{
	if (m_CurrentSate != m_NextState)
	{
		RunAction(m_NextState);
		m_CurrentSate = m_NextState;
	}

	if(m_Collision)
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
}

void Door::SetCollision(bool status)
{
	m_Collision = status;
}

bool Door::IsActive()
{
	return m_CurrentSate == OPEN ? true : false;
}