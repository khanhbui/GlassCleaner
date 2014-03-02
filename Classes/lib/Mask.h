#ifndef  __MASK__H__
#define  __MASK__H__

#include "cocos2d.h"
#include "ScriptingCore.h"

class Mask: public cocos2d::Node {
public:
    // the mask
    cocos2d::Sprite *maskSprite_;
	// the object to be masked
    cocos2d::Sprite *objectSprite_;
    // RenderTexture use for masking
    CC_SYNTHESIZE_RETAIN(cocos2d::RenderTexture*, masked, Masked);
    
    bool initWithObject(cocos2d::Sprite* object, cocos2d::Sprite* mask);
    
    void maskWithClear(float r, float g ,float b, float a);
    
    static Mask* create();
    static Mask* create(cocos2d::Sprite* object, cocos2d::Sprite* mask);
protected:
    virtual ~Mask();
};

#endif // __MASK__H__
