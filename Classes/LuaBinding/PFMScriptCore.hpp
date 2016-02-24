//
//  PFMScript.hpp
//  PlaneFightMaker
//
//  Created by ocean on 2/16/16.
//
//

#ifndef PFMScript_hpp
#define PFMScript_hpp

#include <PFMScriptCore.hpp>
#include "sol.hpp"

class PFMScriptCore
{
public:
    static PFMScriptCore* shared();
    PFMScriptCore();
    sol::state lua;
};
#endif /* PFMScript_hpp */
