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

//for script
void PFMBulletGun::script_beginShoot()
{
    
}

void PFMBulletGun::script_shootWithAngle(float degree)
{
    PFMBullet* bullet = PFMBullet::createWithComponent(_component->getBulletComponent());
    Vec2 position = convertToWorldSpace(Vec2(0,0));
    bullet->setPosition(position);
    bullet->shootWithAngle(_component->angle);
    
    script_preparedBullets.push_back(bullet);
}

void PFMBulletGun::script_endShoot()
{
    for(int i=0;i<script_preparedBullets.size();i++)
    {
        GameSession::currentSession()->rootNode->addChild(script_preparedBullets[i]);
    }
    
    script_preparedBullets.clear();
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