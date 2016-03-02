//
//  PFMScriptSetup.hpp
//  PlaneFightMaker
//
//  Created by ocean on 2/16/16.
//
//

#ifndef PFMScriptSetup_hpp
#define PFMScriptSetup_hpp

#include <stdio.h>
class PFMScriptSetup
{
public:
    static PFMScriptSetup* shared();
    void initGlobalValues();
    std::string routeStrategyScriptWithName(std::string name);
    std::string bulletShootStrategyScriptWithName(std::string name);
    std::string compositionStrategyScriptWithName(std::string name);
};
#endif /* PFMScriptSetup_hpp */
