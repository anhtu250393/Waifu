#include "Wall.h"

Wall::Wall()
{
	BaseObject();
}

Wall::~Wall()
{

}

bool Wall::Init(Layer * layer, ValueMap value)
{
	bool result;

	result = BaseObject::Init(layer, "Image/Pyhsical/Wall.png", value);
	result = setPhysical(false, BITMASK_WALL);

	return result;
}