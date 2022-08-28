#pragma once
#include "GameObjects/BaseObject.h"

class Pedestal : public BaseObject
{
public:
	Pedestal();
	~Pedestal();

	bool Init(Layer* layer, ValueMap property);
};

