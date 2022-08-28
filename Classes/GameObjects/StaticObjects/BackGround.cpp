#include "BackGround.h"
#include "Scene/Level/MapManager.h"

#define MAX_INTENSITY 3060
#define STEP_INTENSITY (MAX_INTENSITY / 255)

BackGround::BackGround()
{
	m_intensity = MAX_INTENSITY;
}

BackGround::~BackGround()
{

}

bool BackGround::Init(Layer * layer)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//add light
	m_effect = LightEffect::create();
	m_effect->retain();
	Vec3 lightPos = Vec3(0, 0, -100);
	m_effect->setLightPos(lightPos);
	m_effect->setLightCutoffRadius(1000);
	m_effect->setBrightness(5.0);

	// add background
	m_Background = EffectSprite::create("Image/BG_AP.png");
	if (m_Background)
	{
		m_Background->setEffect(m_effect, "Image/BG_AP_n.png");
		m_Background->setScaleX(SCREEN_WIDTH / m_Background->getContentSize().width);
		m_Background->setScaleY(SCREEN_HEIGHT / m_Background->getContentSize().height);
		//background->setColor(m_effect->getLightColor());
		m_Background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		layer->addChild(m_Background, 0);
	}

	m_SubBackground = Sprite::create("Image/Back.png");
	if (m_SubBackground)
	{
		m_SubBackground->setScaleX(SCREEN_WIDTH / m_SubBackground->getContentSize().width);
		m_SubBackground->setScaleY(SCREEN_HEIGHT / m_SubBackground->getContentSize().height);
		m_SubBackground->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		m_SubBackground->setOpacity(0);
		layer->addChild(m_SubBackground, 2);
	}
	setIsInit(true);
	return true;
}

void BackGround::update(float dtr)
{
	//update intensity light
	if (m_Status != BackGround::END && m_intensity >= 0)
	{
		m_effect->setLightCutoffRadius(m_intensity--);
		if (m_intensity % STEP_INTENSITY == 0 && m_SubBackground)
		{
			int opacity = 255 - m_intensity / STEP_INTENSITY;
			m_SubBackground->setOpacity(opacity);
		}
	}

	//update pos light
	MainCharacter *m_MainCharacte = MainCharacter::getInstance();
	Vec3 lightPos = Vec3(m_MainCharacte->getSprite()->getPosition().x + m_MainCharacte->getSprite()->getContentSize().width /2,
		m_MainCharacte->getSprite()->getPosition().y + m_MainCharacte->getSprite()->getContentSize().height / 2, 100);
	m_effect->setLightPos(lightPos);

	if (m_intensity < 0)
	{
		MapManager::getInstance()->ResetMap();
	}
}

void BackGround::UpdateLight(int step)
{
	if(step < 3)
		m_Status = STATUS::COLLECTIBLE;
	else if(step ==3)
		m_Status = STATUS::END;

	switch (m_Status)
	{
	case STATUS::COLLECTIBLE:
		m_intensity = m_intensity + 100;
		if (m_intensity > MAX_INTENSITY)
		{
			m_intensity = MAX_INTENSITY;
		}
		break;
	case STATUS::END:
		m_intensity = MAX_INTENSITY;
		m_SubBackground->setOpacity(255);
		break;
	default:
		break;
	}
}
