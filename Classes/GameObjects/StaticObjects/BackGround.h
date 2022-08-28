#pragma once
#include "GameObjects/BaseObject.h"
#include "GameObjects/MovingObjects/MainCharacter.h"

class BackGround : public BaseObject
{
public:

	enum STATUS
	{
		COLLECTIBLE,
		END
	};

	BackGround();
	~BackGround();

	bool Init(Layer* layer);
	void update(float dt);
	void UpdateLight(int step);

protected:

private:
	LightEffect *m_effect;
	EffectSprite* m_Background;
	Sprite* m_SubBackground;
	int m_intensity;
	STATUS m_Status;
	
};

