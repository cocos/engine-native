
#include "cocos/bindings/jswrapper/SeApi.h"

int main(int argc, char **argv) {
    
    auto *engine = se::ScriptEngine::getInstance();
    engine->init();
    engine->start();
    return 0;
}