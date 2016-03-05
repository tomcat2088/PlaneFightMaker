//
//  PFMSceneryPreset.hpp
//  PlaneFightMaker
//
//  Created by wangyang on 16/3/4.
//
//

#ifndef PFMSceneryPreset_hpp
#define PFMSceneryPreset_hpp

#include <PFMPreset.hpp>
class PFMComponent;
class PFMSceneryPreset : public PFMPreset
{
public:
    std::vector<PFMComponent*> components;
public:
    PFMSceneryPreset();
    PFMSceneryPreset(std::string presetPath);
    void loadFromPath(std::string path);
private:
    ~PFMSceneryPreset();
};
#endif /* PFMSceneryPreset_hpp */
