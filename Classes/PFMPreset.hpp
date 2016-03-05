//
//  PFMPreset.hpp
//  PlaneFightMaker
//
//  Created by ocean on 2/12/16.
//
//

#ifndef PFMPreset_hpp
#define PFMPreset_hpp

#include <cocos2d.h>
#include <json/rapidjson.h>
#include <json/document.h>

class PFMComponent;
class PFMPreset
{
public:
    std::vector<PFMComponent*> components;
    virtual cocos2d::Node* createNodeInstance() = 0;
    virtual void setExternValue(rapidjson::GenericValue<rapidjson::UTF8<>>& value,std::string key)
    {
    
    }
protected:
    PFMPreset(std::string presetPath);
    void loadFromPath(std::string path);
};
#endif /* PFMPreset_hpp */
