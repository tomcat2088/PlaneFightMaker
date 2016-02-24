//
//  PFMComponentManager.hpp
//  PlaneFightMaker
//
//  Created by ocean on 2/9/16.
//
//

#ifndef PFMComponentManager_hpp
#define PFMComponentManager_hpp

#include <cocos2d.h>
#include <PFMComponent.hpp>

class PFMComponentManager
{
public:
    static PFMComponentManager* shared();
    void addLoadPath(std::string path);
    void reload();
    PFMComponent* componentWithUID(std::string uid);
private:
    std::vector<std::string> loadPaths;
    std::map<std::string,PFMComponent*> components;
    void loadComponentsUnderPath(std::string filePath);
    PFMComponent* componentWithClassName(std::string className);
};
#endif /* PFMComponentManager_hpp */
