#pragma once

#include "Popup.h"

class PausePopup : public Popup
{
public:
	CREATE_FUNC(PausePopup);

	bool init();
	virtual void onExit();
	void GoToMainMenu();
	void ResetGame();
};