//
//  PFMScript.cpp
//  PlaneFightMaker
//
//  Created by ocean on 2/16/16.
//
//

#include "PFMScriptCore.hpp"
#include "PFMScriptCoreTypes.hpp"

PFMScriptCore* PFMScriptCore::shared()
{
    static PFMScriptCore* _shared = NULL;
    if(_shared == NULL)
    {
        _shared = new PFMScriptCore();
    }
    return _shared;
}

PFMScriptCore::PFMScriptCore()
{
    lua.open_libraries(sol::lib::base);
    lua.set_function("print", [](std::string msg){
        printf(msg.data());
    });
    //register default types
    lua.new_userdata<PFMScriptTypeSize>("Size", "width", &PFMScriptTypeSize::width, "height", &PFMScriptTypeSize::height);
    lua.new_userdata<PFMScriptTypePoint>("Point", "x", &PFMScriptTypePoint::x, "y", &PFMScriptTypePoint::y);
}