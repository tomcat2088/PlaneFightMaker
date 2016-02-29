//
//  PFMEnemy.cpp
//  PlaneFightMaker
//
//  Created by ocean on 2/10/16.
//
//

#include "PFMEnemy.hpp"
#include "PFMComponent.hpp"
#include "PFMEnemyPreset.hpp"
#include "PFMSpriteComponent.hpp"
#include "PFMSprite.hpp"
#include "PFMBulletGun.hpp"
#include "PFMBulletGunComponent.hpp"
#include "PFMScriptCore.hpp"

#include <cocos2d.h>

using namespace cocos2d;
PFMEnemy::PFMEnemy() : xSpeed(2),ySpeed(-2)
{
    scheduleUpdate();
}

void PFMEnemy::setPreset(PFMEnemyPreset* preset)
{
    _preset = preset;
    reload();
}

void PFMEnemy::reload()
{
    if(_preset == NULL)
        return;
    for(int i=0;i<_preset->components.size();i++)
    {
        PFMComponent* component = _preset->components[i];
        if(component->componentClass == "Sprite")
        {
            PFMSpriteComponent* spriteComponent = dynamic_cast<PFMSpriteComponent*>(component);
            PFMSprite* sprite = PFMSprite::createWithComponent(spriteComponent);
            sprite->setRotation(180);
            addChild(sprite);
        }
        else if(component->componentClass == "BulletGun")
        {
            PFMBulletGunComponent* bulletGunComponent = dynamic_cast<PFMBulletGunComponent*>(component);
            bulletGunComponent->angle = fabs(bulletGunComponent->angle) / bulletGunComponent->angle * 180 - bulletGunComponent->angle;
           _mainBulletGun = PFMBulletGun::createWithComponent(bulletGunComponent);
            _mainBulletGun->isAutoShoot = false;
            addChild(_mainBulletGun);
        }
//        else if([component isMemberOfClass:[AstMissleLauncherComponent class]])
//        {
//            AstMissleLauncher* missleLauncher = [[AstMissleLauncher alloc]initWithSession:self.session];
//            [self addNode:missleLauncher.rootNode];
//            [missleLauncher setComponent:(AstMissleLauncherComponent*)component];
//        }
    }
}

void PFMEnemy::update(float delta)
{
    std::string content =  FileUtils::getInstance()->getStringFromFile("xwave.lua");
    PFMScriptCore::shared()->lua.set("target", this);
    PFMScriptCore::shared()->lua.script(content);
    
    
    gunShootTimer+=delta;
    if(_mainBulletGun != NULL&& gunShootTimer > 4)
    {
        gunShootTimer = 0;
        _mainBulletGun->script_beginShoot();
        for(int i=0;i<=12;i++)
        {
            _mainBulletGun->script_shootWithAngle(i * 30 - 180,0.1 * i);
        }
        _mainBulletGun->script_endShoot();
    }
}

cocos2d::Size PFMEnemy::getSize()
{
    Vector<Node*> nodes = getChildren();
    Rect originRect = Rect::ZERO;
    for(int i=0;i<nodes.size();i++)
    {
        Node* node = nodes.at(i);
        Rect bounds = node->getBoundingBox();
        originRect.merge(bounds);
    }
    return originRect.size;
}

//for script
void PFMEnemy::script_setPosition(PFMScriptTypePoint position)
{
    setPosition(position.vec2());
}

float PFMEnemy::script_getPositionX()
{
    return getPositionX();
}

float PFMEnemy::script_getPositionY()
{
    return getPositionY();
}

PFMScriptTypeSize PFMEnemy::script_getSize()
{
    return  PFMScriptTypeSize(getSize());
}

void PFMEnemy::registerToScript()
{
    PFMScriptCore* core = PFMScriptCore::shared();
    core->lua.new_userdata<PFMEnemy>("Enemy",
                                     "getPositionX", &PFMEnemy::script_getPositionX,
                                     "getPositionY", &PFMEnemy::script_getPositionY,
                                     "setPosition", &PFMEnemy::script_setPosition,
                                     "getSize", &PFMEnemy::script_getSize,
                                     "xSpeed",&PFMEnemy::xSpeed,
                                     "ySpeed",&PFMEnemy::ySpeed);
}