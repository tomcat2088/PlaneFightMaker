//
//  PFMLevelMap.cpp
//  PlaneFightMaker
//
//  Created by ocean on 2/10/16.
//
//

#include "PFMLevelMap.hpp"
#include "PFMLevelMapUnit.hpp"

PFMLevelMap* PFMLevelMap::mapFromFile(std::string mapFile)
{
    return new PFMLevelMap();
}

std::vector<PFMLevelMapUnit*> PFMLevelMap::unitsInRect(cocos2d::Rect rect)
{
    for(int i=0;i<units.size();i++)
    {
     //   if(u)
    }
    return std::vector<PFMLevelMapUnit*>();
}