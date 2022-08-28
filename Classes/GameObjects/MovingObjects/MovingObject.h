#pragma once
#include "Config.h"
#include "GameObjects/BaseObject.h"

class MovingObject : public BaseObject
{
public:
	MovingObject();
	virtual ~MovingObject();
	virtual bool onContactBegin(PhysicsBody* body);
	virtual bool onContactStay(PhysicsBody* body);
	virtual bool onContactExit(PhysicsBody* body);

	int GetCurrentState();
	Vec2 getVelocity();
	void SwitchState(int nextState);

protected:

	bool AddAnimation(string path, int num_Sprite, int index, int from = 1);
	bool RunAction();
	bool RunRepeatAction();
	bool RunActionNext(int nextState);
	bool IsOutAbove(BaseObject* object);

	void setVelocity(Vec2 vec);

	int m_CurrentState;
	int m_NextState;
	int m_MaxACtion;
	float m_delaytime;
	vector<Action*> m_Animation;
	Rect m_rec;

private:
};

