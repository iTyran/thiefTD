//
//  ArrowTower.h
//  thiefTD
//
//  Created by cocos2d-x on 14-4-28.
//
//

#ifndef __thiefTD__ArrowTower__
#define __thiefTD__ArrowTower__

#include "TowerBase.h"


class ArrowTower:public TowerBase
{
public:
    
    virtual bool init() ;
    CREATE_FUNC(ArrowTower);

    void rotateAndShoot(float dt);
    void shoot();
    void removeBullet(Node* pSender);
    Sprite* ArrowTowerBullet();
    
private:
    Sprite* rotateArrow;
    
};

#endif /* defined(__thiefTD__ArrowTower__) */
