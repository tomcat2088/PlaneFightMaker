//
//  PFMGameConfig.hpp
//  PlaneFightMaker
//
//  Created by wangyang on 16/3/4.
//
//

#ifndef PFMGameConfig_hpp
#define PFMGameConfig_hpp

#include <stdio.h>
class PFMGameConfig
{
public:
    static PFMGameConfig* shared();
    PFMGameConfig();
    
    //properties
    double width;
    double height;
};
#endif /* PFMGameConfig_hpp */
