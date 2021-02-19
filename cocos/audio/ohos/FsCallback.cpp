#include "cocos/audio/ohos/FsCallback.h"

#include "cocos/platform/ohos/FileUtils-ohos.h"
#include <rawfile/raw_dir.h>
#include <rawfile/raw_file.h>

namespace {
inline cc::FileUtilsOHOS *getFU() {
    return static_cast<cc::FileUtilsOHOS *>(cc::FileUtils::getInstance());
}

struct FatFd {
    union {
        FILE *fp;
        RawFile *rf;
    } file;
    void *user;
    bool isRawFile;
};
} // namespace

namespace cc {
void *ohos_open(const char *path, void *user) {
    bool isRawfile = false;
    const auto newPath = getFU()->expandPath(path, &isRawfile);
    FatFd *ret = new FatFd();
    if (isRawfile) {
        ret->file.rf = OpenRawFile(cc::FileUtilsOHOS::getResourceManager(), newPath.c_str());
    } else {
        ret->file.fp = fopen(newPath.c_str(), "rb");
    }
    ret->user = user;
    ret->isRawFile = isRawfile;
    return (void *)ret;
}

size_t ohos_read(void *ptr, size_t size, size_t nmemb, void *datasource) {
    FatFd *fatFd = (FatFd *)datasource;
    if (fatFd->isRawFile) {
        return ReadRawFile(fatFd->file.rf, ptr, size * nmemb) / size;
    } else {
        return fread(ptr, size, nmemb, fatFd->file.fp);
    }
}

int ohos_seek(void *datasource, long offset, int whence) {
    FatFd *fatFd = (FatFd *)datasource;
    if (fatFd->isRawFile) {
        return SeekRawFile(fatFd->file.rf, offset, whence);
    } else {
        return fseek(fatFd->file.fp, offset, whence);
    }
}

int ohos_close(void *datasource) {
    FatFd *fatFd = (FatFd *)datasource;
    int code = 0;
    if (fatFd->isRawFile) {
        CloseRawFile(fatFd->file.rf);
        code = 0;
    } else {
        code = fclose(fatFd->file.fp);
    }
    delete fatFd;
    return code;
}

long ohos_tell(void *datasource) {
    FatFd *fatFd = (FatFd *)datasource;
    if (fatFd->isRawFile) {
        return GetRawFileOffset(fatFd->file.rf);
    } else {
        return ftell(fatFd->file.fp);
    }
}
} // namespace cc