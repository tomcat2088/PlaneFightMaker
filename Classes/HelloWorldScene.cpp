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
    return true;
}

void HelloWorld::update(float delta)
{
    session->update(delta);
}