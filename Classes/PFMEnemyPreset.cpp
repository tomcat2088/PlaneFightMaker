//
//  PFMEnemyPreset.cpp
//  PlaneFightMaker
//
//  Created by ocean on 2/10/16.
//
//

#include "PFMEnemyPreset.hpp"
#include <json/rapidjson.h>
#include <json/document.h>
#include <cocos2d.h>

#include "PFMComponentManager.hpp"
#include "PFMEnemy.hpp"

using namespace cocos2d;

PFMEnemyPreset::PFMEnemyPreset()
{
    loadFromPath("presets/enemy1.json");
}

cocos2d::Node* PFMEnemyPreset::createNodeInstance()
{
    PFMEnemy* enemy = PFMEnemy::create();
    enemy->setPreset(this);
    return enemy;
}

void PFMEnemyPreset::setExternValue(rapidjson::GenericValue<rapidjson::UTF8<>>& value,std::string key)
{
    if(key == "route")
    {
        routeStrategy = value.GetString();
    }
    else if(key == "shoot")
    {
        shootStrategy = value.GetString();
    }
    else if(key == "composition")
    {
        compositionStrategy = value.GetString();
    }
    else if(key == "health")
    {
        health = value.GetDouble();
    }
}