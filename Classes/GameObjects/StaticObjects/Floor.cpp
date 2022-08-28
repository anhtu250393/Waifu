#include "Floor.h"

Floor::Floor()
{
	BaseObject();
}

Floor::~Floor()
{

}

bool Floor::Init(Layer * layer, ValueMap property, ValueMap box_collison)
{
	bool result;
	
	result = BaseObject::Init(layer, "Image/Pyhsical/Floor.png", property);

	if (box_collison.empty())
		result = setPhysical(false, BITMASK_FLOOR);
	else
		result= setPhysical(box_collison, false, BITMASK_FLOOR);

	return result;
}
