//
//  GameSession.hpp
//  PlaneFightMaker
//
//  Created by ocean on 2/10/16.
//
//

#ifndef GameSession_hpp
#define GameSession_hpp

#include <cocos2d.h>
#include "PFMScriptCoreTypes.hpp"

class PFMPlayer;
class PFMLevelMap;
class InfinityScrollableBackground;
class GameSession : public cocos2d::Ref
{
public:
    static GameSession* currentSession();
    static GameSession* newSession();
    
    GameSession();
public:
    PFMPlayer* player;
    PFMLevelMap* levelMap;
    cocos2d::Layer* rootNode;
    void startInLayer(cocos2d::Layer* scene);
    void update(float delta);
    
    //for script
    float script_getStageSizeWidth();
    float script_getStageSizeHeight();
    
    static void registerToScript();

private:
    static GameSession* _currentSession;
    double _gameSpeed;
    double _loadedPositionBoundY;
    InfinityScrollableBackground* _background;
    int _currentMapLoadSegmentIndex;

    void tryLoadNewMapUnits();
    void loadMapUnits(int segmentIndex);
};
#endif /* GameSession_hpp */
