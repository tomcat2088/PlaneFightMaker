//
//  PFMBoomManager.cpp
//  PlaneFightMaker
//
//  Created by wangyang on 16/3/3.
//
//

#include "PFMBoomManager.hpp"

using namespace cocos2d;

PFMBoomManager* PFMBoomManager::shared()
{
    static PFMBoomManager* _shared = NULL;
    if(_shared == NULL)
    {
        _shared = new PFMBoomManager();
    }
    return _shared;
}

void PFMBoomManager::boomAt(std::string boomEffectName,cocos2d::Point position)
{
    LayerColor* layer = LayerColor::create(Color4B(60,20,20,255));
    rootNode->addChild(layer);
    layer->setContentSize(Size(20,20));
    layer->setPosition(position);
    layer->scheduleOnce([layer](float){
        layer->removeFromParent();
    }, 0.1, "DESTROY");
}