#pragma once
#include "base/ccConfig.h"
#if (CC_PLATFORM == CC_PLATFORM_ANDROID || CC_PLATFORM == CC_PLATFORM_MAC_IOS || CC_PLATFORM == CC_PLATFORM_MAC_OSX || CC_PLATFORM == CC_PLATFORM_WINDOWS)
#include <type_traits>
#include "cocos/scripting/js-bindings/jswrapper/SeApi.h"
#include "cocos/scripting/js-bindings/manual/jsb_conversions.hpp"
#include "cocos/network/CCDownloader.h"

extern se::Object* __jsb_cocos2d_network_DownloadTask_proto;
extern se::Class* __jsb_cocos2d_network_DownloadTask_class;

bool js_register_cocos2d_network_DownloadTask(se::Object* obj);
bool register_all_network(se::Object* obj);

JSB_REGISTER_OBJECT_TYPE(cocos2d::network::DownloadTask);
SE_DECLARE_FUNC(js_network_DownloadTask_DownloadTask);

extern se::Object* __jsb_cocos2d_network_DownloaderHints_proto;
extern se::Class* __jsb_cocos2d_network_DownloaderHints_class;

bool js_register_cocos2d_network_DownloaderHints(se::Object* obj);
bool register_all_network(se::Object* obj);

template<>
bool SEVALUE_TO_NATIVE(const se::Value &, cocos2d::network::DownloaderHints *, se::Object *ctx);
JSB_REGISTER_OBJECT_TYPE(cocos2d::network::DownloaderHints);

extern se::Object* __jsb_cocos2d_network_Downloader_proto;
extern se::Class* __jsb_cocos2d_network_Downloader_class;

bool js_register_cocos2d_network_Downloader(se::Object* obj);
bool register_all_network(se::Object* obj);

JSB_REGISTER_OBJECT_TYPE(cocos2d::network::Downloader);
SE_DECLARE_FUNC(js_network_Downloader_setOnTaskProgress);
SE_DECLARE_FUNC(js_network_Downloader_Downloader);

#endif //#if (CC_PLATFORM == CC_PLATFORM_ANDROID || CC_PLATFORM == CC_PLATFORM_MAC_IOS || CC_PLATFORM == CC_PLATFORM_MAC_OSX || CC_PLATFORM == CC_PLATFORM_WINDOWS)
