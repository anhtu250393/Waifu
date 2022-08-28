#include "MovingPlatform.h"

enum ACTION
{
	IDE = 0,
	RUN,

	MAX_ACTION
};



MovingPlatform::MovingPlatform()
	: DynamicObject()
{
	m_Time = 2.0f;
	m_Range = Vec2(0, 80);
	m_Move = nullptr;
	m_IsAcive = true;
	m_DelaTime = 0.0f;
	m_Collision = false;

	flip = -1;
}

MovingPlatform::~MovingPlatform()
{

}

bool MovingPlatform::Init(Layer *layer, ValueMap property)
{
	float deltaX = property.at("deltaX").asFloat();
	float deltaY = property.at("deltaY").asFloat();
	float moveSec = property.at("moveSec").asFloat();
	float x = property.at("x").asFloat();
	float y = property.at("y").asFloat();
	int type = property.at("type").asInt();
	string m_PathImage = "Image/Pyhsical/Platform_" + to_string(type) + ".png";
	string m_NameBox = "Platform_box_" + to_string(type);
	bool result = false;

	result =BaseObject::Init(layer, m_PathImage, property);
	m_Range = Vec2(deltaX, deltaY);
	m_Time = moveSec;
	m_Pos = Vec2(x, y);

	ValueMap box_collison = getBoxCollision(m_NameBox);
	if (box_collison.empty())
		result = setPhysical(false, BITMASK_MOVING_PLATFORM);
	else
		result = setPhysical(box_collison, false, BITMASK_MOVING_PLATFORM);

	return result;
}

void MovingPlatform::update(float dt)
{
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

	if (!m_IsAcive)
		return;

	switch (m_State)
	{
	case IDE:
		flip *= -1;

		m_Move = MoveBy::create(m_Time, m_Range * flip);
		m_Move->retain();
		getSprite()->runAction(m_Move);

		SwitchState(RUN);
		break;
	case RUN:
		if (m_Move && m_Move->isDone())
		{
			SwitchState(IDE);

			m_Move->release();
		}
		break;
	default:
		break;
	}

	Calculator();
}

void MovingPlatform::SetConlision(bool status)
{
	m_Collision = status;
}

void MovingPlatform::SetTimeMove(long time)
{
	m_Time = time;
}

void MovingPlatform::SetRange(Vec2 range)
{
	m_Range = range;
}

void MovingPlatform::SwitchActive()
{
	m_IsAcive = m_IsAcive == true ? false : true;
}

Vec2 MovingPlatform::GetDelta()
{
	return m_Delta;
}

void MovingPlatform::Calculator()
{
	Vec2 pos = getPosition();
	m_Delta = pos - m_Pos;
	m_Pos = pos;
}
