#pragma once

enum class b2ObjectType
{
    CONTACT,
    CIRCLE_SHAPE,
    EDGE_SHAPE,
    POLYGON_SHAPE,
    CHAIN_SHAPE,
    FIXTURE,
    JOIN,
    BODY
};

typedef void (*b2ObjectDestroyNotifer)(void*, b2ObjectType, const char*);

void b2SetObjectDestroyNotifier(b2ObjectDestroyNotifer notifier);
void b2NotifyObjectDestroyed(void* obj, b2ObjectType type, const char* typeName);
