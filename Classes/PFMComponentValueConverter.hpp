//
//  PFMComponentValueConverter.hpp
//  PlaneFightMaker
//
//  Created by ocean on 2/9/16.
//
//

#ifndef PFMComponentValueConverter_hpp
#define PFMComponentValueConverter_hpp

#include <cocos2d.h>
class PFMComponentValueConverter
{
public:
    static int toInt(std::string value);
    static double toDouble(std::string value);
    static cocos2d::Size toSize(std::string value);
    static cocos2d::Point toPoint(std::string value);
};
#endif /* PFMComponentValueConverter_hpp */
