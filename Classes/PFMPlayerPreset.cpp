//
//  PFMPlayerPreset.cpp
//  PlaneFightMaker
//
//  Created by ocean on 2/10/16.
//
//

#include "PFMPlayerPreset.hpp"
#include <json/rapidjson.h>
#include <json/document.h>
#include <cocos2d.h>

#include "PFMComponentManager.hpp"

using namespace cocos2d;

PFMPlayerPreset::PFMPlayerPreset()
{
    loadFromPath("presets/default_ship.json");
}

PFMPlayerPreset::PFMPlayerPreset(std::string presetPath)
{
    
}

PFMPlayerPreset::~PFMPlayerPreset()
{
    for(auto iter = components.begin();iter != components.end();iter++)
    {
        delete *iter;
    }
    components.clear();
}

void PFMPlayerPreset::loadFromPath(std::string filePath)
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