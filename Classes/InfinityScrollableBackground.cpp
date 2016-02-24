//
//  InfinityScrollableBackground.cpp
//  PlaneFightMaker
//
//  Created by ocean on 2/9/16.
//
//
using namespace cocos2d;

#include "InfinityScrollableBackground.hpp"

InfinityScrollableBackground::InfinityScrollableBackground(std::string imageName):
imageName(imageName),
scrollSpeed(-200),
distance(0)
{
    prepareBackgrounds();
    scheduleUpdate();
}

void InfinityScrollableBackground::prepareBackgrounds()
{
    Image* img = new Image();
    img->initWithImageFile(imageName);
    
    double imgWidth = img->getWidth();
    double imgHeight = img->getHeight();
    double backgroundScale = Director::getInstance()->getVisibleSize().width / imgWidth;
    backgroundHeight = imgHeight * backgroundScale;
    for(int i=0;i<3;i++)
    {
        Sprite* background = Sprite::create(imageName);
        backgrounds.push_back(background);
        background->setScale(backgroundScale);
        background->setAnchorPoint(Vec2(0,0));
        addChild(background);
        background->setPositionY(backgroundHeight * (i - 1));
    }
}

void InfinityScrollableBackground::update(float deltaTime)
{
    distance += fabs(deltaTime * scrollSpeed);
    for(int i=0;i<backgrounds.size();i++)
    {
        Sprite* sprite = dynamic_cast<Sprite*>(backgrounds.at(i));
        double newPos = sprite->getPositionY() + deltaTime * scrollSpeed;
        sprite->setPositionY(newPos);
    }
    repositionBackgroundNodes();
}

void InfinityScrollableBackground::repositionBackgroundNodes()
{
    for(int i=0;i<backgrounds.size();i++)
    {
        Sprite* sprite = dynamic_cast<Sprite*>(backgrounds.at(i));
        double yPos = sprite->getPositionY();
        if(yPos <= - backgroundHeight && scrollSpeed < 0)
        {
            yPos = backgroundHeight * 2 + yPos + backgroundHeight;
        }
        if(yPos >= Director::getInstance()->getVisibleSize().height  && scrollSpeed > 0)
        {
            yPos = - backgroundHeight * 2 + yPos - backgroundHeight;
        }
        sprite->cocos2d::Node::setPositionY(yPos);
    }
}