//
//  PFMScriptSetup.cpp
//  PlaneFightMaker
//
//  Created by ocean on 2/16/16.
//
//

#include "PFMScriptSetup.hpp"
#include "PFMScriptCore.hpp"
#include "PFMEnemy.hpp"
#include "PFMBulletGun.hpp"
#include "GameSession.hpp"


PFMScriptSetup* PFMScriptSetup::shared()
{
    static PFMScriptSetup* _shared = NULL;
    if(_shared == NULL)
    {
        _shared = new PFMScriptSetup();
        PFMEnemy::registerToScript();
        GameSession::registerToScript();
        PFMBulletGun::registerToScript();
    }
    return _shared;
}

void PFMScriptSetup::initGlobalValues()
{
    PFMScriptCore::shared()->lua.set("gameSession", GameSession::currentSession());
}

std::string PFMScriptSetup::routeStrategyScriptWithName(std::string name)
{
    static std::map<std::string,std::string> scriptCache;
    std::string filename = "behavior/route_strategy/" + name + ".lua";
    if(scriptCache.find(filename) != scriptCache.end())
    {
        return scriptCache.at(filename);
    }
    std::string content = cocos2d::FileUtils::getInstance()->getStringFromFile(filename);
    scriptCache[filename] = content;
    return content;
}

std::string PFMScriptSetup::bulletShootStrategyScriptWithName(std::string name)
{
    static std::map<std::string,std::string> scriptCache;
    std::string filename = "behavior/shoot_strategy/" + name + ".lua";
    if(scriptCache.find(filename) != scriptCache.end())
    {
        return scriptCache.at(filename);
    }
    std::string content = cocos2d::FileUtils::getInstance()->getStringFromFile(filename);
    scriptCache[filename] = content;
    return content;
}

std::string PFMScriptSetup::compositionStrategyScriptWithName(std::string name)
{
    static std::map<std::string,std::string> scriptCache;
    std::string filename = "behavior/composition_strategy/" + name + ".lua";
    if(scriptCache.find(filename) != scriptCache.end())
    {
        return scriptCache.at(filename);
    }
    std::string content = cocos2d::FileUtils::getInstance()->getStringFromFile(filename);
    scriptCache[filename] = content;
    return content;
}