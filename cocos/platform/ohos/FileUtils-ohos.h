#pragma once

#include "base/Macros.h"
#include "cocos/platform/FileUtils.h"
#include <rawfile/raw_dir.h>
#include <rawfile/raw_file.h>
#include <rawfile/resource_manager.h>

namespace cc {

class CC_DLL FileUtilsOHOS : public FileUtils {

public:
    //        FileUtilsOHOS();
    //        virtual ~FileUtilsOHOS();

    static bool initResourceManager(ResourceManager *mgr, const std::string &assetPath);

    static ResourceManager *getResourceManager();

    bool init() override;

    virtual FileUtils::Status getContents(const std::string &filename, ResizableBuffer *buffer) override;

    virtual bool isAbsolutePath(const std::string &strPath) const override;

    virtual std::string getWritablePath() const override;

private:
    virtual bool isFileExistInternal(const std::string &strFilePath) const override;

    virtual bool isDirectoryExistInternal(const std::string &dirPath) const override;

    /* weak ref, do not need release */
    static ResourceManager *_ohosResourceMgr;
    static std::string _ohosAssetPath;

    friend class FileUtils;
};

} // namespace cc