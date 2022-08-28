#include"Scene\Popup\ExitPopup.h"

bool ExitPopup::init()
{
	if (!Popup::init())
		return false;

	setTitlePopup("Game exit");

	Button *btnReturn = Button::create();
	btnReturn->setTitleFontName("fonts/Marker Felt.ttf");
	btnReturn->setTitleFontSize(70);
	btnReturn->setTitleText("Return");
	btnReturn->setPosition(Vec2(m_backGround->getPosition().x, m_backGround->getPosition().y));
	btnReturn->addClickEventListener([=](Ref* event) {
		Popup::disappear();
	});
	
	m_popupLayer->addChild(btnReturn);

	return true;
}