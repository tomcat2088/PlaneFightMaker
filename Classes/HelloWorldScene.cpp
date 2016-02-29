#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "InfinityScrollableBackground.hpp"
#include "PFMComponentManager.hpp"
#include "PFMPlayerPreset.hpp"
#include "PFMPlayer.hpp"
#include "GameSession.hpp"
USING_NS_CC;

using namespace cocostudio::timeline;


Scene* HelloWorld::createScene()
{
    
    //load components
    PFMComponentManager::shared()->addLoadPath("res/components/ship.json");
    PFMComponentManager::shared()->reload();
    
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vec2(0,0));
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    session = GameSession::newSession();
    session->startInLayer(this);
    scheduleUpdate();
    EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
    
    listener->onTouchBegan = std::bind(&HelloWorld::onTouchBegan, this, std::placeholders::_1,std::placeholders::_2);
    listener->onTouchMoved = std::bind(&HelloWorld::onTouchMoved, this, std::placeholders::_1,std::placeholders::_2);
    listener->onTouchEnded = std::bind(&HelloWorld::onTouchEnded, this, std::placeholders::_1,std::placeholders::_2);
    
    getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1000);
    return true;
}

void HelloWorld::update(float delta)
{
    session->update(delta);
}

bool HelloWorld::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    _lastTouchPoint = touch->getLocation();
    return true;
}

void HelloWorld::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    cocos2d::Point pt = touch->getLocation();
    float dx = pt.x - _lastTouchPoint.x;
    float dy = pt.y - _lastTouchPoint.y;
    
    cocos2d::Size stageSize = Director::getInstance()->getVisibleSize();
    cocos2d::Size playerSize = session->player->getSize();
    cocos2d::Point playerPos = session->player->getPosition();
    playerPos.x += dx;
    playerPos.y += dy;
    if(playerPos.x < playerSize.width/2)
         playerPos.x = playerSize.width/2;
    else if(playerPos.x > stageSize.width - playerSize.width/2)
        playerPos.x = stageSize.width - playerSize.width/2;
    if(playerPos.y < playerSize.height / 2)
        playerPos.y = playerSize.height / 2;
    else if(playerPos.y > stageSize.height - playerSize.height / 2)
        playerPos.y = stageSize.height - playerSize.height / 2;
    session->player->setPosition(playerPos);
    
    _lastTouchPoint = touch->getLocation();
}

void HelloWorld::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{

}

