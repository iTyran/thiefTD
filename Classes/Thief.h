//
//  Thief.h
//  thiefTD
//
//  Created by cocos2d-x on 14-4-28.
//
//

#ifndef __thiefTD__Thief__
#define __thiefTD__Thief__

#include <iostream>
#include "EnemyBase.h"
#include "cocos2d.h"

USING_NS_CC;

class Thief : public EnemyBase
{
public:
    virtual bool init() override;
    
    static Thief* createThief(Vector<Node*> points);
    
    void changeDirection(float dt);
    void enemyExpload();
    
};

#endif /* defined(__thiefTD__Thief__) */
