//
//  PFMPlayer.cpp
//  PlaneFightMaker
//
//  Created by ocean on 2/10/16.
//
//

#include "PFMPlayer.hpp"
#include "PFMComponent.hpp"
#include "PFMPlayerPreset.hpp"
#include "PFMSpriteComponent.hpp"
#include "PFMSprite.hpp"
#include "PFMBulletGun.hpp"
#include "PFMBulletGunComponent.hpp"
#include "PFMCollideMaskBits.h"
#include <cocos2d.h>

using namespace cocos2d;
PFMPlayer::PFMPlayer()
{
    EventListenerPhysicsContact* eventListener = EventListenerPhysicsContact::create();
    getEventDispatcher()->addEventListenerWithFixedPriority(eventListener, 100);
    eventListener->onContactBegin = [](PhysicsContact& contact){
        printf("contact here!!!!");
        return true;
    };
}

void PFMPlayer::setPreset(PFMPlayerPreset* preset)
{
    _preset = preset;
    reload();
}

void PFMPlayer::reload()
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
            Size size = sprite->getBoundingBox().size;
            PhysicsBody* physicsBody = PhysicsBody::createBox(sprite->getBoundingBox().size);
            physicsBody->setCollisionBitmask(0);
            physicsBody->setCategoryBitmask(PFMCollideMaskBitsPlayer);
            physicsBody->setContactTestBitmask(PFMCollideMaskBitsEnemyBullet | PFMCollideMaskBitsEnemy);
            sprite->addComponent(physicsBody);
            addChild(sprite);
        }
        else if(component->componentClass == "BulletGun")
        {
            PFMBulletGunComponent* bulletGunComponent = dynamic_cast<PFMBulletGunComponent*>(component);
            PFMBulletGun* bulletGun = PFMBulletGun::createWithComponent(bulletGunComponent);
            bulletGun->isHostByPlayer = true;
            bulletGun->isAutoShoot = true;
            addChild(bulletGun);
        }
        //        else if([component isMemberOfClass:[AstMissleLauncherComponent class]])
        //        {
        //            AstMissleLauncher* missleLauncher = [[AstMissleLauncher alloc]initWithSession:self.session];
        //            [self addNode:missleLauncher.rootNode];
        //            [missleLauncher setComponent:(AstMissleLauncherComponent*)component];
        //        }
    }
}

cocos2d::Size PFMPlayer::getSize()
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