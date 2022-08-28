#pragma once

#include "Config.h"

class Popup : public Node
{
public:
	CREATE_FUNC(Popup);

	virtual bool init();

	void onExit();
	void disappear();
	void appear(Node* node);
	void setTitlePopup(string _titlePopup);

protected:
	Layer *m_popupLayer;
	Node *m_currentNode;

	Sprite* m_backGround;
private:
};

