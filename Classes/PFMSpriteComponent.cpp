//
//  PFMSpriteComponent.cpp
//  PlaneFightMaker
//
//  Created by ocean on 2/9/16.
//
//

#include "PFMSpriteComponent.hpp"
#include "PFMComponentValueConverter.hpp"

PFMSpriteComponent::PFMSpriteComponent()
{
    
}

void PFMSpriteComponent::setValue(rapidjson::GenericValue<rapidjson::UTF8<>> &value,std::string key)
{
    PFMComponent::setValue(value, key);
    if(key == "spriteSheetName")
    {
        spriteSheetName = std::string(value.GetString());
    }
    else if(key == "size")
    {
        size = cocos2d::Size(value["width"].GetDouble(),value["height"].GetDouble());
    }
    else if(key == "position")
    {
        position = cocos2d::Point(value["x"].GetDouble(),value["y"].GetDouble());
    }
    else if(key == "canCollide")
    {
        canCollide = value.GetBool();
    }
}

PFMComponent* PFMSpriteComponent::copy()
{
    return new PFMSpriteComponent(*this);
}