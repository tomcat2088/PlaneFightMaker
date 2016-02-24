//
//  InfinityScrollableBackground.hpp
//  PlaneFightMaker
//
//  Created by ocean on 2/9/16.
//
//

#ifndef InfinityScrollableBackground_hpp
#define InfinityScrollableBackground_hpp

#include <cocos2d.h>
class InfinityScrollableBackground : public cocos2d::Node
{
public:
    double scrollSpeed;
    double distance;
public:
    InfinityScrollableBackground(std::string imageName);
    
    virtual void update(float delta);
private:
    std::vector<cocos2d::Node*> backgrounds;
    std::string imageName;
    double backgroundHeight;
    void prepareBackgrounds();
    void setupBackgroundSprite(cocos2d::Sprite* background);
    void repositionBackgroundNodes();
};
#endif /* InfinityScrollableBackground_hpp */
