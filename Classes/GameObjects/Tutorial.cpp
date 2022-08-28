#include "Tutorial.h"

Tutorial::Tutorial()
{
}

Tutorial::~Tutorial()
{
}

bool Tutorial::Init(Layer * layer, string path)
{
	Sprite* sprite = Sprite::create(path);
	if (sprite == nullptr) 
	{
		return false;
	}

	sprite->setAnchorPoint(Vec2(0, 0));
	sprite->setPosition(Vec2(0, 0));
	sprite->setScaleX(SCREEN_WIDTH / sprite->getContentSize().width);
	sprite->setScaleY(SCREEN_HEIGHT / sprite->getContentSize().height);

	layer->addChild(sprite, 3);

	return true;
}
