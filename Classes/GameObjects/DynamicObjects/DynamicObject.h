#pragma once
#include "config.h"
#include "GameObjects/BaseObject.h"

class DynamicObject : public BaseObject
{
public:
	DynamicObject();
	virtual ~DynamicObject();

	virtual void update(float dt);

	void SwitchState(int state);

protected:
	int m_State;
	MoveBy* m_Move;

private:

};

