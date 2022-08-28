#include "DynamicObject.h"

enum ACTION
{
	IDE = 0,

	MAX_ACTION
};

DynamicObject::DynamicObject()
	: BaseObject()
{
	m_State = IDE;
}

DynamicObject::~DynamicObject()
{
}

void DynamicObject::update(float dt)
{
	switch (m_State)
	{
	case IDE:
		break;
	default:
		break;
	}

	return;
}

void DynamicObject::SwitchState(int state)
{
	m_State = state;
}
