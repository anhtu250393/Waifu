#pragma once
#include "GameObjects/AnimationObjects/AnimationObject.h"

class Goal : public AnimationObject
{
public:
	Goal();
	~Goal();

	virtual bool Init(Layer* layer, ValueMap value);

	virtual void update(float dt);
	void Active();
	void setNextLevel(string levelPath) { m_nextLevel = levelPath; }
protected:

private:
	string m_nextLevel = "";
};