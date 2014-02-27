#include "Mask.h"
USING_NS_CC;

Mask* Mask::create() {
    Mask* ret = new Mask();
    return ret;
}

Mask* Mask::create(cocos2d::Node* object, cocos2d::Sprite* mask) {
    Mask* ret = new Mask();
    ret->initWithObject(object, mask);
    
    return ret;
}

bool Mask::initWithObject(cocos2d::Node *object, cocos2d::Sprite *mask) {
    CCAssert(object != NULL, "Invalid sprite for object");
    CCAssert(mask != NULL, "Invalid sprite for mask");
    
    object->retain();
    objectSprite_ = object;
    
    mask->retain();
    maskSprite_ = mask;
        
    // Set up the burn sprite that will "knock out" parts of the darkness layer depending on the alpha value of the pixels in the image.
    maskSprite_->setBlendFunc((BlendFunc){ GL_ZERO, GL_ONE_MINUS_SRC_ALPHA } );
        
    // Get window size, we want masking over entire screen don't we?
    Size size = Director::getInstance()->getWinSize();
    
    // Create point with middle of screen
    Point screenMid = Point(size.width * 0.5f, size.height * 0.5f);
    
    // Create the rendureTextures for the mask
    masked = CCRenderTexture::create(size.width, size.height);
    masked->retain();
    masked->getSprite()->setBlendFunc((BlendFunc) { GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA });
    
    // Set render textures at middle of screen
    masked->setPosition(screenMid);
    
    // Add the masked object to the screen
    this->addChild(masked);
    
    return true;
}

void Mask::mask()
{
	this->maskWithoutClear();
}

void Mask::maskWithClear(float r, float g, float b, float a){
    masked->begin(); //beginWithClear(r, g, b, a);
	// Limit drawing to the alpha channel
    objectSprite_->visit();
	glColorMask(0.0f, 0.0f, 0.0f, 1.0f);
    // Draw mask
    maskSprite_->visit();
    
    // Reset color mask
    glColorMask(1.0f, 1.0f, 1.0f, 1.0f);
    
    masked->end();
}


void Mask::maskWithoutClear()
{
	masked->begin();	
    
    objectSprite_->visit();
	// Limit drawing to the alpha channel
	glColorMask(0.0f, 0.0f, 0.0f, 1.0f);
    
    // Draw mask
    maskSprite_->visit();
    
    // Reset color mask
    glColorMask(1.0f, 1.0f, 1.0f, 1.0f);
    
    masked->end();
}

void Mask::reDrawMask()
{
	//presume object is already drawed in a previous frame 
    masked->begin();
	// Limit drawing to the alpha channel
	glColorMask(0.0f, 0.0f, 0.0f, 1.0f);
    
    // Draw mask
    maskSprite_->visit();
    
    // Reset color mask
    glColorMask(1.0f, 1.0f, 1.0f, 1.0f);
    
    masked->end();
}

void Mask::setObject(cocos2d::Node *object) {
    CC_SAFE_RELEASE(objectSprite_);
    object->retain();
	objectSprite_ = object;
}


void Mask::setMask(Sprite* mask) {
    CC_SAFE_RELEASE(maskSprite_);
    mask->retain();
	maskSprite_ = mask;
    maskSprite_->setBlendFunc((BlendFunc) { GL_ZERO, GL_ONE_MINUS_SRC_ALPHA });
}

Sprite* Mask::maskSprite()
{
	return maskSprite_;
}

Mask::~Mask() {
    // CC_SAFE_FREE(masked);
    // CC_SAFE_RELEASE(maskSprite_);
    // CC_SAFE_RELEASE(objectSprite_);
}