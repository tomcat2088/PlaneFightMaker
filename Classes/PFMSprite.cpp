//
//  PFMSprite.cpp
//  PlaneFightMaker
//
//  Created by ocean on 2/10/16.
//
//

#include "PFMSprite.hpp"
#include "PFMSpriteComponent.hpp"
#include <cocos2d.h>
using namespace cocos2d;

PFMSprite* PFMSprite::createWithComponent(PFMSpriteComponent* component)
{
    PFMSprite* sprite = PFMSprite::create();
    sprite->setComponent(component);
    return sprite;
}

PFMSprite::PFMSprite()
{

}

void PFMSprite::setComponent(PFMSpriteComponent* component)
{
    setTexture(component->spriteSheetName);
    setScaleX(component->size.width / getContentSize().width);
    setScaleY(component->size.height / getContentSize().height);
    setPosition(component->position);
    PhysicsBody* physicsBody = PhysicsBody::createBox(component->size);
    addComponent(physicsBody);
    physicsBody->setCategoryBitmask(0);
    physicsBody->setCollisionBitmask(0);
    physicsBody->setContactTestBitmask(0);
}