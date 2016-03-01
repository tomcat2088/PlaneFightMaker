//
//  GameSession.cpp
//  PlaneFightMaker
//
//  Created by ocean on 2/10/16.
//
//

#include "GameSession.hpp"
#include "InfinityScrollableBackground.hpp"
#include "PFMPlayer.hpp"
#include "PFMPlayerPreset.hpp"
#include "PFMEnemyPreset.hpp"
#include "PFMEnemy.hpp"
#include "PFMScriptCore.hpp"
#include "PFMScriptSetup.hpp"
#include "PFMLevelMap.hpp"
#include "PFMLevelMapUnit.hpp"
#include <cocos2d.h>

using namespace cocos2d;
GameSession* GameSession::_currentSession = NULL;
GameSession* GameSession::currentSession()
{
    return _currentSession;
}

GameSession* GameSession::newSession()
{
    if(_currentSession != NULL)
    {
        _currentSession->rootNode->removeAllChildren();
        delete _currentSession;
    }
    _currentSession = new GameSession();
    PFMScriptSetup::shared()->initGlobalValues();
    return _currentSession;
}

GameSession::GameSession():_gameSpeed(400),
_currentMapLoadSegmentIndex(-1)
{
    levelMap = PFMLevelMap::mapFromFile("levels/level1.json");
}

void GameSession::startInLayer(cocos2d::Layer* layer)
{
    rootNode = layer;
    _background = new InfinityScrollableBackground("img_bg_level_1.jpg");
    _background->scrollSpeed = -_gameSpeed;
    layer->addChild(_background);
    _background->setAnchorPoint(cocos2d::Vec2(0,0));
    _background->setContentSize(Director::getInstance()->getVisibleSize());
    
    player = new PFMPlayer();
    layer->addChild(player);
    player->setPreset(new PFMPlayerPreset());
    player->setPosition(Vec2(Director::getInstance()->getVisibleSize().width/2, 100));
}

void GameSession::update(float delta)
{
    tryLoadNewMapUnits();
}

void GameSession::tryLoadNewMapUnits()
{
    double visualHeight = Director::getInstance()->getVisibleSize().height;
    if((int)_background->distance % (int)visualHeight > 0)
    {
        loadMapUnits((int)_background->distance / (int)visualHeight);
    }
}

void GameSession::loadMapUnits(int segmentIndex)
{
 if(segmentIndex <= _currentMapLoadSegmentIndex)
     return;
    double visualHeight = Director::getInstance()->getVisibleSize().height;
    std::vector<PFMLevelMapUnit*> units = levelMap->unitsInPage(segmentIndex);
    for(int i=0;i<units.size();i++)
    {
        cocos2d::Point offset;
        offset.y = visualHeight - _background->distance;
        rootNode->addChild(units[i]->createNodeInstance(offset));
    }
    
    _currentMapLoadSegmentIndex = segmentIndex;
}

//for script
float GameSession::script_getStageSizeWidth()
{
    return Director::getInstance()->getVisibleSize().width;
}

float GameSession::script_getStageSizeHeight()
{
    return Director::getInstance()->getVisibleSize().height;
}

void GameSession::registerToScript()
{
    PFMScriptCore* core = PFMScriptCore::shared();
    core->lua.new_userdata<GameSession>("GameSession",
                                     "getStageSizeWidth", &GameSession::script_getStageSizeWidth,
                                        "getStageSizeHeight", &GameSession::script_getStageSizeHeight);

}