//
//  PFMComponent.hpp
//  PlaneFightMaker
//
//  Created by ocean on 2/9/16.
//
//

#ifndef PFMComponent_hpp
#define PFMComponent_hpp

#include <json/rapidjson.h>
#include <json/document.h>

class PFMComponent
{
public:
    std::string componentUID;//component的唯一标识
    std::string componentClass;
    
    PFMComponent();
    virtual void setValue(rapidjson::GenericValue<rapidjson::UTF8<>> &value,std::string key);
    virtual PFMComponent* copy();
};
#endif /* PFMComponent_hpp */
