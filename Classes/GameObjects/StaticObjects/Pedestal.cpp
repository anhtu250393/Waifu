#include "Pedestal.h"

Pedestal::Pedestal()
{
	BaseObject();
}

Pedestal::~Pedestal()
{

}

bool Pedestal::Init(Layer * layer, ValueMap property)
{
	int type = property.at("type").asInt();
	string m_PathImage = "Image/Pyhsical/Pedestal_" + to_string(type) + ".png";
	string m_NameBox = "Pedestal_box_" + to_string(type);
	bool result = false;

	result = BaseObject::Init(layer, m_PathImage, property);

	ValueMap box_collison = getBoxCollision(m_NameBox);
	if (box_collison.empty())
		result = setPhysical(false, BITMASK_FLOOR);
	else
		result = setPhysical(box_collison, false, BITMASK_FLOOR);

	return result;
}