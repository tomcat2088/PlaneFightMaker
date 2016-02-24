//
//  PFMSprite.hpp
//  PlaneFightMaker
//
//  Created by ocean on 2/10/16.
//
//

#ifndef PFMSprite_hpp
#define PFMSprite_hpp

#include <cocos2d.h>
class PFMSpriteComponent;
class PFMSprite:public cocos2d::Sprite
{
public:
    PFMSprite();
    static PFMSprite* createWithComponent(PFMSpriteComponent* component);
    void setComponent(PFMSpriteComponent* component);
    
    CREATE_FUNC(PFMSprite);
};
#endif /* PFMSprite_hpp */
