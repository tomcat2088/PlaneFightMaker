//
//  PFMComponent.cpp
//  PlaneFightMaker
//
//  Created by ocean on 2/9/16.
//
//

#include "PFMComponent.hpp"

PFMComponent::PFMComponent()
{
    
}

void PFMComponent::setValue(rapidjson::GenericValue<rapidjson::UTF8<>> &value,std::string key)
{
    if(key == "componentClass")
    {
        componentClass = std::string(value.GetString());
    }
}

PFMComponent* PFMComponent::copy()
{
    return new PFMComponent(*this);
}

