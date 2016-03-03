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
#include "PFMCollideMaskBits.h"
#include "PFMScriptSetup.hpp"
#include "PFMBoomManager.hpp"
#include <cocos2d.h>

using namespace cocos2d;
PFMEnemy::PFMEnemy() : xSpeed(2),ySpeed(-2),totalHealth(2000),health(2000),_healthBar(NULL)
{
    EventListenerPhysicsContact* eventListener = EventListenerPhysicsContact::create();
    eventListener->onContactBegin = CC_CALLBACK_1(PFMEnemy::onContactBegin, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, this);
    scheduleUpdate();
}

PFMEnemy::~PFMEnemy()
{
    printf("Enemy is destruct");
}

void PFMEnemy::setPreset(PFMEnemyPreset* preset)
{
    _preset = preset;
    totalHealth = preset->health;
    health = preset->health;
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
            PhysicsBody* physicsBody = PhysicsBody::createBox(sprite->getBoundingBox().size);
            physicsBody->setCollisionBitmask(0);
            physicsBody->setCategoryBitmask(PFMCollideMaskBitsEnemy);
            physicsBody->setContactTestBitmask(PFMCollideMaskBitsPlayerBullet | PFMCollideMaskBitsPlayer);
            physicsBody->setTag(PFMPhysicsBodyTypeEnemy);
            setPhysicsBody(physicsBody);
            addChild(sprite);
        }
        else if(component->componentClass == "BulletGun")
        {
            PFMBulletGunComponent* bulletGunComponent = dynamic_cast<PFMBulletGunComponent*>(component);
            bulletGunComponent->angle = fabs(bulletGunComponent->angle) / bulletGunComponent->angle * 180 - bulletGunComponent->angle;
            PFMBulletGun* bulletGun = PFMBulletGun::createWithComponent(bulletGunComponent);
            bulletGun->isAutoShoot = false;
            addChild(bulletGun);
            _bulletGuns.pushBack(bulletGun);
        }
        //        else if([component isMemberOfClass:[AstMissleLauncherComponent class]])
        //        {
        //            AstMissleLauncher* missleLauncher = [[AstMissleLauncher alloc]initWithSession:self.session];
        //            [self addNode:missleLauncher.rootNode];
        //            [missleLauncher setComponent:(AstMissleLauncherComponent*)component];
        //        }
    }
    
    if(_healthBar != NULL)
    {
        _healthBar->removeFromParent();
    }
    _healthBar = LayerColor::create(Color4B(200, 30, 30, 255));
    _healthBar->setContentSize(Size(100,5));
    addChild(_healthBar);
    Size allSize = getSize();
    _healthBar->setPosition(Vec2(-50,allSize.height/2 + 10));
}

bool PFMEnemy::onContactBegin(cocos2d::PhysicsContact &contact)
{
    if(contact.getShapeA()->getBody() == getPhysicsBody() ||
       contact.getShapeB()->getBody() == getPhysicsBody())
    {
        PhysicsBody* other = contact.getShapeA()->getBody() == getPhysicsBody()?contact.getShapeB()->getBody() : contact.getShapeA()->getBody();
        switch (other->getTag()) {
            case PFMPhysicsBodyTypePlayerBullet:
            {
                PFMBullet* bullet = dynamic_cast<PFMBullet*>(other->getOwner());
                if(bullet != NULL)
                {
                    health -= bullet->damage;
                }
                const PhysicsContactData* contactData = contact.getContactData();
                PFMBoomManager::shared()->boomAt("", contactData->points[0]);
                other->getOwner()->removeFromParentAndCleanup(true);
                break;
            }
            default:
                break;
        }
    }
    return true;
}

void PFMEnemy::update(float delta)
{
    if(health <= 0)
    {
        removeFromParentAndCleanup(true);
        return;
    }
    
    _healthBar->setContentSize(Size(health / totalHealth * 100,5));
    
    std::string content = PFMScriptSetup::shared()->routeStrategyScriptWithName(_preset->routeStrategy);
    PFMScriptCore::shared()->lua.set("target", this);
    PFMScriptCore::shared()->lua.script(content);
    
    
    content = PFMScriptSetup::shared()->bulletShootStrategyScriptWithName(_preset->shootStrategy);
    PFMScriptCore::shared()->lua.set("target", this);
    PFMScriptCore::shared()->lua.set("bullet_gun_count", _bulletGuns.size());
    for(int i=0;i<_bulletGuns.size();i++)
    {
        PFMScriptCore::shared()->lua.set("bullet_gun_" + std::to_string(i), _bulletGuns.at(i));
    }
    PFMScriptCore::shared()->lua.script(content);
    
    content = PFMScriptSetup::shared()->compositionStrategyScriptWithName(_preset->compositionStrategy);
    PFMScriptCore::shared()->lua.set("target", this);
    PFMScriptCore::shared()->lua.set("bullet_gun_count", _bulletGuns.size());
    for(int i=0;i<_bulletGuns.size();i++)
    {
        PFMScriptCore::shared()->lua.set("bullet_gun_" + std::to_string(i), _bulletGuns.at(i));
    }
    PFMScriptCore::shared()->lua.script(content);
    
    gunShootTimer+=delta;
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
                                     "ySpeed",&PFMEnemy::ySpeed,
                                     "gunShootTimer",&PFMEnemy::gunShootTimer);
}