//
//  PFMBulletComponent.hpp
//  PlaneFightMaker
//
//  Created by ocean on 2/10/16.
//
//

#ifndef PFMBulletComponent_hpp
#define PFMBulletComponent_hpp

#include "PFMSpriteComponent.hpp"

class PFMBulletComponent : public PFMSpriteComponent
{
public:
    double speed;
    double damage;
public:
    PFMBulletComponent();
    virtual void setValue(rapidjson::GenericValue<rapidjson::UTF8<>> &value,std::string key);
    virtual PFMComponent* copy();
};
#endif /* PFMBulletComponent_hpp */
