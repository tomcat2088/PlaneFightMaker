//
//  PFMScriptCoreTypes.hpp
//  PlaneFightMaker
//
//  Created by ocean on 2/16/16.
//
//

#ifndef PFMScriptCoreTypes_hpp
#define PFMScriptCoreTypes_hpp

#include <stdio.h>

struct PFMScriptTypeSize {
    float width;
    float height;
    PFMScriptTypeSize()
    {}
    cocos2d::Vec2 vec2()
    {
        return cocos2d::Vec2(width,height);
    }
    
    PFMScriptTypeSize(cocos2d::Vec2 vec2)
    {
        width = vec2.x;
        height = vec2.y;
    }
    
};

struct PFMScriptTypePoint {
    float x;
    float y;
    PFMScriptTypePoint()
    {}
    cocos2d::Vec2 vec2()
    {
        return cocos2d::Vec2(x,y);
    }
    
    PFMScriptTypePoint(cocos2d::Vec2 vec2)
    {
        x = vec2.x;
        y = vec2.y;
    }
};

#endif /* PFMScriptCoreTypes_hpp */
