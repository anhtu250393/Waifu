#pragma once
#include "GameObjects/BaseObject.h"

class AnimationObject : public BaseObject
{
public:
	AnimationObject();
	virtual ~AnimationObject();
	virtual void update(float dt);
	void SwitchState(int state);
	int GetCurrentState();

protected:
	bool AddAnimation(string path, int num_Sprite, int index, int from = 1);
	virtual bool RunAction(int action);

	int m_MaxACtion;
	int m_NextState;
	int m_CurrentSate;
	vector<Action*> m_Animation;
private:
	bool isActive = false;
	Rect m_rec;
};