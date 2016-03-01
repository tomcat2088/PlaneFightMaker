//
//  PFMBullet.cpp
//  PlaneFightMaker
//
//  Created by ocean on 2/10/16.
//
//

#include "PFMBullet.hpp"
#include "PFMSpriteComponent.hpp"
#include "PFMBulletComponent.hpp"
#include "GameSession.hpp"
#include <cocos2d.h>

using namespace cocos2d;

PFMBullet::PFMBullet()
{

}

PFMBullet* PFMBullet::createWithComponent(PFMBulletComponent* component)
{
    PFMBullet* sprite = PFMBullet::create();
    sprite->setComponent(component);
    PhysicsBody* body = PhysicsBody::createBox(sprite->getBoundingBox().size);
    sprite->addComponent(body);
    return sprite;
}

void PFMBullet::setComponent(PFMBulletComponent *component)
{
    _component = component;
    PFMSprite::setComponent(component);
    damage = component->damage;
    setAnchorPoint(Vec2(0.5,0));
    scheduleUpdate();
}

void PFMBullet::shootWithAngle(float degree)
{
    float rad = degree / 180.0f * M_PI;
    _xSpeed = sinf(rad) * _component->speed;
    _ySpeed = cosf(rad) * _component->speed;
    setRotation(degree);
}

void PFMBullet::update(float delta)
{
    Vec2 position = getPosition();
    position.x += _xSpeed * delta;
    position.y += _ySpeed * delta;
    setPosition(position);
    
    cocos2d::Rect bulletRect = getBoundingBox();
    cocos2d::Rect sessionRect = GameSession::currentSession()->rootNode->getBoundingBox();
    sessionRect.size = Director::getInstance()->getVisibleSize();
    if(sessionRect.intersectsRect(bulletRect) == false)
    {
        removeFromParentAndCleanup(true);
    }
}
