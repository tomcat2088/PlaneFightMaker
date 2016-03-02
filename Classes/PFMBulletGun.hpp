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
#include "PFMBullet.hpp"

class PFMBulletGunComponent;
class PFMBulletGun:public cocos2d::Node
{
public:
    PFMBulletGun();
    ~PFMBulletGun();
    static PFMBulletGun* createWithComponent(PFMBulletGunComponent* component);
    void setComponent(PFMBulletGunComponent* component);
    CREATE_FUNC(PFMBulletGun);
    virtual void update(float delta);
    void shoot();
    bool isAutoShoot;
    bool isHostByPlayer;
    //for script
    cocos2d::Vector<PFMBullet*> script_preparedBullets;
    void script_beginShoot();
    void script_shootWithAngle(float degree,float delay);
    void script_endShoot();
    static void registerToScript();
    
private:
    PFMBulletGunComponent* _component;
    float notShootTimeSum;
    void configBulletPhysicsBody(PFMBullet* bullet);
};
#endif /* PFMBulletGun_hpp */
