//
//  PFMPlayerPreset.hpp
//  PlaneFightMaker
//
//  Created by ocean on 2/10/16.
//
//

#ifndef PFMPlayerPreset_hpp
#define PFMPlayerPreset_hpp

class PFMComponent;
class PFMPlayerPreset
{
public:
    std::vector<PFMComponent*> components;
public:
    PFMPlayerPreset();
    PFMPlayerPreset(std::string presetPath);
    void loadFromPath(std::string path);
private:
    ~PFMPlayerPreset();
};
#endif /* PFMPlayerPreset_hpp */
