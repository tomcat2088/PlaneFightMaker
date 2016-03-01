//
//  PFMComponentManager.hpp
//  PlaneFightMaker
//
//  Created by ocean on 2/9/16.
//
//

#ifndef PFMPresetManager_hpp
#define PFMPresetManager_hpp

#include <cocos2d.h>
#include "PFMPreset.hpp"

class PFMPresetManager
{
public:
    static PFMPresetManager* shared();
    PFMPreset* presetWithName(std::string name);
private:
    std::vector<std::string> loadPaths;
    std::map<std::string,PFMPreset*> presets;
};
#endif /* PFMComponentManager_hpp */
