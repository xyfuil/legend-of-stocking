LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cri_ware_cocos2dx
LOCAL_SRC_FILES := ../../libs/android/armeabi-v7a/libcri_ware_android_LE.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/AtomUtil.cpp \
                   ../../Classes/ActionSprite.cpp \
                   ../../Classes/Bullet.cpp \
                   ../../Classes/Button.cpp \
                   ../../Classes/ContralLayer.cpp \
                   ../../Classes/Explode.cpp \
                   ../../Classes/GameLayer.cpp \
                   ../../Classes/GameScene.cpp \
                   ../../Classes/Hero.cpp \
                   ../../Classes/Robot.cpp \
                   ../../Classes/WelScene.cpp \
                   ../../Classes/WelLayer.cpp \
                   ../../Classes/LoadingScene.cpp \
                   ../../Classes/criware.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
					$(LOCAL_PATH)/../../include/android

LOCAL_LDLIBS += \
        -llog \
        -lOpenSLES \

LOCAL_SHARED_LIBRARIES := libcri_ware_cocos2dx

LOCAL_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
