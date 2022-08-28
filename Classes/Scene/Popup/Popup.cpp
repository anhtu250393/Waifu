#include "Scene/Popup/Popup.h"

bool Popup::init()
{
	if (!Node::init())
	{
		return false;
	}

	Size m_visibleSize = Director::getInstance()->getVisibleSize();
	Point m_origin = Director::getInstance()->getVisibleOrigin();

	m_popupLayer = Layer::create();
	m_popupLayer->setAnchorPoint(Vec2(0.5, 0.5));
	m_popupLayer->setPosition(Vec2(m_visibleSize.width / 2, m_visibleSize.height / 2));
	addChild(m_popupLayer);

	m_backGround = Sprite::create("Image/Back.png");
	m_backGround->setAnchorPoint(Vec2(0.5, 0.5));
	m_backGround->setPosition(Vec2::ZERO);
	m_backGround->setScaleX(0.5);
	m_backGround->setScaleY(0.9);
	m_backGround->setOpacity(170);
	m_popupLayer->addChild(m_backGround);

	setVisible(false);

	return true;
}

void Popup::disappear()
{
	m_currentNode->onEnter();
	m_currentNode = nullptr;
	Director::getInstance()->resume();
	Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(1);
	setVisible(false);
}

void Popup::appear(Node* node)
{
	m_currentNode = node;
	m_currentNode->onExit();
	Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(0);
	Director::getInstance()->pause();
	setVisible(true);
}

void Popup::setTitlePopup(string titlePopup)
{
	auto title = Label::createWithTTF(titlePopup, "fonts/Marker Felt.ttf", 50);

	title->setPosition(Vec2(m_backGround->getPosition().x, m_backGround->getPosition().y + 200));
	title->setScale(1.5f);
	m_popupLayer->addChild(title);
}

void Popup::onExit()
{
	Node::onExit();
}