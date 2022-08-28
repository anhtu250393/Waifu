#pragma once
#include "config.h"

using namespace std;

class BaseObject
{
public:

	BaseObject();
	virtual ~BaseObject();

	virtual void update(float dt);

	int getIndex();
	int getID();
	Vec2 getPosition();
	Sprite* getSprite();
	Size getContentSize();
	PhysicsBody* getPhysicsBody();
	Vec2 getPositionOffsetBox();
	Size geSizeBox();
	bool isInit();
	void setIndex();
	void setID(int id);
	void setScale(float scale);
	void setFlippedX(bool isFilpped);
	void setFlippedY(bool isFilpped);
	void setIsInit(bool value);
protected:
	virtual bool Init(Layer* layer, string path, ValueMap property);
	virtual bool setPhysical(bool isDynamic, int type, float mass = 0);
	virtual bool setPhysical(ValueMap box_collison, bool isDynamic, int bitmask, float mass = 0);

	bool setPosition(Vec2 pos);
	
	void setLayerIndex(float index);

	ValueMap getBoxCollision(string name_box);

private:
	void TranlationCoodinatesTmxToCocos(Size &size, Vec2 &vec);
	void RotationBox(float rotation, Size &size, Vec2 &vec);

	PhysicsBody* m_PhysicsBody;
	Layer* m_Layer;
	Sprite* m_Sprite;
	Size m_size;
	int m_ID;
	int m_LayerIndex;
	bool _isInit;
};

