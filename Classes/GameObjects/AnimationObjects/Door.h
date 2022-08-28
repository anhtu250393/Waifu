#pragma once
#include "GameObjects/AnimationObjects/AnimationObject.h"

class Door : public AnimationObject
{
public:
	Door();
	~Door();

	virtual bool Init(Layer* layer, ValueMap property, ValueMap box_collison);
	virtual void update(float dt);

	void SetCollision(bool status);
	bool IsActive();
protected:

private:
	float m_DelaTime;
	bool m_Collision;
};

