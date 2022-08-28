#pragma once
#include "GameObjects/DynamicObjects/DynamicObject.h"

class Collectible : public DynamicObject
{
public:
	Collectible();
	~Collectible();

	virtual bool Init(Layer* layer, ValueMap value);
	virtual void update(float dt);

protected:
	float m_Time;
	Vec2 m_Range;

private:
	int flip;
};

