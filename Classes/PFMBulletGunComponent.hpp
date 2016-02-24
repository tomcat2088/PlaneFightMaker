//
//  PFMBulletGunComponent.hpp
//  PlaneFightMaker
//
//  Created by ocean on 2/10/16.
//
//

#ifndef PFMBulletGunComponent_hpp
#define PFMBulletGunComponent_hpp

#include "PFMComponent.hpp"
class PFMBulletComponent;
class PFMBulletGunComponent : public PFMComponent
{
public:
    double shootInterval;
    double angle;//in degree
    cocos2d::Point position;
    std::string bulletComponentRef;
    PFMBulletComponent* getBulletComponent();
public:
    PFMBulletGunComponent();
    virtual void setValue(rapidjson::GenericValue<rapidjson::UTF8<>> &value,std::string key);
    virtual PFMComponent* copy();
    
private:
    PFMBulletComponent* _bulletComponent;
};

#endif /* PFMBulletGunComponent_hpp */
