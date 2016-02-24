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
#include <cocos2d.h>
#include "PFMScriptCore.hpp"

using namespace cocos2d;
PFMEnemy::PFMEnemy() : xSpeed(5),ySpeed(-10)
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
            addChild(PFMBulletGun::createWithComponent(bulletGunComponent));
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