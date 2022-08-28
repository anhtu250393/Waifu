LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := $(LOCAL_PATH)/hellocpp/main.cpp \
                   $(LOCAL_PATH)/../../../Classes/AppDelegate.cpp \
                   $(LOCAL_PATH)/../../../Classes/Data.cpp \
                   $(LOCAL_PATH)/../../../Classes/EffectSprite/Effect.cpp \
                   $(LOCAL_PATH)/../../../Classes/EffectSprite/EffectSprite.cpp \
                   $(LOCAL_PATH)/../../../Classes/EffectSprite/LightEffect.cpp \
				   $(LOCAL_PATH)/../../../Classes/GameObjects/BaseObject.cpp \
				   $(LOCAL_PATH)/../../../Classes/GameObjects/Tutorial.cpp \
				   $(LOCAL_PATH)/../../../Classes/GameObjects/MovingObjects/MovingObject.cpp \
				   $(LOCAL_PATH)/../../../Classes/GameObjects/MovingObjects/MonsterChase.cpp \
				   $(LOCAL_PATH)/../../../Classes/GameObjects/MovingObjects/MainCharacter.cpp \
				   $(LOCAL_PATH)/../../../Classes/GameObjects/AnimationObjects/AnimationObject.cpp \
				   $(LOCAL_PATH)/../../../Classes/GameObjects/AnimationObjects/Door.cpp \
				   $(LOCAL_PATH)/../../../Classes/GameObjects/AnimationObjects/DoorExit.cpp \
				   $(LOCAL_PATH)/../../../Classes/GameObjects/AnimationObjects/Lever.cpp \
				   $(LOCAL_PATH)/../../../Classes/GameObjects/AnimationObjects/Goal.cpp \
				   $(LOCAL_PATH)/../../../Classes/GameObjects/DynamicObjects/DynamicObject.cpp \
				   $(LOCAL_PATH)/../../../Classes/GameObjects/DynamicObjects/MovingPlatform.cpp \
				   $(LOCAL_PATH)/../../../Classes/GameObjects/DynamicObjects/CollapsePlatform.cpp \
				   $(LOCAL_PATH)/../../../Classes/GameObjects/DynamicObjects/Collectible.cpp \
				   $(LOCAL_PATH)/../../../Classes/GameObjects/StaticObjects/BackGround.cpp \
				   $(LOCAL_PATH)/../../../Classes/GameObjects/StaticObjects/Pedestal.cpp \
				   $(LOCAL_PATH)/../../../Classes/GameObjects/StaticObjects/Floor.cpp \
				   $(LOCAL_PATH)/../../../Classes/GameObjects/StaticObjects/Wall.cpp \
				   $(LOCAL_PATH)/../../../Classes/Core/Control/CustomControl.cpp \
				   $(LOCAL_PATH)/../../../Classes/Core/Control/SneakyButton.cpp \
				   $(LOCAL_PATH)/../../../Classes/Core/Control/SneakyButtonSkinnedBase.cpp \
				   $(LOCAL_PATH)/../../../Classes/Core/Control/SneakyJoystick.cpp \
				   $(LOCAL_PATH)/../../../Classes/Core/Control/SneakyJoystickSkinnedBase.cpp \
                   $(LOCAL_PATH)/../../../Classes/Scene/Menu/InGameScene.cpp \
                   $(LOCAL_PATH)/../../../Classes/Scene/Menu/EndScene.cpp \
                   $(LOCAL_PATH)/../../../Classes/Scene/Menu/AboutScene.cpp \
                   $(LOCAL_PATH)/../../../Classes/Scene/Menu/MMainScene.cpp \
				   $(LOCAL_PATH)/../../../Classes/Scene/Menu/MSelectLevelScene.cpp \
				   $(LOCAL_PATH)/../../../Classes/Scene/Popup/ExitPopup.cpp \
				   $(LOCAL_PATH)/../../../Classes/Scene/Popup/PausePopup.cpp \
				   $(LOCAL_PATH)/../../../Classes/Scene/Popup/Popup.cpp \

	
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes \
					$(LOCAL_PATH)/../../../Classes/EffectSprite \
					$(LOCAL_PATH)/../../../Classes/Core/Control \
					$(LOCAL_PATH)/../../../Classes/Core \
					$(LOCAL_PATH)/../../../Classes/GameObjects \
					$(LOCAL_PATH)/../../../Classes/GameObjects/MovingObjects \
					$(LOCAL_PATH)/../../../Classes/GameObjects/DynamicObjects \
					$(LOCAL_PATH)/../../../Classes/GameObjects/AnimationObjects \
					$(LOCAL_PATH)/../../../Classes/GameObjects/StaticObjects \
					$(LOCAL_PATH)/../../../Classes/Scene/Menu \
					$(LOCAL_PATH)/../../../Classes/Scene/Popup

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cc_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module, cocos)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
