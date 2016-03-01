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
    std::vector<std::vector<PFMLevelMapUnit*>> units;
    double mapPageWidth;
    double mapPageHeight;
public:
    PFMLevelMap(std::string mapFileContent);
    static PFMLevelMap* mapFromFile(std::string mapFile);
    std::vector<PFMLevelMapUnit*> unitsInPage(int pageIndex);
};
#endif /* PFMLevelMap_hpp */
