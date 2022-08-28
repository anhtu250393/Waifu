#include "Goal.h"
#include "Scene/Level/MapManager.h"

enum STATE
{
	IDE = 0,
	LEVEL_1,
	LEVEL_2,
	LEVEL_3,

	MAX_ACTION
};


Goal::Goal()
	: AnimationObject()
{
}

Goal::~Goal()
{
}

bool Goal::Init(Layer* layer, ValueMap value)
{
	m_MaxACtion = MAX_ACTION;
	m_Animation.resize(m_MaxACtion);
	m_Animation.capacity();

	bool result = false;

	result = BaseObject::Init(layer, "Animation/Goal/1.png", value);
	result = AddAnimation("Animation/Goal/", 1, IDE);
	result = AddAnimation("Animation/Goal/", 1, LEVEL_1, 2);
	result = AddAnimation("Animation/Goal/", 1, LEVEL_2, 3);
	result = AddAnimation("Animation/Goal/", 1, LEVEL_3, 4);
	result = setPhysical(false, BITMASK_GOAL);

	return result;
}

void Goal::update(float dt)
{
	if (m_CurrentSate != m_NextState)
	{
		RunAction(m_NextState);
		m_CurrentSate = m_NextState;
	}
}

void Goal::Active()
{
	if (m_CurrentSate >= LEVEL_2)
	{
		MapManager::getInstance()->LoadNextMap();
	}
}
