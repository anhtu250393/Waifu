#pragma once
#include "Config.h"
#include "GameObjects/MovingObjects/MainCharacter.h"

class CustomControl
{
public:
	enum _TouchEventType
	{
		BEGAN,
		MOVED,
		ENDED,
		CANCELED
	};

	static CustomControl* getInstance();

	bool isDirectLeft();
	void setDirecLeft(bool status);

	bool isDirectRight();
	void setDirecRight(bool status);

	bool isTap();
	void setIsTap(bool status);

	bool isMutiTap();
	void setIsMutiTap(bool status);

	void ResetDirect();

	bool isSwipeLeft();
	void setIsSwipeLeft();

	bool isSwipeRight();
	void setIsSwipeRight();

	bool isSwipeUp();
	void setIsSwipeUp();

	bool isSwipeDown();
	void setIsSwipeDown();

	void Update(const vector<Touch*>& Input, _TouchEventType touchPhase);
	void Caculate_distance(const vector<Touch*>& Input);
	void Caculate_direct(const vector<Touch*>& Input, _TouchEventType phase);
	void Reset();
	void ResetAll();

private:
	CustomControl();
	~CustomControl();

	bool m_isTap;
	bool m_isMutiTap;
	bool m_isDirectLeft;
	bool m_isDirectRight;
	bool m_isSwipeLeft;
	bool m_isSwipeRight;
	bool m_isSwipeUp;
	bool m_isSwipeDown;
	static CustomControl* sInstance;
};

