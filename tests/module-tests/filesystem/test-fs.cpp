
#include "platform/FileUtils.h"

int main(int argc, char **argv) {
    auto *fu = cc::FileUtils::getInstance();
    cc::FileUtils::destroyInstance();
    return 0;
}