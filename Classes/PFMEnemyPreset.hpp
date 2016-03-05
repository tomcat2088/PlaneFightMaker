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
    std::string routeStrategy;
    std::string shootStrategy;
    std::string compositionStrategy;
    float health;
public:
    PFMEnemyPreset();
    virtual cocos2d::Node* createNodeInstance();
    virtual void setExternValue(rapidjson::GenericValue<rapidjson::UTF8<>>& value,std::string key);
private:
    ~PFMEnemyPreset();
};
#endif /* PFMEnemyPreset_hpp */
