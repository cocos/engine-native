LOCAL_PATH := $(call my-dir)
include $(LOCAL_PATH)/../../jni/CocosApplication.mk

# Android instant apps flag
APP_CFLAGS += -DANDROID_INSTANT=1
