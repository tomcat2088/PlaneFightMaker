//
//  PFMBulletGunComponent.cpp
//  PlaneFightMaker
//
//  Created by ocean on 2/10/16.
//
//

#include "PFMBulletGunComponent.hpp"
#include "PFMBulletComponent.hpp"
#include "PFMComponentManager.hpp"

PFMBulletGunComponent::PFMBulletGunComponent():_bulletComponent(NULL)
{

}

PFMBulletComponent* PFMBulletGunComponent::getBulletComponent()
{
    if(_bulletComponent == NULL)
    {
        _bulletComponent = dynamic_cast<PFMBulletComponent*>(PFMComponentManager::shared()->componentWithUID(bulletComponentRef));
    }
    return _bulletComponent;
}

void PFMBulletGunComponent::setValue(rapidjson::GenericValue<rapidjson::UTF8<>> &value,std::string key)
{
    PFMComponent::setValue(value, key);
    if(key == "shootInterval")
    {
        shootInterval = value.GetDouble();
    }
    else if(key == "angle")
    {
        angle = value.GetDouble();
    }
    else if(key == "position")
    {
        position = cocos2d::Point(value["x"].GetDouble(),value["y"].GetDouble());
    }
    else if(key == "bulletComponent")
    {
        bulletComponentRef = std::string(value.GetString());
    }
}

PFMComponent* PFMBulletGunComponent::copy()
{
    return new PFMBulletGunComponent(*this);
}