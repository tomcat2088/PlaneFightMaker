//
//  PFMPreset.cpp
//  PlaneFightMaker
//
//  Created by ocean on 2/12/16.
//
//

#include "PFMPreset.hpp"
#include "PFMComponent.hpp"
#include "PFMComponentManager.hpp"

using namespace cocos2d;
PFMPreset::PFMPreset(std::string presetPath)
{
    loadFromPath(presetPath);
}

void PFMPreset::loadFromPath(std::string filePath)
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