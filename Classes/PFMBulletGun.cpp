//
//  PFMBulletGun.cpp
//  PlaneFightMaker
//
//  Created by ocean on 2/10/16.
//
//

#include "PFMBulletGun.hpp"
#include "PFMBulletGunComponent.hpp"
#include "GameSession.hpp"
#include "PFMBullet.hpp"
#include "PFMCollideMaskBits.h"
#include "PFMScriptCore.hpp"
#include <cocos2d.h>

using namespace cocos2d;

PFMBulletGun* PFMBulletGun::createWithComponent(PFMBulletGunComponent* component)
{
    PFMBulletGun* bulletGun = PFMBulletGun::create();
    bulletGun->setComponent(component);
    return bulletGun;
}

PFMBulletGun::PFMBulletGun():notShootTimeSum(0)
{
    
}

PFMBulletGun::~PFMBulletGun()
{
    printf("bullet gun is destruct");
}

void PFMBulletGun::setComponent(PFMBulletGunComponent* component)
{
    _component = component;
    setPosition(component->position);
    scheduleUpdate();
}

void PFMBulletGun::shoot()
{
    PFMBullet* bullet = PFMBullet::createWithComponent(_component->getBulletComponent());
    GameSession::currentSession()->rootNode->addChild(bullet);
    Vec2 position = convertToWorldSpace(Vec2(0,0));
    bullet->setPosition(position);
    configBulletPhysicsBody(bullet);
    bullet->shootWithAngle(_component->angle);
}

void PFMBulletGun::configBulletPhysicsBody(PFMBullet* bullet)
{
    Size size = bullet->getBoundingBox().size;
    PhysicsBody* physicsBody = bullet->getPhysicsBody();
    if(isHostByPlayer)
    {
        physicsBody->setCategoryBitmask(PFMCollideMaskBitsPlayerBullet);
        physicsBody->setContactTestBitmask(PFMCollideMaskBitsEnemy  | PFMCollideMaskBitsEnemyBullet);
        physicsBody->setTag(PFMPhysicsBodyTypePlayerBullet);
    }
    else
    {
        physicsBody->setCategoryBitmask(PFMCollideMaskBitsEnemyBullet);
        physicsBody->setContactTestBitmask(PFMCollideMaskBitsPlayer | PFMCollideMaskBitsPlayerBullet);
        physicsBody->setTag(PFMPhysicsBodyTypeEnemyBullet);
    }
}

//for script
void PFMBulletGun::script_beginShoot()
{
    
}

void PFMBulletGun::script_shootWithAngle(float degree,float delay)
{
    PFMBullet* bullet = PFMBullet::createWithComponent(_component->getBulletComponent());
    Vec2 position = convertToWorldSpace(Vec2(0,0));
    bullet->setPosition(position);
    bullet->shootDelay = delay;
    bullet->shootWithAngle(degree);
    configBulletPhysicsBody(bullet);
    
    script_preparedBullets.pushBack(bullet);
}

void PFMBulletGun::script_endShoot()
{
}

void PFMBulletGun::registerToScript()
{
    PFMScriptCore* core = PFMScriptCore::shared();
    core->lua.new_userdata<PFMBulletGun>("BulletGun",
                                     "shootWithAngle", &PFMBulletGun::script_shootWithAngle,
                                     "endShoot", &PFMBulletGun::script_endShoot,
                                     "beginShoot", &PFMBulletGun::script_beginShoot);
}

void PFMBulletGun::update(float delta)
{
    if(isAutoShoot == false)
    {
        for(int i=0;i<script_preparedBullets.size();i++)
        {
            if(script_preparedBullets.at(i)->shootDelay > 0)
            {
                script_preparedBullets.at(i)->shootDelay -= delta;
            }
            else
            {
                Vec2 position = convertToWorldSpace(Vec2(0,0));
                script_preparedBullets.at(i)->setPosition(position);
                GameSession::currentSession()->rootNode->addChild(script_preparedBullets.at(i));
                script_preparedBullets.erase(script_preparedBullets.begin()+i);
                i--;
            }
        }
        return;
    }
    notShootTimeSum+=delta;
    if(notShootTimeSum * 1000 >= _component->shootInterval)
    {
        notShootTimeSum = 0;
        shoot();
    }
}