#pragma once

#include "MovingObject.h"

class MainCharacter : public MovingObject
{
public:
	static MainCharacter* getInstance();

	void Init(Layer* layer, ValueMap property, ValueMap box_collison);
	virtual void update(float dt);
	virtual bool onContactBegin(PhysicsBody* body);
	virtual bool onContactStay(PhysicsBody* body);
	virtual bool onContactExit(PhysicsBody* body);
	void SetCurrentKey(EventKeyboard::KeyCode key);
	EventKeyboard::KeyCode GetCurrentKey();
	void AttachObject(BaseObject * Object);
	void DetachObject();

	bool IsHide();

private:
	MainCharacter();
	virtual ~MainCharacter();
#if defined  ANDROID || CONTROLLER 
	void HanldeAnimationTouch();
#else
	void HanldeAnimationKey();
#endif
	void MoveLeft();
	void MoveRight();
	void Jump();
	void Reset();

	static MainCharacter* sInstance;
	EventKeyboard::KeyCode m_CurrentKey;
	BaseObject *m_Object;

	int m_VelocityX;
	int m_VelocityY;

	bool canMove;
};


