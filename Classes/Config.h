#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Box2D/Box2D.h"
#include "base/CCUserDefault.h"

// #define USE_AUDIO_ENGINE 1
#define USE_SIMPLE_AUDIO_ENGINE 1
#define CONTROLLER 1
#define PREMIUM 1

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
#endif

#if defined(PREMIUM)
#define NUMLEVEL 20 
#else
#define NUMLEVEL 5
#endif

#include "EffectSprite/LightEffect.h"
#include "EffectSprite/EffectSprite.h"
#include "EffectSprite/Effect.h"

#include <vector>
#include <map>
#include <string>
#include <cstdio>
#include <math.h>
#include <cstdarg>

using namespace std;
using namespace cocos2d::ui;
USING_NS_CC;

//define Rotate
#define ROTATE_DOWN  0
#define ROTATE_UP    180
#define ROTATE_LEFT  90
#define ROTATE_RIGHT 270
#define MOVE_SPEED 20
#define JUMP_HEIGHT 30
//man hinh ngang
static const float SCREEN_WIDTH  = 1920.0f;
static const float SCREEN_HEIGHT = 1080.0f;

//scale
static float IMAGE_SCALE = 0.3;

static float timeStep = 1 / 20.0f;
static  int velocityIterations = 24;
static int positionIterations = 12;

enum GLOBAL_TYPE
{
	NONE = 0,
	CHARACTER,
	ENEMY,
	COLLECTIBLE,
	LEVER,
	CROSSBAR,
	GOAL
};

enum BitMas {
	BITMASK_CHARACTER				= 0x0001,
	BITMASK_COLLECTIBLE				= 0x0002,
	BITMASK_LEVER					= 0x0004,
	BITMASK_DOOR					= 0x0008,
	BITMASK_GOAL					= 0x0010,
	BITMASK_FLOOR					= 0X0020,
	BITMASK_COLLAPSE_PLATFORM		= 0X0040,
	BITMASK_MOVING_PLATFORM			= 0X0080,
	BITMASK_WALL					= 0X0100,
	BITMASK_ENEMY					= 0X0200,

	BITMASK_CAN_MOVE_JUMP			= BITMASK_COLLAPSE_PLATFORM | BITMASK_FLOOR | BITMASK_MOVING_PLATFORM
};
