//
//  PFMBulletComponent.cpp
//  PlaneFightMaker
//
//  Created by ocean on 2/10/16.
//
//

#include "PFMBulletComponent.hpp"

PFMBulletComponent::PFMBulletComponent()
{
    
}

void PFMBulletComponent::setValue(rapidjson::GenericValue<rapidjson::UTF8<>> &value,std::string key)
{
    PFMSpriteComponent::setValue(value, key);
    if(key == "speed")
    {
        speed = value.GetDouble();
    }
    else if(key == "damage")
    {
        damage = value.GetDouble();
    }
}

PFMComponent* PFMBulletComponent::copy()
{
    return new PFMBulletComponent(*this);
}