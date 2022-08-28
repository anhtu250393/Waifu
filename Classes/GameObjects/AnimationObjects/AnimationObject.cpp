#include "AnimationObject.h"


AnimationObject::AnimationObject()
	: BaseObject()
{
	m_rec = Rect(0, 0, 0, 0);
	m_MaxACtion = 0;
	m_NextState = m_CurrentSate = 0;
}

AnimationObject::~AnimationObject()
{
	for (int i = 0; i < m_Animation.size(); ++i)
	{
		delete m_Animation[i];
	}
	m_Animation.clear();
}

void AnimationObject::update(float dt)
{

}

bool AnimationObject::AddAnimation(string path, int num_Sprite, int index, int from)
{
	if (getSprite() == nullptr)
		return false;

	m_rec = Rect(0, 0, getContentSize().width, getContentSize().height);

	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(num_Sprite);
	for (int i = from; i < from + num_Sprite; ++i)
	{
		string m_path = path + to_string(i) + ".png";
		SpriteFrame* sprite= SpriteFrame::create(m_path.c_str(), m_rec);
		if (sprite == nullptr)
			return false;
		animFrames.pushBack(sprite);
	}

	Animation *animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
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

bool AnimationObject::RunAction(int action)
{
	if (getSprite() == nullptr)
		return false;

	getSprite()->stopAllActions();
	getSprite()->runAction(m_Animation[action]);

	return true;

}

int AnimationObject::GetCurrentState()
{
	return m_CurrentSate;
}

void AnimationObject::SwitchState(int state)
{
	m_NextState = state;
}

