//
//  PFMCollideMaskBits.h
//  PlaneFightMaker
//
//  Created by wangyang on 16/2/29.
//
//

#ifndef PFMCollideMaskBits_h
#define PFMCollideMaskBits_h

typedef enum {
    PFMCollideMaskBitsDeactive = 1 << 0,
    PFMCollideMaskBitsPlayer = 1 << 1,
    PFMCollideMaskBitsPlayerBullet = 1 << 2,
    PFMCollideMaskBitsEnemy = 1 << 3,
    PFMCollideMaskBitsEnemyBullet = 1 << 4
}PFMCollideMaskBits;

typedef enum {
    PFMPhysicsBodyTypeEnemyBullet,
    PFMPhysicsBodyTypePlayerBullet,
    PFMPhysicsBodyTypePlayer,
    PFMPhysicsBodyTypeEnemy
}PFMPhysicsBodyType;


#endif /* PFMCollideMaskBits_h */
