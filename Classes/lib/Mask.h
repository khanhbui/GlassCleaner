#ifndef  __MASK__H__
#define  __MASK__H__

#include "cocos2d.h"
#include "ScriptingCore.h"

class Mask: public cocos2d::Node {
public:
    // the mask
    cocos2d::Sprite *maskSprite_;
	// the object to be masked
    cocos2d::Node *objectSprite_;
    // RenderTexture use for masking
    CC_SYNTHESIZE_RETAIN(cocos2d::RenderTexture*, masked, Masked);
    
    bool initWithObject(cocos2d::Node* object, cocos2d::Sprite* mask);
    
    //change the 'background object'
    void setObject(cocos2d::Node* object);
    //change the maskSprite
    void setMask(cocos2d::Sprite* mask);
    cocos2d::Sprite* maskSprite(); 
    
    void mask();
    void maskWithClear(float r, float g ,float b, float a);
    
    //useful for multiple masks in one render texture
    void maskWithoutClear();
    
    //useful for animations or touch/mouse events to create a scratch-off effect
    void reDrawMask();
    
    static Mask* create();
    static Mask* create(cocos2d::Node* object, cocos2d::Sprite* mask);
protected:
    virtual ~Mask();
};

#endif // __MASK__H__
