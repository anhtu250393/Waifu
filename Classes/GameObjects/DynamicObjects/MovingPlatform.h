#pragma once
#include "GameObjects/DynamicObjects/DynamicObject.h"

class MovingPlatform : public DynamicObject
{
public:

	MovingPlatform();
	~MovingPlatform();
	virtual bool Init(Layer* layer, ValueMap property);
	void update(float dt);
	void Calculator();

	void SetTimeMove(long time);
	void SetRange(Vec2 range);
	void SetConlision(bool status);
	void SwitchActive();
	Vec2 GetDelta();

protected:
	bool m_IsAcive;
	float m_Time;
	Vec2 m_Range;
	Vec2 m_Pos;
	Vec2 m_Delta;

private:
	int flip;
	float m_DelaTime;
	bool m_Collision;
};


