#pragma once
#include "MovingObject.h"
#include "GameObjects\MovingObjects\MainCharacter.h"

class MonsterChase : public MovingObject
{
public:
	MonsterChase();
	virtual ~MonsterChase();
	void Init(Layer *layer, ValueMap property, ValueMap box_collison);
	virtual void update(float dt);
	virtual bool onContactBegin(PhysicsBody* body);
	virtual bool onContactStay(PhysicsBody* body);
	virtual bool onContactExit(PhysicsBody* body);

private:
	void Patrol();
	void Chase();
	bool IsChase();

	float x1;
	float x2;
	float m_MoveSpeed;
	MainCharacter *m_MainCharactor;
};