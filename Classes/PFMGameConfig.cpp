//
//  PFMGameConfig.cpp
//  PlaneFightMaker
//
//  Created by wangyang on 16/3/4.
//
//

#include "PFMGameConfig.hpp"
#include <cocos2d.h>
#include "json.hpp"

using namespace cocos2d;
using namespace nlohmann;

PFMGameConfig* PFMGameConfig::shared()
{
    static PFMGameConfig* _shared = NULL;
    if(_shared == NULL)
    {
        _shared = new PFMGameConfig();
    }
    return _shared;
}

PFMGameConfig::PFMGameConfig()
{
    std::string defaultConfigFileName = "game.config";
    if(FileUtils::getInstance()->isFileExist(defaultConfigFileName) == false)
    {
        cocos2d::log("default game config is not exist.check the game.config file");
        return;
    }
    
    //load game config
    std::string configContent = FileUtils::getInstance()->getStringFromFile(defaultConfigFileName);
    auto jsonObj = json::parse(configContent);
    width = jsonObj["width"].get<double>();
    height = jsonObj["height"].get<double>();
}