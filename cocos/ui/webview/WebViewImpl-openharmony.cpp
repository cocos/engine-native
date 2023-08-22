/****************************************************************************
 Copyright (c) 2022-2023 Xiamen Yaji Software Co., Ltd.

 http://www.cocos.com

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated engine source code (the "Software"), a limited,
 worldwide, royalty-free, non-assignable, revocable and non-exclusive license
 to use Cocos Creator solely to develop games on your target platforms. You shall
 not use Cocos Creator software for developing other software or tools that's
 used for developing games. You are not granted to publish, distribute,
 sublicense, and/or sell copies of Cocos Creator.

 The software or tools in this License Agreement are licensed, not sold.
 Xiamen Yaji Software Co., Ltd. reserves all rights not expressly granted to you.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
****************************************************************************/

#include <cstdlib>
#include <unordered_map>

#include "WebView-inl.h"

#include "platform/CCFileUtils.h"
#include "platform/openharmony/napi/NapiHelper.h"
#include "scripting/js-bindings/manual/jsb_conversions.hpp"
#include "WebViewImpl-openharmony.h"

static const std::string S_DEFAULT_BASE_URL = "file:///openharmony_asset/";
static const std::string S_SD_ROOT_BASE_URL = "file://";

static std::string getFixedBaseUrl(const std::string &baseUrl) {
    std::string fixedBaseUrl;
    if (baseUrl.empty()) {
        fixedBaseUrl = S_DEFAULT_BASE_URL;
    } else if (baseUrl.find(S_SD_ROOT_BASE_URL) != std::string::npos) {
        fixedBaseUrl = baseUrl;
    } else if (baseUrl.c_str()[0] != '/') {
        if (baseUrl.find("assets/") == 0) {
            fixedBaseUrl = S_DEFAULT_BASE_URL + baseUrl.c_str()[7];
        } else {
            fixedBaseUrl = S_DEFAULT_BASE_URL + baseUrl;
        }
    } else {
        fixedBaseUrl = S_SD_ROOT_BASE_URL + baseUrl;
    }

    if (fixedBaseUrl.c_str()[fixedBaseUrl.length() - 1] != '/') {
        fixedBaseUrl += "/";
    }

    return fixedBaseUrl;
}

std::string getUrlStringByFileName(const std::string &fileName) {
    const std::string basePath(S_DEFAULT_BASE_URL);
    std::string fullPath = cocos2d::FileUtils::getInstance()->fullPathForFilename(fileName);
    const std::string assetsPath("assets/");

    std::string urlString;
    if (fullPath.find(assetsPath) != std::string::npos) {
        urlString = fullPath.replace(fullPath.find_first_of(assetsPath), assetsPath.length(),
                                     basePath);
    } else {
        urlString = fullPath;
    }

    return urlString;
}

namespace cocos2d {
static int32_t kWebViewTag = 0;
static std::unordered_map<int, WebViewImpl *> sWebViewImpls;

WebViewImpl::WebViewImpl(WebView *webView) : _viewTag(-1),
                                             _webView(webView) {
    _viewTag = kWebViewTag++;
    NapiHelper::postIntMessageToUIThread("createWebView", _viewTag);
    sWebViewImpls[_viewTag] = this;
}

WebViewImpl::~WebViewImpl() {
    destroy();
}

void WebViewImpl::destroy() {
    if (_viewTag != -1) {
        NapiHelper::postIntMessageToUIThread("removeWebView", _viewTag);
        auto iter = sWebViewImpls.find(_viewTag);
        if (iter != sWebViewImpls.end()) {
            sWebViewImpls.erase(iter);
        }
        _viewTag = -1;
    }
}

void WebViewImpl::loadData(const Data &data, const std::string &mimeType,
                           const std::string &encoding, const std::string &baseURL) {
    std::string dataString(reinterpret_cast<char *>(data.getBytes()),
                             static_cast<unsigned int>(data.getSize()));
    std::unordered_map<std::string, cocos2d::Value> vals;
    vals.insert(std::make_pair("tag", _viewTag));
    vals.insert(std::make_pair("contents", cocos2d::Value(dataString)));
    vals.insert(std::make_pair("mimeType", mimeType));
    vals.insert(std::make_pair("encoding", encoding));
    vals.insert(std::make_pair("baseUrl", baseURL));
    NapiHelper::postUnorderedMapMessageToUIThread("loadData", vals);
}

void WebViewImpl::loadHTMLString(const std::string &string, const std::string &baseURL) {
    std::unordered_map<std::string, cocos2d::Value> vals;
    vals.insert(std::make_pair("tag", _viewTag));
    vals.insert(std::make_pair("contents", cocos2d::Value(string)));
    vals.insert(std::make_pair("baseUrl", baseURL));
    NapiHelper::postUnorderedMapMessageToUIThread("loadHTMLString", vals);
}

void WebViewImpl::loadURL(const std::string &url) {
    std::unordered_map<std::string, cocos2d::Value> vals;
    vals.insert(std::make_pair("tag", _viewTag));
    vals.insert(std::make_pair("url", url));
    NapiHelper::postUnorderedMapMessageToUIThread("loadUrl", vals);
}

void WebViewImpl::loadFile(const std::string &fileName) {
    auto fullPath = getUrlStringByFileName(fileName);
    std::unordered_map<std::string, cocos2d::Value> vals;
    vals.insert(std::make_pair("tag", _viewTag));
    vals.insert(std::make_pair("url", fullPath));
    NapiHelper::postUnorderedMapMessageToUIThread("loadUrl", vals);
}

void WebViewImpl::stopLoading() {
    NapiHelper::postIntMessageToUIThread("stopLoading", _viewTag);
}

void WebViewImpl::reload() {
    NapiHelper::postIntMessageToUIThread("reload", _viewTag);
}

bool WebViewImpl::canGoBack() {
    // TODO(qgh):OpenHarmony does not support this interface.
    return true;
}

bool WebViewImpl::canGoForward() {
    // TODO(qgh):OpenHarmony does not support this interface.
    return true;
}

void WebViewImpl::goBack() {
    NapiHelper::postIntMessageToUIThread("goBack", _viewTag);
}

void WebViewImpl::goForward() {
     NapiHelper::postIntMessageToUIThread("goForward", _viewTag);
}

void WebViewImpl::setJavascriptInterfaceScheme(const std::string &scheme) {
    // TODO(qgh):OpenHarmony does not support this interface.
}

void WebViewImpl::evaluateJS(const std::string &js) {
    std::unordered_map<std::string, cocos2d::Value> vals;
    vals.insert(std::make_pair("tag", _viewTag));
    vals.insert(std::make_pair("jsContents", js));
    NapiHelper::postUnorderedMapMessageToUIThread("evaluateJS", vals);
}

void WebViewImpl::setScalesPageToFit(bool scalesPageToFit) {
    NapiHelper::postIntMessageToUIThread("setScalesPageToFit", _viewTag);
}

bool WebViewImpl::shouldStartLoading(int viewTag, const std::string &url) {
    bool allowLoad = true;
    auto it = sWebViewImpls.find(viewTag);
    if (it != sWebViewImpls.end()) {
        auto webView = it->second->_webView;
        if (webView->_onShouldStartLoading) {
            allowLoad = webView->_onShouldStartLoading(webView, url);
        }
    }
    return allowLoad;
}

void WebViewImpl::didFinishLoading(int viewTag, const std::string &url) {
    auto it = sWebViewImpls.find(viewTag);
    if (it != sWebViewImpls.end()) {
        auto webView = it->second->_webView;
        if (webView->_onDidFinishLoading) {
            webView->_onDidFinishLoading(webView, url);
        }
    }
}

void WebViewImpl::didFailLoading(int viewTag, const std::string &url) {
    auto it = sWebViewImpls.find(viewTag);
    if (it != sWebViewImpls.end()) {
        auto webView = it->second->_webView;
        if (webView->_onDidFailLoading) {
            webView->_onDidFailLoading(webView, url);
        }
    }
}

void WebViewImpl::onJsCallback(int viewTag, const std::string &message) {
    auto it = sWebViewImpls.find(viewTag);
    if (it != sWebViewImpls.end()) {
        auto webView = it->second->_webView;
        if (webView->_onJSCallback) {
            webView->_onJSCallback(webView, message);
        }
    }
}

void WebViewImpl::setVisible(bool visible) {
    std::unordered_map<std::string, cocos2d::Value> vals;
    vals.insert(std::make_pair("tag", _viewTag));
    vals.insert(std::make_pair("visible", visible));
    NapiHelper::postUnorderedMapMessageToUIThread("setVisible", vals);
}

void WebViewImpl::setFrame(float x, float y, float width, float height) {
    //cocos2d::Rect rect(x, y, width, height);
    std::unordered_map<std::string, cocos2d::Value> vals;
    vals.insert(std::make_pair("tag", _viewTag));
    vals.insert(std::make_pair("x", x));
    vals.insert(std::make_pair("y", y));
    vals.insert(std::make_pair("w", width));
    vals.insert(std::make_pair("h", height));
    NapiHelper::postUnorderedMapMessageToUIThread("setWebViewRect", vals);
}

void WebViewImpl::setBounces(bool bounces) {
    // empty function as this was mainly a fix for iOS
}

void WebViewImpl::setBackgroundTransparent(bool isTransparent) {
    // TODO(qgh):OpenHarmony is not supported at this time
}

void OpenHarmonyWebView::GetInterfaces(std::vector<napi_property_descriptor> &descriptors) {
    descriptors = {
        DECLARE_NAPI_FUNCTION("shouldStartLoading", OpenHarmonyWebView::napiShouldStartLoading),
        DECLARE_NAPI_FUNCTION("finishLoading", OpenHarmonyWebView::napiFinishLoading),
        DECLARE_NAPI_FUNCTION("failLoading", OpenHarmonyWebView::napiFailLoading),
        DECLARE_NAPI_FUNCTION("jsCallback", OpenHarmonyWebView::napiJsCallback),
    };
}

napi_value OpenHarmonyWebView::napiShouldStartLoading(napi_env env, napi_callback_info info) {
    size_t      argc = 2;
    napi_value  args[2];
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, args, nullptr, nullptr));
    
    se::ValueArray seArgs;
    seArgs.reserve(2);   
    se::internal::jsToSeArgs(argc, args, &seArgs);

    int32_t viewTag;
    seval_to_int32(seArgs[0], &viewTag);

    std::string url;
    seval_to_std_string(seArgs[1], &url);
    WebViewImpl::shouldStartLoading(viewTag, url);
    return nullptr;
}

napi_value OpenHarmonyWebView::napiFinishLoading(napi_env env, napi_callback_info info) {
    size_t      argc = 2;
    napi_value  args[2];
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, args, nullptr, nullptr));
    
    se::ValueArray seArgs;
    seArgs.reserve(2);   
    se::internal::jsToSeArgs(argc, args, &seArgs);

    int32_t viewTag;
    seval_to_int32(seArgs[0], &viewTag);

    std::string url;
    seval_to_std_string(seArgs[1], &url);
    WebViewImpl::didFinishLoading(viewTag, url);
    return nullptr;
}

napi_value OpenHarmonyWebView::napiFailLoading(napi_env env, napi_callback_info info) {
    size_t      argc = 2;
    napi_value  args[2];
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, args, nullptr, nullptr));
    
    se::ValueArray seArgs;
    seArgs.reserve(2);   
    se::internal::jsToSeArgs(argc, args, &seArgs);

    int32_t viewTag;
    seval_to_int32(seArgs[0], &viewTag);

    std::string url;
    seval_to_std_string(seArgs[1], &url);
    WebViewImpl::didFailLoading(viewTag, url);
    return nullptr;
}

napi_value OpenHarmonyWebView::napiJsCallback(napi_env env, napi_callback_info info) {
    size_t      argc = 2;
    napi_value  args[2];
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, args, nullptr, nullptr));
    
    se::ValueArray seArgs;
    seArgs.reserve(2);   
    se::internal::jsToSeArgs(argc, args, &seArgs);

    int32_t viewTag;
    seval_to_int32(seArgs[0], &viewTag);

    std::string url;
    seval_to_std_string(seArgs[1], &url);
    WebViewImpl::onJsCallback(viewTag, url);
    return nullptr;
}


} //namespace cocos2d
