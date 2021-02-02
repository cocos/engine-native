#include "cocos/platform/ohos/FileUtils-ohos.h"
#include "cocos/base/Log.h"
#include "cocos/platform/java/jni/JniHelper.h"
#include <sys/stat.h>

#define ASSETS_FOLDER_NAME "@assets/"

#ifndef JCLS_HELPER
    #define JCLS_HELPER "com/cocos/lib/CocosHelper"
#endif

namespace cc {

ResourceManager *FileUtilsOHOS::_ohosResourceMgr = {};

FileUtils *FileUtils::getInstance() {
    if (s_sharedFileUtils == nullptr) {
        s_sharedFileUtils = new FileUtilsOHOS();
        if (!s_sharedFileUtils->init()) {
            delete s_sharedFileUtils;
            s_sharedFileUtils = nullptr;
            CC_LOG_DEBUG("ERROR: Could not init CCFileUtilsAndroid");
        }
    }
    return s_sharedFileUtils;
}

//    FileUtilsOHOS::FileUtilsOHOS() {
//    }
//
//    FileUtilsOHOS::~FileUtilsOHOS() noexcept {
//    }

bool FileUtilsOHOS::init() {
    _defaultResRootPath = ASSETS_FOLDER_NAME;
    return FileUtils::init();
}

FileUtils::Status FileUtilsOHOS::getContents(const std::string &filename, ResizableBuffer *buffer) {
    return FileUtils::Status::OK;
}

bool FileUtilsOHOS::isAbsolutePath(const std::string &strPath) const {
    return !strPath.empty() && (strPath[0] == '/' || strPath.find(ASSETS_FOLDER_NAME) == 0);
}

std::string FileUtilsOHOS::getWritablePath() const {
    auto tmp = cc::JniHelper::callStaticStringMethod(JCLS_HELPER, "getWritablePath");
    if (tmp.empty())
        return "./";
    return tmp.append("/");
}

bool FileUtilsOHOS::isFileExistInternal(const std::string &strFilePath) const {
    if (strFilePath.empty()) return false;
    const auto *filePath = strFilePath.c_str();
    auto fileFound = false;
    if (strFilePath[0] == '/') { // absolute path
        struct stat info;
        return stat(filePath, &info) == 0;
    }
    // relative path
    if (strFilePath.find(_defaultResRootPath) == 0) {
        filePath += _defaultResRootPath.length();
    }

    assert(_ohosResourceMgr);

    auto rawFile = OpenRawFile(_ohosResourceMgr, filePath);
    if (rawFile != nullptr) {
        CloseRawFile(rawFile);
        return true;
    }
    return false;
}

bool FileUtilsOHOS::isDirectoryExistInternal(const std::string &dirPath) const {
    if (dirPath.empty()) return false;
    std::string dirPathMf = dirPath[dirPath.length() - 1] == '/' ? dirPath.substr(0, dirPath.length() - 1) : dirPath;

    if (dirPathMf[0] == '/') {
        struct stat st;
        return stat(dirPathMf.c_str(), &st) == 0 && S_ISDIR(st.st_mode);
    }

    if (dirPathMf.find(_defaultResRootPath) == 0) {
        dirPathMf = dirPathMf.substr(_defaultResRootPath.length(), dirPathMf.length());
    }
    assert(_ohosResourceMgr);
    auto dir = OpenRawDir(_ohosResourceMgr, dirPathMf.c_str());
    if (dir != nullptr) {
        CloseRawDir(dir);
        return true;
    }
    return false;
}

} // namespace cc