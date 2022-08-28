#pragma once

#include "Config.h"
#include "Scene/Level/MapManager.h"
#include "Scene/Popup/PausePopup.h"
#include "Scene/Menu/MSelectLevelScene.h"
#include "Core/Control/SneakyButton.h"
#include "Core/Control/SneakyButtonSkinnedBase.h"
#include "Core/Control/SneakyJoystickSkinnedBase.h"


class InGameScene : public Layer
{
public:
	static Scene* createScene();

	bool init();
	void update(float dt);

	CREATE_FUNC(InGameScene);

private:
	SneakyJoystick *leftJoystick;
	cocos2d::ui::Button* jumpBtn;
	cocos2d::ui::Button* hideBtn;
	void addListener();
	void updateReady_dg(float delta);
	void CreateHud();
#if defined(CONTROLLER)
	void createController();
#endif
	void playerJump(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void playerHide(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	//physical coliision
	bool onContactBegin(PhysicsContact& contact);
	bool onContactStay(PhysicsContact& contact, PhysicsContactPreSolve& solve);
	bool onContactExit(PhysicsContact& contact);

#if defined (ANDROID)
	//touch android event
	void onTouchBegan(const vector<Touch*>& touch, Event  *event);
	void onTouchMoved(const vector<Touch*>& touch, Event  *event);
	void onTouchEnded(const vector<Touch*>& touch, Event  *event);
	void onTouchesCancelled(const vector<Touch*>& touch, Event  *event);
#else
	//keyboard event
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
#endif
	static Scene* m_scene;
	Node* mControllerLayer;
	SneakyJoystickSkinnedBase* joystickBase;
};