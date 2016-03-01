//
//  PFMComponentManager.cpp
//  PlaneFightMaker
//
//  Created by ocean on 2/9/16.
//
//

#include "PFMPresetManager.hpp"
#include <json/rapidjson.h>
#include <json/document.h>
#include <json/stringbuffer.h>

#include "PFMPreset.hpp"
#include "PFMEnemyPreset.hpp"
#include "PFMPlayerPreset.hpp"

using namespace cocos2d;

PFMPresetManager* PFMPresetManager::shared()
{
    static PFMPresetManager* _shared = NULL;
    if(_shared == NULL)
    {
        _shared = new PFMPresetManager();
    }
    return _shared;
}

PFMPreset* PFMPresetManager::presetWithName(std::string name)
{
    if(name.find_first_of("enemy") != std::string::npos)
    {
        PFMEnemyPreset* preset = new PFMEnemyPreset("presets/" + name + ".json");
        return preset;
    }
    return NULL;
}
