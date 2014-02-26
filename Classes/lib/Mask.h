#ifndef  __MASK__H__
#define  __MASK__H__

#include "cocos2d.h"
#include "ScriptingCore.h"

class Mask: public cocos2d::CCNode {
public:
    // the mask
    cocos2d::CCSprite *maskSprite_;
	// the object to be masked
    cocos2d::CCNode *objectSprite_;
    // RenderTexture use for masking
    CC_SYNTHESIZE_RETAIN(cocos2d::CCRenderTexture*, masked, Masked);
    
    bool initWithObject(cocos2d::CCNode* object, cocos2d::CCSprite* mask);
    
    //change the 'background object'
    void setObject(cocos2d::CCNode* object);
    //change the maskSprite
    void setMask(cocos2d::CCSprite* mask);
    cocos2d::CCSprite* maskSprite(); 
    
    void mask();
    void maskWithClear(float r, float g ,float b, float a);
    
    //useful for multiple masks in one render texture
    void maskWithoutClear();
    
    //useful for animations or touch/mouse events to create a scratch-off effect
    void reDrawMask();
protected:
    virtual ~Mask();
};

#endif // __MASK__H__
