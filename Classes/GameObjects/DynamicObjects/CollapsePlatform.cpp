#include "CollapsePlatform.h"

enum ACTION
{
	IDE = 0,
	ACTION,
	COLLAPSE,
	HIDE,

	MAX_ACTION
};

CollapsePlatform::CollapsePlatform()
	: DynamicObject()
{
	m_Time = 0.25f;
	m_DelaTime = 0.0f;
	m_Range = Vec2(0, 80);
	m_Move = nullptr;
	m_IsAcive = true;

	flip = -1;
}

CollapsePlatform::~CollapsePlatform()
{

}

bool CollapsePlatform::Init(Layer *layer, ValueMap property)
{
	int type = property.at("type").asInt();
	string m_PathImage = "Image/Pyhsical/Collapse_" + to_string(type) + ".png";
	string m_NameBox = "Collapse_box_" + to_string(type);
	bool result = false;

	result = BaseObject::Init(layer, m_PathImage, property);

	ValueMap box_collison = getBoxCollision(m_NameBox);
	if (box_collison.empty())
		result = setPhysical(false, BITMASK_COLLAPSE_PLATFORM);
	else
		result =  setPhysical(box_collison, false, BITMASK_COLLAPSE_PLATFORM);

	return result;
}

void CollapsePlatform::update(float dt)
{
	if (!m_IsAcive)
		return;

	auto fadeOut = FadeOut::create(m_Time);
	auto fadeIn = FadeIn::create(m_Time);
	auto fadeAction = Sequence::create(fadeOut, fadeIn, nullptr);
	fadeAction->retain();

	switch (m_State)
	{
	case IDE:
		m_DelaTime = 0.0f;
		break;
	case ACTION:
		m_DelaTime += dt;
		if (getSprite()->getNumberOfRunningActions() == 0)
		{
			getSprite()->runAction(fadeAction);
		}

		if (m_DelaTime >= 2)
		{
			SwitchState(COLLAPSE);
		}
		break;
	case COLLAPSE:
		m_DelaTime = 0.0f;
		getPhysicsBody()->setVelocity(Vec2(0, -50));
		break;
	case HIDE:
		break;
	default:
		break;
	}
}

void CollapsePlatform::SetTimeMove(long time)
{
	m_Time = time;
}

void CollapsePlatform::SetRange(Vec2 range)
{
	m_Range = range;
}

void CollapsePlatform::SetActive(bool state)
{
	m_IsAcive = state;
}
