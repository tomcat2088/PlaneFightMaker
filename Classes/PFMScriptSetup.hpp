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
};
#endif /* PFMScriptSetup_hpp */
