//
//  PFMPlayer.hpp
//  PlaneFightMaker
//
//  Created by ocean on 2/10/16.
//
//

#ifndef PFMPlayer_hpp
#define PFMPlayer_hpp

#include <cocos2d.h>
class PFMPlayerPreset;
class PFMPlayer : public cocos2d::Node
{
public:
    PFMPlayer();
    void setPreset(PFMPlayerPreset* preset);
    void reload();
    cocos2d::Size getSize();
    float health;
private:
    PFMPlayerPreset* _preset;
    bool onContactBegin(cocos2d::PhysicsContact& contact);
};
#endif /* PFMPlayer_hpp */
