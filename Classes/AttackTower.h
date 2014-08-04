//
//  AttackTower.h
//  thiefTD
//
//  Created by cocos2d-x on 14-5-7.
//
//

#ifndef __thiefTD__AttackTowerTower__
#define __thiefTD__AttackTowerTower__

#include "TowerBase.h"

class AttackTower:public TowerBase
{
public:
    
    virtual bool init() ;
    CREATE_FUNC(AttackTower);

    void shoot(float dt);
    void removeBullet(Node* pSender);
    Sprite* AttackTowerBullet();
    
private:
    Sprite* tower;
    
};

#endif /* defined(__thiefTD__AttackTower__) */
