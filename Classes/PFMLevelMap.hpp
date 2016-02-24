//
//  PFMLevelMap.hpp
//  PlaneFightMaker
//
//  Created by ocean on 2/10/16.
//
//

#ifndef PFMLevelMap_hpp
#define PFMLevelMap_hpp

#include <stdio.h>
class PFMLevelMapUnit;
class PFMLevelMap
{
public:
    std::vector<PFMLevelMapUnit*> units;
public:
    static PFMLevelMap* mapFromFile(std::string mapFile);
    std::vector<PFMLevelMapUnit*> unitsInRect(cocos2d::Rect rect);
};
#endif /* PFMLevelMap_hpp */
