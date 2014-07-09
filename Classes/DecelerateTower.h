//
//  DecelerateTower.h
//  thiefTD
//
//  Created by cocos2d-x on 14-5-7.
//
//

#ifndef __thiefTD__DecelerateTower__
#define __thiefTD__DecelerateTower__

#include "TowerBase.h"


class DecelerateTower:public TowerBase
{
public:
    
    virtual bool init() ;
    CREATE_FUNC(DecelerateTower);
    
    void shoot(float dt);
    void removeBullet(Node* pSender);
    Sprite* DecelerateTowerBullet();
    
private:
    Sprite* rotateArrow;
    Sprite* tower;
    
};

#endif /* defined(__thiefTD__DecelerateTower__) */
