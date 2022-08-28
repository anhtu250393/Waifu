#include "MovingObject.h"

MovingObject::MovingObject()
	: BaseObject()
{
	m_rec = Rect(0, 0, 0, 0);
	m_MaxACtion = 0;
	m_CurrentState = 0;
	m_NextState = 0;
	m_delaytime = 0.3;
}

MovingObject::~MovingObject()
{
	for (int i = 0; i < m_Animation.size(); ++i)
	{
		delete m_Animation[i];
	}
	m_Animation.clear();
}

bool MovingObject::AddAnimation(string path, int num_Sprite, int index, int from)
{
	if (getSprite() == nullptr)
		return false;

	m_rec = Rect(0, 0, getContentSize().width, getContentSize().height);

	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(num_Sprite);
	for (int i = from; i < from + num_Sprite; ++i)
	{
		string m_path = path + to_string(i) + ".png";
		SpriteFrame* sprite = SpriteFrame::create(m_path.c_str(), m_rec);
		if (sprite == nullptr)
			return false;
		animFrames.pushBack(sprite);
	}
	
	float delayTime = m_delaytime / num_Sprite;

	Animation *animation = Animation::createWithSpriteFrames(animFrames, delayTime);
	if (!animation)
		return false;

	Animate* animate = Animate::create(animation);
	if (!animate)
		return false;

	Repeat *repeat = Repeat::create(animate, 1);
	if (!repeat)
		return false;

	repeat->retain();
	m_Animation[index] = repeat;

	return true;
}

bool MovingObject::RunAction()
{
	if (getSprite() == nullptr)
		return false;

	if (m_NextState != m_CurrentState)
	{
		getSprite()->stopAllActions();
		getSprite()->runAction(m_Animation[m_NextState]);
		m_CurrentState = m_NextState;
	}

	return true;
}

bool MovingObject::RunRepeatAction()
{
	if (getSprite() == nullptr)
		return false;

	if (m_NextState != m_CurrentState)
	{
		getSprite()->stopAllActions();
		getSprite()->runAction(m_Animation[m_NextState]);
		m_CurrentState = m_NextState;
	}
	else if (getSprite()->getNumberOfRunningActions() == 0)
	{
		getSprite()->runAction(m_Animation[m_CurrentState]);
	}

	return true;
}

bool MovingObject::RunActionNext(int nextState)
{
	if (getSprite() == nullptr)
		return false;

	if (m_NextState != m_CurrentState)
	{
		getSprite()->stopAllActions();
		getSprite()->runAction(m_Animation[m_NextState]);
		m_CurrentState = m_NextState;
	}
	else if (getSprite()->getNumberOfRunningActions() == 0)
	{
		SwitchState(nextState);
	}

	return true;
}

bool MovingObject::onContactBegin(PhysicsBody* body)
{
	return true;
}

bool MovingObject::onContactStay(PhysicsBody* body)
{
	return true;
}

bool MovingObject::onContactExit(PhysicsBody* body)
{
	return true;
}

int MovingObject::GetCurrentState()
{
	return m_CurrentState;
}

Vec2 MovingObject::getVelocity()
{
	return getPhysicsBody()->getVelocity();
}

void MovingObject::SwitchState(int nextState)
{
	if (m_NextState == m_CurrentState)
	{
		m_NextState = nextState;
	}
}

void MovingObject::setVelocity(Vec2 vec) 
{
	getPhysicsBody()->setVelocity(vec);
}

bool MovingObject::IsOutAbove(BaseObject* object)
{
	int y = 0;
	int _y = 0;
	int rotation = object->getSprite()->getRotation();
	if (rotation == 0)
	{
		y = getPosition().y + getPositionOffsetBox().y + (getContentSize().height - geSizeBox().height) / 2;
		_y = object->getPosition().y + object->getPositionOffsetBox().y + (object->getContentSize().height - object->geSizeBox().height) / 2;
	}
	else if (rotation == 90)
	{
		y = getPosition().y + getPositionOffsetBox().y + (getContentSize().height - geSizeBox().height) / 2;
		_y = object->getPosition().y + object->getPositionOffsetBox().y + (object->getContentSize().width - object->geSizeBox().width) / 2;
	}
	
	if (y > _y - 10)
	{
		return true;
	}
	else
	{
		return false;
	}
}

