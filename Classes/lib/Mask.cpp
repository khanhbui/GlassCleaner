#include "Mask.h"
USING_NS_CC;

Mask* Mask::create() {
    Mask* ret = new Mask();
    return ret;
}

Mask* Mask::create(cocos2d::Sprite* object, cocos2d::Sprite* mask) {
    Mask* ret = new Mask();
    ret->initWithObject(object, mask);
    
    return ret;
}

bool Mask::initWithObject(cocos2d::Sprite *object, cocos2d::Sprite *mask) {
    CCAssert(object != NULL, "Invalid sprite for object");
    CCAssert(mask != NULL, "Invalid sprite for mask");
    
    object->retain();
    objectSprite_ = object;
    
    mask->retain();
    maskSprite_ = mask;
        
    // Set up the burn sprite that will "knock out" parts of the darkness layer depending on the alpha value of the pixels in the image.
    maskSprite_->setBlendFunc((BlendFunc){ GL_ONE, GL_ZERO });
    objectSprite_->setBlendFunc((BlendFunc){ GL_DST_ALPHA, GL_ZERO });
        
    // Get window size, we want masking over entire screen don't we?
    Size size = Director::getInstance()->getWinSize();
    
    // Create point with middle of screen
    Point screenMid = Point(size.width * 0.5f, size.height * 0.5f);
    
    // Create the rendureTextures for the mask
    masked = CCRenderTexture::create(size.width, size.height);
    
    // Set render textures at middle of screen
    masked->setPosition(screenMid);
    
    // Add the masked object to the screen
    this->addChild(masked);
    
    return true;
}

void Mask::maskWithClear(float r, float g, float b, float a){
    masked->beginWithClear(r, g, b, a);
    maskSprite_->visit();
    objectSprite_->visit();
    masked->end();
}

Mask::~Mask() {
}