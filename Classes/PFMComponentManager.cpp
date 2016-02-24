//
//  PFMComponentManager.cpp
//  PlaneFightMaker
//
//  Created by ocean on 2/9/16.
//
//

#include "PFMComponentManager.hpp"
#include <json/rapidjson.h>
#include <json/document.h>
#include <json/stringbuffer.h>

#include "PFMComponent.hpp"
#include "PFMSpriteComponent.hpp"
#include "PFMBulletGunComponent.hpp"
#include "PFMBulletComponent.hpp"
using namespace cocos2d;

PFMComponentManager* PFMComponentManager::shared()
{
    static PFMComponentManager* _shared = NULL;
    if(_shared == NULL)
    {
        _shared = new PFMComponentManager();
    }
    return _shared;
}

void PFMComponentManager::addLoadPath(std::string path)
{
    loadPaths.push_back(path);
}

void PFMComponentManager::reload()
{
    components.clear();
    for(int i=0;i<loadPaths.size();i++)
    {
        std::string filePath = loadPaths.at(i);
        loadComponentsUnderPath(filePath);
    }
}

PFMComponent* PFMComponentManager::componentWithUID(std::string uid)
{
    if(components[uid]->componentUID == uid)
    {
        return components[uid]->copy();
    }
    return new PFMComponent();
}

void PFMComponentManager::loadComponentsUnderPath(std::string filePath)
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
            for(auto iter = document.MemberBegin();iter != document.MemberEnd();iter++)
            {
                if(iter->value.IsObject())
                {
                    std::string componentClassName = std::string(iter->value["componentClass"].GetString());
                    PFMComponent* component = componentWithClassName(componentClassName);
                    for(auto iter2 = iter->value.MemberBegin();iter2 != iter->value.MemberEnd();iter2++)
                    {
                        component->setValue(iter2->value, std::string(iter2->name.GetString()));
                    }
                    component->componentUID = std::string(iter->name.GetString());
                    components[component->componentUID] = component;
                }
            }
        }
        
    }
}

PFMComponent* PFMComponentManager::componentWithClassName(std::string className)
{
    if(className == "Sprite")
    {
        return new PFMSpriteComponent();
    }
    else if(className == "BulletGun")
    {
        return new PFMBulletGunComponent();
    }
    else if(className == "Bullet")
    {
        return new PFMBulletComponent();
    }
    return new PFMComponent();
}