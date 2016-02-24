//
//  PFMSpriteComponent.hpp
//  PlaneFightMaker
//
//  Created by ocean on 2/9/16.
//
//

#ifndef PFMSpriteComponent_hpp
#define PFMSpriteComponent_hpp

#include "PFMComponent.hpp"

class PFMSpriteComponent : public PFMComponent
{
public:
    std::string spriteSheetName;
    cocos2d::Size size;
    bool canCollide;
    cocos2d::Point position;
public:
    PFMSpriteComponent();
    virtual void setValue(rapidjson::GenericValue<rapidjson::UTF8<>> &value,std::string key);
    virtual PFMComponent* copy();
};
#endif /* PFMSpriteComponent_hpp */
