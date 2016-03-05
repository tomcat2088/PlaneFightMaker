//
//  PFMLevelMap.cpp
//  PlaneFightMaker
//
//  Created by ocean on 2/10/16.
//
//

#include "PFMLevelMap.hpp"
#include "PFMLevelMapUnit.hpp"
#include "PFMPresetManager.hpp"
#include "PFMComponentManager.hpp"
#include "PFMComponentValueConverter.hpp"

PFMLevelMap* PFMLevelMap::mapFromFile(std::string mapFile)
{
    std::string content = cocos2d::FileUtils::getInstance()->getStringFromFile(mapFile);
    return new PFMLevelMap(content);
}

PFMLevelMap::PFMLevelMap(std::string mapFileContent)
{
    rapidjson::Document document;
    document.Parse<0>(mapFileContent.data());
    if(document.HasParseError())
    {
        return;
    }
    if(document.IsObject())
    {
        mapPageHeight = document["pageHeight"].GetDouble();
        backgroundImage = document["background"].GetString();
        
        if(document["pages"].IsArray())
        {
            for(auto pageIter = document["pages"].Begin();pageIter != document["pages"].End();pageIter++)
            {
                std::vector<PFMLevelMapUnit*> pageUnits;
                for(auto unitIter = pageIter->Begin();unitIter != pageIter->End();unitIter++)
                {
                    std::string type = std::string(unitIter->FindMember("type")->value.GetString());
                    std::string ref = std::string(unitIter->FindMember("ref")->value.GetString());
                    
                    auto positionMember = unitIter->FindMember("position");
                    cocos2d::Point position = cocos2d::Point(positionMember->value["x"].GetDouble(),positionMember->value["y"].GetDouble());
                    if(type == "Preset")
                    {
                        PFMPreset* preset = PFMPresetManager::shared()->presetWithName(ref);
                        if(preset == NULL)
                            continue;
                        auto externValue = unitIter->FindMember("extern");
                        
                        for(auto externIter = externValue->value.MemberBegin();externIter != externValue->value.MemberEnd();externIter++)
                        {
                            preset->setExternValue(externIter->value, std::string(externIter->name.GetString()));
                        }
                        PFMLevelMapUnit* mapUnit = new PFMLevelMapUnit(preset);
                        mapUnit->position = position;
                        mapUnit->type = PFMLevelMapUnitTypePreset;
                        
                        pageUnits.push_back(mapUnit);
                    }
                    else if(type == "Component")
                    {
                        PFMComponent* component = PFMComponentManager::shared()->componentWithUID(ref);
                        for(auto iter = unitIter->MemberBegin();iter != unitIter->MemberEnd();iter++)
                        {
                            component->setValue(iter->value, std::string(iter->name.GetString()));
                        }
                        
                        PFMLevelMapUnit* mapUnit = new PFMLevelMapUnit(component);
                        mapUnit->position = position;
                        mapUnit->type = PFMLevelMapUnitTypeComponent;
                        
                        pageUnits.push_back(mapUnit);
                    }
                }
                units.push_back(pageUnits);
            }
        }
    }
}

std::vector<PFMLevelMapUnit*> PFMLevelMap::unitsInPage(int pageIndex)
{
    if(pageIndex >=0 && pageIndex < units.size())
    {
        return units.at(pageIndex);
    }
    return std::vector<PFMLevelMapUnit*>();
}