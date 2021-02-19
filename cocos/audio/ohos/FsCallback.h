#pragma once

#include <cstdint>

namespace cc {
void *ohos_open(const char *path, void *user);

size_t ohos_read(void *ptr, size_t size, size_t nmemb, void *datasource);

int ohos_seek(void *datasource, long offset, int whence);

int ohos_close(void *datasource);

long ohos_tell(void *datasource);

void *ohos_open_all(const char *path, void *user);

size_t ohos_read_all(void *ptr, size_t size, size_t nmemb, void *datasource);

int ohos_seek_all(void *datasource, long offset, int whence);

int ohos_close_all(void *datasource);

long ohos_tell_all(void *datasource);
} // namespace cc