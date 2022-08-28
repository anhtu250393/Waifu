#pragma once
#include "GameObjects/BaseObject.h"

class Floor : public BaseObject
{
public:
	Floor();
	~Floor();

	bool Init(Layer* layer, ValueMap property, ValueMap box_collison);
};

