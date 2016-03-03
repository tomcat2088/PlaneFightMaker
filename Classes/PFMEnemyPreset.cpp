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

PFMEnemyPreset::PFMEnemyPreset(std::string presetPath)
{
    loadFromPath(presetPath);
}

PFMEnemyPreset::~PFMEnemyPreset()
{
    for(auto iter = components.begin();iter != components.end();iter++)
    {
        delete *iter;
    }
    components.clear();
}

void PFMEnemyPreset::loadFromPath(std::string filePath)
{
    if(FileUtils::getInstance()->isFileExist(filePath))
    {
        std::string jsonContent = FileUtils::getInstance()->getStringFromFile(filePath);
        
        rapidjson::Document document;
        document.Parse<0>(jsonContent.data());
        if(document.HasParseError())
        {
            return;
        }
        if(document.IsObject())
        {
            if(document["components"].IsArray())
            {
                for(auto componentIter = document["components"].Begin();componentIter != document["components"].End();componentIter++)
                {
                    std::string refName = std::string(componentIter->FindMember("ref")->value.GetString());
                    PFMComponent* component = PFMComponentManager::shared()->componentWithUID(refName);
                    for(auto iter = componentIter->MemberBegin();iter != componentIter->MemberEnd();iter++)
                    {
                        component->setValue(iter->value, std::string(iter->name.GetString()));
                    }
                    components.push_back(component);
                }
            }
        }
    }
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