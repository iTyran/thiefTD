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
    
    // 旋转后射击
    void rotateAndShoot(float dt);
    // 射击，射击后移除超出屏幕的子弹
    void shoot();
    // 移除超出屏幕的子弹
    void removeBullet(Node* pSender);
    
    // 箭塔的子弹
    Sprite* ArrowTowerBullet();
    
private:
    
    // 旋转的箭
    Sprite* rotateArrow;
    
};

#endif /* defined(__thiefTD__ArrowTower__) */
