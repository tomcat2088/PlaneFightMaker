//
//  PFMLevelMapUnit.cpp
//  PlaneFightMaker
//
//  Created by ocean on 2/12/16.
//
//

#include "PFMLevelMapUnit.hpp"
#include "PFMPreset.hpp"

PFMLevelMapUnit::PFMLevelMapUnit(PFMPreset* preset):_preset(preset)
{
    
}

PFMLevelMapUnit::PFMLevelMapUnit(PFMComponent* component):_component(component)
{

}

cocos2d::Node* PFMLevelMapUnit::createNodeInstance(cocos2d::Vec2 offset)
{
    if(type == PFMLevelMapUnitTypePreset)
    {
        cocos2d::Node* node = _preset->createNodeInstance();
        cocos2d::Point pos = position;
        pos.x += offset.x;
        pos.y += offset.y;
        node->setPosition(pos);
        return node;
    }
    return NULL;
}