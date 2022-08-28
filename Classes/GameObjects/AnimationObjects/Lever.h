#pragma once
#include "GameObjects/AnimationObjects/AnimationObject.h"

class Lever : public AnimationObject
{
public:

	Lever();
	~Lever();

	virtual bool Init(Layer* layer, ValueMap property, ValueMap box_collison, BaseObject* target = NULL);
	virtual void update(float dt);

	void SetConlision(bool state);
	bool SetActive();

protected:
	bool m_Collision;
	float m_DelaTime;
private:

	BaseObject* m_target;
};

