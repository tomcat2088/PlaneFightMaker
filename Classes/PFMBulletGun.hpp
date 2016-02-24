//
//  PFMBulletGun.hpp
//  PlaneFightMaker
//
//  Created by ocean on 2/10/16.
//
//

#ifndef PFMBulletGun_hpp
#define PFMBulletGun_hpp

#include <cocos2d.h>
class PFMBulletGunComponent;
class PFMBulletGun:public cocos2d::Node
{
public:
    PFMBulletGun();
    static PFMBulletGun* createWithComponent(PFMBulletGunComponent* component);
    void setComponent(PFMBulletGunComponent* component);
    CREATE_FUNC(PFMBulletGun);
    
    virtual void update(float delta);
    void shoot();
private:
    PFMBulletGunComponent* _component;
    float notShootTimeSum;
};
#endif /* PFMBulletGun_hpp */
