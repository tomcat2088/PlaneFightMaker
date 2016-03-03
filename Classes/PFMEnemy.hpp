//
//  PFMEnemy.hpp
//  PlaneFightMaker
//
//  Created by ocean on 2/10/16.
//
//

#ifndef PFMEnemy_hpp
#define PFMEnemy_hpp

#include <cocos2d.h>
#include "PFMScriptCoreTypes.hpp"

class PFMEnemyPreset;
class PFMEnemyMoveStrategy;
class PFMBulletGun;
class PFMEnemy : public cocos2d::Node
{
public:
    PFMEnemy();
    ~PFMEnemy();
    void setPreset(PFMEnemyPreset* preset);
    void reload();
    void update(float delta);
    cocos2d::Size getSize();
    float health;
    float totalHealth;
    
    //for script
    float xSpeed;
    float ySpeed;
    void script_setPosition(PFMScriptTypePoint position);
    float script_getPositionX();
    float script_getPositionY();
    PFMScriptTypeSize script_getSize();
    static void registerToScript();
    
    CREATE_FUNC(PFMEnemy);
private:
    PFMEnemyPreset* _preset;
    PFMBulletGun* _mainBulletGun;
    cocos2d::Vector<PFMBulletGun*> _bulletGuns;
    cocos2d::LayerColor* _healthBar;
    float gunShootTimer;
    
    bool onContactBegin(cocos2d::PhysicsContact &contact);
};
#endif /* PFMEnemy_hpp */
