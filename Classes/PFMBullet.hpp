//
//  PFMBullet.hpp
//  PlaneFightMaker
//
//  Created by ocean on 2/10/16.
//
//

#ifndef PFMBullet_hpp
#define PFMBullet_hpp

#include "PFMSprite.hpp"
class PFMBulletComponent;
class PFMBullet:public PFMSprite
{
public:
    PFMBullet();
    static PFMBullet* createWithComponent(PFMBulletComponent* component);
    void setComponent(PFMBulletComponent* component);
    CREATE_FUNC(PFMBullet);
    
    virtual void update(float delta);
    void shootWithAngle(float degree);
    float shootDelay;
    float damage;
private:
    PFMBulletComponent* _component;
    float _degree;
    float _xSpeed;
    float _ySpeed;
};
#endif /* PFMBullet_hpp */
