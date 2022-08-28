#pragma once
#include "GameObjects/DynamicObjects/DynamicObject.h"

class CollapsePlatform : public DynamicObject
{
public:

	CollapsePlatform();
	~CollapsePlatform();
	virtual bool Init(Layer* layer, ValueMap property);
	void update(float dt);

	void SetTimeMove(long time);
	void SetRange(Vec2 range);
	void SetActive(bool state);

protected:
	bool m_IsAcive;
	float m_Time;
	float m_DelaTime;
	Vec2 m_Range;

private:
	int flip;
};

