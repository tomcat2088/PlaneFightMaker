//
//  PFMComponentValueConverter.cpp
//  PlaneFightMaker
//
//  Created by ocean on 2/9/16.
//
//

#include "PFMComponentValueConverter.hpp"

int PFMComponentValueConverter::toInt(std::string value)
{
    return atoi(value.data());
}

double PFMComponentValueConverter::toDouble(std::string value)
{
    return atof(value.data());
}

cocos2d::Size PFMComponentValueConverter::toSize(std::string value)
{
    return cocos2d::Size(100,100);
}

cocos2d::Point PFMComponentValueConverter::toPoint(std::string value)
{
    return cocos2d::Point(100,100);
}