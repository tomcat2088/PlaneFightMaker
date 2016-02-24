//
//  PFMScriptSetup.cpp
//  PlaneFightMaker
//
//  Created by ocean on 2/16/16.
//
//

#include "PFMScriptSetup.hpp"
#include "PFMScriptCore.hpp"
#include "PFMEnemy.hpp"
#include "GameSession.hpp"


PFMScriptSetup* PFMScriptSetup::shared()
{
    static PFMScriptSetup* _shared = NULL;
    if(_shared == NULL)
    {
        _shared = new PFMScriptSetup();
        PFMEnemy::registerToScript();
        GameSession::registerToScript();
    }
    return _shared;
}

void PFMScriptSetup::initGlobalValues()
{
    PFMScriptCore::shared()->lua.set("gameSession", GameSession::currentSession());
}