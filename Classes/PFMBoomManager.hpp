//
//  PFMBoomManager.hpp
//  PlaneFightMaker
//
//  Created by wangyang on 16/3/3.
//
//

#ifndef PFMBoomManager_hpp
#define PFMBoomManager_hpp

#include <cocos2d.h>
class PFMBoomManager
{
public:
    static PFMBoomManager* shared();
    cocos2d::Layer* rootNode;
    void boomAt(std::string boomEffectName,cocos2d::Point position);
};
#endif /* PFMBoomManager_hpp */
