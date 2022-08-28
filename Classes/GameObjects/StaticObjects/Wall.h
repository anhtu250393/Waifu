#pragma once
#include "GameObjects/BaseObject.h"

class Wall : public BaseObject
{
public:
	Wall();
	~Wall();

	bool Init(Layer* layer, ValueMap value);
};

