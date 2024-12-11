#include "b2ObjectDestroyNotifier.h"

static b2ObjectDestroyNotifer __objectDestroyNotifier = nullptr;

void b2SetObjectDestroyNotifier(b2ObjectDestroyNotifer notifier)
{
    __objectDestroyNotifier = notifier;
}

void b2NotifyObjectDestroyed(void* obj, b2ObjectType type, const char* typeName)
{
    if (__objectDestroyNotifier != nullptr)
    {
        __objectDestroyNotifier(obj, type, typeName);
    }
}
