#pragma once

NS_CC_BEGIN

enum class CCMTLCmdType : uint8_t
{
    BEGIN_RENDER_PASS,
    END_RENDER_PASS,
    BIND_STATES,
    DRAW,
    UPDATE_BUFFER,
    COPY_BUFFER_TO_TEXTURE,
    COUNT
};

class CCMTLCmd : public Object
{
public:
    CCMTLCmdType type;
    uint refCount = 0;
    
    CCMTLCmd(CCMTLCmdType _type) : type(_type) {};
    virtual ~CCMTLCmd() = default;
    
    virtual void clear() = 0;
};

class CCMTLCmdBeginRenderPass : public CCMTLCmd
{
public:
    GFXRect renderRect;
    GFXClearFlags clearFlags = GFXClearFlags::NONE;
    uint numOfClearColor = 0;
    GFXColor clearColors[GFX_MAX_ATTACHMENTS];
    float clearDepth = 1.f;
    int clearStencil = 0;
    
    CCMTLCmdBeginRenderPass() : CCMTLCmd(CCMTLCmdType::BEGIN_RENDER_PASS) {}
    
    virtual void clear() override
    {
        numOfClearColor = 0;
    }
};

NS_CC_END
