#include "CustomControl.h"
#include "GameObjects/MovingObjects/MainCharacter.h"

CustomControl* CustomControl::sInstance = nullptr;

CustomControl* CustomControl::getInstance()
{
	if (sInstance == nullptr)
	{
		sInstance = new CustomControl();
	}
	return sInstance;
}

CustomControl::CustomControl()
{
	ResetAll();
}

CustomControl::~CustomControl()
{
}

bool CustomControl::isDirectLeft()
{
	return m_isDirectLeft;
}

void CustomControl::setDirecLeft(bool status)
{
	m_isDirectLeft = status;
}

bool CustomControl::isDirectRight()
{
	return m_isDirectRight;
}

void CustomControl::setDirecRight(bool status)
{
	m_isDirectRight = status;
}

void CustomControl::ResetDirect()
{
	m_isTap = false;
	m_isDirectLeft = false;
	m_isDirectRight = false;
}

void CustomControl::setIsSwipeDown()
{
	m_isSwipeLeft = false;
	m_isSwipeRight = false;
	m_isSwipeUp = false;
	m_isSwipeDown = true;
}

bool CustomControl::isSwipeDown()
{
	return m_isSwipeDown;
}

void CustomControl::setIsSwipeUp()
{
	m_isSwipeLeft = false;
	m_isSwipeRight = false;
	m_isSwipeDown = false;
	m_isSwipeUp = true;
}

bool CustomControl::isSwipeUp()
{
	return m_isSwipeUp;
}

void CustomControl::setIsSwipeLeft()
{
	m_isSwipeRight = false;
	m_isSwipeUp = false;
	m_isSwipeDown = false;
	m_isSwipeLeft = true;
}

bool CustomControl::isSwipeLeft()
{
	return m_isSwipeLeft;
}

void CustomControl::setIsSwipeRight()
{
	m_isSwipeLeft = false;
	m_isSwipeUp = false;
	m_isSwipeDown = false;
	m_isSwipeRight = true;
}

bool CustomControl::isSwipeRight()
{
	return m_isSwipeRight;
}

void CustomControl::setIsTap(bool status)
{
	m_isTap = status;
}

bool CustomControl::isTap()
{
	return m_isTap;
}

bool CustomControl::isMutiTap()
{
	return m_isMutiTap;
}

void CustomControl::setIsMutiTap(bool status)
{
	m_isMutiTap = status;
}

void CustomControl::Update(const vector<Touch*>& Input, _TouchEventType phase)
{
	if (Input.size() > 0)
	{
		if (Input.size() > 1)
		{
			setIsMutiTap(true);
		}
		if (phase == _TouchEventType::ENDED || phase == _TouchEventType::CANCELED)
		{
			if (isMutiTap())
			{
				setIsMutiTap(false);
			}
			else
			{
				setIsTap(false);
			}
		}

		Caculate_direct(Input, phase);

		if (phase == _TouchEventType::MOVED)
		{
			Caculate_distance(Input);
		}
	}
}

void CustomControl::Caculate_direct(const vector<Touch*>& Input, _TouchEventType phase)
{
	MainCharacter *m_MainCharacte = MainCharacter::getInstance();
	if (Input[0]->getLocationInView().x > m_MainCharacte->getPosition().x + m_MainCharacte->getContentSize().width)
	{
		if (phase == _TouchEventType::BEGAN)
		{
			if (!isTap())
			{
				setDirecRight(true);
				setIsTap(true);
			}
		}
		else if (phase == _TouchEventType::ENDED || phase == _TouchEventType::CANCELED)
		{
			setDirecRight(false);
		}
	}
	else if (Input[0]->getLocationInView().x < m_MainCharacte->getPosition().x)
	{
		if (phase == _TouchEventType::BEGAN)
		{
			if (!isTap())
			{
				setDirecLeft(true);
				setIsTap(true);
			}
		}
		else if (phase == _TouchEventType::ENDED || phase == _TouchEventType::CANCELED)
		{
			setDirecLeft(false);
		}
	}
	else
	{
		setDirecRight(false);
		setDirecLeft(false);
	}
}

void CustomControl::Caculate_distance(const vector<Touch*>& Input)
{
	Vec2 m_v2SwipeDelta = Input[0]->getStartLocationInView() - Input[0]->getPreviousLocationInView();

	//Did we cross the deadzone?
	if (m_v2SwipeDelta.length() > 100)
	{
		// Which direction ?
		float x = m_v2SwipeDelta.x;
		float y = m_v2SwipeDelta.y;
		if (abs(x) > abs(y))
		{
			// Left or Right
			if (x < 0)
			{
				//setIsSwipeLeft();
			}
			else
			{
				//setIsSwipeRight();
			}
		}
		else
		{
			// Up or Down
			if (y < 0)
			{
				setIsSwipeDown();
			}
			else
			{
				setIsSwipeUp();
			}
		}
	}
}

void CustomControl::Reset()
{
	m_isSwipeLeft = false;
	m_isSwipeRight = false;
	m_isSwipeUp = false;
	m_isSwipeDown = false;
}

void CustomControl::ResetAll()
{
	m_isTap = false;
	m_isMutiTap = false;

	m_isSwipeLeft = false;
	m_isSwipeRight = false;

	m_isSwipeUp = false;
	m_isSwipeDown = false;
	m_isDirectLeft = false;
	m_isDirectRight = false;
}
