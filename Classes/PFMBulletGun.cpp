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
    bullet->shootWithAngle(_component->angle);
}

void PFMBulletGun::update(float delta)
{
    notShootTimeSum+=delta;
    if(notShootTimeSum * 1000 >= _component->shootInterval)
    {
        notShootTimeSum = 0;
        shoot();
    }
}