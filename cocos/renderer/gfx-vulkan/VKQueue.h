#ifndef CC_GFXCCVK_CCVK_QUEUE_H_
#define CC_GFXCCVK_CCVK_QUEUE_H_

NS_CC_BEGIN

class CC_VULKAN_API CCVKQueue : public GFXQueue {
 public:
  CCVKQueue(GFXDevice* device);
  ~CCVKQueue();

  friend class CCVKDevice;
  
 public:
  bool initialize(const GFXQueueInfo& info);
  void destroy();
  void submit(const std::vector<GFXCommandBuffer*>& cmd_buffs);
  
  CC_INLINE bool isAsync() const { return _isAsync; }
  
 private:
  bool _isAsync = false;
  uint _numDrawCalls = 0;
  uint _numInstances = 0;
  uint _numTriangles = 0;
};

NS_CC_END

#endif
