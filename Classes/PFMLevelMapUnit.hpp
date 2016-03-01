//
//  PFMLevelMapUnit.hpp
//  PlaneFightMaker
//
//  Created by ocean on 2/12/16.
//
//

#ifndef PFMLevelMapUnit_hpp
#define PFMLevelMapUnit_hpp

#include <cocos2d.h>
#include <json/rapidjson.h>
#include <json/document.h>

class PFMPreset;
class PFMComponent;

typedef enum
{
    PFMLevelMapUnitTypePreset,
    PFMLevelMapUnitTypeComponent
}PFMLevelMapUnitType;

class PFMLevelMapUnit
{
public:
    PFMLevelMapUnitType type;
    cocos2d::Point position;
    rapidjson::GenericValue<rapidjson::UTF8<>>* externValue;
    
    PFMLevelMapUnit(PFMPreset* preset);
    PFMLevelMapUnit(PFMComponent* component);
    
public:
    cocos2d::Node* createNodeInstance(cocos2d::Vec2 offset);
private:
    PFMPreset* _preset;
    PFMComponent* _component;
};
#endif /* PFMLevelMapUnit_hpp */
