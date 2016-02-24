//
//  PFMPlayer.cpp
//  PlaneFightMaker
//
//  Created by ocean on 2/10/16.
//
//

#include "PFMPlayer.hpp"
#include "PFMComponent.hpp"
#include "PFMPlayerPreset.hpp"
#include "PFMSpriteComponent.hpp"
#include "PFMSprite.hpp"
#include "PFMBulletGun.hpp"
#include "PFMBulletGunComponent.hpp"
#include <cocos2d.h>

using namespace cocos2d;
PFMPlayer::PFMPlayer()
{

}

void PFMPlayer::setPreset(PFMPlayerPreset* preset)
{
    _preset = preset;
    reload();
}

void PFMPlayer::reload()
{
    if(_preset == NULL)
        return;
    for(int i=0;i<_preset->components.size();i++)
    {
        PFMComponent* component = _preset->components[i];
        if(component->componentClass == "Sprite")
        {
            PFMSpriteComponent* spriteComponent = dynamic_cast<PFMSpriteComponent*>(component);
            addChild(PFMSprite::createWithComponent(spriteComponent));
        }
        else if(component->componentClass == "BulletGun")
        {
            PFMBulletGunComponent* bulletGunComponent = dynamic_cast<PFMBulletGunComponent*>(component);
            addChild(PFMBulletGun::createWithComponent(bulletGunComponent));
        }
//        else if([component isMemberOfClass:[AstMissleLauncherComponent class]])
//        {
//            AstMissleLauncher* missleLauncher = [[AstMissleLauncher alloc]initWithSession:self.session];
//            [self addNode:missleLauncher.rootNode];
//            [missleLauncher setComponent:(AstMissleLauncherComponent*)component];
//        }
    }
}