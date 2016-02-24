//
//  PFMEnemyPreset.hpp
//  PlaneFightMaker
//
//  Created by ocean on 2/10/16.
//
//

#ifndef PFMEnemyPreset_hpp
#define PFMEnemyPreset_hpp

#include <PFMPreset.hpp>
class PFMComponent;
class PFMEnemyPreset : public PFMPreset
{
public:
    std::vector<PFMComponent*> components;
public:
    PFMEnemyPreset();
    PFMEnemyPreset(std::string presetPath);
    void loadFromPath(std::string path);
    
    virtual cocos2d::Node* createNodeInstance();
private:
    ~PFMEnemyPreset();
};
#endif /* PFMEnemyPreset_hpp */
