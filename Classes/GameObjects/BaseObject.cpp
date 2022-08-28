#include "BaseObject.h"
#include "Scene/Level/MapManager.h"

BaseObject::BaseObject()
{
	_isInit = false;
	m_Layer = nullptr;
	m_Sprite = nullptr;
	m_PhysicsBody == nullptr;
	m_ID = -1;
	m_LayerIndex = 1;
}

BaseObject::~BaseObject()
{
	m_Layer = nullptr;
	m_Sprite = nullptr;
	m_PhysicsBody == nullptr;
}

bool BaseObject::Init(Layer* layer, string path, ValueMap property)
{
	float x = property.at("x").asFloat();
	float y = property.at("y").asFloat();
	int id = property.at("id").asInt();
	float width = property.at("width").asFloat();
	float height = property.at("height").asFloat();
	float rotation = property.at("rotation").asFloat();

	m_Layer = layer;
	m_Sprite = Sprite::create(path);
	if (m_Sprite == nullptr) 
	{
		CCLOG("m_Sprite is NULL can not create");
		return false;
	}

	m_Sprite->setAnchorPoint(Vec2(0, 0));
	m_Sprite->setPosition(Vec2(x, y + height));
	m_Sprite->setScaleX(width / m_Sprite->getContentSize().width);
	m_Sprite->setScaleY(height / m_Sprite->getContentSize().height);
	m_Sprite->setRotation(rotation);
	m_ID = id;
	_isInit = true;
	layer->addChild(m_Sprite, m_LayerIndex);

	return true;
}

bool BaseObject::setPhysical(bool isDynamic, int bitmask, float mass)
{
	if (m_Sprite == nullptr)
		return false;

	m_PhysicsBody = PhysicsBody::createBox(m_Sprite->getContentSize(), PhysicsMaterial(1.0f, 0.0f, 1.0f));
	if (m_PhysicsBody == nullptr)
		return false;

	m_PhysicsBody->setMass(mass);
	m_PhysicsBody->setDynamic(isDynamic);
	m_PhysicsBody->setCollisionBitmask(bitmask);
	m_PhysicsBody->setRotationEnable(false);
	m_PhysicsBody->setContactTestBitmask(true);
	m_Sprite->setPhysicsBody(m_PhysicsBody);

	setIndex();

	return true;
}

bool BaseObject::setPhysical(ValueMap box_collison, bool isDynamic, int bitmask, float mass)
{
	float x = box_collison.at("x").asFloat();
	float y = box_collison.at("y").asFloat();
	int id = box_collison.at("id").asInt();
	float width = box_collison.at("width").asFloat();
	float height = box_collison.at("height").asFloat();

	if (m_Sprite == nullptr)
		return false;

	Vec2 vec(x, y);
	m_size = Size(width, height);
	RotationBox(m_Sprite->getRotation(), m_size, vec);

	m_PhysicsBody = PhysicsBody::createBox(m_size, PhysicsMaterial(1.0f, 0.0f, 1.0f));
	if (m_PhysicsBody == nullptr)
		return false;

	m_PhysicsBody->setPositionOffset(vec);
	m_PhysicsBody->setMass(mass);
	m_PhysicsBody->setDynamic(isDynamic);
	m_PhysicsBody->setCollisionBitmask(bitmask);
	m_PhysicsBody->setRotationEnable(false);
	m_PhysicsBody->setContactTestBitmask(true);
	m_Sprite->setPhysicsBody(m_PhysicsBody);

	setIndex();

	return true;
}

void BaseObject::update(float dt)
{
}

void BaseObject::setIndex()
{
	vector<BaseObject*> &m_Objects = MapManager::getInstance()->getObjects();
	m_PhysicsBody->setGroup(m_Objects.size());
	m_Objects.push_back(this);
}

void BaseObject::setID(int ID)
{
	m_ID = ID;
}

int BaseObject::getID()
{
	return m_ID;
}

int BaseObject::getIndex()
{
	return m_PhysicsBody->getGroup();
}

bool BaseObject::setPosition(Vec2 pos)
{
	if (m_Sprite == nullptr)
		return false;

	m_Sprite->setPosition(pos);
	return true;
}

void BaseObject::setScale(float scale)
{
	m_Sprite->setScale(scale);
}

void BaseObject::setFlippedX(bool isFilpped)
{
	m_Sprite->setFlippedX(isFilpped);
}

void BaseObject::setFlippedY(bool isFilpped)
{
	m_Sprite->setFlippedY(isFilpped);
}

bool BaseObject::isInit()
{
	return _isInit;
}

void BaseObject::setIsInit(bool value)
{
	_isInit = value;
}

void BaseObject::setLayerIndex(float index)
{
	m_LayerIndex = index;
}

Vec2 BaseObject::getPosition()
{
	return m_Sprite->getPosition();
}

Sprite* BaseObject::getSprite()
{
	return m_Sprite;
}

Size BaseObject::getContentSize()
{
	return m_Sprite->getContentSize();
}

PhysicsBody* BaseObject::getPhysicsBody()
{
	return m_PhysicsBody;
}

Vec2 BaseObject::getPositionOffsetBox()
{
	return m_PhysicsBody->getPositionOffset();
}

Size BaseObject::geSizeBox()
{
	return m_size;
}

void BaseObject::TranlationCoodinatesTmxToCocos(Size &size, Vec2 &vec)
{
	vec.x = vec.x - (m_Sprite->getContentSize().width - size.width) / 2;
	vec.y = -(SCREEN_HEIGHT - (vec.y + size.height)) + (m_Sprite->getContentSize().height - size.height) / 2;
}

void BaseObject::RotationBox(float rotation, Size &size, Vec2 &vec)
{
	if (rotation == 0)
	{
		TranlationCoodinatesTmxToCocos(size, vec);
	}
	else if (abs(rotation) == 90.0f)
	{
		TranlationCoodinatesTmxToCocos(size, vec);
		swap(vec.x, vec.y);
		swap(size.width, size.height);
	}
	else if (abs(rotation) == 180.0f)
	{
		TranlationCoodinatesTmxToCocos(size, vec);
		vec.x = -vec.x;
		vec.y = -vec.y;
	}
	else if (abs(rotation) == 270.0f)
	{
		TranlationCoodinatesTmxToCocos(size, vec);
		swap(vec.x, vec.y);
		swap(size.width, size.height);
		vec.x = -vec.x;
		vec.y = -vec.y;
	}
}

ValueMap BaseObject::getBoxCollision(string name_box)
{
	return MapManager::getInstance()->GetBoxCollision(name_box);
}